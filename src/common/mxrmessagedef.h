/**
 *    @file       mxrmessagedef.h
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __MXRMESSAGEDEF_H__
#define __MXRMESSAGEDEF_H__
#include <limits.h>
#include "utils.h"
#include "framecommon/framecommon.h"

const int LISTEN_TASK_NUM = 2;
const int RECV_BUF_LEN = 40960;
const int MXRMESSAGE_VERSION = 94;
const int MXR_GCID_LEN = 40;
const string CROSS_FILENAME = "crossdomain.xml";

///log type : [10-99]
const int DEBUG_LOG_TYPE = 10;

///cmd id
const int CMDID_ANCHOR = 52;
const int CMDID_ANCHOR_RES = 53;
const int CMDID_PING = 54;
const int CMDID_PING_RES = 55;
const int CMDID_USER_NOTICE = 56;
const int CMDID_GET = 58;
const int CMDID_GET_RES = 59;
const int CMDID_GETLIST = 60;
const int CMDID_GETLIST_RES = 61;

///thread type : [10-99]
const int ENTITYTYPE_LISTENS = 10;
const int ENTITYTYPE_HTTPPROCESS = 12;
const int ENTITYTYPE_UDPPROCESS = 15;
const int ENTITYTYPE_ONTIME = 16;
const int ENTITYTYPE_SESSION_PROCESS = 17;

///msg type : [0-999]
const int MSGTYPE_SHORT_CONNECT=12;
const int MSGTYPE_HTTP_CONNECT=13;
const int MSGTYPE_MSG = 59;
const int MSGTYPE_SESSION = 60;
const int MSGTYPE_CHECK_SESSION = 61;
const int MSGTYPE_CMD = 62;
const int MSGTYPE_CMD_RES = 63;
const int MSGTYPE_NOTICE = 64;

///task type
const int TASKTYPE_SHORTLISTEN = 10;
const int TASKTYPE_HTTPLISTEN = 11;
const int TASKTYPE_SHORT_CONNECT =12;
const int TASKTYPE_HTTP_CONNECT = 13;

struct TSocketAddr
{
	string m_strHost;
	short m_nPort;
	int m_nTaskType;
};

enum ESessionType
{
	SESSION_ADD = 0,
	SESSION_DEL = 1,
};

struct TAnchorInfo
{
	unsigned int m_nAnchorId;
	string m_strName;
	char m_nAction;
	vector<unsigned int> m_vecChannel;
	unsigned int m_nLastReportTime;

	enum EAcTion
	{
		ANCHOR_ADD = 0,
		ANCHOR_DEL = 1,
	};

	bool operator==(const TAnchorInfo &tAnchorInfo) const
	{
		return (this->m_nAnchorId == tAnchorInfo.m_nAnchorId);
	}

	TAnchorInfo()
	{
		m_nAnchorId = 0;
		m_nAction = 0;
		m_strName = "";
		m_nLastReportTime = 0;
		m_vecChannel.clear();
	}

	void Print()
	{
		WRITE_ALL_LOG(DEBUG_LOG_TYPE, "anchorid:%d, name:%s, action:%d", m_nAnchorId, m_strName.c_str(), m_nAction);
	}
};

struct TUserInfo
{
	string m_strUnique;
	unsigned int m_nUid;
	unsigned int m_nFarIp;
	unsigned short m_nFarPort;
	unsigned int m_nEntityType;
	unsigned int m_nEntityId;
	unsigned long long m_nTaskId;
	unsigned int m_nLastReportTime;

	unsigned int GetIndex() const
	{
		return CToolKit::shortELFhash(m_strUnique.c_str(), m_strUnique.length());
	}

	bool operator==(const TUserInfo &tUserInfo) const
	{
		return (this->m_strUnique == tUserInfo.m_strUnique);
	}

	void GenUid()
	{
		m_strUnique = Utils::IPInt2Str(ntohl(m_nFarIp)) + ":" + CToolKit::IntToStr(m_nFarPort);
	}

	TUserInfo()
	{
		m_strUnique = "";
		m_nUid = 0;
		m_nFarIp = 0;
		m_nFarPort = 0;
		m_nLastReportTime = 0;
	}

	void Print()
	{
		WRITE_ALL_LOG(DEBUG_LOG_TYPE, "user:%s, uid:%d, entitytype:%d", m_strUnique.c_str(), m_nUid, m_nEntityType);
	}
};

struct TNoticeInfo
{
	vector<TAnchorInfo> m_vecAnchor;
	vector<TUserInfo> m_vecUser;
};

#endif


