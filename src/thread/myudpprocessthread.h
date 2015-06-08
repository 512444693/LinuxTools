/**
 *    @file       myudpprocessthread.h
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __MYUDPPROCESSTHREAD_H__
#define __MYUDPPROCESSTHREAD_H__

#include "udpsendthread.h"
#include "sessionhashtable.h"

class CMyUdpProcessThread: public CUdpSendThread
{
public:
	CMyUdpProcessThread(int nEntityType, int nEntityId, string& strIp, unsigned short nPort);
	virtual ~CMyUdpProcessThread();
	virtual int Init();
	virtual int Run();
private:
	virtual int Process(CMsg* pMsg);
	int ProcessClientMsg(CMsg *pMsg);
	int ProcessCmdResMsg (CMsg *pMsg);
};

#endif

