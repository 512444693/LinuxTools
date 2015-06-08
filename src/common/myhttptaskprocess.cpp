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
#include "myhttptaskprocess.h"
#include "HttpRecvAndSendTask.h"
#include "httpprocesstask.h"
#include "threadmsgbody.h"
#include "httpreply.h"
#include "mxrmessage.h"
#include "utils.h"
using namespace std;

CMyHttpTaskProcess::CMyHttpTaskProcess(CNetProcessThread* pNetProcessThread, CRecvAndSendTask* pRecvAndSendTask, CTcpSocket* pTcpSocket)
: CHttpRecvAndSendTaskProcess(pNetProcessThread, pRecvAndSendTask, pTcpSocket)
{
}

CMyHttpTaskProcess::~CMyHttpTaskProcess()
{
}

int CMyHttpTaskProcess::ProcessRecvPacket(const char* pPacket, unsigned int uiBufLen)
{
	CHttpProcessTask *pTask = (CHttpProcessTask *)m_pRecvAndSendTask;
	pTask->ProcessResponseData(NULL, 0, METHOD_NOT_ALLOWED);
	return 0;
}

int CMyHttpTaskProcess::ProcessHeadReq(const char* pPacket, unsigned int uiBufLen)
{
	CHttpProcessTask *pTask = (CHttpProcessTask *)m_pRecvAndSendTask;
	pTask->ProcessResponseData(NULL, 0, METHOD_NOT_ALLOWED);
	return 0;
}

int CMyHttpTaskProcess::ProcessGetReq(const char* pPacket, unsigned int uiBufLen)
{
	int nCode = ProcessGetPacket(pPacket, uiBufLen);
	if (nCode != 0)
	{
		CHttpProcessTask *pTask = (CHttpProcessTask *)m_pRecvAndSendTask;
		pTask->ProcessResponseData(NULL, 0, nCode);
	}
	return 0;
}

int CMyHttpTaskProcess::ProcessGetPacket(const char* pPacket, unsigned int uiBufLen)
{
	string strUri;
	string strHttpHead(pPacket, uiBufLen);
	unsigned int nClientIp = ntohl(m_pRecvAndSendTask->GetAddr().sin_addr.s_addr);
	string strIp = Utils::IPInt2Str(htonl(nClientIp));
	WRITE_ALL_LOG(DEBUG_LOG_TYPE, "Recv request from client:%s, strHttpHead:%s", strIp.c_str(), strHttpHead.c_str());
	int nRet = CToolKit::GetStringByLabel(strHttpHead, " ", " ", strUri, 0, 0);
	if (nRet != 0)
	{
		WRITE_ALL_LOG(DEBUG_LOG_TYPE, "CMyHttpTaskProcess::ProcessGetPacket : Invalid url %s", strUri.c_str());
		return BAD_REQUEST;
	}

	string strGcid;
	int nPos = strUri.find('/');
	if (nPos == (int)string::npos)
	{
		WRITE_ALL_LOG(DEBUG_LOG_TYPE, "Can not find gcid in %s", strUri.c_str());
		return BAD_REQUEST;
	}
	CMxrMessage* pServer = (CMxrMessage*)CMyserver::GetInstance();
	CHttpProcessTask *pTask = (CHttpProcessTask *)m_pRecvAndSendTask;
	strGcid = strUri.substr(nPos + 1);

	string strResponse;
	strResponse.clear();
	if (strGcid == CROSS_FILENAME)
	{
		pServer->GetConf().GetCrossString(strResponse);
		pTask->ProcessResponseData((char*)strResponse.c_str(), (int)strResponse.length());
	}
	else if ((int)strGcid.length() == MXR_GCID_LEN)
	{
		TMxrMessageConf tServerConf = pServer->GetConf().GetConf();
		unsigned int nHashNum = CToolKit::shortELFhash(strGcid.c_str(), strGcid.length());
		int nIndex = nHashNum % tServerConf.m_nSessionMsgNum;
		
		pTask->m_nQueryType = EQT_QUERY;
		string strRespone;
		stringstream ss;
		ss << Utils::IPInt2Str(ntohl(tServerConf.m_vecIpInfo[nIndex].m_nIp))
			<< ":" << tServerConf.m_vecIpInfo[nIndex].m_nPort;
		strRespone = ss.str();
		pTask->ProcessResponseData((char*)strRespone.c_str(), (int)strRespone.length());
	}
	else
	{
		WRITE_ALL_LOG(DEBUG_LOG_TYPE, "It must be crossdomain.xml or gcid with length 40.");
		return BAD_REQUEST;
	}

	return 0;
}

const char* CMyHttpTaskProcess::ProcessSendPacket(const char *pOldPacket, unsigned int uiOldBufLen, unsigned int &uiNewBufLen)
{
	char* pNewBuf = (char*)pOldPacket;
	uiNewBufLen = uiOldBufLen;

	if(!CAESEncryptApplication::AESEncryptEx(pNewBuf, uiNewBufLen))
	{
		return NULL;
	}

	return pNewBuf;
}

