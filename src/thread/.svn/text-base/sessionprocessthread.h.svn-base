/**
 *    @file       sessionprocessthread.h
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2015/3/15
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __SESSIONPROCESSTHREAD_H__
#define __SESSIONPROCESSTHREAD_H__

#include "synworkthread.h"
#include "sessionhashtable.h"

class CSessionProcessThread : public CSynWorkThread
{
public:
	CSessionProcessThread(int nEntityType, int nEntityId);
	virtual ~CSessionProcessThread();
protected:
private:
	virtual int Process(CMsg *pMsg);
	int ProcessSessionMsg(CMsg *pMsg);
	int ProcessCheckSessionMsg(CMsg *pMsg);
	int ProcessNoticeUser(const string &strSession, const vector<TUserInfo> &vecUser, const vector<TAnchorInfo> &vecAnchor);
private:
	CSessionHashTable *m_sessions;
};

#endif
