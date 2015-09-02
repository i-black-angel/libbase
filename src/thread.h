#ifndef _THREAD_H_
#define _THREAD_H_

#include "define.h"
#include "attr.h"				// thread attributation

namespace base {
	
#ifdef BASE_HAVE_WINDOWS
	typedef unsigned int (__stdcall *thread_callback)(void *);
#else  /* linux */
	typedef void * (*thread_callback)(void *pvoid);
#endif /* BASE_HAVE_WINDOWS */

	/**
	 * IRunnable interface
	 * 
	 */
	class IRunnable
	{
	public:
		virtual ~IRunnable() { }
		virtual void run() = 0;
	};

	/** 
	 * Thread class
	 * 
	 */
	class Thread
	{
	public:
		Thread(Attr *attr = NULL);
		Thread(IRunnable *runnable, Attr *attr = NULL);
		virtual ~Thread();
#ifdef BASE_HAVE_WINDOWS
		DWORD self() const {
			return ::GetCurrentThreadId();
		}
#else	
		pthread_t self() const {
			return pthread_self();
		}
#endif /* BASE_HAVE_WINDOWS */
	
		// activity
		int start();
		static void exit();
		int join();
		int detach();
		int cancel();

		virtual void run();
	
	private:
#ifdef BASE_HAVE_WINDOWS
		HANDLE _self;
#else
		pthread_t _self;
#endif /* BASE_HAVE_WINDOWS */
		thread_callback _routine;
		IRunnable *_runnable;
		Attr *_attr;
	};
}

#endif /* _THREAD_H_ */
