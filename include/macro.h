#ifndef _MACRO_H_
#define _MACRO_H_

#include <stdlib.h>

#define SAFE_DELETE(x) do { if (NULL != x) { delete x; x = NULL; } } while(0)
#define ELEMENTS(x)  ( sizeof( (x) ) / sizeof( (x)[0] ) )


#define SINGLETON_DEFINE(ClassName)				\
public:											\
	static ClassName *instance();				\
	static void destroy();						\
private:										\
    static ClassName *_instance


#define SINGLETON_IMPLEMNET(ClassName)			\
	ClassName *ClassName::_instance = NULL;		\
	ClassName *ClassName::instance()			\
	{											\
		if (NULL == _instance) {				\
			_instance = new ClassName();		\
		}										\
		return _instance;						\
	}											\
	void ClassName::destroy()					\
	{											\
		SAFE_DELETE(_instance);					\
	}

#endif /* _MACRO_H_ */
