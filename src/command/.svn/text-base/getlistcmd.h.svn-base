/**
 *    @file       getlistcmd.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __GETLISTCMD_H__
#define __GETLISTCMD_H__

#include "framecommon/framecommon.h"
#include "mybasecmd.h"
#include "mxrmessagedef.h"
#include "mxrmessageconf.h"

using namespace std;
using namespace MYFRAMECOMMON;

struct TGetList
{
	int Decode(CBufMgr &bufMgr)
	{
		return 0;
	}
};

struct TGetListRes
{
	char m_cResult;
	vector<TServerInfo> m_vecInfo;

	int Encode(CBufMgr& bufMgr)
	{
		int nRet = 0;
		nRet += bufMgr.PutChar(m_cResult);
		int nSize = m_vecInfo.size();
		nRet += bufMgr.PutInt(nSize);
		for (int i = 0; i < nSize; i ++)
		{
			nRet += bufMgr.PutInt(m_vecInfo[i].m_nIp);
			nRet += bufMgr.PutShort(m_vecInfo[i].m_nPort);
		}

		return nRet;
	}

	int GetSize()
	{
		int nLen = 0;
		nLen += sizeof(char);
		int nSize = m_vecInfo.size();
		nLen += sizeof(int);
		for (int i = 0; i < nSize; i ++)
		{
			nLen += sizeof(m_vecInfo[i].m_nIp);
			nLen += sizeof(m_vecInfo[i].m_nPort);
		}

		return nLen;
	}
};

class CGetListCmd: public CDecodeCmd<TCmdHead, TGetList>
{
public:
	CGetListCmd(char* pBuf, int nLen) : CDecodeCmd<TCmdHead, TGetList>(pBuf, nLen){}
	virtual ~CGetListCmd(){}

protected:
	int ProcessCmd();
private:
};

class CGetListCmdRes: public CEncodeCmd<TCmdHead, TGetListRes>
{
public:
	CGetListCmdRes(CGetListCmd &cmdReq, const vector<TServerInfo> &vecInfo);
	virtual ~CGetListCmdRes(){}
protected:
	int ProcessCmd();
private:
};

#endif

