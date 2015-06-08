/**
*    @file       httprecvandsendthread.h
*
*    @brief      
*    @details    
*
*    @version    1.0
*    @date       2015/4/25
*
*    @author     zhangjiaxing, zhangjiaxing@baofeng.com
*/
#ifndef __HTTPRECVANDSENDTHREAD_H__
#define __HTTPRECVANDSENDTHREAD_H__

#include "netprocessthread.h"

class CHttpRecvAndSendThread
	: public CNetProcessThread
{
public:
	CHttpRecvAndSendThread(int nEntityType, int nEntityId);
	virtual ~CHttpRecvAndSendThread();

protected:
	virtual int Process(CMsg* pMsg);
};



#endif


