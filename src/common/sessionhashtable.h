/**
 *    @file       sessionhashtable.h
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __SESSIONHASHTABLE_H__
#define __SESSIONHASHTABLE_H__

#include "framecommon/framecommon.h"
#include "userhashtable.h"

struct TSessionInfo
{
	TSessionInfo()
	{
		m_strSessionId = "";
		m_lstAnchorInfo.clear();
		m_pHashTable = NULL;
	}

	bool operator==(const TSessionInfo &tSessionInfo) const
	{
		return (this->m_strSessionId == tSessionInfo.m_strSessionId);
	}

	unsigned int GetIndex() const
	{
		return CToolKit::shortELFhash(this->m_strSessionId.c_str(), this->m_strSessionId.length());
	}

	string m_strSessionId;
	list<TAnchorInfo> m_lstAnchorInfo;
	CUserHashTable* m_pHashTable;
};

class CSessionHashTable: public CMyHashTable< TSessionInfo, list<TSessionInfo> >
{
public:
	CSessionHashTable(int nHashLen, int iIfLOCK);
	~CSessionHashTable();

	int AddItem(const string &strSession, const TAnchorInfo &tAnchorInfo, vector<TUserInfo> &vecUsers);
	int DelItem(const TSessionInfo &tSessionInfo);
	int AddAnchor(list<TAnchorInfo> &lstInfo, const TAnchorInfo &tAnchor);
	int AddUser(const string &strSessionId, const TUserInfo &tUserInfo, vector<TAnchorInfo> &vecInfo, int &nTotalNum);
	void CheckTimeOut(map<string, TNoticeInfo> &mapNotice);
	int Print();
private:
	int GetUserInfo(const string &strSession, vector<TUserInfo> &vecUserInfo);
};

#endif

