/**
 * @file SystemHelper.h windowsϵͳ���ú�������
 *
 * ����        ����        ����
 * 2016/07/20  gxl		   create
 */
#pragma once

#include <string>
#include <windows.h>
#include <Tlhelp32.h>

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
	 * @brief ��鵱ǰ���򻥳���
	 *
	 * @param cMutexName[in]  ����������
	 *
	 * @return true-������ false-δ����
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRunning = CSystemHelper::CheckProcessMutex("Single.test");
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
	static bool CheckProcessMutex(const char* cMutexName)
	{
		HANDLE hSingleton = CreateMutexA(NULL, FALSE, cMutexName);
		if ((hSingleton != NULL) && (GetLastError() == ERROR_ALREADY_EXISTS))
		{
			return true;
		}

		return false;
	}	

	/**
	 * @brief �������Ƿ����
	 *
	 * @param cProcessName[in] ��������
	 *
	 * @return true-���� false-������
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bExist = CSystemHelper::CheckProcessExist("demo.exe");
	     if (bExist){
	         cout << "yes" << endl;
	     } else {
	         cout << "no" << endl;
	     }

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool CheckProcessExist(const char* cProcessName)
	{
		bool bRet = false;

		HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			return bRet;
		}

		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		BOOL bMore = Process32First(hProcessSnap, &pe32);
		while (bMore)
		{
			if (strcmp(cProcessName, pe32.szExeFile) == 0 &&
				pe32.th32ProcessID != GetCurrentProcessId())
			{
				bRet = true;
			}
			bMore = ::Process32Next(hProcessSnap, &pe32);
		}
		CloseHandle(hProcessSnap);

		return bRet;
	}
};