/**
 * @file SystemHelper.h windowsϵͳ���ú�������
 *
 * ����        ����        ����
 * 2016/07/20  gxl		   create
 */
#pragma once

#include <string>
#include <windows.h>

using namespace std;

/**
 * @brief windowsϵͳ���ú���������
 */
class CSystemHelper
{
public:
	CSystemHelper(){}
	~CSystemHelper(){}

public:
	/**
	 * @brief �жϵ�ǰ�����Ƿ�������
	 *
	 * @param cMutexName[in]  ����������
	 *
	 * @return true-������ false-δ����
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRunning = CSystemHelper::IsRunning("Single.test");
	     if (bRunning){
	         cout << "yes" << endl;
	     } else {
	         cout << "no" << endl;
	     }

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsRunning(const char* cMutexName)
	{
		HANDLE hSingleton = CreateMutexA(NULL, FALSE, cMutexName);
		if ((hSingleton != NULL) && (GetLastError() == ERROR_ALREADY_EXISTS))
		{
			return true;
		}

		return false;
	}	
};