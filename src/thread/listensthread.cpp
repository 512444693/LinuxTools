/**
 *    @file       listensthread.cpp
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2015/4/28
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */

#include "listensthread.h"
#include "myserver.h"

CListensThread::CListensThread(int iEntityType, int iEntityId, vector<TSocketAddr>& vecAddrs, TListensBlock *pListenBlock)
	:CNetProcessThread(iEntityType, iEntityId), m_vecAddrs(vecAddrs), m_pListenBlock(pListenBlock)
{
}

CListensThread::~CListensThread()
{
	int nVecSize = m_vecListenTasks.size();
	for(int i = 0; i < nVecSize; i++)
	{
		delete m_vecListenTasks[i];
	}
	m_vecListenTasks.clear();

	nVecSize = m_vecTcpSockets.size();
	for(int i = 0; i < nVecSize; i++)
	{
		delete m_vecTcpSockets[i];
	}
	m_vecTcpSockets.clear();
}

int CListensThread::Init()
{
	if( m_pListenBlock->vecSocks.size() != m_vecAddrs.size() )
	{	
		return -1;
	}
	
	int nRetValue = 0;
	nRetValue = CNetProcessThread::Init();
	if (nRetValue != 0)
	{
		return -1;
	}

	int nSize = m_vecAddrs.size();
	for(int i = 0; i < nSize; i++ )
	{
		m_pListenBlock->mutex.Lock();
		if (m_pListenBlock->vecSocks[i] == -1)
		{
			//生成一个监听句柄
			int nSocket;
			nRetValue = CMySocket::CreateSock(SOCK_STREAM, m_vecAddrs[i].m_strHost, m_vecAddrs[i].m_nPort, nSocket);
			if (nRetValue < 0)
			{
				WriteRunInfo::WriteLog("Create listen sock fail %d", nRetValue);
				m_pListenBlock->mutex.UnLock();
				return -1;
			}
			m_pListenBlock->vecSocks[i] = nSocket;
		}
		m_pListenBlock->mutex.UnLock();

		CTcpSocket* pTcpSocket = new CTcpSocket( m_vecAddrs[i].m_strHost, m_vecAddrs[i].m_nPort, m_pListenBlock->vecSocks[i] );
		if (pTcpSocket == NULL)
		{
			WriteRunInfo::WriteLog("New listen socket object failed at %s:%d", m_vecAddrs[i].m_strHost.c_str(), m_vecAddrs[i].m_nPort);
			return -1;
		}
		WriteRunInfo::WriteLog("New listen socket object at %s:%d", m_vecAddrs[i].m_strHost.c_str(), m_vecAddrs[i].m_nPort);
		m_vecTcpSockets.push_back(pTcpSocket);

		//起监听端口
		CShortListenTask* pListenTask = (CShortListenTask*)CMyserver::GetInstance()->GetClassFactory()->GenSocketTask(this, pTcpSocket,  m_vecAddrs[i].m_nTaskType);

		if (pListenTask == NULL)
		{
			WriteRunInfo::WriteLog("Malloc memory fail or listen fail");
			return -1;
		}
		m_vecListenTasks.push_back(pListenTask);
		
		pListenTask->Init();
	}
	return 0;
}

