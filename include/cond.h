/**
 * @file   cond.h
 * @author Shusheng Shao <iblackangel@163.com>
 * @date   Fri Nov 20 14:45:41 2015
 * 
 * @brief  A cross-platform library that provides thread's condition API to
 *         wait and wakeup signal
 * 
 * This file is part of libbase package, testing and running on POSIX systems.
 * Also this can be used on WIN32 systems excepted broadcast() function.
 */
#ifndef _COND_H_
#define _COND_H_

#include "define.h"
#include "mutex.h"

namespace base {
	/**
	 * @class Cond
	 * This is Cond class definition, supported functions for handling
	 * conditional variables
	 */
	class LIBBASE_API Cond
	{
	public:
		Cond();
		virtual ~Cond();
		
		/** 
		 * Wait for condition variable COND to be signaled or broadcast.
		 * mutex is assumed to be locked before.
		 *
		 * This function is a cancellation point and therefore not marked with
		 * __THROW
		 * 
		 * @param[in] mutex mutex lock
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int wait(base::Mutex &mutex);

		/** 
		 * Wait for condition variable COND to be signaled or broadcast until
		 * \c sec. \c mutex is assumed to be locked before. \c sec is an
		 * absolute time specification; zero is the currently time.
		 * 
		 * @param[in] mutex mutex lock
		 * @param[in] sec second
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int timedwait(base::Mutex &mutex, time_t sec);

		/** 
		 * Wake up one thread waiting for condition variable COND.
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int signal();

		/** 
		 * Wake up all threads waiting for condition variables COND.
		 * 
		 * But I'm so sorry to tell you that this function
		 * was not implemented on win32 platform, so be careful to use it
		 * 
		 * @return 0 if success, other's failed
		 */
		int broadcast();
	private:
#ifdef BASE_HAVE_WINDOWS
		HANDLE _cond;
#else
		pthread_cond_t _cond;
#endif /* BASE_HAVE_WINDOWS */
	};
}

#endif /* _COND_H_ */
