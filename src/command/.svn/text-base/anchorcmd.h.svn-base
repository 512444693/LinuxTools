/**
 *    @file       anchorcmd.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __ANCHORCMD_H__
#define __ANCHORCMD_H__

#include "framecommon/framecommon.h"
#include "mybasecmd.h"
#include "mxrmessagedef.h"

using namespace std;
using namespace MYFRAMECOMMON;

struct TAnchor
{
	string m_strSession;
	TAnchorInfo m_tAnchorInfo;

	int Decode(CBufMgr &bufMgr)
	{
		if (bufMgr.GetString(m_strSession) != 0) {return -1;}
		if (m_strSession.length() != (int)MXR_GCID_LEN) {return -1;}
		if (bufMgr.GetInt(m_tAnchorInfo.m_nAnchorId) != 0) {return -1;}
		if (bufMgr.GetChar(m_tAnchorInfo.m_nAction) != 0) {return -1;}
		if ((m_tAnchorInfo.m_nAction != TAnchorInfo::ANCHOR_ADD) && (m_tAnchorInfo.m_nAction != TAnchorInfo::ANCHOR_DEL)) {return -1;}
		if (bufMgr.GetString(m_tAnchorInfo.m_strName) != 0) {return -1;}
		int nChannelNum = 0;
		if (bufMgr.GetInt(nChannelNum) != 0) {return -1;}
		for (int nB = 0; nB < nChannelNum; nB ++)
		{
			int nChannelId = 0;
			if (bufMgr.GetInt(nChannelId) != 0) {return -1;}
			m_tAnchorInfo.m_vecChannel.push_back(nChannelId);
		}

		return 0;
	}
};

struct TAnchorRes
{
	char m_cResult;

	int Encode(CBufMgr& bufMgr)
	{
		int nRet = 0;
		nRet += bufMgr.PutChar(m_cResult);

		return nRet;
	}

	int GetSize()
	{
		int nLen = 0;
		nLen += sizeof(m_cResult);

		return nLen;
	}

};

class CAnchorCmd: public CDecodeCmd<TCmdHead, TAnchor>
{
public:
	CAnchorCmd(char* pBuf, int nLen) : CDecodeCmd<TCmdHead, TAnchor>(pBuf, nLen){}
	virtual ~CAnchorCmd(){}

protected:
	int ProcessCmd();
private:
};

class CAnchorCmdRes: public CEncodeCmd<TCmdHead, TAnchorRes>
{
public:
	CAnchorCmdRes(CAnchorCmd &cmdReq, int nResult);
	virtual ~CAnchorCmdRes(){}
protected:
	int ProcessCmd();
private:
};

#endif

