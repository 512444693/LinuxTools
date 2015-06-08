/**
 *    @file       sessionhashtable.cpp
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "sessionhashtable.h"
#include "mxrmessage.h"

CSessionHashTable::CSessionHashTable(int nHashLen, int iIfLOCK)
	:CMyHashTable< TSessionInfo, list<TSessionInfo> >(nHashLen, iIfLOCK)
{

}

CSessionHashTable::~CSessionHashTable()
{
	for (int nRealIndex = 0; nRealIndex < m_nHashBucketLen; nRealIndex++)
	{
		HASHLOCK(nRealIndex);
		HashIterator listItr = m_list[nRealIndex].begin();
		for (; listItr != m_list[nRealIndex].end();)
		{
			delete listItr->m_pHashTable;
			listItr ++;
		}
		HASHUNLOCK(nRealIndex);
	}
}

int CSessionHashTable::AddItem(const string &strSession, const TAnchorInfo &tAnchor, vector<TUserInfo> &vecUsers)
{
	TSessionInfo tSessionInfo;
	tSessionInfo.m_strSessionId = strSession;
	int nTmpIndex = tSessionInfo.GetIndex();
	int nRealIndex = nTmpIndex % m_nHashBucketLen;

	HASHLOCK(nRealIndex)
	HashIterator listItr = m_list[nRealIndex].begin();
	for (; listItr != m_list[nRealIndex].end(); listItr++)
	{
		if (tSessionInfo == *listItr)
		{
			break;
		}
	}
	int nRet = 0;
	if (listItr == m_list[nRealIndex].end())
	{
		if (tAnchor.m_nAction == TAnchorInfo::ANCHOR_ADD)
		{
			CMxrMessage *pServer = (CMxrMessage*)CMyserver::GetInstance();
			TMxrMessageConf& conf = pServer->GetConf().GetConf();
			int nUserHashTableLen = conf.m_nUserBucketLen;
			tSessionInfo.m_lstAnchorInfo.push_back(tAnchor);
			tSessionInfo.m_pHashTable = new CUserHashTable(nUserHashTableLen);
			WRITE_ALL_LOG(DEBUG_LOG_TYPE, "new session:%s.", tSessionInfo.m_strSessionId.c_str());

			m_list[nRealIndex].push_back(tSessionInfo);
			m_nNodeNum++;
			nRet = 1;
		}
	}
	else
	{
		int nReturn = AddAnchor(listItr->m_lstAnchorInfo, tAnchor);
		if (nReturn == 1)
		{
			GetUserInfo(listItr->m_strSessionId, vecUsers);
			if (listItr->m_lstAnchorInfo.size() == 0)
			{
				WRITE_ALL_LOG(DEBUG_LOG_TYPE, "erase session:%s.", listItr->m_strSessionId.c_str());
				delete listItr->m_pHashTable;
				m_list[nRealIndex].erase(listItr);
				m_nNodeNum--;
			}
		}
	}
	HASHUNLOCK(nRealIndex)

	return nRet;
}

int CSessionHashTable::AddUser(const string &strSessionId, const TUserInfo &tUserInfo, vector<TAnchorInfo> &vecInfo, int &nTotalNum)
{
	TSessionInfo tSessionInfo;
	tSessionInfo.m_strSessionId = strSessionId;
	int nTmpIndex = tSessionInfo.GetIndex();
	int nRealIndex = nTmpIndex % m_nHashBucketLen;

	int nRet = 0;
	HASHLOCK(nRealIndex)
	HashIterator listItr = m_list[nRealIndex].begin();
	for (; listItr != m_list[nRealIndex].end(); listItr++)
	{
		if (tSessionInfo == *listItr)
		{
			list<TAnchorInfo>::iterator itrLst = listItr->m_lstAnchorInfo.begin();
			while (itrLst != listItr->m_lstAnchorInfo.end())
			{
				if (tUserInfo.m_nUid != 0 && tUserInfo.m_nUid == itrLst->m_nAnchorId)
				{
					unsigned int nCurTime = CMyserver::GetInstance()->GetTimeVal().tv_sec;
					itrLst->m_nLastReportTime = nCurTime;
					nRet = 1;
				}
				vecInfo.push_back(*itrLst);
				itrLst ++;
			}
			if (tUserInfo.m_nUid == 0 || nRet == 1)
			{
				nRet = 1;
				listItr->m_pHashTable->UpdateItem(tUserInfo);
			}
			nTotalNum = listItr->m_pHashTable->GetNodeNum();
			break;
		}
	}
	HASHUNLOCK(nRealIndex)

	return nRet;
}

int CSessionHashTable::AddAnchor(list<TAnchorInfo> &lstInfo, const TAnchorInfo &tAnchor)
{
	int nRet = 0;
	WRITE_ALL_LOG(DEBUG_LOG_TYPE, "anchor:%d,action:%d", tAnchor.m_nAnchorId, tAnchor.m_nAction);
	list<TAnchorInfo>::iterator itrTmp = lstInfo.begin();
	for (; itrTmp != lstInfo.end(); itrTmp ++)
	{
		if (*itrTmp == tAnchor)
		{
			break;
		}
	}
	if (itrTmp == lstInfo.end())
	{
		if (tAnchor.m_nAction == TAnchorInfo::ANCHOR_ADD)
		{
			nRet = 1;
			lstInfo.push_back(tAnchor);
		}
	}
	else
	{
		if (tAnchor.m_nAction == TAnchorInfo::ANCHOR_DEL)
		{
			WRITE_ALL_LOG(DEBUG_LOG_TYPE, "del anchor:%d,name:%s", tAnchor.m_nAnchorId, tAnchor.m_strName.c_str());
			lstInfo.erase(itrTmp);
			nRet = 1;
		}
		else
		{
			WRITE_ALL_LOG(DEBUG_LOG_TYPE, "anchor:%d exist", tAnchor.m_nAnchorId);
			*itrTmp = tAnchor;
		}

	}

	return nRet;
}

int CSessionHashTable::GetUserInfo(const string &strSession, vector<TUserInfo> &vecUserInfo)
{
	TSessionInfo tSessionInfo;
	tSessionInfo.m_strSessionId = strSession;
	int nTmpIndex = tSessionInfo.GetIndex();
	int nRealIndex = nTmpIndex % m_nHashBucketLen;

	int nRet = 0;
	HASHLOCK(nRealIndex);
	HashIterator listItr = m_list[nRealIndex].begin();
	for (; listItr != m_list[nRealIndex].end(); listItr ++)
	{
		if (*listItr == tSessionInfo)
		{
			nRet = 1;
			listItr->m_pHashTable->GetAllUser(vecUserInfo);
		}
	}
	HASHUNLOCK(nRealIndex);

	return nRet;
}

void CSessionHashTable::CheckTimeOut(map<string, TNoticeInfo> &mapNotice)
{
	long long nCurTime = CMyserver::GetInstance()->GetTimeVal().tv_sec;
	CMxrMessage *pServer = (CMxrMessage*)CMyserver::GetInstance();
	unsigned int nUserTimeOut = pServer->GetConf().GetConf().m_nUserTimeOut;
	for (int nRealIndex = 0; nRealIndex < m_nHashBucketLen; nRealIndex++)
	{
		HASHLOCK(nRealIndex);
		HashIterator listItr = m_list[nRealIndex].begin();
		for (; listItr != m_list[nRealIndex].end();)
		{
			list<TAnchorInfo>::iterator itrLst = listItr->m_lstAnchorInfo.begin();
			for (; itrLst != listItr->m_lstAnchorInfo.end(); )
			{
				if (nCurTime - itrLst->m_nLastReportTime >= nUserTimeOut)
				{
					itrLst->m_nAction = TAnchorInfo::ANCHOR_DEL;
					map<string, TNoticeInfo>::iterator itrMap = mapNotice.find(listItr->m_strSessionId);
					if (itrMap == mapNotice.end())
					{
						TNoticeInfo tNotices;
						tNotices.m_vecAnchor.push_back(*itrLst);
						GetUserInfo(listItr->m_strSessionId, tNotices.m_vecUser);
						mapNotice.insert(make_pair(listItr->m_strSessionId, tNotices));
					}
					else
					{
						itrMap->second.m_vecAnchor.push_back(*itrLst);
					}
					WRITE_ALL_LOG(DEBUG_LOG_TYPE, "erase anchor:%d, name:%s", itrLst->m_nAnchorId, itrLst->m_strName.c_str());
					listItr->m_lstAnchorInfo.erase(itrLst ++);
				}
				else
				{
					itrLst ++;
				}
			}
			if (listItr->m_lstAnchorInfo.size() == 0)
			{
				WRITE_ALL_LOG(DEBUG_LOG_TYPE, "erase session:%s.", listItr->m_strSessionId.c_str());
				delete listItr->m_pHashTable;
				m_list[nRealIndex].erase(listItr ++);
				m_nNodeNum--;
			}
			else
			{
				listItr->m_pHashTable->CheckTimeOut();
				listItr ++;
			}
		}
		HASHUNLOCK(nRealIndex);
	}
}

int CSessionHashTable::DelItem(const TSessionInfo &tSessionInfo)
{
	int nTmpIndex = tSessionInfo.GetIndex();
	int nRealIndex = nTmpIndex % m_nHashBucketLen;

	int nRet = 0;
	HASHLOCK(nRealIndex)
	HashIterator listItr = m_list[nRealIndex].begin();
	for (; listItr != m_list[nRealIndex].end(); listItr++)
	{
		if (tSessionInfo == *listItr)
		{
			delete listItr->m_pHashTable;
			m_list[nRealIndex].erase(listItr);
			m_nNodeNum--;
			nRet = 1;
			break;
		}
	}
	HASHUNLOCK(nRealIndex)
	return nRet;
}

int CSessionHashTable::Print()
{
	for (int nRealIndex = 0; nRealIndex < m_nHashBucketLen; nRealIndex++)
	{
		HASHLOCK(nRealIndex);
		HashIterator listItr = m_list[nRealIndex].begin();
		for (; listItr != m_list[nRealIndex].end();)
		{
			WRITE_ALL_LOG(DEBUG_LOG_TYPE, "======session:%s", listItr->m_strSessionId.c_str());
			list<TAnchorInfo>::iterator itrLst = listItr->m_lstAnchorInfo.begin();
			stringstream ss;
			while (itrLst != listItr->m_lstAnchorInfo.end())
			{
				ss << "id:" << itrLst->m_nAnchorId << "\t"
					<< "name:" << itrLst->m_strName << "\t"
					<< "channelid:(";
				int nChannelNum = itrLst->m_vecChannel.size();
				for (int nA = 0; nA < nChannelNum; nA ++)
				{
					ss << itrLst->m_vecChannel[nA];
					if (nA != nChannelNum - 1)
					{
						ss << ",";
					}
				}
				ss << ")\t";
				ss << CToolKit::Secd2Time(itrLst->m_nLastReportTime) << "\n";
				itrLst ++;
			}
			WRITE_ALL_LOG(DEBUG_LOG_TYPE, "anchor info:\n%s", ss.str().c_str());
			listItr->m_pHashTable->Print();
			listItr ++;
		}
		HASHUNLOCK(nRealIndex);
	}

	return 0;
}

