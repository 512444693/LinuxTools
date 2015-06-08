/**
 *    @file       main.cpp
 *
 *    @brief
 *    @details
 *
 *    @version    1.0
 *    @date       2014/10/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include <iostream>
#include "framecommon/framecommon.h"
#include "mxrmessage.h"
#include "mxrmessagedef.h"

using namespace std;
using namespace MYFRAMECOMMON;

int main(int argc, char *argv[])
{
	int nLogFlag = 0;
	if (argc == 2 && strcasecmp(argv[1], "-l") == 0)
	{
		nLogFlag = 1;
	}

	TLogType LogType;
	LogType.nLogtype = DEBUG_LOG_TYPE;
	LogType.nFileNum = 0;
	LogType.nLogOff = nLogFlag;
	strncpy(LogType.sFileNameSuffix, ".debug", sizeof(LogType.sFileNameSuffix));
	WriteRunInfo::LOGTYPEARRAY.InsertLogType(LogType);

	WriteRunInfo::Init("mxrmessage");

	CMxrMessage* pServer = new CMxrMessage;
	CMyserver::SetServer(pServer);
	int nRet = pServer->InitServer();
	if (nRet != 0)
	{
		WriteRunInfo::WriteLog("Server init fail");
		return -1;
	}
	if (pServer->StartServer() != 0)
	{
		WriteRunInfo::WriteLog("Server Start fail");
		return -1;
	}

	WriteRunInfo::WriteLog("Server Start Succ");

	while(1)
	{
		sleep(1000);
	}

	return 0;
}

