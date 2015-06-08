/**
 *    @file       myrecvandsendtask.cpp
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "myrecvandsendtask.h"
#include "mybasecmd.h"
#include "mxrmessagedef.h"
#include "mxrmessage.h"
#include "getcmd.h"
#include "threadmsgbody.h"

CMyRecvAndSendTask::CMyRecvAndSendTask(CTcpSocket *pSocket, CNetProcessThread *pWorkThread)
	: CRecvAndSendTask(pSocket, pWorkThread, 0)
{
	m_state = ReadPacketHead;
	m_nReceiveSize = 0;
	m_nReceiveLeft = TCmdHead::HEAD_LEN;
	m_recvBuff = new char[RECV_BUF_LEN];
}

CMyRecvAndSendTask::~CMyRecvAndSendTask()
{
	delete [] m_recvBuff;
}

int CMyRecvAndSendTask::Init()
{
	AddToEpoll();
	return 0;
}

int CMyRecvAndSendTask::DestroySelf()
{
	delete this;
	return 0;
}

int CMyRecvAndSendTask::AddToEpoll()
{
	int tmpEvent = MYPOLLERR|MYPOLLHUP|MYPOLLIN;
	if (m_sendList.GetNum() != 0 || m_pCurSendMsg != NULL)
	{
		tmpEvent = tmpEvent|MYPOLLOUT;
	}

	CNetProcessThread *pNetThread = (CNetProcessThread*)m_pThread;
	CEpoll *pEoll = pNetThread->GetEpoll();
	pEoll->AddToEpoll(this, tmpEvent);
	return 0;
}

int CMyRecvAndSendTask::PutMsgToSendList(const char *pBuf, int nLen)
{
	if (pBuf == NULL || nLen == 0)
	{
		return -1;
	}
	char *pTmpBuf = new char[nLen];
	memcpy(pTmpBuf, pBuf, nLen);
	CSendMsg *pSendMsg = new CSendMsg(nLen, pTmpBuf);

	m_sendList.push_back(pSendMsg);
	int tmpEvent = MYPOLLERR|MYPOLLHUP|MYPOLLIN|MYPOLLOUT;
	CNetProcessThread *pNetThread = (CNetProcessThread*)m_pThread;
	CEpoll *pEoll = pNetThread->GetEpoll();
	pEoll->ModifyFromEpoll(this, tmpEvent);
	return 0;
}

int CMyRecvAndSendTask::RecvProcess()
{
	int iReced;
	iReced = recv(GetSocket(), m_recvBuff + m_nReceiveSize, m_nReceiveLeft, MSG_DONTWAIT);

	if (0 == iReced)
	{
		WriteRunInfo::WriteTrace("CMyRecvAndSendTask::RecvProcess : recv client close , close the socket");
		return -1;
	}

	if (iReced < 0)
	{
		if (errno != EINTR && errno != EAGAIN)
		{
			WriteRunInfo::WriteLog("CMyRecvAndSendTask::RecvProcess : recv client error(%d) , close the socket", errno);
			return -1;
		}
		return 0;
	}

	m_nReceiveSize += iReced;
	m_nReceiveLeft -= iReced;

	switch(m_state)
	{
	case ReadPacketHead:
		{
			if(m_nReceiveSize >= TCmdHead::HEAD_LEN)
			{
				m_state = ReadPacket;
				int nBodyLen;
				memcpy(&nBodyLen, m_recvBuff + TCmdHead::BODYLEN_OFFSET, sizeof(nBodyLen));
				nBodyLen = ntohl(nBodyLen);
				if (nBodyLen + TCmdHead::CMDID_OFFSET > RECV_BUF_LEN)
				{
					WriteRunInfo::WriteError("CMyRecvAndSendTask::RecvProcess : command body is too long");
					return -1;
				}
				m_nReceiveLeft = nBodyLen + TCmdHead::CMDID_OFFSET - m_nReceiveSize;
				if (m_nReceiveLeft <= 0)
				{
					int nRet = ProcessPacket();
					if (-1 == nRet)
					{
						WriteRunInfo::WriteError("CMyRecvAndSendTask::RecvProcess : recv invalid packet from client!!");
						return -1;
					}
					m_state = ReadPacketHead;
					m_nReceiveSize = 0;
					m_nReceiveLeft = TCmdHead::HEAD_LEN;
				}

			}
			break;
		}
	case ReadPacket:
		{
			if( m_nReceiveLeft <= 0)
			{
				int nRet = ProcessPacket();
				if (-1 == nRet)
				{
					WriteRunInfo::WriteError("CMyRecvAndSendTask::RecvProcess : recv invalid packet from client!!");
					return -1;
				}
				m_state = ReadPacketHead;
				m_nReceiveSize = 0;
				m_nReceiveLeft = TCmdHead::HEAD_LEN;
			}
			break;
		}
	default:
		{
			WriteRunInfo::WriteError("CMyRecvAndSendTask::RecvProcess : wrong state!!");
			return -1;
			break;
		}
	}

	return 0;
}

int CMyRecvAndSendTask::SendProcess()
{
	int retValue = 0;
	if (m_pCurSendMsg != NULL)
	{
		retValue = SendData();
	}
	else
	{
		m_pCurSendMsg = GetMsgFromSendList();
		if (m_pCurSendMsg != NULL)
		{
			retValue = SendData();
		}
		else
		{
			int tmpEvent = MYPOLLERR|MYPOLLHUP|MYPOLLIN;
			CNetProcessThread *pNetThread = (CNetProcessThread*)m_pThread;
			CEpoll *pEoll = pNetThread->GetEpoll();
			pEoll->ModifyFromEpoll(this, tmpEvent);
			retValue = 1;
		}
	}
	/*if(1 == retValue)
	{
		DestroySelf();
	}*/
	return retValue;
}

int CMyRecvAndSendTask::ProcessPacket()
{
	string strIp, strSessionId;
	TUserInfo tUserInfo;
	tUserInfo.m_nEntityType = m_pThread->GetEntityType();
	tUserInfo.m_nEntityId = m_pThread->GetEntityId();
	tUserInfo.m_nTaskId = GetTaskId();
	tUserInfo.m_nFarIp = ntohl(m_pTcpSocket->GetAddr().sin_addr.s_addr);
	tUserInfo.m_nFarPort = ntohs(m_pTcpSocket->GetAddr().sin_port);
	tUserInfo.GenUid();
	tUserInfo.m_nLastReportTime = CMyserver::GetInstance()->GetTimeVal().tv_sec;

	int nThreadId = -1;
	CMxrMessage* pServer = (CMxrMessage*)CMyserver::GetInstance();
	int nSessionProcessThreadNum = pServer->GetConf().GetConf().m_nSessionProcessThreadNum;
	strSessionId = Utils::GetSessionId(m_recvBuff, m_nReceiveSize);
	if (strSessionId != "")
	{
		nThreadId = CToolKit::shortELFhash(strSessionId.c_str(), strSessionId.length()) % nSessionProcessThreadNum;
	}
	strIp = Utils::IPInt2Str(ntohl(tUserInfo.m_nFarIp));
	WRITE_ALL_LOG(DEBUG_LOG_TYPE, "tcp recv msg from %s: %d", strIp.c_str(), tUserInfo.m_nFarPort);
	char *pBuf = new char[m_nReceiveSize];
	memcpy(pBuf, m_recvBuff, m_nReceiveSize);
	CSessionMsgBody *pMsgBody = new CSessionMsgBody(tUserInfo, pBuf, m_nReceiveSize);
	m_pThread->SendMsg(ENTITYTYPE_SESSION_PROCESS, nThreadId, 0, MSGTYPE_CMD, pMsgBody, GetTaskId());

	return 0;
}



