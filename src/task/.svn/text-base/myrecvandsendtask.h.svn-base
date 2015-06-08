/**
 *    @file       myrecvandsendtask.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __MYRECVANDSENDTASK_H__
#define __MYRECVANDSENDTASK_H__

#include "recvandsendtask.h"
#include "netprocessthread.h"

class CMyRecvAndSendTask: public CRecvAndSendTask
{
public:
	/**
	* @brief constructor
	* @param[in] pWorkThread this task will work in this thread
	* @param[in] pSocket this task will use this tcp socket
	*/
	CMyRecvAndSendTask(CTcpSocket *pSocket, CNetProcessThread *pWorkThread);

	/**
	 * @brief destructor
	 */
	virtual ~CMyRecvAndSendTask();

	/**
	 * @brief init task
	 * @return 0, succeed; otherwise, fail
	 */
	virtual int Init();

	/**
	 * @brief delete task
	 * @return 0
	 */
	virtual int DestroySelf();

	/**
	 * @brief put msg to send list
	 * @return 0, succeed; otherwise, fail
	 */
	virtual int PutMsgToSendList(const char *pBuf, int nLen);

protected:
	/**
	 * @brief add task to epoll
	 * @return 0, succeed; otherwise, fail
	 */
	int AddToEpoll();

	/**
	 * @brief recv process
	 * @return 0, succeed; otherwise, fail
	 */
	virtual int RecvProcess();

	/**
	 * @brief send process
	 * @return 0, succeed; otherwise, fail
	 */
	virtual int SendProcess();

	/**
	 * @brief process recv packet
	 * @return 0, succeed; otherwise, fail
	 */
	int ProcessPacket();
private:
	enum State
	{
		ReadPacketHead = 0,
		ReadPacket = 1
	};
	State m_state;/**< receive state */
	char *m_recvBuff;/**< receive buffer */
	int m_nReceiveSize;/**< receive buffer length */
	int m_nReceiveLeft;/**< buffer left to receive */
};

#endif
