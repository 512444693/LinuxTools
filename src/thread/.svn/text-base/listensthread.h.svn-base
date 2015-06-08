/**
 *    @file       listensthread.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2015/4/28
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */

#ifndef __LISTENS_THREAD_H_
#define __LISTENS_THREAD_H_
#include "netprocessthread.h"
#include "shortlistentask.h"
#include "mxrmessagedef.h"
#include <vector>
using namespace std;

struct TListensBlock
{
	vector<int> vecSocks;

	CThreadMutex mutex;
	explicit TListensBlock(unsigned int nSockCounts)
	{
		for(unsigned int i = 0; i < nSockCounts; i++)
		{
			vecSocks.push_back(-1);
		}
	}
};

class CListensThread: public CNetProcessThread
{
public:
	CListensThread(int iEntityType, int iEntityId, vector<TSocketAddr>& vecAddrs, TListensBlock *pListenBlock);
	virtual ~CListensThread();
	int Init();
	TListensBlock *GetListenBlock()
	{
		return m_pListenBlock;
	}

protected:
	vector<TSocketAddr> m_vecAddrs;
	vector<CTcpSocket*> m_vecTcpSockets;
	vector<CShortListenTask*> m_vecListenTasks;
	TListensBlock *m_pListenBlock;
};

#endif

