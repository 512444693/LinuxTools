/**
 *    @file       ontimethread.h
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __ONTIMETHREAD_H__
#define __ONTIMETHREAD_H__

#include "workthread.h"
#include "asynqueue.h"

class COnTimeThread : public CWorkThread
{
public:
	COnTimeThread(int nEntityType, int nEntityId);
	virtual ~COnTimeThread();

public:
	virtual int Init();
	virtual int Run();
	virtual int PutMsgToInputList(CMsg * pMsg);

protected:
	CAsynQueue  m_inputList;

private:
	virtual int Process(CMsg *pMsg);
};

#endif

