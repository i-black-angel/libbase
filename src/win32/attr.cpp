#include "attr.h"

base::Attr::Attr() 
{
}

base::Attr::~Attr()
{
    
}

int base::Attr::getdetachstate() const
{
	return 0;
}

int base::Attr::setdetachstate(int detachstate) {
	return 0;
}

int base::Attr::getstack(void **stackaddr, size_t *stacksize) const {
	return 0;
}

int base::Attr::setstack(void *stackaddr, size_t stacksize) {
	return 0;
}

int base::Attr::getstacksize(size_t *stacksize) const {
	return 0;
}

int base::Attr::setstacksize(size_t stacksize) {
	return 0;
}

int base::Attr::getguardsize(size_t *guardsize) const
{
	return 0;
}

int base::Attr::setguardsize(size_t guardsize) {
	return 0;
}
