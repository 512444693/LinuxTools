/**
 *    @file       myudprecvthread.cpp
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "framecommon/framecommon.h"
#include "myudprecvthread.h"
#include "mxrmessagedef.h"
#include "mxrmessage.h"
#include "mybasecmd.h"

using namespace MYFRAMECOMMON;

CMyUdpRecvThread::CMyUdpRecvThread(int nEntityType, int nEntityId, CUdpCommonSock* pUdpRecvSocket)
	:CUdpRecvThread(nEntityType, nEntityId, pUdpRecvSocket)
{
}

CMyUdpRecvThread::~CMyUdpRecvThread()
{
	if (m_pUdpSocket != NULL)
	{
		delete m_pUdpSocket;
	}
}

int CMyUdpRecvThread::Run()
{
	int nRecvLen = 0;
	while(m_nRunFlag)
	{
		nRecvLen = m_pUdpSocket->UdpRecv(m_pUdpSocket->GetSocket(), m_RecvBuf, MAX_UDP_RECV_PACKET_LEN, m_pUdpSocket->GetCurSrcAddr());
		if(nRecvLen > 0)
		{
			char *pTmpBuf = new char[nRecvLen];
			memcpy(pTmpBuf, m_RecvBuf, nRecvLen);

			CUdpCommonBufMsgBody * pUdpBufMsgBody = new CUdpCommonBufMsgBody(pTmpBuf, nRecvLen, m_pUdpSocket->GetSocket(), ntohl(m_pUdpSocket->GetCurSrcAddr().sin_addr.s_addr), ntohs(m_pUdpSocket->GetCurSrcAddr().sin_port));
			SendMsg(ENTITYTYPE_UDPPROCESS, -1, 0 ,UDPCLIENTMSG, pUdpBufMsgBody, 0);
		}
	}

	return 0;
}


