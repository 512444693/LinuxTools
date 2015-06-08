/**
*    @file       utils.cpp
*
*    @brief      
*    @details    
*
*    @version    1.0
*    @date       2015/4/25
*
*    @author     zhangjiaxing, zhangjiaxing@baofeng.com
*/
#include <errno.h>
#include <sys/time.h>
#include <string>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "utils.h"
#include <sys/time.h>
#include <sys/times.h>
#include "mybasecmd.h"
#include "framecommon/framecommon.h"

unsigned int Utils::IPStr2Int(string strIp)
{
	return inet_addr(const_cast<char*>(strIp.c_str()));
}

string Utils::IPInt2Str(unsigned int nIp)
{
	struct in_addr addr1;
	addr1.s_addr = nIp;
	string retStr = inet_ntoa(addr1);
	return retStr;
}

string Utils::GetGMTTime()
{
	char psDateTime[50];
	const char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	const char *wMon[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	int iYear, iMonth, iDay, iWay, iHour, iMin, iSec;
	struct tm *ptmstu;
	time_t lSecd;
	time(&lSecd);
	ptmstu = gmtime(&lSecd);

	iYear = ptmstu->tm_year+1900;
	iMonth = ptmstu->tm_mon;
	iDay = ptmstu->tm_mday;
	iWay = ptmstu->tm_wday;
	iHour = ptmstu->tm_hour;
	iMin = ptmstu->tm_min;
	iSec = ptmstu->tm_sec;

	snprintf(psDateTime, sizeof(psDateTime), "%s, %02d %s %d %02d:%02d:%02d %s", wday[iWay], iDay, wMon[iMonth], iYear, iHour, iMin, iSec, "GMT");
	return string(psDateTime);
}

string Utils::GetSessionId(char *pBuf, int nBufLen)
{
	if (pBuf == NULL || nBufLen < TCmdHead::HEAD_LEN)
	{
		return string("");
	}
	int nLen;
	memcpy(&nLen, pBuf + TCmdHead::HEAD_LEN, sizeof(nLen));
	nLen = ntohl(nLen);
	if (nLen != 40)
	{
		return string("");
	}

	return string(pBuf + TCmdHead::HEAD_LEN + sizeof(nLen), nLen);
}
