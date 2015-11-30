/**
 * @file   attr.h
 * @author Shusheng Shao <iblackangel@163.com>
 * @date   Fri Nov 20 14:36:28 2015
 * 
 * @brief  Thread's attribute API to get and set informations of POSIX
 *         thread
 * 
 * This file is part of libbase package, non-implemented on WINDOWS platform.
 */
#ifndef _ATTR_H_
#define _ATTR_H_

#include "define.h"

namespace base {
	/**
	 * @class Attr
	 * This is the Attr class definition, getting and setting \c detachstate,
	 * \c stack, \c stacksize and \c guardsize
	 */
	class LIBBASE_API Attr
	{
	public:
		/**
		 * @enum DetachState
		 * Flag thread is joinable or detached
		 */
		enum DetachState {
			JOINABLE,			/**< Thread is joinable */
			DETACHED			/**< Thread is detached */
		};
	public:
		Attr();
		virtual ~Attr();
		/** 
		 * Get detach state attribute
		 * 
		 * @return 0 joinable
		 * @return 1 detached
		 */
		int getdetachstate() const;
		
		/** 
		 * Set detach state attribute
		 * 
		 * @param[in] detachstate detach state attribute value 0 or 1
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int setdetachstate(int detachstate);
		// int getstack(void **stackaddr, size_t *stacksize) const;
		// int setstack(void *stackaddr, size_t stacksize);

		/** 
		 * Return the currently used minimal stack size.
		 * 
		 * @return the stack size
		 */
		size_t getstacksize() const;

		/** 
		 * Add information about the minimum stack size needed for the thread
		 * to be started. This size must never be less than PTHREAD_STACK_MIN
		 * and must also not exceed the system limits.
		 * 
		 * @param[in] stacksize the setting stack size
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
		int setstacksize(size_t stacksize);

		/** 
		 * Get the size of the guard area created for stack overflow protection.
		 * 
		 * @return the guard size
		 */
		size_t getguardsize() const;

		/** 
		 * Set the size of the guard area created for stack overflow protection.
		 * 
		 * @param[in] guardsize the setting guard size
		 * 
		 * @return 0 success
		 * @return 1 failed
		 */
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
