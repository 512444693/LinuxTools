/**
 *    @file       mxrmessageconf.cpp
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "mxrmessageconf.h"
#include "mxrmessagedef.h"
#include "utils.h"

CMxrMessageConf::CMxrMessageConf()
{

}
CMxrMessageConf::~CMxrMessageConf()
{

}

int CMxrMessageConf::Init()
{
	string strTmp;
	Magic_Config conf(string(MXRMESSAGECONFFILE));
	int nRet = conf.Init();
	if (nRet != 0)
	{
		WriteRunInfo::WriteLog("Read config file error.");
		return -1;
	}
	
	//session bucket len
	strTmp.clear();
	conf.ReadItem("SERVERINFO", "SessionBucketLen", "10001", strTmp);
	if (strTmp.empty())
	{
		return -1;
	}
	m_confItem.m_nSessionBucketLen = atoi(strTmp.c_str());
	if (m_confItem.m_nSessionBucketLen <= 0)
	{
		WriteRunInfo::WriteError ("invalid SessionBucketLen %d", m_confItem.m_nSessionBucketLen);
		return -1;
	}

	strTmp.clear();
	conf.ReadItem("SERVERINFO", "UserBucketLen", "10001", strTmp);
	if (strTmp.empty())
	{
		return -1;
	}
	m_confItem.m_nUserBucketLen = atoi(strTmp.c_str());
	if (m_confItem.m_nUserBucketLen <= 0)
	{
		WriteRunInfo::WriteError ("invalid UserBucketLen %d", m_confItem.m_nUserBucketLen);
		return -1;
	}

	//Read recv and send thread number
	conf.ReadItem("SERVERINFO", "RecvAndSendThreadNum", "4", strTmp);
	if (strTmp == "")
	{
		WriteRunInfo::WriteLog("Read config file error : RecvAndSendThreadNum error!");
		return -1;
	}
	m_confItem.m_nRecvAndSendThreadNum = atoi(strTmp.c_str());
	if (m_confItem.m_nRecvAndSendThreadNum <= 0)
	{
		WriteRunInfo::WriteLog("Read config file error : RecvAndSendThreadNum error!");
		return -1;
	}

	conf.ReadItem("SERVERINFO", "SessionProcessThreadNum", "4", strTmp);
	if (strTmp == "")
	{
		WriteRunInfo::WriteLog("Read config file error : SessionProcessThreadNum error!");
		return -1;
	}
	m_confItem.m_nSessionProcessThreadNum = atoi(strTmp.c_str());
	if (m_confItem.m_nSessionProcessThreadNum <= 0)
	{
		WriteRunInfo::WriteLog("Read config file error : SessionProcessThreadNum error!");
		return -1;
	}

	strTmp.clear();
	conf.ReadItem("SERVERINFO", "UdpProcessThreadNum", "3", strTmp);
	if (strTmp.empty())
	{
		return -1;
	}
	m_confItem.m_nUdpProcessThreadNum = atoi(strTmp.c_str());
	if (m_confItem.m_nUdpProcessThreadNum <= 0)
	{
		WriteRunInfo::WriteError ("invalid UdpProcessThreadNum %d", m_confItem.m_nUdpProcessThreadNum);
		return -1;
	}

	strTmp.clear();
	conf.ReadItem("SERVERINFO", "UdpRecvThreadNum", "3", strTmp);
	if (strTmp.empty())
	{
		return -1;
	}
	m_confItem.m_nUdpRecvThreadNum = atoi(strTmp.c_str());
	if (m_confItem.m_nUdpRecvThreadNum <= 0)
	{
		WriteRunInfo::WriteError ("invalid nUdpRecvThreadNum %d", m_confItem.m_nUdpRecvThreadNum);
		return -1;
	}

	strTmp.clear();
	conf.ReadItem("SERVERINFO", "CheckUserInterval", "60", strTmp);
	if (strTmp.empty())
	{
		return -1;
	}
	m_confItem.m_nCheckUserInterval = atoi(strTmp.c_str());
	if (m_confItem.m_nCheckUserInterval <= 0)
	{
		WriteRunInfo::WriteError ("invalid CheckUserInterval %d", m_confItem.m_nCheckUserInterval);
		return -1;
	}

	strTmp.clear();
	conf.ReadItem("SERVERINFO", "UserTimeOut", "300", strTmp);
	if (strTmp.empty())
	{
		return -1;
	}
	m_confItem.m_nUserTimeOut = atoi(strTmp.c_str());
	if (m_confItem.m_nUserTimeOut <= 0)
	{
		WriteRunInfo::WriteError ("invalid UserTimeOut %d", m_confItem.m_nUserTimeOut);
		return -1;
	}

	strTmp.clear();
	conf.ReadItem("SESSIONMSGINFO", "SessionMsgNum", "", strTmp);
	if (strTmp.empty())
	{
		return -1;
	}
	m_confItem.m_nSessionMsgNum = atoi(strTmp.c_str());
	if (m_confItem.m_nSessionMsgNum <= 0)
	{
		return -1;
	}

	strTmp.clear();
	conf.ReadItem("SESSIONMSGINFO", "SessionMsgPort", "", strTmp);
	if (strTmp.empty())
	{
		return -1;
	}
	m_confItem.m_nSessionMsgPort = atoi(strTmp.c_str());

	m_confItem.m_vecIpInfo.clear();
	for (int i = 0; i < m_confItem.m_nSessionMsgNum; i ++)
	{
		stringstream ss;
		ss << "SESSIONMSG" << i;
		string strIp;
		TServerInfo tServerInfo;
		conf.ReadItem(ss.str().c_str(), "Ip", "", strIp);
		if (strIp == "")
		{
			return -1;
		}
		if(inet_pton(AF_INET, strIp.c_str(), &tServerInfo.m_nIp) > 0)
		{
			tServerInfo.m_nIp = ntohl(tServerInfo.m_nIp);
		}
		else
		{
			tServerInfo.m_nIp = 0;
		}
		tServerInfo.m_nPort = m_confItem.m_nSessionMsgPort;

		
		strTmp.clear();
		conf.ReadItem(ss.str().c_str(), "Flag", "", strTmp);
		if (strTmp.empty())
		{
			return -1;
		}
		if (strTmp == "true")
		{
			tServerInfo.m_bFlag = true;
		}
		m_confItem.m_vecIpInfo.push_back(tServerInfo);
	}

	//Read Short Connect Listen Conf
	int nTmp;
	conf.ReadItem ("SHORTLISTENADDR", "IP", "0.0.0.0", strTmp);
	if(strTmp.empty())
	{
		strTmp = "0.0.0.0";
	}
	if (0 == strTmp.length() || inet_pton (AF_INET, strTmp.c_str(), &nTmp) < 0)
	{
		WriteRunInfo::WriteError ("ReadConf SHORTLISTENADDR->IP fail");
		return -1;
	}
	m_confItem.m_ShortListenAddr.m_strHost = strTmp;
	
	conf.ReadItem ("SHORTLISTENADDR", "PORT", "", strTmp);
	if (0 == strTmp.length())
	{
		WriteRunInfo::WriteError ("ReadConf SHORTLISTENADDR->PORT fail");
		return -1;
	}
	m_confItem.m_ShortListenAddr.m_nPort = atoi(strTmp.c_str());
	
	m_confItem.m_ShortListenAddr.m_nTaskType = TASKTYPE_SHORTLISTEN;
	
	//Read Http Connect Listen Conf
	conf.ReadItem ("HTTPLISTENADDR", "IP", "0.0.0.0", strTmp);
	if(strTmp.empty())
	{
		strTmp = "0.0.0.0";
	}
	if (0 == strTmp.length() || inet_pton (AF_INET, strTmp.c_str(), &nTmp) < 0)
	{
		WriteRunInfo::WriteError ("ReadConf HTTPLISTENADDR->IP fail");
		return -1;
	}
	m_confItem.m_HttpListenAddr.m_strHost = strTmp;

	conf.ReadItem ("HTTPLISTENADDR", "PORT", "", strTmp);
	if (0 == strTmp.length())
	{
		WriteRunInfo::WriteError ("ReadConf HTTPLISTENADDR->PORT fail");
		return -1;
	}
	m_confItem.m_HttpListenAddr.m_nPort = atoi(strTmp.c_str());
	
	m_confItem.m_HttpListenAddr.m_nTaskType = TASKTYPE_HTTPLISTEN;

	nRet = ReadCrossFile();
	if (0 != nRet)
	{
		WriteRunInfo::WriteError("Load crossdomain.xml fail");
		return -1;
	}

	Print();
	return 0;
}

int CMxrMessageConf::ReadCrossFile()
{
	if (access(strFilePath.c_str(), F_OK) != 0)
	{
		WRITE_ALL_LOG(DEBUG_LOG_TYPE, "CMxQueryConf::ReadCrossFile : xml file %s is not exist", strFilePath.c_str());
		return -1;
	}

	struct stat statDb;
	if (stat(strFilePath.c_str(), &statDb) != 0)
	{
		WRITE_ALL_LOG(DEBUG_LOG_TYPE, "CMxQueryConf::ReadCrossFile : stat xml file %s fail", strFilePath.c_str());
		return -1;
	}
	long long nFileSize = statDb.st_size;
	if (nFileSize == 0)
	{
		WRITE_ALL_LOG(DEBUG_LOG_TYPE, "CMxQueryConf::ReadCrossFile : xml file %s is empty", strFilePath.c_str());
		return -1;
	}
	FILE* pFile = fopen(strFilePath.c_str(), "r");
	if (!pFile)
	{
		WRITE_ALL_LOG(DEBUG_LOG_TYPE, "CMxQueryConf::ReadCrossFile : open xml file %s fail", strFilePath.c_str());
		return -1;
	}
	char* pBuf = new char[nFileSize];
	if (fread(pBuf, nFileSize, 1, pFile) != 1)
	{
		WRITE_ALL_LOG(DEBUG_LOG_TYPE, "CMxQueryConf::ReadCrossFile : read xml file %s fail", strFilePath.c_str());
		fclose(pFile);
		delete [] pBuf;
		return -1;
	}
	fclose(pFile);

	m_confItem.m_strCrossDomain.clear();
	m_confItem.m_strCrossDomain.assign(pBuf, nFileSize);
	WRITE_ALL_LOG(DEBUG_LOG_TYPE, "CMxQueryConf::ReadCrossFile : Cross domain string:\n%s", m_confItem.m_strCrossDomain.c_str());
	delete [] pBuf;
	return 0;
}

int CMxrMessageConf::GetCrossString(string &strCrossDomain)
{
	strCrossDomain = m_confItem.m_strCrossDomain;
	return 0;
}

void CMxrMessageConf::Print()
{
	stringstream str;
	str << "[SERVERINFO]" << "\n"
		<< "SessionBucketLen = " << m_confItem.m_nSessionBucketLen << "\n"
		<< "UserBucketLen = " << m_confItem.m_nUserBucketLen << "\n"
		<< "RecvAndSendThreadNum = " << m_confItem.m_nRecvAndSendThreadNum << "\n"
		<< "SessionProcessThreadNum = " << m_confItem.m_nSessionProcessThreadNum << "\n"
		<< "UdpProcessThreadNum = " << m_confItem.m_nUdpProcessThreadNum << "\n"
		<< "UdpRecvThreadNum = " << m_confItem.m_nUdpRecvThreadNum << "\n"
		<< "CheckUserInterval = " << m_confItem.m_nCheckUserInterval << "\n"
		<< "UserTimeOut = " << m_confItem.m_nUserTimeOut << "\n";
	str << "[SESSIONMSGINFO]" << "\n"
		<< "SessionMsgNum = " << m_confItem.m_nSessionMsgNum << "\n"
		<< "SessionMsgPort = " << m_confItem.m_nSessionMsgPort << "\n";
	for (int i = 0; i < m_confItem.m_nSessionMsgNum; i ++)
	{
		str << "[SESSIONMSG" << i << "]" << "\n"
			<< "Ip = " << Utils::IPInt2Str(ntohl(m_confItem.m_vecIpInfo[i].m_nIp)) << "\n";
		if (m_confItem.m_vecIpInfo[i].m_bFlag)
		{
			str << "Flag = true\n";
		}
		else
		{
			str << "Flag = false\n";
		}
	}

	str << "[SHORTLISTENADDR]" << "\n"
		<< "strIp=" << m_confItem.m_ShortListenAddr.m_strHost << "\n"
		<< "port=" << m_confItem.m_ShortListenAddr.m_nPort << "\n"
		<< "type=" << m_confItem.m_ShortListenAddr.m_nTaskType << "\n"
		<< "[HTTPLISTENADDR]" << "\n"
		<< "strIp=" << m_confItem.m_HttpListenAddr.m_strHost << "\n"
		<< "Port=" << m_confItem.m_HttpListenAddr.m_nPort << "\n"
		<< "type=" << m_confItem.m_HttpListenAddr.m_nTaskType << "\n";

	WRITE_ALL_LOG(DEBUG_LOG_TYPE, "----------- configuration ----------------: \n%s ", str.str().c_str());
}


