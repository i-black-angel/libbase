#include "rwlock.h"

#ifdef BASE_HAVE_WINDOWS

base::RWLock::RWLock() 
{
}

base::RWLock::~RWLock()
{
}

int base::RWLock::rdlock()
{
	return 0;
}

int base::RWLock::wrlock()
{
	return 0;
}

int base::RWLock::unlock()
{
	return 0;
}

int base::RWLock::tryrdlock()
{
	return 0;
}

int base::RWLock::trywrlock()
{
	return 0;
}

#else  /* non-windows platform */

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
#endif /* BASE_HAVE_WINDOWS */
