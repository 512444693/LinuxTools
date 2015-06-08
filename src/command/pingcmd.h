/**
 *    @file       pingcmd.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __PINGCMD_H__
#define __PINGCMD_H__

#include "framecommon/framecommon.h"
#include "mybasecmd.h"
#include "mxrmessagedef.h"

using namespace std;
using namespace MYFRAMECOMMON;

struct TPing
{
	string m_strSession;
	int m_nUid;

	int Decode(CBufMgr &bufMgr)
	{
		if (bufMgr.GetString(m_strSession) != 0) {return -1;}
		if (m_strSession.length() != (int)MXR_GCID_LEN) {return -1;}
		if (bufMgr.GetInt(m_nUid) != 0) {return -1;}

		return 0;
	}
};

struct TPingRes
{
	char m_cResult;
	string m_strSession;
	unsigned int m_nTotalNum;
	vector<TAnchorInfo> m_vecInfo;

	int Encode(CBufMgr& bufMgr)
	{
		int nRet = 0;
		nRet += bufMgr.PutChar(m_cResult);
		nRet += bufMgr.PutString(m_strSession);
		nRet += bufMgr.PutInt(m_nTotalNum);
		int nVecSize = m_vecInfo.size();
		nRet += bufMgr.PutInt(nVecSize);
		for (int nA = 0; nA < nVecSize; nA ++)
		{
			nRet += bufMgr.PutInt(m_vecInfo[nA].m_nAnchorId);
			nRet += bufMgr.PutChar(m_vecInfo[nA].m_nAction);
			nRet += bufMgr.PutString(m_vecInfo[nA].m_strName);
			int nChannelNum = m_vecInfo[nA].m_vecChannel.size();
			nRet += bufMgr.PutInt(nChannelNum);
			for (int nB = 0; nB < nChannelNum; nB ++)
			{
				nRet += bufMgr.PutInt(m_vecInfo[nA].m_vecChannel[nB]);
			}
		}
		return nRet;
	}

	int GetSize()
	{
		int nLen = 0;
		nLen += sizeof(m_cResult);
		nLen += sizeof(int) + m_strSession.length();
		nLen += sizeof(m_nTotalNum);
		int nVecSize = m_vecInfo.size();
		nLen += sizeof(nVecSize);
		for (int nA = 0; nA < nVecSize; nA ++)
		{
			nLen += sizeof(m_vecInfo[nA].m_nAnchorId);
			nLen += sizeof(m_vecInfo[nA].m_nAction);
			nLen += sizeof(int) + m_vecInfo[nA].m_strName.length();
			int nChannelNum = m_vecInfo[nA].m_vecChannel.size();
			nLen += sizeof(nChannelNum);
			for (int nB = 0; nB < nChannelNum; nB ++)
			{
				nLen += sizeof(m_vecInfo[nA].m_vecChannel[nB]);
			}
		}
		return nLen;
	}
};

class CPingCmd: public CDecodeCmd<TCmdHead, TPing>
{
public:
	CPingCmd(char* pBuf, int nLen) : CDecodeCmd<TCmdHead, TPing>(pBuf, nLen){}
	virtual ~CPingCmd(){}

protected:
	int ProcessCmd();
private:
};

class CPingCmdRes: public CEncodeCmd<TCmdHead, TPingRes>
{
public:
	CPingCmdRes(CPingCmd &cmdReq, int nTotalNum, const vector<TAnchorInfo> &vecInfo, int nResult);
	virtual ~CPingCmdRes(){}
protected:
	int ProcessCmd();
private:
};

#endif

