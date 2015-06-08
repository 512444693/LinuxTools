/**
*    @file       myhttptaskprocess.h
*
*    @brief      
*    @details    
*
*    @version    1.0
*    @date       2015/4/28
*
*    @author     zhangjiaxing, zhangjiaxing@baofeng.com
*/
#ifndef __MYHTTPTASKPROCESS_H__
#define __MYHTTPTASKPROCESS_H__

#include "HttpRecvAndSendTaskProcess.h"
#include "mxrmessagedef.h"
#include "framecommon/framecommon.h"
using namespace MYFRAMECOMMON;

class CMyHttpTaskProcess
: public CHttpRecvAndSendTaskProcess
{
public:
	CMyHttpTaskProcess(CNetProcessThread* pNetProcessThread, CRecvAndSendTask* pRecvAndSendTask, CTcpSocket* pTcpSocket);
	virtual ~CMyHttpTaskProcess();
	virtual const char* ProcessSendPacket(const char* pOldPacket, unsigned int uiOldBufLen, unsigned int& uiNewBufLen);
	virtual int ProcessGetReq(const char* pPacket, unsigned int uiBufLen);
	virtual int ProcessHeadReq(const char* pPacket, unsigned int uiBufLen);
	int ProcessRecvPacket(const char* pPacket, unsigned int uiBufLen);

private:
	int ProcessGetPacket(const char* pPacket, unsigned int uiBufLen);
private:
};

#endif


