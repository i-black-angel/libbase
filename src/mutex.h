#ifndef _MUTEX_H_
#define _MUTEX_H_

#include "define.h"

namespace base {
#ifdef BASE_HAVE_WINDOWS
	class Mutex
	{
		Mutex() {
			InitializeCriticalSection(&cs);
		}
		virtual ~Mutex() {
			DeleteCriticalSection(&cs);
		}
		void lock() {
			EnterCriticalSection(&cs);
		}

		bool trylock() {
			return (TryEnterCriticalSection(&cs)) ? true : false;
		}

		void unlock() {
			LeaveCriticalSection(&cs);
		}
	private:
		CRITICAL_SECTION cs;
	};

#else  // linux
#include <errno.h>

	class Mutex
	{
	public:
		Mutex() {
			int rc = pthread_mutex_init(&_mutex, NULL);
		}
		virtual ~Mutex() {
			int rc = pthread_mutex_destroy (&_mutex);
		}

		void lock() {
			int rc = pthread_mutex_lock(&_mutex);
		}
		bool trylock() {
			int rc = pthread_mutex_trylock(&_mutex);
			if (EBUSY == rc) return false;
			return true;
		}
		void unlock() {
			int rc = pthread_mutex_unlock(&_mutex);
		}
		pthread_mutex_t *mutex() { return &_mutex; }
	private:
		pthread_mutex_t _mutex;
	};
#endif /* BASE_HAVE_WINDOWS */
}

#endif /* _MUTEX_H_ */
