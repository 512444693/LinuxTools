/**
 *    @file       userhashtable.h
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __USERINFOTABLE_H__
#define __USERINFOTABLE_H__
#include <string>
#include <list>
#include <map>
#include <time.h>

#include "commmsg.h"
#include "framecommon/framecommon.h"
#include "mxrmessagedef.h"

using namespace std;
using namespace MYFRAMECOMMON;

class CUserHashTable : public CMyHashTable<TUserInfo, list<TUserInfo> >
{
public:
	/**
	* @brief constructor
	*/
	CUserHashTable(int nHashBucketLen);

	/**
	* @brief destructor
	*/
	~CUserHashTable();
public:
	/**
	* @brief init
	*/
	int Init();

	/**
	* @brief add user info to hash
	* @param[in] tUserInfo user info
	* @return 1, ok; 0 exist
	*/
	int UpdateItem(const TUserInfo &tUserInfo);

	/**
	* @brief find user info
	* @param[in] tUserInfo user info
	* @return 1, succeed; 0 fail
	*/
	int Find(const TUserInfo &tUserInfo) const;

	/**
	 * @brief get all user info
	 * @param[in] vecUserInfo all user info
	 * @return 1, ok; 0 exist
	 */
	int GetAllUser(vector<TUserInfo> &vecUserInfo);

	/**
	 * @brief check user time out
	 */
	int CheckTimeOut();

	/**
	* @brief print user info in hash
	*/
	void Print();

	/**
	* @brief get hash length
	* @return hash length, succeed
	*/
	int GetHashLength()
	{
		return m_nHashBucketLen;
	}
};

#endif

