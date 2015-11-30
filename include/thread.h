/**
 * @file   thread.h
 * @author Shusheng Shao <iblackangel@163.com>
 * @date   Fri Nov 20 16:30:35 2015
 * 
 * @brief  A cross-platform library that provides a new way to manage threads.
 * 
 * This file is part of libbase package.
 */
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
	class LIBBASE_API IRunnable
	{
	public:
		virtual ~IRunnable() { }
		virtual void run() = 0;
	};

	/** 
	 * @class Thread
	 * This is the Thread class definition, provides a
	 * platform-independent way to manage threads. 
	 */
	class LIBBASE_API Thread
	{
	public:
		Thread(Attr *attr = NULL);
		Thread(IRunnable *runnable, Attr *attr = NULL);
		virtual ~Thread();
#ifdef BASE_HAVE_WINDOWS
		/** 
		 * Obtain the identifier of the current thread.
		 * 
		 * @return the identifier of the current thread
		 */
		DWORD self() const {
			return ::GetCurrentThreadId();
		}
#else
		/** 
		 * Obtain the identifier of the current thread.
		 * 
		 * @return the identifier of the current thread
		 */
		pthread_t self() const {
			return pthread_self();
		}
#endif /* BASE_HAVE_WINDOWS */

		/** 
		 * Create a new thread, starting with execution of START-ROUTINE
		 * getting passed ARG. Creation attributed come from ATTR. the new
		 * handle is stored in *NEWTHREAD.
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int start();

		/** 
		 * Make calling thread wait for termination of the thread TH. The 
		 * exit status of the thread is stored in *THREAD_RETURN, if
		 * THREAD_RETURN is not NULL.
		 *
		 * This function is a cancellation point and therefore not marked with
		 * __THROW.
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int join();

		/** 
		 * Indicate that the thread TH is never to be joined with PTHREAD_JOIN.
		 * The resources of TH will therefore be freed immediately when it
		 * terminates, instead of waiting for another thread to perform
		 * PTHREAD_JOIN on it.
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int detach();

		/** 
		 * Cancel THREAD immediately or at the next possibility.
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int cancel();

		/** 
		 * Terminate calling thread.
		 *
		 * The registered cleanup handlers are called via exception handling
		 * so we cannot mark this function with __THROW.
		 */
		static void thread_exit();

		/** 
		 * this is a virtual function for sub-calss implementation
		 */
		virtual void run() { }

		/**
		 * i wanna using Thread in some classes,
		 * so, may be i can use Thread _t instead of Thread *_t now
		 */
		void set_func(IRunnable *runnable) {
			_runnable = runnable;
		}
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
