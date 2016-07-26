/**
 * @file StringHelper.h �ַ������ú�������
 *
 * ����        ����        ����
 * 2016/07/20  gxl		   create 
 */
#ifndef G_STRINGHELPER_H_
#define G_STRINGHELPER_H_

#include <sstream>
#include <string>
#include <vector>
#include <regex>

#include "hashtool/hi_md5.h"
using namespace std;

/**
 * @brief �ַ������ú���������
 */
class CStringHelper
{
public:
	CStringHelper(){}
	~CStringHelper(){}

public:
	/**
	 * @brief ���ݵ����ָ����������ַ���
     * 
     * @param chStr[in]      ���ָ���ַ���
     * @param cSeparator[in] �ָ��
     * @param strList[out]   ���صĽ����
     *
     * @code
       int main(int argc, char* argv[])
        {
            vector<string> m_StrList;
            CStringHelper::GetSubStringBySingleSeparator("$123$���ĵ�����$fdff$233",'$',m_StrList);

            for(auto str : m_StrList)
            {
                cout << str << endl;
            }

            ::system("pause");
            return 0;
        }
     * @endcode
	 */
	static void GetSubStringBySingleSeparator(char* chStr, char cSeparator, vector<string> &strList)
	{
		strList.clear();

		string cWaitAnalyStr = chStr;

		string::size_type nLen = cWaitAnalyStr.length();
		string::size_type nEndPos = cWaitAnalyStr.find(cSeparator);

		while (nLen != 0 && nEndPos != -1)
		{
			string cSubStr = cWaitAnalyStr.substr(0, nEndPos);
			cWaitAnalyStr = cWaitAnalyStr.substr(nEndPos + 1, nLen - nEndPos - 1);

			strList.push_back(cSubStr);

			nLen -= nEndPos + 1;
			nEndPos = cWaitAnalyStr.find(cSeparator);
		}
	}    

	/**
	 * @brief �ж��ַ����Ƿ�ȫΪ�������
	 *
	 * ����ʹ��c++11�����ԣ�������ȷ��������֧�֣������ı�������GCC-4.9.0����VS2013���°汾������������ʹ�ã�
	 *
	 * @param chStr[in]      ��У����ַ���
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {    
	     bool bRet = CStringHelper::IsNumberString("123");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsNumberString(const char* chStr)
	{
		regex pattern("^[0-9]*$");
		return regex_match(chStr, pattern);
	}

	/**
	 * @brief �ж��ַ����Ƿ�Ϊ�Ϸ���e_mail��ַ
	 *
	 * ����ʹ��c++11�����ԣ�������ȷ��������֧�֣������ı�������GCC-4.9.0����VS2013���°汾������������ʹ�ã�
	 *
	 * @param chStr[in]      ��У����ַ���
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRet = CStringHelper::IsEmailString("931047642@qq.com");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsEmailString(const char* chStr)
	{
		regex pattern("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
		return regex_match(chStr, pattern);
	}

	/**
	 * @brief �ж��ַ����Ƿ�Ϊ�Ϸ��Ĺ̶��绰����
	 *
	 * ����ʹ��c++11�����ԣ�������ȷ��������֧�֣������ı�������GCC-4.9.0����VS2013���°汾������������ʹ�ã�
	 *
	 * @param chStr[in]      ��У����ַ���
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRet = CStringHelper::IsFixedNumberString("0513-12345678");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsFixedNumberString(const char* chStr)
	{
		regex pattern("^(\\d{3}-\\d{8}|\\d{4}-\\d{7}|\\d{4}-\\d{8})$");
		return regex_match(chStr, pattern);
	}

	/**
	 * @brief �ж��ַ����Ƿ�Ϊ�Ϸ��ֻ�����
	 *
	 * ����ʹ��c++11�����ԣ�������ȷ��������֧�֣������ı�������GCC-4.9.0����VS2013���°汾������������ʹ�ã�
	 *
	 * @param chStr[in]      ��У����ַ���
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRet = CStringHelper::IsMobileNumberString("13588881234");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsMobileNumberString(const char* chStr)
	{
		regex pattern("^(13[0-9]|14[5|7]|15[0|1|2|3|5|6|7|8|9]|18[0|1|2|3|5|6|7|8|9])\\d{8}$");
		return regex_match(chStr, pattern);
	}

	/**
	 * @brief �ж��ַ����Ƿ�Ϊ��ʱ���ַ���ʽ(yyyy-mm-dd hh:mm:ss)
	 *
	 * ����ʹ��c++11�����ԣ�������ȷ��������֧�֣������ı�������GCC-4.9.0����VS2013���°汾������������ʹ�ã�
	 *
	 * @param chStr[in]      ��У����ַ���
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRet = CStringHelper::IsLongTimeString("2016-07-25 10:00:00");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsLongTimeString(const char* chStr)
	{
		regex pattern("^\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}$");
		return regex_match(chStr, pattern);
	}

	/**
	 * @brief �ж��ַ����Ƿ�Ϊ�Ϸ�IP��ַ
	 *
	 * ����ʹ��c++11�����ԣ�������ȷ��������֧�֣������ı�������GCC-4.9.0����VS2013���°汾������������ʹ�ã�
	 *
	 * @param chStr[in]      ��У����ַ���
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     bool bRet = CStringHelper::IsIPString("127.0.0.1");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static bool IsIPString(const char* chStr)
	{
		regex pattern("^((?:(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d)\\.){3}(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d))$");
		return regex_match(chStr, pattern);
	}

	/**
	 * @brief ʹ��MD5�㷨ת���ַ���
	 *
	 * @param chStr[in]  ��ת�����ַ���
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     string str = CStringHelper::Md5String("abc");

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static string Md5String(const char* chStr)
	{
		HL_MD5_CTX ctx;
		MD5 md5;
		md5.MD5Init(&ctx);
		md5.MD5Update(&ctx, (unsigned char*)chStr, strlen(chStr));

		unsigned char buff[16] = "";
		md5.MD5Final((unsigned char*)buff, &ctx);

		std::ostringstream os;
		for (int i = 0; i < 16; ++i)
		{
			os.width(2);
			os.fill('0');
			os << std::hex << static_cast<unsigned int>(buff[i]);
		}

		return os.str();
	}
};

#endif // G_STRINGHELPER_H_