/**
 *    @file       shortlistentask.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2015/4/28
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __SHORTLISTEN_TASK_H_
#define __SHORTLISTEN_TASK_H_

#include "sockettask.h"
#include "framecommon/framecommon.h"
using namespace std;

class CShortListenTask: public CSocketTask
{
public:
	CShortListenTask(CTcpSocket *pSocket, CNetProcessThread*pWorkThread, int nTaskType, int nConnectThreadType);
	virtual ~CShortListenTask();
	virtual int Init();

	virtual int Process(CMsg *pMsg);
	virtual int HandleProcess(int event);
protected:
	virtual int DestroySelf();
	virtual int PutMsgToSendList(const char *pBuf, int nLen);
	virtual int AddToEpoll();
	
	int m_nSendMsgType;

};
#endif

