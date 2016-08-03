/**
 * @file FileHelper.h �ļ����ô���������
 *
 * ����        ����        ����
 * 2016/07/20  gxl         create
 */
#ifndef G_FILEHELPER_H_
#define G_FILEHELPER_H_

#include <string>

#include <windows.h>
#include <dbghelp.h> 

#pragma comment(lib, "version.lib")

/**
 * @brief �ļ������ú���������
 */
class CFileHelper
{
public:
	/**
	 * @brief ��ȡ�ļ��汾���������ʾ����v1.0.0.1
	 *
	 * @param cFileName[in]  �ļ�·��
	 *
	 * @return �汾�����ַ�
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string cVersion = CFileHelper::GetFileVersionString("D:\\WorkSpace\\ZCMsgService\\Release\\ZCMsgService.exe");
	     cout << cVersion << endl;

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string GetFileVersionString(char* cFileName)
	{
		string verString("unknown");

		DWORD dwHandle;
		int size = GetFileVersionInfoSize(cFileName, &dwHandle);
		if (size > 0)
		{
			byte *pBuffer = new byte[size];
			if (GetFileVersionInfo(cFileName, dwHandle, size, pBuffer))
			{
				VS_FIXEDFILEINFO *pVI = NULL;
				if (VerQueryValue(pBuffer, "\\", (LPVOID*)&pVI, (PUINT)&size))
				{
					char szVer[64] = { 0 };
					sprintf_s(szVer, 64, "v%d.%d.%d.%d", HIWORD(pVI->dwFileVersionMS), LOWORD(pVI->dwFileVersionMS),
						HIWORD(pVI->dwFileVersionLS), LOWORD(pVI->dwFileVersionLS));
					verString = szVer;
				}
			}
			delete[] pBuffer;
		}

		return verString;
	}

	/**
	 * @brief ��ȡ��ǰӦ�ó���汾���������ʾ����v1.0.0.1
	 *
	 * @return �汾�����ַ�
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string cVersion = CFileHelper::GetCurrentFileVersionString();
	     cout << cVersion << endl;

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string GetCurrentFileVersionString()
	{
		char fileName[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, fileName, sizeof(fileName));

		return GetFileVersionString(fileName);
	}

	/**
	 * @brief ��ȡ��ǰӦ�ó���·��
	 *
	 * @return ·���ַ���
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string cPath = CFileHelper::GetCurrentFilePath();
	     cout << cPath << endl;

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string GetCurrentFilePath()
	{
		char exeFullPath[MAX_PATH] = {0};
		GetModuleFileName(NULL, exeFullPath, MAX_PATH);

		char *p = strrchr(exeFullPath, '\\');
		if (p)
		{
			*p = '\0';
		}
		string strPath = exeFullPath;
		return strPath;
	}	

	/**
	 * @brief ��ȡ��ǰӦ�ó����ϲ�Ŀ¼
	 *
	 * @param nDeep[in] �ϼ����� 0-�ļ�·���������ļ����ƣ� 1-��ǰĿ¼ 2-�ϲ�Ŀ¼ 3-�ϲ�Ŀ¼���ϲ�Ŀ¼ ����Χʱ���ش��̸�Ŀ¼
	 *
	 * @return ·���ַ���
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string cPath = CFileHelper::GetCurrentFileParentPath(1);
	     cout << cPath << endl;

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string GetCurrentFileParentPath(int nDeep)
	{
		char exeFullPath[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, exeFullPath, MAX_PATH);

		for (int deep = 0; deep < nDeep; ++deep)
		{
			char *p = strrchr(exeFullPath, '\\');
			if (p)
			{
				*p = '\0';
			}
		}

		string strPath = exeFullPath;
		return strPath;
	}
};

#endif // G_FILEHELPER_H_