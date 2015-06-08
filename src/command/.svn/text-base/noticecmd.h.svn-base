/**
 *    @file       noticecmd.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __NOTICECMD_H__
#define __NOTICECMD_H__

#include "framecommon/framecommon.h"
#include "mybasecmd.h"
#include "mxrmessagedef.h"

using namespace std;
using namespace MYFRAMECOMMON;

struct TNotice
{
	vector<TAnchorInfo> m_vecAnchor;

	int Encode(CBufMgr &bufMgr)
	{
		int nRet = 0;
		int nSize = m_vecAnchor.size();
		nRet += bufMgr.PutInt(nSize);
		for (int nA = 0; nA  < nSize; nA ++)
		{
			nRet += bufMgr.PutInt(m_vecAnchor[nA].m_nAnchorId);
			nRet += bufMgr.PutChar(m_vecAnchor[nA].m_nAction);
			nRet += bufMgr.PutString(m_vecAnchor[nA].m_strName);
			int nChannelNum = m_vecAnchor[nA].m_vecChannel.size();
			nRet += bufMgr.PutInt(nChannelNum);
			for (int nB = 0; nB < nChannelNum; nB ++)
			{
				nRet += bufMgr.PutInt(m_vecAnchor[nA].m_vecChannel[nB]);
			}
		}

		return 0;
	}

	int GetSize()
	{
		int nLen = 0;
		int nSize = m_vecAnchor.size();
		nLen += sizeof(nSize);
		for (int nA  = 0; nA < nSize; nA ++)
		{
			nLen += sizeof(m_vecAnchor[nA].m_nAnchorId);
			nLen += sizeof(m_vecAnchor[nA].m_nAction);
			nLen += sizeof(int) + m_vecAnchor[nA].m_strName.length();
			int nChannelNum = m_vecAnchor[nA].m_vecChannel.size();
			nLen += sizeof(nChannelNum);
			for (int nB = 0; nB < nChannelNum; nB ++)
			{
				nLen += sizeof(m_vecAnchor[nA].m_vecChannel[nB]);
			}
		}

		return nLen;
	}
};

struct TNoticeRes
{
	char m_cResult;

	int Decode(CBufMgr& bufMgr)
	{
		if (bufMgr.GetChar(m_cResult) != 0) {return -1;}
		
		return 0;
	}

	int GetSize()
	{
		int nLen = 0;
		nLen += sizeof(m_cResult);

		return nLen;
	}
};

class CNoticeCmd: public CEncodeCmd<TCmdHead, TNotice>
{
public:
	CNoticeCmd(const vector<TAnchorInfo> &vecAnchor);
	virtual ~CNoticeCmd(){}

protected:
	int ProcessCmd();
};

class CNoticeCmdRes: public CDecodeCmd<TCmdHead, TNoticeRes>
{
public:
	CNoticeCmdRes(char* pBuf, int nLen) : CDecodeCmd<TCmdHead, TNoticeRes>(pBuf, nLen){};
	virtual ~CNoticeCmdRes(){}
protected:
	int ProcessCmd();
};

#endif
