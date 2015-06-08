/**
 *    @file       userhashtable.cpp
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
#include "userhashtable.h"
#include "utils.h"

CUserHashTable::CUserHashTable(int nHashBucketLen)
	: CMyHashTable<TUserInfo, list<TUserInfo> >(nHashBucketLen, 1)
{
}

CUserHashTable::~CUserHashTable()
{
}

int CUserHashTable::Init()
{
	return 0;
}

int CUserHashTable::UpdateItem(const TUserInfo &tUserInfo)
{
	int nTmpIndex = tUserInfo.GetIndex();
	int nRealIndex = nTmpIndex % m_nHashBucketLen;

	HASHLOCK(nRealIndex)
	HashIterator listItr = m_list[nRealIndex].begin();
	for (; listItr != m_list[nRealIndex].end(); listItr++)
	{
		if (tUserInfo == *listItr)
		{
			break;
		}
	}
	int nRet = 0;
	if (listItr == m_list[nRealIndex].end())
	{
		m_list[nRealIndex].push_back(tUserInfo);
		m_nNodeNum++;
		nRet = 1;
	}
	else
	{
		*listItr = tUserInfo;
	}
	HASHUNLOCK(nRealIndex)

	return nRet;
}

int CUserHashTable::Find(const TUserInfo &tUserInfo) const
{
	int nTmpIndex = tUserInfo.GetIndex();
	int nRealIndex = nTmpIndex % m_nHashBucketLen;

	HASHLOCK(nRealIndex)
	HashIterator listItr = m_list[nRealIndex].begin();
	int nRet = 0;
	for (; listItr != m_list[nRealIndex].end(); listItr++)
	{	
		if (tUserInfo == *listItr)
		{
			nRet = 1;
			break;
		}
	}
	HASHUNLOCK(nRealIndex)

	return nRet;
}

int CUserHashTable::GetAllUser(vector<TUserInfo> &vecUserInfo)
{
	for (int nRealIndex = 0; nRealIndex < m_nHashBucketLen; nRealIndex++)
	{
		HASHLOCK(nRealIndex);
		HashIterator listItr = m_list[nRealIndex].begin();
		for (; listItr != m_list[nRealIndex].end();)
		{
			vecUserInfo.push_back(*listItr);
			listItr ++;
		}
		HASHUNLOCK(nRealIndex);
	}

	return 0;
}

int CUserHashTable::CheckTimeOut()
{
	int nRet = 0;
	long long nCurTime = CMyserver::GetInstance()->GetTimeVal().tv_sec;
	CMxrMessage *pServer = (CMxrMessage*)CMyserver::GetInstance();
	unsigned int nUserTimeOut = pServer->GetConf().GetConf().m_nUserTimeOut;
	for (int nRealIndex = 0; nRealIndex < m_nHashBucketLen; nRealIndex ++)
	{
		HASHLOCK(nRealIndex);
		HashIterator listItr = m_list[nRealIndex].begin();
		for (; listItr != m_list[nRealIndex].end(); )
		{
			if(nCurTime - listItr->m_nLastReportTime >= nUserTimeOut)
			{
				WRITE_ALL_LOG(DEBUG_LOG_TYPE, "clear user:%s, last report time:%s.", listItr->m_strUnique.c_str(), CToolKit::Secd2Time(listItr->m_nLastReportTime).c_str());
				m_list[nRealIndex].erase(listItr ++);
				m_nNodeNum--;
			}
			else
			{
				listItr++;
			}
		}
		HASHUNLOCK(nRealIndex);
	}
	return nRet;
}

void CUserHashTable::Print()
{
	if ((WriteRunInfo::LOGTYPEARRAY[DEBUG_LOG_TYPE].nLogOff))
	{
		stringstream str;
		for(int nRealIndex = 0; nRealIndex < m_nHashBucketLen; nRealIndex++)
		{
			HASHLOCK(nRealIndex)
			HashIterator listItr = m_list[nRealIndex].begin();
			for (; listItr != m_list[nRealIndex].end(); listItr++)
			{
				str << listItr->m_strUnique << "\t" << Utils::IPInt2Str(htonl(listItr->m_nFarIp)) << "\t"
					<< listItr->m_nFarPort << "\t"
					<< CToolKit::Secd2Time(listItr->m_nLastReportTime) << "\n ";
			}
			HASHUNLOCK(nRealIndex)
		}

		WRITE_ALL_LOG(DEBUG_LOG_TYPE, "----------- user hash table ----------------: \n %s ", str.str().c_str());
	}
}


