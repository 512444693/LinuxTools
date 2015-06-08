/**
 *    @file       anchorcmd.cpp
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "anchorcmd.h"

int CAnchorCmd::ProcessCmd()
{
	return 0;
}

CAnchorCmdRes::CAnchorCmdRes(CAnchorCmd &cmdReq, int nResult)
{
	m_CmdHead.m_nProtocolVer = cmdReq.GetCmdHead().m_nProtocolVer;
	m_CmdHead.m_nSequence = cmdReq.GetCmdHead().m_nSequence;
	m_CmdHead.m_nCmdId = CMDID_ANCHOR_RES;
	m_CmdBody.m_cResult = nResult;
}

int CAnchorCmdRes::ProcessCmd()
{
	return 0;
}


