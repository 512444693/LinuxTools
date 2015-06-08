/**
 *    @file       getcmd.cpp
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "getcmd.h"

int CGetCmd::ProcessCmd()
{
	return 0;
}

CGetCmdRes::CGetCmdRes(CGetCmd &cmdReq, int nIp, int nPort)
{
	m_CmdHead.m_nProtocolVer = cmdReq.GetCmdHead().m_nProtocolVer;
	m_CmdHead.m_nSequence = cmdReq.GetCmdHead().m_nSequence;
	m_CmdHead.m_nCmdId = CMDID_GET_RES;
	m_CmdBody.m_cResult = 0;
	m_CmdBody.m_nIp = nIp;
	m_CmdBody.m_nPort = nPort;
}

int CGetCmdRes::ProcessCmd()
{
	return 0;
}


