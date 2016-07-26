/**
 * @file TTSHelper.h �ı�����ת��������
 *
 * ����        ����        ����
 * 2016/07/26  gxl         create 
 */
#ifndef G_TTSHELPER_H_
#define G_TTSHELPER_H_

#include <sapi.h>
#pragma comment(lib,"sapi.lib")

/**
 * @brief �ı�����ת�������� 
 *
 * @note 1�������࣬����ȫ��ʹ�ã�
 * @note 2���첽�������Է�������
 * @note 3��Ŀǰֻ��װ�˲��š�ֹͣ�����ӿڣ������ٶȣ�SetRate��������������SetVolume����ʱʡ��
 */
class TTSHelper
{
private:
	static TTSHelper* m_pTTSInst;
	TTSHelper(void) : m_bInit(false)
	{
		if (!m_bInit)
		{
			::CoInitialize(NULL);
			HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
			m_bInit = (SUCCEEDED(hr)) ? true : false;
		}
	}

	ISpVoice* pVoice = NULL;
	bool m_bInit;

public:
	~TTSHelper(void)
	{
		if (m_bInit && pVoice)
		{
			pVoice->Speak(NULL, SPF_PURGEBEFORESPEAK, 0);
			pVoice->Release();
			CoUninitialize();
		}	
	}

	/**
	 * @brief ��ȡȫ��Ψһ��������
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     TTSHelper* pTTSHelper = TTSHelper::Instance();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static TTSHelper* Instance(){ return (m_pTTSInst == NULL ? m_pTTSInst = new TTSHelper() : m_pTTSInst); }

	/**
	 * @brief �ͷ���Դ
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     TTSHelper::FreeInstance();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void FreeInstance()
	{
		if (m_pTTSInst)
		{
			delete m_pTTSInst;
			m_pTTSInst = NULL;
		}
	}

public:
	/**
	 * @brief ��������
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     TTSHelper::Instance()->Speak();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	bool Speak(const char* chStr)
	{
		if (m_bInit && pVoice)
		{
			int nLen = strlen(chStr);
			int nwLen = MultiByteToWideChar(CP_ACP, 0, chStr, -1, NULL, 0);
			WCHAR* pwStr = new WCHAR[nwLen];
			MultiByteToWideChar(CP_ACP, 0, chStr, -1, pwStr, nwLen);
			pwStr[nwLen - 1] = '\0';

			//char ch[64] = "���Ѿ�3454352345234";
			HRESULT	ret = pVoice->Speak(pwStr, SPF_ASYNC, 0);  //�첽��ʽ
			if (SUCCEEDED(ret))
			{
				return true;
			}

			delete[] pwStr;
		}

		return false;
	}

	/**
	 * @brief ֹͣ����
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     TTSHelper::Instance()->Stop();

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	void Stop()
	{
		if (m_bInit && pVoice)
		{
			pVoice->Speak(NULL, SPF_PURGEBEFORESPEAK, 0);
		}
	}
};

TTSHelper* TTSHelper::m_pTTSInst = NULL;

#endif // G_TTSHELPER_H_ 