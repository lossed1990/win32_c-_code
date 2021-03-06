/**
 * @file TimeHelper.h 时间处理常用函数整理
 *
 * 日期        作者        描述
 * 2016/07/20  gxl		   create 
 */
#ifndef G_TIMEHELPER_H_
#define G_TIMEHELPER_H_

#include <time.h>

/**
 * @brief 程序运行计时帮助类
 * @code
 int main(int argc, char* argv[])
 {
     CTimeCounter newTimeCounter;
     Sleep(501);
     cout << "运行耗时:" << newTimeCounter.GetExecutionTime() << endl;

     ::system("pause");
     return 0;
 }
 * @endcode
 */
class CTimeCounter
{
public:
	CTimeCounter(void)
	{
		QueryPerformanceFrequency(&m_nFreq);
		QueryPerformanceCounter(&m_nBeginTime);
	}

	virtual ~CTimeCounter(void){}

	__int64 GetExecutionTime()
	{
		LARGE_INTEGER nEndTime;
		__int64 nCalcTime;

		QueryPerformanceCounter(&nEndTime);
		nCalcTime = (nEndTime.QuadPart - m_nBeginTime.QuadPart) *
			1000 / m_nFreq.QuadPart;

		return nCalcTime;
	}

protected:
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
};

typedef struct {
	SYSTEMTIME s_BeginTime;
	SYSTEMTIME s_EndTime;
} G_TIMES, *LPG_TIMES;

/**
 * @brief 时间处理常用函数帮助类
 */
class CTimeHelper
{
public:
	/**
	 * @brief 获取当日时间区间
	 *
	 * 获取系统当前年月日，并返回00:00:00至当前时间区间（包含星期 0-周日 1-周一 以此类推）
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     G_TIMES sTimes;
	     CTimeHelper::ThisDay(sTimes);

	     char str[128] = {0};
	     sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
	                          sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
	                          sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
	                          sTimes.s_BeginTime.wDayOfWeek,
	                          sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
	                          sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
	                          sTimes.s_EndTime.wDayOfWeek
	     );

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void ThisDay(G_TIMES &sTimes)
	{
		GetLocalTime(&sTimes.s_EndTime);

		sTimes.s_BeginTime.wYear = sTimes.s_EndTime.wYear;
		sTimes.s_BeginTime.wMonth = sTimes.s_EndTime.wMonth;
		sTimes.s_BeginTime.wDay = sTimes.s_EndTime.wDay;
		sTimes.s_BeginTime.wHour = 0;
		sTimes.s_BeginTime.wMinute = 0;
		sTimes.s_BeginTime.wSecond = 0;
		sTimes.s_BeginTime.wDayOfWeek = sTimes.s_EndTime.wDayOfWeek;
		sTimes.s_BeginTime.wMilliseconds = 0;
	}

	/**
	 * @brief 获取昨日时间区间
	 * 
	 * 推算昨天的年月日，并返回00:00:00至23:59:59的时间区间（包含星期 0-周日 1-周一 以此类推）
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     G_TIMES sTimes;
	     CTimeHelper::LastDay(sTimes);
	  
	     char str[128] = {0};
	     sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
	                         sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
	                         sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
	                         sTimes.s_BeginTime.wDayOfWeek,
                             sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
                             sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
	                         sTimes.s_EndTime.wDayOfWeek
	     );

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void LastDay(G_TIMES &sTimes)
	{
		time_t time_now;
		time(&time_now);

		time_t time_lastday = time_now - 24 * 60 * 60;
		tm tm_LastDay;
		localtime_s(&tm_LastDay,&time_lastday);

		sTimes.s_BeginTime.wYear = tm_LastDay.tm_year + 1900;
		sTimes.s_BeginTime.wMonth = tm_LastDay.tm_mon + 1;
		sTimes.s_BeginTime.wDay = tm_LastDay.tm_mday;
		sTimes.s_BeginTime.wHour = 0;
		sTimes.s_BeginTime.wMinute = 0;
		sTimes.s_BeginTime.wSecond = 0;
		sTimes.s_BeginTime.wDayOfWeek = tm_LastDay.tm_wday;
		sTimes.s_BeginTime.wMilliseconds = 0;

		sTimes.s_EndTime.wYear = tm_LastDay.tm_year + 1900;
		sTimes.s_EndTime.wMonth = tm_LastDay.tm_mon + 1;
		sTimes.s_EndTime.wDay = tm_LastDay.tm_mday;
		sTimes.s_EndTime.wHour = 23;
		sTimes.s_EndTime.wMinute = 59;
		sTimes.s_EndTime.wSecond = 59;
		sTimes.s_EndTime.wDayOfWeek = tm_LastDay.tm_wday;
		sTimes.s_EndTime.wMilliseconds = 0;
	}

	/**
	 * @brief 获取前几日时间区间
	 *
	 * 推算前几日的年月日（不包含今日），并返回00:00:00至23:59:59的时间区间（包含星期 0-周日 1-周一 以此类推）
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     G_TIMES sTimes;
	     CTimeHelper::LastDays(sTimes,3);  //获取最近3天的时间区间

	     char str[128] = {0};
	     sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
	                         sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
	                         sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
	                         sTimes.s_BeginTime.wDayOfWeek,
	                         sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
	                         sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
	                         sTimes.s_EndTime.wDayOfWeek
	     );

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void LastDays(G_TIMES &sTimes,int nCount)
	{
		if (nCount <= 1)
		{
			LastDay(sTimes);
			return;
		}

		time_t time_now;
		time(&time_now);

		time_t time_beginday = time_now - 24 * 60 * 60 * nCount;
		tm tm_BeginDay;
		localtime_s(&tm_BeginDay, &time_beginday);

		time_t time_endday = time_now - 24 * 60 * 60;
		tm tm_EndDay;
		localtime_s(&tm_EndDay, &time_endday);

		sTimes.s_BeginTime.wYear = tm_BeginDay.tm_year + 1900;
		sTimes.s_BeginTime.wMonth = tm_BeginDay.tm_mon + 1;
		sTimes.s_BeginTime.wDay = tm_BeginDay.tm_mday;
		sTimes.s_BeginTime.wHour = 0;
		sTimes.s_BeginTime.wMinute = 0;
		sTimes.s_BeginTime.wSecond = 0;
		sTimes.s_BeginTime.wDayOfWeek = tm_BeginDay.tm_wday;
		sTimes.s_BeginTime.wMilliseconds = 0;

		sTimes.s_EndTime.wYear = tm_EndDay.tm_year + 1900;
		sTimes.s_EndTime.wMonth = tm_EndDay.tm_mon + 1;
		sTimes.s_EndTime.wDay = tm_EndDay.tm_mday;
		sTimes.s_EndTime.wHour = 23;
		sTimes.s_EndTime.wMinute = 59;
		sTimes.s_EndTime.wSecond = 59;
		sTimes.s_EndTime.wDayOfWeek = tm_EndDay.tm_wday;
		sTimes.s_EndTime.wMilliseconds = 0;
	}

	/**
	 * @brief 获取本周时间区间
	 *
	 * 获取系统本周年月日，并返回00:00:00至当前时间区间（包含星期 0-周日 1-周一 以此类推）
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     G_TIMES sTimes;
	     CTimeHelper::ThisWeek(sTimes);

	     char str[128] = {0};
	     sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
	                         sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
	                         sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
	                         sTimes.s_BeginTime.wDayOfWeek,
	                         sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
	                         sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
	                         sTimes.s_EndTime.wDayOfWeek
	     );

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void ThisWeek(G_TIMES &sTimes)
	{	
		GetLocalTime(&sTimes.s_EndTime);
		
		int nCount = sTimes.s_EndTime.wDayOfWeek;
		if (1 == nCount)  //周一，直接返回当天
		{
			ThisDay(sTimes);
			return;
		}

		G_TIMES tTimes;
		nCount = (0 == nCount) ? 6 : nCount - 1;
		LastDays(tTimes, nCount);

		memcpy_s(&sTimes.s_BeginTime, sizeof(SYSTEMTIME), &tTimes.s_BeginTime, sizeof(SYSTEMTIME));
	}

	/**
	 * @brief 获取上周时间区间
	 *
	 * 推算系统上周年月日，并返回00:00:00至23:59:59的时间区间（包含星期 0-周日 1-周一 以此类推）
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     G_TIMES sTimes;
	     CTimeHelper::LastWeek(sTimes);

	     char str[128] = {0};
	     sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
	                         sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
	                         sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
	                         sTimes.s_BeginTime.wDayOfWeek,
	                         sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
	                         sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
	                         sTimes.s_EndTime.wDayOfWeek
	     );

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void LastWeek(G_TIMES &sTimes)
	{
		SYSTEMTIME tNowTime;
		GetLocalTime(&tNowTime);
		int nCount = (0 == tNowTime.wDayOfWeek) ? 7 : tNowTime.wDayOfWeek;

		time_t time_now;
		time(&time_now);

		time_t time_beginday = time_now - 24 * 60 * 60 * (nCount+6);
		tm tm_BeginDay;
		localtime_s(&tm_BeginDay, &time_beginday);

		time_t time_endday = time_now - 24 * 60 * 60 * nCount;
		tm tm_EndDay;
		localtime_s(&tm_EndDay, &time_endday);

		sTimes.s_BeginTime.wYear = tm_BeginDay.tm_year + 1900;
		sTimes.s_BeginTime.wMonth = tm_BeginDay.tm_mon + 1;
		sTimes.s_BeginTime.wDay = tm_BeginDay.tm_mday;
		sTimes.s_BeginTime.wHour = 0;
		sTimes.s_BeginTime.wMinute = 0;
		sTimes.s_BeginTime.wSecond = 0;
		sTimes.s_BeginTime.wDayOfWeek = tm_BeginDay.tm_wday;
		sTimes.s_BeginTime.wMilliseconds = 0;

		sTimes.s_EndTime.wYear = tm_EndDay.tm_year + 1900;
		sTimes.s_EndTime.wMonth = tm_EndDay.tm_mon + 1;
		sTimes.s_EndTime.wDay = tm_EndDay.tm_mday;
		sTimes.s_EndTime.wHour = 23;
		sTimes.s_EndTime.wMinute = 59;
		sTimes.s_EndTime.wSecond = 59;
		sTimes.s_EndTime.wDayOfWeek = tm_EndDay.tm_wday;
		sTimes.s_EndTime.wMilliseconds = 0;
	}

	/**
	 * @brief 获取本月时间区间
	 *
	 * 获取系统本月年月日，并返回00:00:00至当前时间区间（包含星期 0-周日 1-周一 以此类推）
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     G_TIMES sTimes;
	     CTimeHelper::ThisMonth(sTimes);

	     char str[128] = {0};
	     sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
	                         sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
	                         sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
	                         sTimes.s_BeginTime.wDayOfWeek,
	                         sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
	                         sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
	                         sTimes.s_EndTime.wDayOfWeek
	     );

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void ThisMonth(G_TIMES &sTimes)
	{
		GetLocalTime(&sTimes.s_EndTime);

		int nDays = sTimes.s_EndTime.wDay - 1;  //距月初天数
		int nDayOfWeek = sTimes.s_EndTime.wDayOfWeek - nDays % 7;

		sTimes.s_BeginTime.wYear = sTimes.s_EndTime.wYear;
		sTimes.s_BeginTime.wMonth = sTimes.s_EndTime.wMonth;
		sTimes.s_BeginTime.wDay = 1;
		sTimes.s_BeginTime.wHour = 0;
		sTimes.s_BeginTime.wMinute = 0;
		sTimes.s_BeginTime.wSecond = 0;
		sTimes.s_BeginTime.wDayOfWeek = (nDayOfWeek < 0) ? nDayOfWeek + 7 : nDayOfWeek;
		sTimes.s_BeginTime.wMilliseconds = 0;
	}

	/**
	 * @brief 获取上月时间区间
	 *
	 * 推算系统上月年月日，并返回00:00:00至23:59:59的时间区间（包含星期 0-周日 1-周一 以此类推）
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     G_TIMES sTimes;
	     CTimeHelper::LastMonth(sTimes);

	     char str[128] = {0};
	     sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
	                         sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
	                         sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
	                         sTimes.s_BeginTime.wDayOfWeek,
	                         sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
	                         sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
	                         sTimes.s_EndTime.wDayOfWeek
	     );

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void LastMonth(G_TIMES &sTimes)
	{
		SYSTEMTIME tNowTime;
		GetLocalTime(&tNowTime);

		//本月初日期
		time_t time_thismonthbegin = {0};
		tm tm_ThisMonthBegin;
		tm_ThisMonthBegin.tm_year = tNowTime.wYear - 1900;
		tm_ThisMonthBegin.tm_mon = tNowTime.wMonth - 1;
		tm_ThisMonthBegin.tm_mday = 1;
		tm_ThisMonthBegin.tm_hour = 12;
		tm_ThisMonthBegin.tm_min = 0;
		tm_ThisMonthBegin.tm_sec = 0;
		time_thismonthbegin = mktime(&tm_ThisMonthBegin);

		time_t time_endday = time_thismonthbegin - 24 * 60 * 60;  //上月末秒数
		tm tm_EndDay;
		localtime_s(&tm_EndDay, &time_endday);

		time_t time_beginday = time_thismonthbegin - 24 * 60 * 60 * tm_EndDay.tm_mday;
		tm tm_BeginDay;
		localtime_s(&tm_BeginDay, &time_beginday);

		sTimes.s_BeginTime.wYear = tm_BeginDay.tm_year + 1900;
		sTimes.s_BeginTime.wMonth = tm_BeginDay.tm_mon + 1;
		sTimes.s_BeginTime.wDay = tm_BeginDay.tm_mday;
		sTimes.s_BeginTime.wHour = 0;
		sTimes.s_BeginTime.wMinute = 0;
		sTimes.s_BeginTime.wSecond = 0;
		sTimes.s_BeginTime.wDayOfWeek = tm_BeginDay.tm_wday;
		sTimes.s_BeginTime.wMilliseconds = 0;

		sTimes.s_EndTime.wYear = tm_EndDay.tm_year + 1900;
		sTimes.s_EndTime.wMonth = tm_EndDay.tm_mon + 1;
		sTimes.s_EndTime.wDay = tm_EndDay.tm_mday;
		sTimes.s_EndTime.wHour = 23;
		sTimes.s_EndTime.wMinute = 59;
		sTimes.s_EndTime.wSecond = 59;
		sTimes.s_EndTime.wDayOfWeek = tm_EndDay.tm_wday;
		sTimes.s_EndTime.wMilliseconds = 0;
	}

	/**
	 * @brief 获取本季度时间区间
	 *
	 * 获取系统本季度年月日，并返回00:00:00至当前时间区间（包含星期 0-周日 1-周一 以此类推）
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     G_TIMES sTimes;
	     CTimeHelper::ThisQuarter(sTimes);

	     char str[128] = {0};
	     sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
	                         sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
	                         sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
	                         sTimes.s_BeginTime.wDayOfWeek,
	                         sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
	                         sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
	                         sTimes.s_EndTime.wDayOfWeek
	     );

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void ThisQuarter(G_TIMES &sTimes)
	{
		GetLocalTime(&sTimes.s_EndTime);
		
		int nMonth = (sTimes.s_EndTime.wMonth % 3 != 0) ? ((sTimes.s_EndTime.wMonth / 3) * 3 + 1) : sTimes.s_EndTime.wMonth - 2;

		sTimes.s_BeginTime.wYear = sTimes.s_EndTime.wYear;
		sTimes.s_BeginTime.wMonth = nMonth;
		sTimes.s_BeginTime.wDay = 1;
		sTimes.s_BeginTime.wHour = 0;
		sTimes.s_BeginTime.wMinute = 0;
		sTimes.s_BeginTime.wSecond = 0;
		sTimes.s_BeginTime.wMilliseconds = 0;

		time_t time_thisquarterbegin = { 0 };
		tm tm_ThisQuarterBegin;
		tm_ThisQuarterBegin.tm_year = sTimes.s_EndTime.wYear - 1900;
		tm_ThisQuarterBegin.tm_mon = nMonth - 1;
		tm_ThisQuarterBegin.tm_mday = 1;
		tm_ThisQuarterBegin.tm_hour = 12;
		tm_ThisQuarterBegin.tm_min = 0;
		tm_ThisQuarterBegin.tm_sec = 0;
		time_thisquarterbegin = mktime(&tm_ThisQuarterBegin);
		localtime_s(&tm_ThisQuarterBegin, &time_thisquarterbegin);

		sTimes.s_BeginTime.wDayOfWeek = tm_ThisQuarterBegin.tm_wday;
	}

	/**
	 * @brief 获取上季度时间区间
	 *
	 * 推算系统上季度年月日，并返回00:00:00至23:59:59的时间区间（包含星期 0-周日 1-周一 以此类推）
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     G_TIMES sTimes;
	     CTimeHelper::LastQuarter(sTimes);

	     char str[128] = {0};
	     sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
	                         sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
	                         sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
	                         sTimes.s_BeginTime.wDayOfWeek,
	                         sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
	                         sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
	                         sTimes.s_EndTime.wDayOfWeek
	     );

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void LastQuarter(G_TIMES &sTimes)
	{
		SYSTEMTIME tNowTime;
		GetLocalTime(&tNowTime);

		int nBeginMonth;
		int nThisQuarterBeginMonth = (tNowTime.wMonth % 3 != 0) ? ((tNowTime.wMonth / 3) * 3 + 1) : tNowTime.wMonth - 2;
		nBeginMonth = (nThisQuarterBeginMonth - 3 < 0) ? 10 : nThisQuarterBeginMonth - 3;

		sTimes.s_BeginTime.wYear = (nBeginMonth == 10) ? tNowTime.wYear - 1 : tNowTime.wYear;
		sTimes.s_BeginTime.wMonth = nBeginMonth;
		sTimes.s_BeginTime.wDay = 1;
		sTimes.s_BeginTime.wHour = 0;
		sTimes.s_BeginTime.wMinute = 0;
		sTimes.s_BeginTime.wSecond = 0;
		sTimes.s_BeginTime.wMilliseconds = 0;

		sTimes.s_EndTime.wYear = sTimes.s_BeginTime.wYear;
		sTimes.s_EndTime.wMonth = nBeginMonth + 2;
		sTimes.s_EndTime.wDay = (nBeginMonth == 1 || nBeginMonth == 10) ? 31 : 30;
		sTimes.s_EndTime.wHour = 23;
		sTimes.s_EndTime.wMinute = 59;
		sTimes.s_EndTime.wSecond = 59;
		sTimes.s_EndTime.wMilliseconds = 0;

		//计算周几
		time_t time_thisquarterbegin = { 0 };
		tm tm_ThisQuarterBegin;
		tm_ThisQuarterBegin.tm_year = sTimes.s_BeginTime.wYear - 1900;
		tm_ThisQuarterBegin.tm_mon = sTimes.s_BeginTime.wMonth - 1;
		tm_ThisQuarterBegin.tm_mday = sTimes.s_BeginTime.wDay;
		tm_ThisQuarterBegin.tm_hour = 12;
		tm_ThisQuarterBegin.tm_min = 0;
		tm_ThisQuarterBegin.tm_sec = 0;
		time_thisquarterbegin = mktime(&tm_ThisQuarterBegin);
		localtime_s(&tm_ThisQuarterBegin, &time_thisquarterbegin);
		sTimes.s_BeginTime.wDayOfWeek = tm_ThisQuarterBegin.tm_wday;

		tm_ThisQuarterBegin.tm_year = sTimes.s_EndTime.wYear - 1900;
		tm_ThisQuarterBegin.tm_mon = sTimes.s_EndTime.wMonth - 1;
		tm_ThisQuarterBegin.tm_mday = sTimes.s_EndTime.wDay;
		tm_ThisQuarterBegin.tm_hour = 12;
		tm_ThisQuarterBegin.tm_min = 0;
		tm_ThisQuarterBegin.tm_sec = 0;
		time_thisquarterbegin = mktime(&tm_ThisQuarterBegin);
		localtime_s(&tm_ThisQuarterBegin, &time_thisquarterbegin);
		sTimes.s_EndTime.wDayOfWeek = tm_ThisQuarterBegin.tm_wday;
	}

	/**
	 * @brief 获取本年时间区间
	 *
	 * 获取系统本年年月日，并返回00:00:00至当前时间区间（包含星期 0-周日 1-周一 以此类推）
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     G_TIMES sTimes;
	     CTimeHelper::ThisYear(sTimes);

	     char str[128] = {0};
	     sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
	                         sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
	                         sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
	                         sTimes.s_BeginTime.wDayOfWeek,
	                         sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
	                         sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
	                         sTimes.s_EndTime.wDayOfWeek
	     );

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void ThisYear(G_TIMES &sTimes)
	{
		GetLocalTime(&sTimes.s_EndTime);
		
		sTimes.s_BeginTime.wYear = sTimes.s_EndTime.wYear;
		sTimes.s_BeginTime.wMonth = 1;
		sTimes.s_BeginTime.wDay = 1;
		sTimes.s_BeginTime.wHour = 0;
		sTimes.s_BeginTime.wMinute = 0;
		sTimes.s_BeginTime.wSecond = 0;
		sTimes.s_BeginTime.wMilliseconds = 0;

		time_t time_thisyearbegin = { 0 };
		tm tm_ThisYearBegin;
		tm_ThisYearBegin.tm_year = sTimes.s_EndTime.wYear - 1900;
		tm_ThisYearBegin.tm_mon = 0;
		tm_ThisYearBegin.tm_mday = 1;
		tm_ThisYearBegin.tm_hour = 12;
		tm_ThisYearBegin.tm_min = 0;
		tm_ThisYearBegin.tm_sec = 0;
		time_thisyearbegin = mktime(&tm_ThisYearBegin);
		localtime_s(&tm_ThisYearBegin, &time_thisyearbegin);

		sTimes.s_BeginTime.wDayOfWeek = tm_ThisYearBegin.tm_wday;
	}

	/**
	 * @brief 获取上年时间区间
	 *
	 * 推算系统上年年月日，并返回00:00:00至23:59:59的时间区间（包含星期 0-周日 1-周一 以此类推）
	 *
	 * @code
	 int main(int argc, char* argv[])
	 {
	     G_TIMES sTimes;
	     CTimeHelper::LastYear(sTimes);

	     char str[128] = {0};
	     sprintf_s(str, 128, "begin:%04d-%02d-%02d %02d:%02d:%02d 星期:%d;end:%04d-%02d-%02d %02d:%02d:%02d 星期:%d",
	                         sTimes.s_BeginTime.wYear,sTimes.s_BeginTime.wMonth,sTimes.s_BeginTime.wDay,
	                         sTimes.s_BeginTime.wHour,sTimes.s_BeginTime.wMinute,sTimes.s_BeginTime.wSecond,
	                         sTimes.s_BeginTime.wDayOfWeek,
	                         sTimes.s_EndTime.wYear,sTimes.s_EndTime.wMonth,sTimes.s_EndTime.wDay,
	                         sTimes.s_EndTime.wHour,sTimes.s_EndTime.wMinute,sTimes.s_EndTime.wSecond,
	                         sTimes.s_EndTime.wDayOfWeek
	     );

	     ::system("pause");
	     return 0;
	 }
	 * @endcode
	 */
	static void LastYear(G_TIMES &sTimes)
	{
		SYSTEMTIME tNowTime;
		GetLocalTime(&tNowTime);

		sTimes.s_BeginTime.wYear = tNowTime.wYear - 1;
		sTimes.s_BeginTime.wMonth = 1;
		sTimes.s_BeginTime.wDay = 1;
		sTimes.s_BeginTime.wHour = 0;
		sTimes.s_BeginTime.wMinute = 0;
		sTimes.s_BeginTime.wSecond = 0;
		sTimes.s_BeginTime.wMilliseconds = 0;

		sTimes.s_EndTime.wYear = sTimes.s_BeginTime.wYear;
		sTimes.s_EndTime.wMonth = 12;
		sTimes.s_EndTime.wDay = 31;
		sTimes.s_EndTime.wHour = 23;
		sTimes.s_EndTime.wMinute = 59;
		sTimes.s_EndTime.wSecond = 59;
		sTimes.s_EndTime.wMilliseconds = 0;

		//计算周几
		time_t time_thisyear = { 0 };
		tm tm_ThisYear;
		tm_ThisYear.tm_year = sTimes.s_BeginTime.wYear - 1900;
		tm_ThisYear.tm_mon = sTimes.s_BeginTime.wMonth - 1;
		tm_ThisYear.tm_mday = sTimes.s_BeginTime.wDay;
		tm_ThisYear.tm_hour = 12;
		tm_ThisYear.tm_min = 0;
		tm_ThisYear.tm_sec = 0;
		time_thisyear = mktime(&tm_ThisYear);
		localtime_s(&tm_ThisYear, &time_thisyear);
		sTimes.s_BeginTime.wDayOfWeek = tm_ThisYear.tm_wday;

		tm_ThisYear.tm_year = sTimes.s_EndTime.wYear - 1900;
		tm_ThisYear.tm_mon = sTimes.s_EndTime.wMonth - 1;
		tm_ThisYear.tm_mday = sTimes.s_EndTime.wDay;
		tm_ThisYear.tm_hour = 12;
		tm_ThisYear.tm_min = 0;
		tm_ThisYear.tm_sec = 0;
		time_thisyear = mktime(&tm_ThisYear);
		localtime_s(&tm_ThisYear, &time_thisyear);
		sTimes.s_EndTime.wDayOfWeek = tm_ThisYear.tm_wday;
	}
};

#endif // G_TIMEHELPER_H_