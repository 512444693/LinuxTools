/**
 *    @file       ontimethread.cpp
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "ontimethread.h"
#include "mxrmessagedef.h"
#include "mxrmessage.h"

COnTimeThread::COnTimeThread(int nEntityType, int nEntityId)
	:CWorkThread(nEntityType, nEntityId)
{

}

COnTimeThread::~COnTimeThread()
{

}

int COnTimeThread::Init()
{
	return 0;
}

int COnTimeThread::PutMsgToInputList(CMsg * pMsg)
{
	m_inputList.put(pMsg);
	return 0;
}

int COnTimeThread::Process(CMsg *pMsg)
{
	return 0;
}

int COnTimeThread::Run()
{
	long long nCurTime = CMyserver::GetInstance()->GetTimeVal().tv_sec;
	TMxrMessageConf conf = ((CMxrMessage*)CMyserver::GetInstance())->GetConf().GetConf();
	long long nLastCheckUserTime = nCurTime;

	while (m_nRunFlag)
	{
		CMsg *pMsg = m_inputList.get();
		if (pMsg != NULL)
		{
			Process(pMsg);
			delete pMsg;
		}

		nCurTime = CMyserver::GetInstance()->GetTimeVal().tv_sec;

		if (nCurTime - nLastCheckUserTime >= conf.m_nCheckUserInterval)
		{
			for (int i = 0; i < conf.m_nSessionProcessThreadNum; i ++)
			{
				SendMsg(ENTITYTYPE_SESSION_PROCESS, i, 0, MSGTYPE_CHECK_SESSION, NULL, 0);
			}
			nLastCheckUserTime = nCurTime;
		}

		usleep(1000);
	}
	return 0;
}

