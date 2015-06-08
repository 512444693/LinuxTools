/**
 *    @file       getcmd.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __GETCMD_H__
#define __GETCMD_H__

#include "framecommon/framecommon.h"
#include "mybasecmd.h"
#include "mxrmessagedef.h"

using namespace std;
using namespace MYFRAMECOMMON;

struct TGet
{
	string m_strSession;

	int Decode(CBufMgr &bufMgr)
	{
		if (bufMgr.GetString(m_strSession) != 0) {return -1;}
		if (m_strSession.length() != (int)MXR_GCID_LEN ) {return -1;}

		return 0;
	}
};

struct TGetRes
{
	char m_cResult;
	int m_nIp;
	short m_nPort;

	int Encode(CBufMgr& bufMgr)
	{
		int nRet = 0;
		nRet += bufMgr.PutChar(m_cResult);
		nRet += bufMgr.PutInt(m_nIp);
		nRet += bufMgr.PutShort(m_nPort);

		return nRet;
	}

	int GetSize()
	{
		int nLen = 0;
		nLen += sizeof(m_cResult);
		nLen += sizeof(m_nIp);
		nLen += sizeof(m_nPort);

		return nLen;
	}
};

class CGetCmd: public CDecodeCmd<TCmdHead, TGet>
{
public:
	CGetCmd(char* pBuf, int nLen) : CDecodeCmd<TCmdHead, TGet>(pBuf, nLen){}
	virtual ~CGetCmd(){}

protected:
	int ProcessCmd();
private:
};

class CGetCmdRes: public CEncodeCmd<TCmdHead, TGetRes>
{
public:
	CGetCmdRes(CGetCmd &cmdReq, int nIp, int nPort);
	virtual ~CGetCmdRes(){}
protected:
	int ProcessCmd();
private:
};

#endif

