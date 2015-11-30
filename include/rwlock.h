/**
 * @file   rwlock.h
 * @author Shusheng Shao <iblackangel@163.com>
 * @date   Fri Nov 20 16:22:13 2015
 * 
 * @brief  A cross-platform library that provides functions for handling
 *         read-write locks
 * 
 * This file is part of libbase package.
 */
#ifndef _RWLOCK_H_
#define _RWLOCK_H_

#include "define.h"

namespace base {
	/**
	 * @class RWLock
	 * This is the RWLock class definition, provides functions for handling
	 * read-write locks
	 */
	class LIBBASE_API RWLock
	{
	public:
		RWLock();
		virtual ~RWLock();

		/** 
		 * Acquire read lock for RWLOCK
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int rdlock();

		/** 
		 * Acquire write lock for RWLOCK
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int wrlock();

		/** 
		 * Unlock RWLOCK
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int unlock();

		/** 
		 * Try to acquire read lock for RWLOCK
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int tryrdlock();

		/** 
		 * Try to acquire write lock for RWLOCK
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int trywrlock();
	private:
#ifdef BASE_HAVE_WINDOWS
		// TODO::
#else
		pthread_rwlock_t _rwlock;
#endif /* BASE_HAVE_WINDOWS */
	};
}

#endif /* _RWLOCK_H_ */
