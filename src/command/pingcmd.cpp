/**
 *    @file       pingcmd.cpp
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "pingcmd.h"

int CPingCmd::ProcessCmd()
{
	return 0;
}

CPingCmdRes::CPingCmdRes(CPingCmd &cmdReq, int nTotalNum, const vector<TAnchorInfo> &vecInfo, int nResult)
{
	m_CmdHead.m_nProtocolVer = cmdReq.GetCmdHead().m_nProtocolVer;
	m_CmdHead.m_nCmdId = CMDID_PING_RES;
	m_CmdBody.m_cResult = nResult;
	m_CmdBody.m_strSession = cmdReq.GetCmdBody().m_strSession;
	m_CmdBody.m_vecInfo = vecInfo;
	m_CmdBody.m_nTotalNum = nTotalNum;
}

int CPingCmdRes::ProcessCmd()
{
	return 0;
}


