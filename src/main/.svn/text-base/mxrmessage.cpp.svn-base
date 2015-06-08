/**
 *    @file       mxrmessage.cpp
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "mxrmessage.h"
#include "mxrmessagedef.h"
#include "myclassfactory.h"

CMxrMessage::CMxrMessage() : CMyserver()
{
	m_pTimerThreadGrp = NULL;
	m_pListenThreadGrp = NULL;
	m_pMaintainUpdThread = NULL;
	m_pUdpRecvThreadGrp = NULL;
	m_pUdpProcessThreadGrp= NULL;
	m_pShortConListenThreadGrp = NULL;
	m_pRecvAndSendThreadGrp = NULL;
	m_pOnTimeThreadGrp = NULL;
}

CMxrMessage::~CMxrMessage()
{

}

int CMxrMessage::InitServer()
{
	int nRet = CMyserver::InitServer();
	if(nRet != 0)
	{
		return -1;
	}

	nRet = m_conf.Init();
	if(nRet != 0)
	{
		WriteRunInfo::WriteLog("Load conf fail ...");
		return -1;
	}

	m_pClassFactory = new CMyClassFactory;
	if (NULL == m_pClassFactory)
	{
		return -1;
	}

	return 0;
}

int CMxrMessage::StartServer()
{
	int nRet = 0;
	WriteRunInfo::WriteLog("==========================Begin start server====================================");
	//start timer thread
	m_pTimerThreadGrp = new CThreadGroup(1, TIMERENTITY);
	nRet = m_pTimerThreadGrp->Init();
	if ( nRet != 0 )
	{
		WriteRunInfo::WriteLog("Init timer thread fail");
		return -1;
	}
	WriteRunInfo::WriteLog("Init timer thread succeed");

	//Start Listen Thread
	CNewBufMgr bufAddrs;
	bufAddrs.SetIfNetTrans(0);
	bufAddrs.PutInt(LISTEN_TASK_NUM);
	bufAddrs.PutString(m_conf.GetConf().m_ShortListenAddr.m_strHost);
	bufAddrs.PutShort(m_conf.GetConf().m_ShortListenAddr.m_nPort);
	bufAddrs.PutInt(m_conf.GetConf().m_ShortListenAddr.m_nTaskType);
	bufAddrs.PutString(m_conf.GetConf().m_HttpListenAddr.m_strHost);
	bufAddrs.PutShort(m_conf.GetConf().m_HttpListenAddr.m_nPort);
	bufAddrs.PutInt(m_conf.GetConf().m_HttpListenAddr.m_nTaskType);
	
	m_pListenThreadGrp = new CThreadGroup(1, ENTITYTYPE_LISTENS, bufAddrs.GetBuf());
	nRet = m_pListenThreadGrp->Init();
	if (0 != nRet)
	{
		WriteRunInfo::WriteError ("Init listens thread fail");
		return -1;
	}
	WriteRunInfo::WriteLog("Init listen thread succeed");

	//start short connect listen Thread
	/*int nPort = m_baseConf.GetConfigItem().nTcpPort;
	string strHost = m_baseConf.GetConfigItem().sServerAddr;
	string strTmpData = string((char*)(&nPort), 4);
	strTmpData.append(strHost);
	m_pShortConListenThreadGrp = new CThreadGroup(1, LISTENENTITY, strTmpData);
	nRet = m_pShortConListenThreadGrp->Init();
	if (nRet != 0)
	{
		WriteRunInfo::WriteError("Init short connect listen thread fail");
		return -1;
	}
	WriteRunInfo::WriteLog("Init short connect listen thread succeed");*/

	int nSessionProcessThreadNum = m_conf.GetConf().m_nSessionProcessThreadNum;
	m_pSessionProcessThreadGrp = new CThreadGroup(nSessionProcessThreadNum, ENTITYTYPE_SESSION_PROCESS);
	nRet = m_pSessionProcessThreadGrp->Init();
	if (nRet != 0)
	{
		WriteRunInfo::WriteError("Init session process thread fail");
		return -1;
	}
	WriteRunInfo::WriteLog("Init session process thread succeed");

	//start recv and send Thread
	int nTcpThreadNum = m_conf.GetConf().m_nRecvAndSendThreadNum;
	m_pRecvAndSendThreadGrp = new CThreadGroup(nTcpThreadNum, RECVANDSENDMSGENTITY);
	nRet = m_pRecvAndSendThreadGrp->Init();
	if (nRet!= 0)
	{
		WriteRunInfo::WriteError("Init recv and send thread fail");
		return -1;
	}
	WriteRunInfo::WriteLog ("Init recv and send thread succeed");

	//Start Maintain UDP Thread
	m_pMaintainUpdThread = new CMaintainUdpThread(m_baseConf.GetConfigItem().sMaintainIp, m_baseConf.GetConfigItem().nMaintainPort);
	nRet = m_pMaintainUpdThread->Start();
	if (nRet != 0)
	{
		WriteRunInfo::WriteLog("Init MAINTAINUDPENTITY fail!");
		return -1;
	}
	WriteRunInfo::WriteLog("Start MAINTAINUDPENTITY succeed!");

	//Start Udp Send and Process thread;
	int nUdpProcessThreadNum = m_conf.GetConf().m_nUdpProcessThreadNum;
	m_pUdpProcessThreadGrp = new CThreadGroup(nUdpProcessThreadNum, ENTITYTYPE_UDPPROCESS);
	nRet = m_pUdpProcessThreadGrp->Init();
	if(nRet != 0)
	{
		WriteRunInfo::WriteError("Init UDPPROCESSENTITY Failed!");
		return -1;
	}
	WriteRunInfo::WriteLog("Start UDPPROCESSENTITY succeed!");

	//Start Udp Recv Thread
	CUdpCommonSock* pUdpCommonSocket = new CUdpCommonSock(m_baseConf.GetConfigItem().sServerAddr, m_baseConf.GetConfigItem().nUdpPort, false, true);
	if (pUdpCommonSocket->CreateUdpSocket() < 0)
	{
		WriteRunInfo::WriteError("Create Udp Recv socket Failed!");
		return -1;
	}
	int nSockBufLen = 10 * 1024 * 1024;
	nRet = setsockopt(pUdpCommonSocket->GetSocket(), SOL_SOCKET, SO_SNDBUF, &nSockBufLen, sizeof(nSockBufLen));
	if (nRet != 0)
	{
		WriteRunInfo::WriteError("setsockopt SO_SNDBUF fail: errno %d", errno);
		return -1;
	}
	nRet = setsockopt(pUdpCommonSocket->GetSocket(), SOL_SOCKET, SO_RCVBUF, &nSockBufLen, sizeof(nSockBufLen));
	if (nRet != 0)
	{
		WriteRunInfo::WriteError("setsockopt SO_RCVBUF fail: errno %d", errno);
		return -1;
	}
	int nRecvThreadNum = m_conf.GetConf().m_nUdpRecvThreadNum;
	m_pUdpRecvThreadGrp = new CThreadGroup(nRecvThreadNum, UDPRECVENTITY, "", pUdpCommonSocket);
	nRet = m_pUdpRecvThreadGrp->Init();
	if(nRet != 0)
	{
		WriteRunInfo::WriteError("Init UDPRECVENTITY Failed!");
		return -1;
	}
	WriteRunInfo::WriteLog("Start udp recv thread succeed!");

	//start on time thread
	m_pOnTimeThreadGrp = new CThreadGroup(1, ENTITYTYPE_ONTIME);
	nRet = m_pOnTimeThreadGrp->Init();
	if (nRet != 0)
	{
		WriteRunInfo::WriteError("Init ONTIMETHREAD Failed!");
		return -1;
	}
	WriteRunInfo::WriteLog ("Init ontime thread succeed");

	WriteRunInfo::WriteLog("server start succeed ...");

	return  0;
}



