#include <sys/time.h>
#include "cond.h"

#ifdef BASE_HAVE_WINDOWS
base::Cond::Cond() {
	_cond = CreateEvent(NULL, FALSE, FALSE, NULL);
}

base::Cond::~Cond() {
	CloseHandle(_cond);
}

int base::Cond::wait(Mutex &mutex)
{
	return WaitForSingleObject(_cond, INFINITE);
}

int base::Cond::timedwait(Mutex &mutex, time_t sec)
{
	return WaitForSingleObject(_cond, sec * 1000);
}

int base::Cond::signal() {
	return SetEvent(_cond);
}

int base::Cond::broadcast() {
	// TODO::
	// may be some day, i will implement this.
	return 0;
}

#else
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
#endif /* BASE_HAVE_WINDOWS */

