#ifndef _ATTR_H_
#define _ATTR_H_

#include "define.h"

namespace base {
	class LIBBASE_API Attr
	{
	public:
		enum DetachState {
			JOINABLE,
			DETACHED
		};
	public:
		Attr();
		virtual ~Attr();
		int getdetachstate() const;
		int setdetachstate(int detachstate);
		int getstack(void **stackaddr, size_t *stacksize) const; // unsupported
		int setstack(void *stackaddr, size_t stacksize);   // unsupported
		int getstacksize(size_t *stacksize) const;
		int setstacksize(size_t stacksize);
		int getguardsize(size_t *guardsize) const;
		int setguardsize(size_t guardsize);
	
#ifdef BASE_HAVE_WINDOWS
		SECURITY_ATTRIBUTES *attr() { return &_attr; }
	private:
		SECURITY_ATTRIBUTES _attr;
#else
		pthread_attr_t *attr() { return &_attr; }
	private:
		pthread_attr_t _attr;
#endif /* BASE_HAVE_WINDOWS */
	};
}
#endif /* _ATTR_H_ */
