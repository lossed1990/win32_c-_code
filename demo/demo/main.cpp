/**
 * @file main.cpp 使用demo
 *
 * 日期        作者        描述
 * 2016/07/20  gxl         create 
 */
#include <iostream>

#include "../../SystemHelper.h"
#include "../../FileHelper.h"
#include "../../StringHelper.h"
#include "../../TimeHelper.h"
#include "../../LogHelper.h"
#include "../../DumpHelper.h"

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

void SetColor(unsigned short forecolor = 4, unsigned short backgroudcolor = 0)
{
	//SetColor(14,0); //10-绿 11-蓝 12-红 14-黄 15-白 

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);             //获取缓冲区句柄
	SetConsoleTextAttribute(hCon, forecolor | backgroudcolor); //设置文本及背景色
}

int main(int argc, char* argv[])
{
	testSystemHelper();
	testFileHelper();
	testStringHelper();
	testTimeHelper();
	testLogHelper();
	testDumpHelper();

	cout << "请输入restart，测试重新开启一个程序" <<endl;
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
	string str = CSystemHelper::CheckProcessMutex("Single.test") ? "本程序已运行" : "本程序未运行";
	TEST_RES(str);

	TEST_FUNC("CheckProcessExist(\"firefox.exe\")");
	str = CSystemHelper::CheckProcessExist("firefox.exe") ? "firefox.exe进程存在" : "firefox.exe进程不存在";
	TEST_RES(str);

	TEST_FUNC("DestoryProcess(\"hh.exe\")");
	CSystemHelper::DestoryProcess("hh.exe");
	TEST_RES("void");

	TEST_FUNC("SetAutoStartup(\"demo\")");
	str = CSystemHelper::SetAutoStartup("demo") ? "设置自启动成功" : "设置自启动失败，请查看是否没有管理员权限";
	TEST_RES(str);

	TEST_FUNC("CancelAutoStartup(\"demo\")");
	str = CSystemHelper::CancelAutoStartup("demo") ? "取消自启动设置成功" : "取消自启动设置失败，请查看是否没有管理员权限";
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

	TEST_FUNC("GetSubStringBySingleSeparator(\"$123$第三方$fdff$233$\",'$',m_StrList)");
	vector<string> m_StrList;
	CStringHelper::GetSubStringBySingleSeparator("$123$第三方$fdff$233$",'$',m_StrList);

	string str("");
	for (auto item : m_StrList){
		str += item + "; ";
	}
	 
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

	//此处列举常用的三种日志记录方式，更多使用方法，请查阅相关资料
	//①跟踪日志
	LOG(INFO) << "这是跟踪日志";
	//②警告日志
	LOG(WARNING) << "这是警告日志";
	//③警告日志
	LOG(ERROR) << "这是错误日志";

	TEST_RES("更多使用方法，请参考网上资料");
}

void testDumpHelper()
{
	TEST_BEGIN("testDumpHelper");

	CDumpHelper dumper;
	dumper.SetHandler();

	TEST_RES("请修改demo代码，测试dump的生成");
	//添加以下内容，运行demo时将生成一个dump文件
	//int* i = NULL;
	//*i = 0;
}

