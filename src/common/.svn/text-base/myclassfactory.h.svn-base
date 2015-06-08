/**
 *    @file       myclassfactory.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __MYLASSFACTORY_H__
#define __MYLASSFACTORY_H__

#include "framecommon/framecommon.h"
#include "classfactory.h"

using namespace MYFRAMECOMMON;

class CMyClassFactory : public CClassFactory
{
public:
	/**
	 * @brief constructor
	 */
	CMyClassFactory();

	/**
	 * @brief destructor
	 */
	~CMyClassFactory();
	public:
	/**
	 * @brief create work thread according to entity type.
	 * @param[in] nEntityType thread type
	 * @param[in] nEntityId thread id
	 * @param[in] sAnnexData some argument such as listen ip and port
	 * @param[in] arg some argument
	 * @return not null, succee; nul, fail
	 */
	virtual CWorkThread *GenWorkThread(int nEntityType , int nEntityId , string sAnnexData , void *arg=NULL);

	/* *
	 * @brief create socket task according to task type.
	 * @param[in] pWorkThread this task will work in this thread
	 * @param[in] pTcpSocket this task will use this tcp socket
	 * @param[in] nTaskType task type
	 * @param[in] pTaskArg some argument
	 * @return not null, succee; nul, fail
	 */
	virtual CSocketTask* GenSocketTask(CNetProcessThread* pWorkThread, CTcpSocket* pTcpSocket, int nTaskType, CTaskArg* pTaskArg = NULL);
};

#endif


