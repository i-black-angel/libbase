#include "cond.h"
#include <sys/time.h>

base::Cond::Cond()
{
	// -std=c++11 or -std=gnu++11
	// _cond = PTHREAD_COND_INITIALIZER;
	pthread_cond_init(&_cond, NULL);
}

base::Cond::~Cond()
{
}

int base::Cond::wait(Mutex &mutex)
{
	return pthread_cond_wait(&_cond, mutex.mutex());
}

int base::Cond::timedwait(Mutex &mutex, time_t sec)
{
	struct timespec timeout;
	struct timeval now;
	gettimeofday(&now, NULL);
	timeout.tv_sec = now.tv_sec;
	timeout.tv_nsec = now.tv_usec * 1000;  /* usec to nsec */
	// add the offset to get timeout value
	timeout.tv_sec += sec;
	return pthread_cond_timedwait(&_cond, mutex.mutex(), &timeout);
}

int base::Cond::signal() {
	return pthread_cond_signal(&_cond);
}

int base::Cond::broadcast() {
	return pthread_cond_broadcast(&_cond);
}

