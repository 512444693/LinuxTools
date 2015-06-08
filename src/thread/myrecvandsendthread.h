/**
 *    @file       myrecvandsendthread.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __MYRECVANDSENDTHREAD_H__
#define __MYRECVANDSENDTHREAD_H__

#include "framecommon/framecommon.h"
#include "netprocessthread.h"
using namespace std;
using namespace MYFRAMECOMMON;

class CMyRecvAndSendThread: public CNetProcessThread
{
public:
	/**
	* @brief constructor
	* @param[in] iEntityType thread type
	* @param[in] iEntityId thread id
	*/
	CMyRecvAndSendThread(int iEntityType, int iEntityId);

	/**
	 * @brief destructor
	 */
	virtual ~CMyRecvAndSendThread();
protected:
private:
	/**
	 * @brief process message
	 * @param[in] pMsg message body
	 * @return 0, succeed; otherwise, fail
	 */
	virtual int Process(CMsg *pMsg);
};

#endif

