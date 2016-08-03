/**
 * @file MonitorHelper.h ��ʾ������������
 *
 * ����        ����        ����
 * 2016/08/03  gxl         create 
 */
#ifndef G_MONITORHELPER_H_
#define G_MONITORHELPER_H_

#include <vector>

typedef struct {
	HMONITOR hMonitor;  ///< ��ʾ�����
	HDC hdcMonitor;     ///< ��ʾ��DC���
	RECT rcMonitor;     ///< ��ʾ�����귶Χ
} G_Monitor_Info, *LPG_Monitor_Info;

/**
 * @brief ��ʾ������������
 *
 * @note 1�������࣬����ȫ��ʹ�ã�
 * @note 2������ʱö��������ʾ�������������
 */
class MonitorHelper
{
private:
	static MonitorHelper* m_pMonitorInst;
	MonitorHelper(void)
	{
		//��ȡӲ����ʾ������
		int nCount = ::GetSystemMetrics(SM_CMONITORS);

		//ö����ʾ������ȡλ��
		::EnumDisplayMonitors(NULL, NULL, EnumMonitorCallBack, (LPARAM)this);

		//�ȴ�ö�����
		while (1) 
		{
			if (m_vecMonitorInfo.size() >= nCount)
			{
				break;
			}

			Sleep(10);
		}
	}

public:
	/**
	 * @brief ��ȡȫ��Ψһ��������
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     MonitorHelper* pMonitorHelper = MonitorHelper::Instance();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static MonitorHelper* Instance(){ return (m_pMonitorInst == NULL ? m_pMonitorInst = new MonitorHelper() : m_pMonitorInst); }

	/**
	 * @brief �ͷ���Դ
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     MonitorHelper::FreeInstance();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void FreeInstance()
	{
		if (m_pMonitorInst)
		{
			delete m_pMonitorInst;
			m_pMonitorInst = NULL;
		}
	}

public:
	/**
	 * @brief ��ȡϵͳ��ʾ������
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     MonitorHelper::Instance()->GetMonitorCount();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	int GetMonitorCount()
	{
		return m_vecMonitorInfo.size();  //Ҳ����ͨ��::GetSystemMetrics(SM_CMONITORS)ϵͳ������ȡ
	}

public:
	static BOOL CALLBACK EnumMonitorCallBack(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
	{
		MonitorHelper* pUnit = (MonitorHelper*)dwData;

		G_Monitor_Info newInfo = { 0 };
		newInfo.hdcMonitor = hdcMonitor;
		newInfo.hMonitor = hMonitor;
		memcpy_s(&newInfo.rcMonitor, sizeof(RECT), lprcMonitor, sizeof(RECT));
		pUnit->m_vecMonitorInfo.push_back(newInfo);
		return TRUE;
	}

public:
	vector<G_Monitor_Info> m_vecMonitorInfo;  ///< ϵͳ��ʾ����ϸ��Ϣ
};

MonitorHelper* MonitorHelper::m_pMonitorInst = NULL;

#endif // G_MONITORHELPER_H_ 