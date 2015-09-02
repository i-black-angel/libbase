#include <iostream>
#include <cstring>
#include <cstdio>
#include "thread.h"

#ifndef BASE_HAVE_WINDOWS
void * on_thread_callback(void *pvoid) {
	Thread *t = static_cast<Thread *>(pvoid);
	if (NULL != t) {
		t->run();
	}
	return NULL;	
}

void * on_runnable_callback(void *pvoid) {
	IRunnable *r = static_cast<IRunnable *>(pvoid);
	if (NULL != r) {
		r->run();
	}
	return NULL;
}

#else

unsigned int CALLBACK on_thread_callback(void *pvoid) {
	Thread *t = static_cast<Thread *>(pvoid);
	if (NULL != t) {
		t->run();
	}
	return NULL;	
}

unsigned int CALLBACK on_runnable_callback(void *pvoid) {
	IRunnable *r = static_cast<IRunnable *>(pvoid);
	if (NULL != r) {
		r->run();
	}
	return NULL;	
}

#endif /* BASE_HAVE_LINUX */


Thread::Thread(Attr *attr) 
{
	_self = 0;
	_routine = NULL;
	_runnable = NULL;
	_attr = attr;
}

Thread::Thread(IRunnable *runnable, Attr *attr) {
	_runnable = runnable;
	_attr = attr;
}

Thread::~Thread()
{
    _routine = NULL;
	_runnable = NULL;
	_attr = NULL;
}

#ifndef BASE_HAVE_WINDOWS

int Thread::start()
{
	int res = 0;
	// using IRunnable
	if (NULL != _runnable) {
		_routine = on_runnable_callback;
		const pthread_attr_t *thread_attr = NULL;
		if (NULL != _attr)
			thread_attr = _attr->attr();
		res = pthread_create(&_self, thread_attr, _routine, static_cast<void *>(_runnable));
		if (0 != res) {
			std::cerr << "can't create thread: " << strerror(res) << std::endl;
		}
		return res;
	}
	
	// using Thread
	_routine = on_thread_callback;
	const pthread_attr_t *thread_attr = NULL;
	if (NULL != _attr)
		thread_attr = _attr->attr();
	res = pthread_create(&_self, thread_attr, _routine, static_cast<void *>(this));
	if (0 != res) {
		std::cerr << "can't create thread: " << strerror(res) << std::endl;
	}
	return res;
}

void Thread::exit()
{
	pthread_exit(NULL);
}

int Thread::join()
{
	return pthread_join(_self, NULL);
}

int Thread::detach() {
	return pthread_detach(_self);
}

int Thread::cancel() {
	return pthread_cancel(_self);
}

//////////////////////////////////////////////////
#else /* windows */
/////////////////////////////////////////////////
int Thread::start()
{
	if (NULL != _runnable) {
		_routine = on_runnable_callback;
		LPSECURITY_ATTRIBUTES thread_attr = NULL;
		if (NULL != _attr)
			thread_attr = _attr->attr();
		_self = (HANDLE) _beginthreadex(thread_attr, 0, _routine,
										static_cast<void *>(_runnable),
										0, NULL);
		if (NULL == _self) {
			std::cerr << "can't create thread: " << strerror(errno) << std::endl;
			return BASE_ERROR;
		}
		return BASE_OK;
	}

	_routine = on_thread_callback;
	LPSECURITY_ATTRIBUTES thread_attr = NULL;
	if (NULL != _attr)
		thread_attr = _attr->attr();
	_self = (HANDLE) _beginthreadex(thread_attr, 0, _routine,
									static_cast<void *>(this)
									0, NULL);
	if (NULL == _self) {
		std::cerr << "can't create thread: " << strerror(errno) << std::endl;
		return BASE_ERROR;
	}
	return BASE_OK;
}

void Thread::exit()
{
	// TODO:: must be rewrite later.
	ExitThread(0);
}

int Thread::join()
{
	DWORD rc = WaitForSingleObject(_self, INFINITE);
	if (WAIT_FAILED == rc) return BASE_ERROR;;
	BOOL rc2 = CloseHandle(_self);
	if (!rc2) return BASE_ERROR;
	return BASE_OK;
}

int Thread::detach() {
	// TODO:: must be rewrite later.
	return 0;
}

int Thread::cancel() {
	// TODO:: must be rewrite later.
	BOOL res = TerminateThread(_self, 0);
	if (res) return BASE_OK;
	return BASE_ERROR;
}

#endif /* BASE_HAVE_WINDOWS */

/** 
 * this is a virtual function for sub-class implementation
 * 
 */
void Thread::run()
{
	// TODO::implementation in sub-class
}
