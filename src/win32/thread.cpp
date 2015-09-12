#include <iostream>
#include <cstring>
#include <cstdio>
#include "thread.h"

#ifdef _MSC_VER
# pragma warning (push)
# pragma warning (disable: 4996)
#endif

unsigned int CALLBACK on_thread_callback(void *pvoid) {
	base::Thread *t = static_cast<base::Thread *>(pvoid);
	if (NULL != t) {
		t->run();
	}
	return NULL;	
}

unsigned int CALLBACK on_runnable_callback(void *pvoid) {
	base::IRunnable *r = static_cast<base::IRunnable *>(pvoid);
	if (NULL != r) {
		r->run();
	}
	return NULL;	
}

base::Thread::Thread(Attr *attr) 
{
	_self = 0;
	_routine = NULL;
	_runnable = NULL;
	_attr = attr;
}

base::Thread::Thread(IRunnable *runnable, Attr *attr) {
	_runnable = runnable;
	_attr = attr;
}

base::Thread::~Thread()
{
    _routine = NULL;
	_runnable = NULL;
	_attr = NULL;
}

int base::Thread::start()
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
									static_cast<void *>(this),
									0, NULL);
	if (NULL == _self) {
		std::cerr << "can't create thread: " << strerror(errno) << std::endl;
		return BASE_ERROR;
	}
	return BASE_OK;
}

void base::Thread::thread_exit()
{
	// TODO:: must be rewrite later.
	ExitThread(0);
}

int base::Thread::join()
{
	DWORD rc = WaitForSingleObject(_self, INFINITE);
	if (WAIT_FAILED == rc) return BASE_ERROR;;
	BOOL rc2 = CloseHandle(_self);
	if (!rc2) return BASE_ERROR;
	return BASE_OK;
}

int base::Thread::detach() {
	// TODO:: must be rewrite later.
	return 0;
}

int base::Thread::cancel() {
	// TODO:: must be rewrite later.
	BOOL res = TerminateThread(_self, 0);
	if (res) return BASE_OK;
	return BASE_ERROR;
}

#ifdef _MSC_VER
# pragma warning (pop)
#endif
