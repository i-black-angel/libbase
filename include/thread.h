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
	 * Thread class
	 * 
	 */
	class LIBBASE_API Thread
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
		int join();
		int detach();
		int cancel();
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
