/**
 *    @file       httpprocesstask.cpp
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2015/4/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "httpprocesstask.h"
#include "mxrmessagedef.h"
#include "threadmsgbody.h"
#include "mxrmessage.h"
#include "httpreply.h"
#include "utils.h"

CHttpProcessTask::CHttpProcessTask(CTcpSocket *pSocket, CNetProcessThread *pWorkThread, int nListType/* =0 */)
: CHttpRecvAndSendTask<CMyHttpTaskProcess>(pSocket, pWorkThread, nListType, 4096, 1024)
{
	m_nQueryType = EQT_DEFAULT;
}

CHttpProcessTask::~CHttpProcessTask()
{
}

int CHttpProcessTask::ProcessResponseData(char *pResponseData, int nResponseLen, int nCode)
{
	if (nCode == 0)
	{
		nCode = (nResponseLen > 0)?OK:BAD_REQUEST;
	}
	PutGetResMsgToSendList(pResponseData, nResponseLen, nCode);

	return 0;
}

int CHttpProcessTask::PutGetResMsgToSendList(char *pBuf, int nLen, int nCode)
{
	string strHTTPHead = ToString(nCode);
	string strGmt;
	strGmt = Utils::GetGMTTime();
	string strContentType = HTTP_CONTENT_TYPE;
	if (nCode == OK && m_nQueryType == EQT_QUERY)
	{
		strContentType = HTTP_CONTENT_TYPE;
	}
	if (CHttpProcessTask::m_bEncodeHttpHead)
	{
		char nBodLen[12];
		memset(nBodLen, 0 , sizeof(nBodLen));
		snprintf(nBodLen, sizeof(nBodLen), "%d", nLen);
		strHTTPHead = GEN_NEW_HTTP_RET_HEAD(strHTTPHead, nBodLen, strContentType, strGmt);
	}

	CSendMsg *pSendMsg = NULL;
	char *tmpBuf = new char[strHTTPHead.length() + nLen];
	memset(tmpBuf, 0, strHTTPHead.length() + nLen);
	memcpy(tmpBuf, strHTTPHead.c_str(), strHTTPHead.length());
	memcpy(tmpBuf + strHTTPHead.length(), pBuf, nLen);

	pSendMsg = new CSendMsg(strHTTPHead.length() + nLen, tmpBuf);
	CHttpRecvAndSendTask<CMyHttpTaskProcess>::m_sendList.push_back(pSendMsg);
	int tmpEvent = MYPOLLERR|MYPOLLHUP|MYPOLLIN| MYPOLLOUT;
	CNetProcessThread* pNetThread = (CNetProcessThread*)CHttpRecvAndSendTask<CMyHttpTaskProcess>::m_pThread;
	CEpoll* pEoll = pNetThread->GetEpoll();
	pEoll->ModifyFromEpoll(this, tmpEvent);

	return 0;
}

