/**
 * @file LogHelper.h ��־��¼������
 *
 * ����        ����        ����
 * 2016/07/20  gxl         create
 */
#ifndef G_LOGHELPER_H_
#define G_LOGHELPER_H_

#include<iostream>

#define GLOG_NO_ABBREVIATED_SEVERITIES

#include "glog/logging.h"
#include "glog/raw_logging.h"

#pragma comment(lib,"glog/libglog.lib")
/**
 * @brief ��־��¼������
 * 
 * ������Ҫ��װ�ȸ�glog��־��ĳ�ʼ����������ز�������ʹ�ã�ʹ��ʱ�����glog�ļ���ͷ�ļ�������ʱ�����libglog.dll
 */
class CLogHelper
{
public:
	/**
	 * @breif ��־�����๹�캯��
	 *
	 * @param program[in] �������ƣ����Բ���
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     //ʹ��ʾ���� ʵ����һ������󣬼����ڳ����κεط�ʹ����غ������־�ļ�¼
	     CLogHelper lh("");

	     //�˴��оٳ��õ�������־��¼��ʽ������ʹ�÷�����������������
	     //�ٸ�����־
	     LOG(INFO) << "���Ǹ�����־";
	     //�ھ�����־
	     LOG(WARNING) << "���Ǿ�����־";
	     //�۾�����־
	     LOG(ERROR) << "���Ǵ�����־";

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	CLogHelper(char* program)
	{
		google::InitGoogleLogging(program);

		//std::cout << 1;            //test,�Է���־�������ʱ����ԭ���ݲ���ȷ

		//���ò���
		FLAGS_logbufsecs = 0;      //ˢ����־��Ӳ�̵�ʱ�䣬Ĭ���ǻỺ��ģ�0��ʾʵʱ
		FLAGS_max_log_size = 30;   //��־��С����30Mʱ�������µ���־
		FLAGS_stop_logging_if_full_disk = true;   //Ӳ����ʱֹͣ��¼
		FLAGS_colorlogtostderr = true;            //ͨ����ɫ���ֿ���̨��ͬ�ȼ�����־
		FLAGS_alsologtostderr = false;
	}
	~CLogHelper(){ google::ShutdownGoogleLogging(); }

	/**
	 * @breif �����Ƿ���־���������̨
	 *
	 * ������ͨ��Ӧ�ó��򣬿�����ѡ�������vs������п�����־������ʹ��windbg����ʱ��������־��
	 *
	 * @param bOutput[in] true-��� false-�����
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     CLogHelper lh("");
		 lh.SetLogToStderr(true);

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	void SetLogToStderr(bool bOutput) { FLAGS_alsologtostderr = bOutput; }

	/**
	 * @breif ����Info�������־���·�����������򲻻����ı��ļ���¼
	 *
	 * glogԴ������ļ��в����ڣ��������־��¼��ϵͳtemp�ļ����У�demo��libglog.dll�����޸Ĺ����ļ��в�����ʱ������¼
	 *
	 * @param filepath[in] ����ļ��е�ȫ·��
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     CLogHelper lh("");
	     lh.SetInfoLogDestination("c:/");   //��ע���ļ��в�����ʱ�����ᴴ��

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	void SetInfoLogDestination(const char* filepath) { google::SetLogDestination(google::GLOG_INFO, filepath); }

	/**
	 * @breif ����warning�������־���·�����������򲻻����ı��ļ���¼
	 *
	 * glogԴ������ļ��в����ڣ��������־��¼��ϵͳtemp�ļ����У�demo��libglog.dll�����޸Ĺ����ļ��в�����ʱ������¼
	 *
	 * @param filepath[in] ����ļ��е�ȫ·��
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     CLogHelper lh("");
	     lh.SetWarnLogDestination("c:/");   //��ע���ļ��в�����ʱ�����ᴴ��

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	void SetWarnLogDestination(const char* filepath) { google::SetLogDestination(google::GLOG_WARNING, filepath); }

	/**
	 * @breif ����error�������־���·�����������򲻻����ı��ļ���¼
	 *
	 * glogԴ������ļ��в����ڣ��������־��¼��ϵͳtemp�ļ����У�demo��libglog.dll�����޸Ĺ����ļ��в�����ʱ������¼
	 *
	 * @param filepath[in] ����ļ��е�ȫ·��
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     CLogHelper lh("");
	     lh.SetErrorLogDestination("c:/");   //��ע���ļ��в�����ʱ�����ᴴ��

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	void SetErrorLogDestination(const char* filepath) { google::SetLogDestination(google::GLOG_ERROR, filepath); }
};

#endif // G_LOGHELPER_H_