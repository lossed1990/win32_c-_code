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
	//SetColor(14,0); //10-�� 11-�� 12-�� 14-�� 15-�� 

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);             //��ȡ���������
	SetConsoleTextAttribute(hCon, forecolor | backgroudcolor); //�����ı�������ɫ
}

int main(int argc, char* argv[])
{
	testSystemHelper();
	testFileHelper();
	testStringHelper();
	testTimeHelper();
	testLogHelper();
	testDumpHelper();

	::system("pause");
	return 0;
}

void testSystemHelper()
{
	TEST_BEGIN("testSystemHelper");

	TEST_FUNC("IsRunning()");
	string str = CSystemHelper::IsRunning("Single.test") ? "����������" : "����δ����";
	TEST_RES(str);
}

void testFileHelper()
{
	TEST_BEGIN("testFileHelper");

	TEST_FUNC("GetFileVersionString(\"demo.exe\")");
	string cVersion = CFileHelper::GetFileVersionString("demo.exe");
	TEST_RES(cVersion);

	TEST_FUNC("GetCurrentFileVersionString()");
	cVersion = CFileHelper::GetCurrentFileVersionString();
	TEST_RES(cVersion);
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
}

void testTimeHelper()
{

}

void testLogHelper()
{

}

void testDumpHelper()
{

}

