/**
 *    @file       getlistcmd.cpp
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "getlistcmd.h"

int CGetListCmd::ProcessCmd()
{
	return 0;
}

CGetListCmdRes::CGetListCmdRes(CGetListCmd &cmdReq, const vector<TServerInfo> &vecInfo)
{
	m_CmdHead.m_nProtocolVer = cmdReq.GetCmdHead().m_nProtocolVer;
	m_CmdHead.m_nSequence = cmdReq.GetCmdHead().m_nSequence;
	m_CmdHead.m_nCmdId = CMDID_GETLIST_RES;
	m_CmdBody.m_cResult = 0;
	m_CmdBody.m_vecInfo = vecInfo;
}

int CGetListCmdRes::ProcessCmd()
{
	return 0;
}


