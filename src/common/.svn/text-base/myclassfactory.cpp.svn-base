/**
 *    @file       myclassfactory.cpp
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "mxrmessage.h"
#include "myclassfactory.h"
#include "myudprecvthread.h"
#include "myudpprocessthread.h"
#include "myrecvandsendthread.h"
#include "myrecvandsendtask.h"
#include "sessionprocessthread.h"
#include "ontimethread.h"
#include "mxrmessagedef.h"
#include "shortlistentask.h"
#include "listensthread.h"
#include "httpprocesstask.h"

CMyClassFactory::CMyClassFactory()
{
}

CMyClassFactory::~CMyClassFactory()
{
}

CWorkThread *CMyClassFactory::GenWorkThread(int nEntityType , int nEntityId , string sAnnexData , void *arg/* =NULL */)
{
	CWorkThread *pWorkThread = NULL;
	CMxrMessage *pServer = (CMxrMessage*)CMyserver::GetInstance();
	if(!pServer)
	{
		return pWorkThread;
	}
	CBaseConf &BaseConf = pServer->GetBaseConf();
	switch(nEntityType)
	{
		case ENTITYTYPE_LISTENS:
			{
				CNewBufMgr bufAddrs(sAnnexData);
				bufAddrs.SetIfNetTrans(0);
				int nAddrsCounts = 0;
				if( bufAddrs.GetInt(nAddrsCounts) == -1)
				{
					return NULL;
				}
				
				vector<TSocketAddr> vecAddrs;
				for(int i = 0; i < nAddrsCounts; i++)
				{
					TSocketAddr SocketAddr;
					bufAddrs.GetString(SocketAddr.m_strHost);
					bufAddrs.GetShort(SocketAddr.m_nPort);
					bufAddrs.GetInt(SocketAddr.m_nTaskType);
					vecAddrs.push_back(SocketAddr);
				}

				TListensBlock *pListensBlock = NULL;
				if (arg == NULL)
				{
					pListensBlock = new TListensBlock(nAddrsCounts);
				}
				else
				{
					pListensBlock = (TListensBlock*)arg;
				}
				pWorkThread = new CListensThread(nEntityType, nEntityId, vecAddrs, pListensBlock);
				break;
			}
		case ENTITYTYPE_UDPPROCESS:
			{
				pWorkThread = new CMyUdpProcessThread(nEntityType, nEntityId, BaseConf.GetConfigItem().sServerAddr, BaseConf.GetConfigItem().nUdpPort);
				break;
			}
		case UDPRECVENTITY:
			{
				pWorkThread = new CMyUdpRecvThread(nEntityType, nEntityId, (CUdpCommonSock*)arg);
				break;
			}
		case ENTITYTYPE_SESSION_PROCESS:
			{
				pWorkThread = new CSessionProcessThread(nEntityType, nEntityId);
				break;
			}
		case RECVANDSENDMSGENTITY:
			{
				pWorkThread = new CMyRecvAndSendThread(nEntityType, nEntityId);
				break;
			}
		case ENTITYTYPE_ONTIME:
			{
				pWorkThread = new COnTimeThread(nEntityType, nEntityId);
				break;
			}
		default:
			{
				pWorkThread = CClassFactory::GenWorkThread(nEntityType, nEntityId, sAnnexData, arg);
				break;
			}
	}
	return pWorkThread;
}

CSocketTask* CMyClassFactory::GenSocketTask(CNetProcessThread* pWorkThread, CTcpSocket* pTcpSocket, int nTaskType, CTaskArg* pTaskArg /* = NULL */)
{
	CSocketTask* pSocketTask = NULL;
	switch (nTaskType)
	{
		case TASKTYPE_SHORTLISTEN:
			{
				pSocketTask = new CShortListenTask(pTcpSocket, pWorkThread, TASKTYPE_SHORTLISTEN, MSGTYPE_SHORT_CONNECT);
				break;
			}
		case TASKTYPE_HTTPLISTEN:
			{
				pSocketTask = new CShortListenTask(pTcpSocket, pWorkThread, TASKTYPE_HTTPLISTEN, MSGTYPE_HTTP_CONNECT);
				break;
			}
		case TASKTYPE_HTTP_CONNECT:
			{
				pSocketTask = new CHttpProcessTask(pTcpSocket, pWorkThread);
				break;
			}
		case TASKTYPE_SHORT_CONNECT:
			{
				pSocketTask = new CMyRecvAndSendTask(pTcpSocket, pWorkThread);
				break;
			}
		default:
			{
				pSocketTask = CClassFactory::GenSocketTask(pWorkThread, pTcpSocket, nTaskType);
				break;
			}
	}
	return pSocketTask;
}


