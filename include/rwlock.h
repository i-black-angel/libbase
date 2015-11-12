#ifndef _RWLOCK_H_
#define _RWLOCK_H_

#include "define.h"

namespace base {
	class LIBBASE_API RWLock
	{
	public:
		RWLock();
		virtual ~RWLock();

		int rdlock();
		int wrlock();
		int unlock();
		int tryrdlock();
		int trywrlock();
	private:
#ifdef BASE_HAVE_WINDOWS
		// TODO::
#else
		pthread_rwlock_t _rwlock;
#endif /* BASE_HAVE_WINDOWS */
	};
}

#endif /* _RWLOCK_H_ */
