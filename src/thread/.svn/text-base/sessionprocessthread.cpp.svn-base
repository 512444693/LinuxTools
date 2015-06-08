/**
 *    @file       sessionprocessthread.cpp
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2015/3/15
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "sessionprocessthread.h"
#include "mxrmessage.h"
#include "mxrmessagedef.h"
#include "pingcmd.h"
#include "noticecmd.h"
#include "anchorcmd.h"
#include "getcmd.h"
#include "getlistcmd.h"
#include "threadmsgbody.h"

CSessionProcessThread::CSessionProcessThread(int nEntityType, int nEntityId)
	:CSynWorkThread(nEntityType, nEntityId)
{
	m_sessions = new CSessionHashTable(((CMxrMessage*)CMyserver::GetInstance())->GetConf().GetConf().m_nSessionBucketLen, false);
}

CSessionProcessThread::~CSessionProcessThread()
{
	if (m_sessions != NULL)
	{
		delete m_sessions;
	}
}

int CSessionProcessThread::Process(CMsg *pMsg)
{
	TMsg* pTMsg = pMsg->GetTMsg();

	if (pTMsg->msgType == MSGTYPE_CMD)
	{
		ProcessSessionMsg(pMsg);
	}
	else if (pTMsg->msgType == MSGTYPE_CHECK_SESSION)
	{
		ProcessCheckSessionMsg(pMsg);
	}
	else
	{
		WriteRunInfo::WriteError("recv invalid msg type:%d", pTMsg->msgType);
	}
	
	return 0;
}

int CSessionProcessThread::ProcessSessionMsg(CMsg *pMsg)
{
	int nRet = 0;
	TMsg* pTMsg = pMsg->GetTMsg();
	CSessionMsgBody *pMsgBody = (CSessionMsgBody*)pMsg->GetMsgBody();
	int nCmdId = TCmdHead::GetCmdId(pMsgBody->GetBuf(), pMsgBody->Size());

	switch(nCmdId)
	{
	case CMDID_GET:
		{
			CGetCmd reqCmd(pMsgBody->GetBuf(), pMsgBody->Size());
			nRet = reqCmd.Process();
			if(nRet == -1)
			{
				reqCmd.DetachBuf();
				return -1;
			}

			CMxrMessage* pServer = (CMxrMessage*)CMyserver::GetInstance();
			TMxrMessageConf tServerConf = pServer->GetConf().GetConf();
			string strSession = reqCmd.GetCmdBody().m_strSession;
			WRITE_ALL_LOG(DEBUG_LOG_TYPE, "recv get server session:%s from user:", strSession.c_str());
			unsigned int nHashNum = CToolKit::shortELFhash(strSession.c_str(), strSession.length());
			int nIndex = nHashNum % tServerConf.m_nSessionMsgNum;
			int nIp = tServerConf.m_vecIpInfo[nIndex].m_nIp;
			short nPort = tServerConf.m_nSessionMsgPort;

			CGetCmdRes resCmd(reqCmd, nIp, nPort);
			resCmd.Process();
			CSessionMsgBody *pResBody = new CSessionMsgBody(pMsgBody->GetInfo(), resCmd.GetBuf(), resCmd.GetBufLen());
			SendMsg(pTMsg->srcEntityType, pTMsg->srcEntityId, pTMsg->srcTaskId, MSGTYPE_CMD_RES, pResBody);
			reqCmd.DetachBuf();
			resCmd.DetachBuf();
		}
		break;
	case CMDID_GETLIST:
		{
			CGetListCmd reqCmd(pMsgBody->GetBuf(), pMsgBody->Size());
			nRet = reqCmd.Process();
			if(nRet == -1)
			{
				reqCmd.DetachBuf();
				return -1;
			}

			CMxrMessage* pServer = (CMxrMessage*)CMyserver::GetInstance();
			TMxrMessageConf tServerConf = pServer->GetConf().GetConf();

			CGetListCmdRes resCmd(reqCmd, tServerConf.m_vecIpInfo);
			resCmd.Process();
			CSessionMsgBody *pResBody = new CSessionMsgBody(pMsgBody->GetInfo(), resCmd.GetBuf(), resCmd.GetBufLen());
			SendMsg(pTMsg->srcEntityType, pTMsg->srcEntityId, pTMsg->srcTaskId, MSGTYPE_CMD_RES, pResBody);
			reqCmd.DetachBuf();
			resCmd.DetachBuf();
		}
		break;
	case CMDID_PING:
		{
			CPingCmd reqCmd(pMsgBody->GetBuf(), pMsgBody->Size());
			nRet = reqCmd.Process();
			if (nRet == -1)
			{
				reqCmd.DetachBuf();
				return -1;
			}

			vector<TAnchorInfo> vecInfo;
			vecInfo.clear();
			int nTotalNum = 0;
			string strSession = reqCmd.GetCmdBody().m_strSession;
			pMsgBody->m_tUserInfo.m_nUid = reqCmd.GetCmdBody().m_nUid;
			WRITE_ALL_LOG(DEBUG_LOG_TYPE, "recv ping session:%s from user:", strSession.c_str());
			pMsgBody->m_tUserInfo.Print();
			int nResult = 0;
			CMxrMessage* pServer = (CMxrMessage*)CMyserver::GetInstance();
			TMxrMessageConf tServerConf = pServer->GetConf().GetConf();
			unsigned int nHashNum = CToolKit::shortELFhash(strSession.c_str(), strSession.length());
			int nIndex = nHashNum % tServerConf.m_nSessionMsgNum;
			if (!tServerConf.m_vecIpInfo[nIndex].m_bFlag)
			{
				nResult = 1;
			}
			else
			{
				nRet = m_sessions->AddUser(strSession, pMsgBody->m_tUserInfo, vecInfo, nTotalNum);
				if (nRet == 0)
				{
					WRITE_ALL_LOG(DEBUG_LOG_TYPE, "ping session:%s not found.", strSession.c_str());
					nResult = 2;
				}
				m_sessions->Print();
			}

			CPingCmdRes resCmd(reqCmd, nTotalNum, vecInfo, nResult);
			resCmd.Process();
			CSessionMsgBody *pResBody = new CSessionMsgBody(pMsgBody->GetInfo(), resCmd.GetBuf(), resCmd.GetBufLen());
			SendMsg(pTMsg->srcEntityType, pTMsg->srcEntityId, pTMsg->srcTaskId, MSGTYPE_CMD_RES, pResBody);
			reqCmd.DetachBuf();
			resCmd.DetachBuf();
		}
		break;
	case CMDID_ANCHOR:
		{
			CAnchorCmd reqCmd(pMsgBody->GetBuf(), pMsgBody->Size());
			nRet = reqCmd.Process();
			if (nRet == -1)
			{
				reqCmd.DetachBuf();
				return -1;
			}
			
			string strSession = reqCmd.GetCmdBody().m_strSession;
			WRITE_ALL_LOG(DEBUG_LOG_TYPE, "recv anchor cmd, sessionid:%s", strSession.c_str());
			reqCmd.GetCmdBody().m_tAnchorInfo.Print();
			reqCmd.GetCmdBody().m_tAnchorInfo.m_nLastReportTime = CMyserver::GetInstance()->GetTimeVal().tv_sec;

			int nResult = 0;
			CMxrMessage* pServer = (CMxrMessage*)CMyserver::GetInstance();
			TMxrMessageConf tServerConf = pServer->GetConf().GetConf();
			unsigned int nHashNum = CToolKit::shortELFhash(strSession.c_str(), strSession.length());
			int nIndex = nHashNum % tServerConf.m_nSessionMsgNum;
			if (!tServerConf.m_vecIpInfo[nIndex].m_bFlag)
			{
				nResult = 1;
			}
			else
			{
				vector<TUserInfo> vecUsers;
				nRet = m_sessions->AddItem(strSession, reqCmd.GetCmdBody().m_tAnchorInfo, vecUsers);
				if (nRet == 0 && vecUsers.size() != 0)
				{
					vector<TAnchorInfo> vecInfo;
					vecInfo.push_back(reqCmd.GetCmdBody().m_tAnchorInfo);
					ProcessNoticeUser(strSession, vecUsers, vecInfo);
				}
				m_sessions->Print();
			}

			CAnchorCmdRes resCmd(reqCmd, nResult);
			resCmd.Process();
			CSessionMsgBody *pResBody = new CSessionMsgBody(pMsgBody->GetInfo(), resCmd.GetBuf(), resCmd.GetBufLen());
			SendMsg(pTMsg->srcEntityType, pTMsg->srcEntityId, pTMsg->srcTaskId, MSGTYPE_CMD_RES, pResBody);
			reqCmd.DetachBuf();
			resCmd.DetachBuf();
		}
		break;
	default:
		{
			WriteRunInfo::WriteError("unkown cmd:%d", nCmdId);
			break;
		}
	}

	return 0;
}

int CSessionProcessThread::ProcessCheckSessionMsg(CMsg *pMsg)
{
	map<string, TNoticeInfo> mapNotice;
	m_sessions->CheckTimeOut(mapNotice);
	if (mapNotice.size() != 0)
	{
		map<string, TNoticeInfo>::iterator itrMap = mapNotice.begin();
		for (; itrMap != mapNotice.end(); itrMap ++)
		{
			ProcessNoticeUser(itrMap->first, itrMap->second.m_vecUser, itrMap->second.m_vecAnchor);
		}
	}

	return 0;
}

int CSessionProcessThread::ProcessNoticeUser(const string &strSession, const vector<TUserInfo> &vecUsers, const vector<TAnchorInfo> &vecAnchor)
{
	CNoticeCmd reqCmd(vecAnchor);
	reqCmd.Process();
	int nSize = vecUsers.size();
	for (int i = 0; i < nSize; i ++)
	{
		char *pBuf = new char[reqCmd.GetBufLen()];
		memcpy(pBuf, reqCmd.GetBuf(), reqCmd.GetBufLen());
		CSessionMsgBody *pMsgBody = new CSessionMsgBody(vecUsers[i], pBuf, reqCmd.GetBufLen());
		SendMsg(vecUsers[i].m_nEntityType, vecUsers[i].m_nEntityId, vecUsers[i].m_nTaskId, MSGTYPE_CMD_RES, pMsgBody);
	}

	return 0;
}












