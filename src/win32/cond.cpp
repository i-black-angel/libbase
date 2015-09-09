#include "cond.h"

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
	return WaitForSingleObject(_cond, (DWORD)(sec * 1000));
}

int base::Cond::signal() {
	return SetEvent(_cond);
}

int base::Cond::broadcast() {
	// TODO::
	// may be some day, i will implement this.
	return 0;
}
