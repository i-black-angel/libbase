#include "attr.h"

namespace base {
	Attr::Attr() 
	{
		pthread_attr_init(&_attr);
	}

	Attr::~Attr()
	{
    
	}

	int Attr::getdetachstate() const
	{
		int detachstate = 0;
		pthread_attr_getdetachstate(&_attr, &detachstate);
		return detachstate;
	}

	int Attr::setdetachstate(int detachstate) {
		int state = 0;
		switch (detachstate) {
		case JOINABLE:
			state = PTHREAD_CREATE_JOINABLE; break;
		case DETACHED:
			state = PTHREAD_CREATE_DETACHED; break;
		}
		return pthread_attr_setdetachstate(&_attr, state);
	}

// int base::Attr::getstack(void **stackaddr, size_t *stacksize) const {
// 	return pthread_attr_getstack(&_attr, stackaddr, stacksize);
// }

// int base::Attr::setstack(void *stackaddr, size_t stacksize) {
// 	return pthread_attr_setstack(&_attr, stackaddr, stacksize);
// }

	size_t Attr::getstacksize() const {
		size_t stacksize = 0;
		pthread_attr_getstacksize(&_attr, &stacksize);
		return stacksize;
	}

	int Attr::setstacksize(size_t stacksize) {
		return pthread_attr_setstacksize(&_attr, stacksize);
	}

	size_t Attr::getguardsize() const
	{
		size_t guardsize = 0;
		pthread_attr_getguardsize(&_attr, &guardsize);
		return guardsize;
	}

	int Attr::setguardsize(size_t guardsize) {
		return pthread_attr_setguardsize(&_attr, guardsize);
	}
}
