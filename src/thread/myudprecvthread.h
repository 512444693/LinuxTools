/**
 *    @file       myudprecvthread.h
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __MYUDPRECVTHREAD_H__
#define __MYUDPRECVTHREAD_H__

#include "udprecvthread.h"

class CMyUdpRecvThread : public CUdpRecvThread
{
public:
	CMyUdpRecvThread(int nEntityType, int nEntityId, CUdpCommonSock* pUdpRecvSocket);
	~CMyUdpRecvThread();
	virtual int Run();
private:
	int GetSessionId(char *pBuf, int nBufLen, string &strSessionId);
};

#endif

