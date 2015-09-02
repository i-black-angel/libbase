#include "rwlock.h"

base::RWLock::RWLock() 
{
	// _rwlock = PTHREAD_RWLOCK_INITIALIZER;
	pthread_rwlock_init(&_rwlock, NULL);
}

base::RWLock::~RWLock()
{
    // pthread_rwlock_destroy(_rwlock);
}

int base::RWLock::rdlock()
{
	return pthread_rwlock_rdlock(&_rwlock);
}

int base::RWLock::wrlock()
{
	return pthread_rwlock_wrlock(&_rwlock);
}

int base::RWLock::unlock()
{
	return pthread_rwlock_unlock(&_rwlock);
}

int base::RWLock::tryrdlock()
{
	return pthread_rwlock_tryrdlock(&_rwlock);
}

int base::RWLock::trywrlock()
{
	return pthread_rwlock_trywrlock(&_rwlock);
}
