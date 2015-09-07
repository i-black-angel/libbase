#ifndef _COND_H_
#define _COND_H_

#include "define.h"
#include "mutex.h"

namespace base {
	class LIBBASE_API Cond
	{
	public:
		Cond();
		virtual ~Cond();
		int wait(base::Mutex &mutex);
		int timedwait(base::Mutex &mutex, time_t sec);
		int signal();

		/** 
		 * Oh my god, I'm so sorry to tell you that this function
		 * was not implemented on win32 platform, so be careful to use it
		 * 
		 * @return 0 if success, other's failed
		 */
		int broadcast();
	private:
#ifdef BASE_HAVE_WINDOWS
		HANDLE _cond;
#else
		pthread_cond_t _cond;
#endif /* BASE_HAVE_WINDOWS */
	};
}
#endif /* _COND_H_ */
