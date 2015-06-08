/**
 *    @file       httpprocesstask.h
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2015/4/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __HTTPPROCESSTASK_H__
#define __HTTPPROCESSTASK_H__

#include "HttpRecvAndSendTask.h"
#include "myhttptaskprocess.h"

enum EQueryType
{
	EQT_DEFAULT = 0,
	EQT_QUERY = 1,
};

class CHttpProcessTask: public CHttpRecvAndSendTask<CMyHttpTaskProcess>
{
public:
	CHttpProcessTask(CTcpSocket* pSocket, CNetProcessThread* pWorkThread, int nListType = 0);
	virtual ~CHttpProcessTask();
	int ProcessResponseData(char *pResponseData, int nResponseLen, int nCode = 0);
	int PutGetResMsgToSendList(char *pBuf, int nLen, int nCode);
	int ProcessMsg(CMsg *pMsg);
	int ProcessQuery();

protected:
	int GenResponse(vector<unsigned int> &vecIp, string &strResponse);
public:
	int m_nQueryType;
};

#endif
