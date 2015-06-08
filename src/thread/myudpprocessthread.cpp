/**
 *    @file       myudpprocessthread.cpp
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
#include "myudpprocessthread.h"
#include "threadmsgbody.h"
#include "utils.h"

CMyUdpProcessThread::CMyUdpProcessThread(int nEntityType, int nEntityId, string& strIp, unsigned short nPort)
	: CUdpSendThread(nEntityType, nEntityId, strIp, nPort)
{
}

CMyUdpProcessThread::~CMyUdpProcessThread()
{
}

int CMyUdpProcessThread::Init()
{
	int nRet = CUdpSendThread::Init();
	if (nRet != 0)
	{
		return -1;
	}
	int nSockBufLen = 100 * 1024;
	nRet = setsockopt(m_UdpSocket.GetSocket(), SOL_SOCKET, SO_SNDBUF, &nSockBufLen, sizeof(nSockBufLen));
	if (nRet != 0)
	{
		WriteRunInfo::WriteError("setsockopt SO_SNDBUF fail: errno %d", errno);
		return -1;
	}
	nRet = setsockopt(m_UdpSocket.GetSocket(), SOL_SOCKET, SO_RCVBUF, &nSockBufLen, sizeof(nSockBufLen));
	if (nRet != 0)
	{
		WriteRunInfo::WriteError("setsockopt SO_RCVBUF fail: errno %d", errno);
		return -1;
	}
	return 0;
}

int CMyUdpProcessThread::Run()
{
	while (m_nRunFlag)
	{
		CMsg *pMsg = m_InputList.get();
		if (pMsg != NULL)
		{
			Process(pMsg);
			delete pMsg;
		}
	}

	return 0;
}

int CMyUdpProcessThread::Process(CMsg *pMsg)
{
	int nRet = 0;
	TMsg *pTMsg = pMsg->GetTMsg();
	if (pTMsg->srcEntityType == UDPRECVENTITY)
	{
		if (pTMsg->msgType == UDPCLIENTMSG)
		{
			nRet = ProcessClientMsg(pMsg);
		}
	}
	else if (pTMsg->srcEntityType == ENTITYTYPE_SESSION_PROCESS)
	{
		if (pTMsg->msgType == MSGTYPE_CMD_RES)
		{
			ProcessCmdResMsg(pMsg);
		}
	}
	else
	{
		WriteRunInfo::WriteError("invalid msg type %u", pTMsg->msgType);
	}

	return nRet;
}

int CMyUdpProcessThread::ProcessClientMsg(CMsg *pMsg)
{
	CUdpCommonBufMsgBody *pMsgBody = (CUdpCommonBufMsgBody *)pMsg->GetMsgBody();
	if (pMsgBody == NULL)
	{
		return -1;
	}

	string strIp, strSessionId;
	TUserInfo tUserInfo;
	tUserInfo.m_nEntityType = m_nEntityType;
	tUserInfo.m_nEntityId = m_nEntityId;
	tUserInfo.m_nTaskId = 0;
	tUserInfo.m_nFarIp = pMsgBody->GetClientIp();
	tUserInfo.m_nFarPort = pMsgBody->GetCientPort();
	tUserInfo.GenUid();
	tUserInfo.m_nLastReportTime = CMyserver::GetInstance()->GetTimeVal().tv_sec;

	int nThreadId = -1;
	CMxrMessage* pServer = (CMxrMessage*)CMyserver::GetInstance();
	int nSessionProcessThreadNum = pServer->GetConf().GetConf().m_nSessionProcessThreadNum;
	strSessionId = Utils::GetSessionId(pMsgBody->GetBuf(), pMsgBody->Size());
	if (strSessionId != "")
	{
		nThreadId = CToolKit::shortELFhash(strSessionId.c_str(), strSessionId.length()) % nSessionProcessThreadNum;
	}
	strIp = Utils::IPInt2Str(ntohl(pMsgBody->GetClientIp()));
	WRITE_ALL_LOG(DEBUG_LOG_TYPE, "udp recv msg from %s: %d", strIp.c_str(), pMsgBody->GetCientPort());

	char *pBuf = new char[pMsgBody->Size()];
	memcpy(pBuf, pMsgBody->GetBuf(), pMsgBody->Size());
	CSessionMsgBody *pBody = new CSessionMsgBody(tUserInfo, pBuf, pMsgBody->Size());
	SendMsg(ENTITYTYPE_SESSION_PROCESS, nThreadId, 0, MSGTYPE_CMD, pBody);

	return 0;
}

int CMyUdpProcessThread::ProcessCmdResMsg(CMsg *pMsg)
{
	int nRet = 0;
	CSessionMsgBody *pMsgBody = (CSessionMsgBody *)pMsg->GetMsgBody();
	int nIp = pMsgBody->m_tUserInfo.m_nFarIp;
	short nPort = pMsgBody->m_tUserInfo.m_nFarPort;
	nRet = m_UdpSocket.UdpSend(pMsgBody->GetBuf(), pMsgBody->Size(), nIp, nPort);

	return 0;
}

