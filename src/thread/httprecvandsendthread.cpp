/**
*    @file       httprecvandsendthread.cpp
*
*    @brief      
*    @details    
*
*    @version    1.0
*    @date       2015/4/25
*
*    @author     zhangjiaxing, zhangjiaxing@baofeng.com
*/
#include "httprecvandsendthread.h"
#include "httpprocesstask.h"
#include "mxrmessage.h"

CHttpRecvAndSendThread::CHttpRecvAndSendThread(int nEntityType, int nEntityId)
	: CNetProcessThread(nEntityType, nEntityId)
{
}

CHttpRecvAndSendThread::~CHttpRecvAndSendThread()
{
}

int CHttpRecvAndSendThread::Process(CMsg* pMsg)
{
	TMsg* pTMsg = pMsg->GetTMsg();
	if (!pTMsg)
	{
		return 0;
	}

	if (pTMsg->srcEntityType == LISTENENTITY)
	{
		if (pTMsg->msgType == RECVMSGTYPE)
		{
			CRecvMsgBody* pBody = (CRecvMsgBody*)pMsg->GetMsgBody();
			CTcpSocket* pSocket = new CTcpSocket(pBody->GetSockAddr(), sizeof(sockaddr_in), pBody->GetSocket());
			CSocketTask* pTmpSocketTask = NULL;
			pTmpSocketTask = CMyserver::GetInstance()->GetClassFactory()->GenSocketTask(this, pSocket, TASKTYPE_HTTP_CONNECT);
			if (pTmpSocketTask != NULL)
			{
				pTmpSocketTask->Init();
				pTmpSocketTask->SetTimeStat(pBody->GetTimeStat());
			}
			else
			{
				WriteRunInfo::WriteError ("CHttpRecvAndSendThread::Process : Http thread generate RECVANDSENDTASK fail.");
			}
		}
		else
		{
			WriteRunInfo::WriteError ("CHttpRecvAndSendThread::Process : Http thread invalid msgtype %d", pTMsg->msgType);
		}
	}
	else
	{
		CNetProcessThread::Process(pMsg);
	}
	return 0;
	
}






