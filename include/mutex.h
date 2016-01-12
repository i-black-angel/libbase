/**
 * @file   mutex.h
 * @author Shusheng Shao <iblackangel@163.com>
 * @date   Fri Nov 20 16:13:01 2015
 * 
 * @brief  A cross-platform mutex handling
 * 
 * 
 */
#ifndef _MUTEX_H_
#define _MUTEX_H_

#include "define.h"

namespace base {
#ifdef BASE_HAVE_WINDOWS
	/**
	 * @class Mutex
	 * This is the Mutex class definition, for handling MUTEX
	 */
	class LIBBASE_API Mutex
	{
	public:
		/**
		 * Mutex constructure
		 */
		inline Mutex() {
			InitializeCriticalSection(&cs);
		}		
		/**
		 * Mutex destructure
		 */
		virtual ~Mutex() {
			DeleteCriticalSection(&cs);
		}
		
		/** 
		 * Lock a mutex
		 */
		inline void lock() {
			EnterCriticalSection(&cs);
		}
		
		/** 
		 * Try locking a mutex
		 * 
		 * @return true success
		 * @return false failed
		 */
		inline bool trylock() {
			return (TryEnterCriticalSection(&cs)) ? true : false;
		}

		/** 
		 * Unlock a mutex
		 */
		inline void unlock() {
			LeaveCriticalSection(&cs);
		}
	private:
		CRITICAL_SECTION cs;

		// Disable copy construction and assignment
		Mutex(const Mutex &);
		Mutex & operator = (const Mutex &);
	};

#else  // linux
#include <errno.h>
	/**
	 * @class Mutex
	 * This is the Mutex class definition, for handling MUTEX
	 */
	class Mutex
	{
	public:
		/**
		 * Mutex constructure
		 */
		inline Mutex() {
			int rc = pthread_mutex_init(&_mutex, NULL);
		}
		/**
		 * Mutex destructure
		 */
		virtual ~Mutex() {
			int rc = pthread_mutex_destroy (&_mutex);
		}

		/** 
		 * Lock a mutex
		 */
		inline void lock() {
			int rc = pthread_mutex_lock(&_mutex);
		}
		
		/** 
		 * Try locking a mutex
		 * 
		 * @return true success
		 * @return false failed
		 */
		inline bool trylock() {
			int rc = pthread_mutex_trylock(&_mutex);
			if (EBUSY == rc) return false;
			return true;
		}
		
		/** 
		 * Unlock a mutex
		 */
		inline void unlock() {
			int rc = pthread_mutex_unlock(&_mutex);
		}
		pthread_mutex_t *mutex() { return &_mutex; }
	private:
		pthread_mutex_t _mutex;

		// Disable copy construction and assignment.
		Mutex( const Mutex &);
		Mutex &operator = (const Mutex &);
	};
#endif /* BASE_HAVE_WINDOWS */
}

namespace base {
	class LIBBASE_API ScopeLock {
	public:
		ScopeLock(Mutex &mutex)
			: _mutex(mutex)
		{
			_mutex.lock();
		}
		virtual ~ScopeLock() {
			_mutex.unlock();
		}
	private:
		Mutex &_mutex;

		// Disable copy construction and assignment
		ScopeLock(const ScopeLock &);
		ScopeLock& operator=(const ScopeLock &rhs);
	};
}

#endif /* _MUTEX_H_ */
