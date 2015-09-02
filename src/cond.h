#ifndef _COND_H_
#define _COND_H_

#include <pthread.h>
#include "mutex.h"

namespace base {
	class Cond
	{
	public:
		Cond();
		virtual ~Cond();
		int wait(base::Mutex &mutex);
		int timedwait(base::Mutex &mutex, time_t sec);
		int signal();
		int broadcast();
	private:
		pthread_cond_t _cond;
	};
}
#endif /* _COND_H_ */
