#include "attr.h"

base::Attr::Attr() 
{
	pthread_attr_init(&_attr);
}

base::Attr::~Attr()
{
    
}

int base::Attr::getdetachstate() const
{
	int detachstate = 0;
	pthread_attr_getdetachstate(&_attr, &detachstate);
	return detachstate;
}

int base::Attr::setdetachstate(int detachstate) {
	int state = 0;
	switch (detachstate) {
	case JOINABLE:
		state = PTHREAD_CREATE_JOINABLE; break;
	case DETACHED:
		state = PTHREAD_CREATE_DETACHED; break;
	}
	return pthread_attr_setdetachstate(&_attr, state);
}

int base::Attr::getstack(void **stackaddr, size_t *stacksize) const {
	return pthread_attr_getstack(&_attr, stackaddr, stacksize);
}

int base::Attr::setstack(void *stackaddr, size_t stacksize) {
	return pthread_attr_setstack(&_attr, stackaddr, stacksize);
}

int base::Attr::getstacksize(size_t *stacksize) const {
	return pthread_attr_getstacksize(&_attr, stacksize);
}

int base::Attr::setstacksize(size_t stacksize) {
	return pthread_attr_setstacksize(&_attr, stacksize);
}

int base::Attr::getguardsize(size_t *guardsize) const
{
	return pthread_attr_getguardsize(&_attr, guardsize);
}

int base::Attr::setguardsize(size_t guardsize) {
	return pthread_attr_setguardsize(&_attr, guardsize);
}
