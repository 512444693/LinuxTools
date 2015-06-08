/**
 *    @file       myrecvandsendthread.cpp
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "myrecvandsendthread.h"
#include "mxrmessagedef.h"
#include "myrecvandsendtask.h"
#include "threadmsgbody.h"

CMyRecvAndSendThread::CMyRecvAndSendThread(int iEntityType, int iEntityId)
	: CNetProcessThread(iEntityType, iEntityId)
{

}

CMyRecvAndSendThread::~CMyRecvAndSendThread()
{

}

int CMyRecvAndSendThread::Process(CMsg *pMsg)
{
	TMsg* pTMsg = pMsg->GetTMsg();
	if (!pTMsg)
	{
		return 0;
	}

	if (pTMsg->srcEntityType == ENTITYTYPE_LISTENS)
	{
		if (pTMsg->msgType == MSGTYPE_SHORT_CONNECT)
		{
			CRecvMsgBody* pBody = (CRecvMsgBody*)pMsg->GetMsgBody();
			CTcpSocket* pSocket = new CTcpSocket(pBody->GetSockAddr(), sizeof(sockaddr_in), pBody->GetSocket());
			CSocketTask* pSocketTask = NULL;
			pSocketTask = CMyserver::GetInstance()->GetClassFactory()->GenSocketTask(this, pSocket, TASKTYPE_SHORT_CONNECT);
			if (pSocketTask != NULL)
			{
				pSocketTask->Init();
				pSocketTask->SetTimeStat(pBody->GetTimeStat());
			}
			else
			{
				WriteRunInfo::WriteError ("CMyRecvAndSendThread thread generate TASKTYPE_SHORT_CONNECT fail!!");
			}
		}
		else if (pTMsg->msgType == MSGTYPE_HTTP_CONNECT)
		{
			CRecvMsgBody* pBody = (CRecvMsgBody*)pMsg->GetMsgBody();
			CTcpSocket* pSocket = new CTcpSocket(pBody->GetSockAddr(), sizeof(sockaddr_in), pBody->GetSocket());
			CSocketTask* pSocketTask = NULL;
			pSocketTask = CMyserver::GetInstance()->GetClassFactory()->GenSocketTask(this, pSocket, TASKTYPE_HTTP_CONNECT);
			if (pSocketTask != NULL)
			{
				pSocketTask->Init();
				pSocketTask->SetTimeStat(pBody->GetTimeStat());
			}
			else
			{
				WriteRunInfo::WriteError ("CMyRecvAndSendThread thread generate TASKTYPE_HTTP_CONNECT fail!!");
			}
		}
	}
	else if (pTMsg->srcEntityType == ENTITYTYPE_SESSION_PROCESS)
	{
		if (pTMsg->msgType == MSGTYPE_CMD_RES)
		{
			CSessionMsgBody *pMsgBody = (CSessionMsgBody *)pMsg->GetMsgBody();
			CMyRecvAndSendTask* pSocketTask = (CMyRecvAndSendTask*)FindSocketTask(pTMsg->taskId);
			if (pSocketTask != NULL)
			{
				pSocketTask->PutMsgToSendList(pMsgBody->GetBuf(), pMsgBody->Size());
			}
			else
			{
				WRITE_ALL_LOG(DEBUG_LOG_TYPE, "can not found task:%lu",pTMsg->taskId);
			}
		}
		else
		{
			WRITE_ALL_LOG(DEBUG_LOG_TYPE, "invalid msg type:%d", pTMsg->msgType);
		}
	}
	else
	{
		CNetProcessThread::Process(pMsg);
	}

	return 0;
}

