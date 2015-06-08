/**
*    @file       utils.h
*
*    @brief      
*    @details    
*
*    @version    1.0
*    @date       2015/4/25
*
*    @author     zhangjiaxing, zhangjiaxing@baofeng.com
*/
#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <vector>
using namespace std;

class Utils
{
public:
	static unsigned int IPStr2Int(string strIp);
	static string IPInt2Str(unsigned int nIp);
	static string GetGMTTime();
	static string GetSessionId(char *pBuf, int nBufLen);

	template<class T1>
	static void RemoveFromVec(vector<T1> &vecT1, T1 t1)
	{
		int nNum = vecT1.size();
		vector<T1> vecTmp;
		vecTmp.reserve(nNum);
		for (int nA = 0; nA < nNum; nA ++)
		{
			if (vecT1[nA] != t1)
			{
				vecTmp.push_back(vecT1[nA]);
			}
		}
		vecT1.swap(vecTmp);
	}

private:
};

#endif

