/**
 *    @file       noticecmd.cpp
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "noticecmd.h"
#include "mxrmessagedef.h"

CNoticeCmd::CNoticeCmd(const vector<TAnchorInfo> &vecAnchor)
{
	m_CmdBody.m_vecAnchor = vecAnchor;
}

int CNoticeCmd::ProcessCmd()
{
	m_CmdHead.m_nProtocolVer = MXRMESSAGE_VERSION;
	m_CmdHead.m_nSequence = rand() % 65536;
	m_CmdHead.m_nCmdId = CMDID_USER_NOTICE;
	return 0;
}

int CNoticeCmdRes::ProcessCmd()
{
	return 0;
}

