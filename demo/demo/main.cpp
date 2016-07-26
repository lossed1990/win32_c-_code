/**
 * @file main.cpp ʹ��demo
 *
 * ����        ����        ����
 * 2016/07/20  gxl         create 
 */
#include <iostream>

#include "../../SystemHelper.h"
#include "../../FileHelper.h"
#include "../../StringHelper.h"
#include "../../TimeHelper.h"
#include "../../LogHelper.h"
#include "../../DumpHelper.h"
#include "../../TTSHelper.h"

#define TEST_BEGIN(str) SetColor(10,0);(cout<<"====begin "<<(str)<<endl)
#define TEST_FUNC(str) SetColor(15,0);(cout<<"@function>> "<<(str)<<endl)
#define TEST_RES(str) SetColor(15,0);(cout<<"@result>> "<<(str)<<endl<<endl)

using namespace std;

void testSystemHelper();
void testFileHelper();
void testStringHelper();
void testTimeHelper();
void testLogHelper();
void testDumpHelper();
void testTTSHelper();

void SetColor(unsigned short forecolor = 4, unsigned short backgroudcolor = 0)
{
	//SetColor(14,0); //10-�� 11-�� 12-�� 14-�� 15-�� 

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);             //��ȡ���������
	SetConsoleTextAttribute(hCon, forecolor | backgroudcolor); //�����ı�������ɫ
}

int main(int argc, char* argv[])
{
	testSystemHelper();
	testTTSHelper();
	testFileHelper();
	testStringHelper();
	testTimeHelper();
	testLogHelper();
	testDumpHelper();
	
	cout << "������restart���������¿���һ������" <<endl;
	char cParam[32] = { 0 };
	cin >> cParam;
	if (strcmp("restart", cParam) == 0)
	{
		TEST_FUNC("ReStartProcess()");	
		CSystemHelper::ReStartProcess();
		TEST_RES("void");
		exit(0);
	}

	::system("pause");
	return 0;
}

void testSystemHelper()
{
	TEST_BEGIN("testSystemHelper");

	TEST_FUNC("CheckProcessMutex(\"Single.test\")");
	string str = CSystemHelper::CheckProcessMutex("Single.test") ? "������������" : "������δ����";
	TEST_RES(str);

	TEST_FUNC("CheckProcessExist(\"firefox.exe\")");
	str = CSystemHelper::CheckProcessExist("firefox.exe") ? "firefox.exe���̴���" : "firefox.exe���̲�����";
	TEST_RES(str);

	TEST_FUNC("DestoryProcess(\"hh.exe\")");
	CSystemHelper::DestoryProcess("hh.exe");
	TEST_RES("void");

	TEST_FUNC("SetAutoStartup(\"demo\")");
	str = CSystemHelper::SetAutoStartup("demo") ? "�����������ɹ�" : "����������ʧ�ܣ���鿴�Ƿ�û�й���ԱȨ��";
	TEST_RES(str);

	TEST_FUNC("CancelAutoStartup(\"demo\")");
	str = CSystemHelper::CancelAutoStartup("demo") ? "ȡ�����������óɹ�" : "ȡ������������ʧ�ܣ���鿴�Ƿ�û�й���ԱȨ��";
	TEST_RES(str);
	
	
}

void testFileHelper()
{
	TEST_BEGIN("testFileHelper");

	TEST_FUNC("GetFileVersionString(\"demo.exe\")");
	string cResult = CFileHelper::GetFileVersionString("demo.exe");
	TEST_RES(cResult);

	TEST_FUNC("GetCurrentFileVersionString()");
	cResult = CFileHelper::GetCurrentFileVersionString();
	TEST_RES(cResult);

	TEST_FUNC("GetCurrentFilePath()");
	cResult = CFileHelper::GetCurrentFilePath();
	TEST_RES(cResult);

	TEST_FUNC("GetCurrentFileParentPath()");
	cResult = CFileHelper::GetCurrentFileParentPath(5);
	TEST_RES(cResult);
	
}

void testStringHelper()
{
	TEST_BEGIN("testStringHelper");

	TEST_FUNC("GetSubStringBySingleSeparator(\"$123$������$fdff$233$\",'$',m_StrList)");
	vector<string> m_StrList;
	CStringHelper::GetSubStringBySingleSeparator("$123$������$fdff$233$",'$',m_StrList);

	string str("");
	for (auto item : m_StrList){
		str += item + "; ";
	}
	 
	TEST_RES(str);

	TEST_FUNC("IsNumberString(\"123\")");
	str = CStringHelper::IsNumberString(" 123") ? "ȫΪ����" : "��ȫΪ����";
	TEST_RES(str);

	TEST_FUNC("IsEmailString(\"931047642@qq.com\")");
	str = CStringHelper::IsEmailString("931047642@qq.com") ? "�Ϸ������ַ" : "�Ƿ������ַ";
	TEST_RES(str);

	TEST_FUNC("IsFixedNumberString(\"0513-12345678\")");
	str = CStringHelper::IsFixedNumberString("0513-12345678") ? "�Ϸ��̶��绰����" : "�Ƿ��̶��绰����";
	TEST_RES(str);

	TEST_FUNC("IsMobileNumberString(\"13588881234\")");
	str = CStringHelper::IsMobileNumberString("13588881234") ? "�Ϸ��ֻ��绰����" : "�Ƿ��ֻ��绰����";
	TEST_RES(str);

	TEST_FUNC("IsLongTimeString(\"2016-07-25 10:00:00\")");
	str = CStringHelper::IsLongTimeString("2016-07-25 10:00:00") ? "�Ϸ���ʱ���ʽ" : "�Ƿ���ʱ���ʽ";
	TEST_RES(str);

	TEST_FUNC("IsIPString(\"127.0.0.1\")");
	str = CStringHelper::IsIPString("127.0.0.1") ? "�Ϸ�IP��ַ" : "�Ƿ�IP��ַ";
	TEST_RES(str);	

	TEST_FUNC("Md5String(\"abc\")");
	str = CStringHelper::Md5String("abc");
	TEST_RES(str);
	
}

void testTimeHelper()
{

}

void testLogHelper()
{
	TEST_BEGIN("testLogHelper");
	SetColor(15, 0);

	CLogHelper g_LogHelper("");
	g_LogHelper.SetLogToStderr(true);

	//�˴��оٳ��õ�������־��¼��ʽ������ʹ�÷�����������������
	//�ٸ�����־
	LOG(INFO) << "���Ǹ�����־";
	//�ھ�����־
	LOG(WARNING) << "���Ǿ�����־";
	//�۾�����־
	LOG(ERROR) << "���Ǵ�����־";

	TEST_RES("����ʹ�÷�������ο���������");
}

void testDumpHelper()
{
	TEST_BEGIN("testDumpHelper");

	CDumpHelper dumper;
	dumper.SetHandler();

	TEST_RES("���޸�demo���룬����dump������");
	//����������ݣ�����demoʱ������һ��dump�ļ�
	//int* i = NULL;
	//*i = 0;
}

void testTTSHelper()
{
	TEST_BEGIN("testTTSHelper");

	TEST_FUNC("TTSHelper::Instance()->Speak(\"hello world\")");
	TTSHelper::Instance()->Speak("hello world");
	TEST_RES("�������ʱ����ע�����TTSHelper::FreeInstance()�ͷ���Դ");
}