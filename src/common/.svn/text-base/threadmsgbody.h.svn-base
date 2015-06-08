/**
*    @file       threadmsgbody.h
*
*    @brief      
*    @details    
*
*    @version    1.0
*    @date       2014/10/25
*
*    @author     zhangjiaxing, zhangjiaxing@baofeng.com
*/
#ifndef __THREADMSGBODY_H__
#define __THREADMSGBODY_H__

#include "framecommon/framecommon.h"
#include "commmsg.h"

using namespace std;
using namespace MYFRAMECOMMON;

class CSessionMsgBody : public CMsgBody
{
public:
	CSessionMsgBody(const TUserInfo &tUserInfo, char *pBuf, int nBufLen)
	{
		m_tUserInfo = tUserInfo;
		m_pBuf = pBuf;
		m_nBufLen = nBufLen;
	}

	~CSessionMsgBody()
	{
		if (m_pBuf != NULL)
		{
			delete [] m_pBuf;
		}
	}

	void DetachBuf()
	{
		m_pBuf = NULL;
	}

	char *GetBuf()
	{
		return m_pBuf;
	}

	TUserInfo& GetInfo()
	{
		return m_tUserInfo;
	}

	int Size()
	{
		return m_nBufLen;
	}

	CMsgBody *Clone()
	{
		return NULL;
	}

public:
	TUserInfo m_tUserInfo;
	char *m_pBuf;
	int m_nBufLen;
};

#endif //__THDMSGBODY_H__

