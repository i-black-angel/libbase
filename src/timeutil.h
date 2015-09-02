/**
 * @file   timeutil.h
 * @author Shusheng Shao <iblackangel@163.com>
 * @date   Thu Jun 18 16:23:43 2015
 * 
 * @brief  A cross-platform library that provides a simple API to get and calculate system time
 * 
 * 
 */
#ifndef _TIMEUTIL_H_
#define _TIMEUTIL_H_

#ifdef _MSC_VER
# pragma warning (push)
# pragma warning (disable: 4996)
#endif /* _MSC_VER */

#include <ctime>
#include <string>
#ifndef _WIN32
#include <sys/time.h>
#endif

using namespace std;

#ifdef _DEBUG
# ifndef assert
#  include <cassert>
# endif
# define TU_ASSERT(x)  assert(x)
#else
# define TU_ASSERT(x)
#endif

#ifdef _WIN32
# include <tchar.h>
#else
# ifdef _UNICODE
#  define _tcsftime   wcsftime
#  define _T(x)       L ## x
# else
#  define _tcsftime   strftime
#  define _T(x)       x
# endif
#endif

/**
 * One minute has 60 seconds
 */
#ifndef SECONDS_PER_MIN
#define SECONDS_PER_MIN 60
#endif

/**
 * One hour has 60*60 seconds
 */
#ifndef SECONDS_PER_HOUR
#define SECONDS_PER_HOUR 3600
#endif

/**
 * One day has 24*hours equals to (24*60*60)
 */
#ifndef SECONDS_PER_DAY
#define SECONDS_PER_DAY 86400
#endif

namespace base {
	typedef struct tm * tm_ptr;

	template <typename CharT>
	class CTimeUtilTempl
	{
	public:
		CTimeUtilTempl();
		virtual ~CTimeUtilTempl();

		// clock_t Clock();
		void start();
		double end() const;
		int day() const;
		int day_of_year() const;
		int day_of_week() const;
		int year() const;
		int month() const;
		int hour() const;
		int minute() const;
		int second() const;
		std::basic_string<CharT> now() const;
		std::basic_string<CharT> localtime(time_t t) const;
		void range(time_t t, time_t &begin_of_day, time_t &end_of_day) const;
	protected:
		// std::basic_string<CharT> Yesterday(int year, int month, int day,
		// 				 int hour = 0, int min = 0, int sec = 0) const; // disable
		// std::basic_string<CharT> Tomorrow(int year, int month, int day,
		// 				int hour = 0, int min = 0, int sec = 0) const; // disable
		tm_ptr CurrentTime() const;
	private:
#if defined(_WIN32) || defined(_WIN64)
		clock_t m_clock_start;		// In win32, using m_clock_start records the starting of program
#else
		struct timeval m_time_start; // In linux, using m_time_start records the starting of program
#endif /* _WIN32 */
	};

	template <typename CharT>
	CTimeUtilTempl<CharT>::CTimeUtilTempl()
	{
	}

	template <typename CharT>
	CTimeUtilTempl<CharT>::~CTimeUtilTempl() {
	}

// template <typename CharT>
// clock_t CTimeUtilTempl<CharT>::Clock() {
// 	m_clock_start = clock();
// 	return m_clock_start;
// }
	template <typename CharT>
	void CTimeUtilTempl<CharT>::start() {
#ifdef _WIN32
		m_clock_start = clock();
#else
		gettimeofday(&m_time_start, NULL);
#endif /* _WIN32 */
	}

	template <typename CharT>
	double CTimeUtilTempl<CharT>::end() const {
		double time_elapsed = 0;
#ifdef _WIN32
		time_elapsed = (double)(clock() - m_clock_start) / CLOCKS_PER_SEC;
#else
		struct timeval time_end;
		gettimeofday(&time_end, NULL);
		time_elapsed = (time_end.tv_sec - m_time_start.tv_sec) * 1000000
			+ (time_end.tv_usec - m_time_start.tv_usec);
		time_elapsed /= 1000000;
#endif /* _WIN32 */
		return time_elapsed;
	}

	template <typename CharT>
	int CTimeUtilTempl<CharT>::day() const {
		return CurrentTime()->tm_mday;
	}

	template <typename CharT>
	int CTimeUtilTempl<CharT>::day_of_year() const {
		return CurrentTime()->tm_yday + 1;
	}

	template <typename CharT>
	int CTimeUtilTempl<CharT>::day_of_week() const {
		return CurrentTime()->tm_wday;
	}

	template <typename CharT>
	int CTimeUtilTempl<CharT>::year() const {
		return CurrentTime()->tm_year + 1900;
	}

	template <typename CharT>
	int CTimeUtilTempl<CharT>::month() const {
		return CurrentTime()->tm_mon + 1;
	}

	template <typename CharT>
	int CTimeUtilTempl<CharT>::hour() const {
		return CurrentTime()->tm_hour;
	}

	template <typename CharT>
	int CTimeUtilTempl<CharT>::minute() const {
		return CurrentTime()->tm_min;
	}

	template <typename CharT>
	int CTimeUtilTempl<CharT>::second() const {
		return CurrentTime()->tm_sec;
	}

	template <typename CharT>
	tm_ptr CTimeUtilTempl<CharT>::CurrentTime() const {
		time_t _cur_time = time(NULL);
		return std::localtime(&_cur_time);
	}

	template <typename CharT>
	std::basic_string<CharT> CTimeUtilTempl<CharT>::now() const {
		CharT buffer[64] = {0};
		_tcsftime(buffer, 64, _T("%Y-%m-%d %H:%M:%S"), CurrentTime());
		return std::basic_string<CharT>(buffer);
	}

	template <typename CharT>
	std::basic_string<CharT> CTimeUtilTempl<CharT>::localtime(time_t t) const {
		CharT buffer[64] = {0};
		time_t __time = t;
		_tcsftime(buffer, 64, _T("%Y-%m-%d %H:%M:%S"), localtime(&__time));
		return std::basic_string<CharT>(buffer);
	}

	template <typename CharT>
	void CTimeUtilTempl<CharT>::range(time_t t, time_t &begin_of_day,
									  time_t &end_of_day) const {
		time_t daytime = t;
		struct tm *st = localtime(&daytime);
		st->tm_hour = 0;
		st->tm_min  = 0;
		st->tm_sec  = 0;
		begin_of_day = mktime(st);

		st->tm_hour = 23;
		st->tm_min  = 59;
		st->tm_sec  = 59;
		end_of_day = mktime(st);
	}

// ------------------------------------------------------
//                 TYPE DEFINITIONS
// ------------------------------------------------------
	typedef CTimeUtilTempl<char>        CTimeUtilA;
	typedef CTimeUtilTempl<wchar_t>     CTimeUtilW;

#ifdef _UNICODE
# define TimeUtil  CTimeUtilW
#else
# define TimeUtil CTimeUtilA
#endif
}
#ifdef _MSC_VER
# pragma warning (pop)
#endif /* _MSC_VER */

#endif /* _TIMEUTIL_H_ */
