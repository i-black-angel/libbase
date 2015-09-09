#include <iostream>
#include <cstring>
#include <cstdio>
#include "thread.h"

void * on_thread_callback(void *pvoid) {
	base::Thread *t = static_cast<base::Thread *>(pvoid);
	if (NULL != t) {
		t->run();
	}
	return NULL;	
}

void * on_runnable_callback(void *pvoid) {
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

void base::Thread::exit()
{
	pthread_exit(NULL);
}

int base::Thread::join()
{
	return pthread_join(_self, NULL);
}

int base::Thread::detach() {
	return pthread_detach(_self);
}

int base::Thread::cancel() {
	return pthread_cancel(_self);
}
