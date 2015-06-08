/**
 *    @file       mxrmessage.h
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __MXRMESSAGE_H__
#define __MXRMESSAGE_H__

#include "myserver.h"
#include "threadgroup.h"
#include "maintainudpthread.h"
#include "mxrmessageconf.h"

class CMxrMessage : public CMyserver
{
public:
	CMxrMessage();
	~CMxrMessage();
public:
	virtual int InitServer( void );
	virtual int StartServer();

	CMxrMessageConf &GetConf()
	{
		return m_conf;
	}

private:
	CMxrMessageConf m_conf;
private:
	CThreadGroup *m_pTimerThreadGrp;
	CThreadGroup *m_pListenThreadGrp;
	CMaintainUdpThread *m_pMaintainUpdThread;
	CThreadGroup *m_pUdpRecvThreadGrp;
	CThreadGroup *m_pUdpProcessThreadGrp;
	CThreadGroup *m_pShortConListenThreadGrp;
	CThreadGroup *m_pRecvAndSendThreadGrp;
	CThreadGroup *m_pSessionProcessThreadGrp;
	CThreadGroup *m_pOnTimeThreadGrp;
};

#endif


