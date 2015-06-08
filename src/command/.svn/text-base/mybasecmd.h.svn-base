/**
 *    @file       mybasecmd.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __MYBASECMD_H__
#define __MYBASECMD_H__

#include "framecommon/framecommon.h"
using namespace std;
using namespace MYFRAMECOMMON;

struct TCmdHead
{
	int m_nProtocolVer;
	int m_nSequence;
	int m_nBodyLen;
	char m_nCmdId;
public:
	TCmdHead()
	{
		m_nProtocolVer = 0;
		m_nSequence = 0;
		m_nBodyLen = 0;
		m_nCmdId = 0;
	}
public:
	enum CmdHead
	{
		HEAD_LEN = 13,
		BODYLEN_OFFSET = 8,
		CMDID_OFFSET = 12,
		EXTRA_BODYLEN = 1
	};

	static char GetCmdId(char* pBuf, int nBufLen)
	{
		if (!pBuf || nBufLen < HEAD_LEN)
		{
			return -1;
		}
		return (char)(*(pBuf + CMDID_OFFSET));
	}

	static int GetBodyLen(char* pBuf, int nBufLen)
	{
		if (!pBuf || nBufLen < HEAD_LEN)
		{
			return -1;
		}
		return htonl(*((int*)(pBuf + BODYLEN_OFFSET)));
	}

	int GetSize()
	{
		return HEAD_LEN;
	}

	int Encode(CBufMgr& BufMgr)
	{
		int nRet = 0;
		nRet += BufMgr.PutInt(m_nProtocolVer);
		nRet += BufMgr.PutInt(m_nSequence);
		nRet += BufMgr.PutInt(m_nBodyLen);
		nRet += BufMgr.PutChar(m_nCmdId);
		return nRet;
	}

	int Decode(CBufMgr& BufMgr)
	{
		if (BufMgr.GetInt(m_nProtocolVer) != 0) {return -1;}
		if (BufMgr.GetInt(m_nSequence) != 0) {return -1;}
		if (BufMgr.GetInt(m_nBodyLen) != 0) {return -1;}
		if (BufMgr.GetChar(m_nCmdId) != 0) {return -1;}
		return 0;
	}

	template<typename TCmdBody>
	void SetBodyLen(TCmdBody& CmdBody)
	{
		m_nBodyLen = EXTRA_BODYLEN + CmdBody.GetSize();
	}

	int GetBufLen()
	{
		return (HEAD_LEN + m_nBodyLen - EXTRA_BODYLEN);
	}
};

template<typename TCmdHead, typename TCmdBody>
class CEncodeCmd
{
public:
	CEncodeCmd() : m_Buf(NULL, 0, 1, 1) {}
	virtual ~CEncodeCmd() {}

public:
	virtual int Process()
	{
		int nRet = 0;
		nRet = ProcessCmd();
		if (nRet == 0)
		{
			m_CmdHead.SetBodyLen(m_CmdBody);
			int nBufLen = m_CmdHead.GetBufLen();
			char* pBuf = new char[nBufLen];
			memset(pBuf, 0, nBufLen);
			m_Buf.AttachBuf(pBuf, nBufLen);
			nRet += m_CmdHead.Encode(m_Buf);
			nRet += m_CmdBody.Encode(m_Buf);
		}
		return nRet;
	}

	char* GetBuf() {return m_Buf.GetBuf();}
	int GetBufLen() {return m_Buf.GetBufLen();}
	void AttachBuf(char* pBuf, int nBufLen)
	{
		m_Buf.AttachBuf(pBuf, nBufLen);
	}
	void DetachBuf() {m_Buf.DistachBuf();}
	TCmdHead& GetCmdHead() {return m_CmdHead;}
	TCmdBody& GetCmdBody() {return m_CmdBody;}

protected:
	virtual int ProcessCmd()
	{
		return 0;
	}

protected:
	TCmdHead m_CmdHead;
	TCmdBody m_CmdBody;
	CBufMgr m_Buf;
};

template<typename TCmdHead, typename TCmdBody>
class CDecodeCmd
{
public:
	CDecodeCmd(char* pBuf, int nBufLen) : m_Buf(pBuf, nBufLen, 1, 1){}
	virtual ~CDecodeCmd() {}

public:
	virtual int Process()
	{
		if (m_CmdHead.Decode(m_Buf) != 0)
		{
			WriteRunInfo::WriteError("CDecodeCmd::Process : Decode CmdHead Fail.");
			return -1;
		}
		if (m_CmdBody.Decode(m_Buf) != 0)
		{
			WriteRunInfo::WriteError("CDecodeCmd::Process : Decode CmdBody Fail.");
			return -1;
		}
		return ProcessCmd();
	}

	char* GetBuf() {return m_Buf.GetBuf();}
	int GetBufLen() {return m_Buf.GetBufLen();}
	void AttachBuf(char* pBuf, int nBufLen)
	{
		m_Buf.AttachBuf(pBuf, nBufLen);
	}
	void DetachBuf() {m_Buf.DistachBuf();}
	TCmdHead& GetCmdHead() {return m_CmdHead;}
	TCmdBody& GetCmdBody() {return m_CmdBody;}

protected:
	virtual int ProcessCmd()
	{
		return 0;
	}
protected:
	CBufMgr m_Buf;
	TCmdHead m_CmdHead;
	TCmdBody m_CmdBody;
};

#endif

