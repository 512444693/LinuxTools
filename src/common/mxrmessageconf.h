/**
 *    @file      mxrmessageconf.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#ifndef __MXRMESSAGECONF_H__
#define __MXRMESSAGECONF_H__

#include <string>
#include "mxrmessagedef.h"
#include "framecommon/framecommon.h"
using namespace MYFRAMECOMMON;
using namespace std;

#define MXRMESSAGECONFFILE "conf/mxrmessage.conf"
const string strFilePath = "conf/crossdomain.xml";

struct TServerInfo
{
	int m_nIp;
	short m_nPort;
	bool m_bFlag;

	TServerInfo()
	{
		m_nIp = 0;
		m_nPort = 0;
		m_bFlag = false;
	}
};

struct TMxrMessageConf
{
	int m_nSessionBucketLen;
	int m_nUserBucketLen;
	int m_nRecvAndSendThreadNum;
	int m_nSessionProcessThreadNum;
	int m_nUdpProcessThreadNum;
	int m_nUdpRecvThreadNum;
	int m_nCheckUserInterval;
	int m_nUserTimeOut;

	int m_nSessionMsgNum;
	short m_nSessionMsgPort;
	vector<TServerInfo> m_vecIpInfo;
	TSocketAddr m_ShortListenAddr;
	TSocketAddr m_HttpListenAddr;
	string m_strCrossDomain;
};

class CMxrMessageConf
{
public:
	CMxrMessageConf();
	~CMxrMessageConf();

	int Init();
	TMxrMessageConf& GetConf()
	{
		return m_confItem;
	}
	int GetCrossString(string &strCrossDomain);
private:
	int ReadCrossFile();
	void Print();
private:
	TMxrMessageConf m_confItem;
};

#endif


