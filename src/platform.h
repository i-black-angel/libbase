#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#ifdef _MSC_VER
# ifndef BASE_HAVE_WINDOWS
#  define BASE_HAVE_WINDOWS
# endif
#else
# ifndef BASE_HAVE_LINUX
#  define BASE_HAVE_LINUX
# endif
#endif

#endif /* _PLATFORM_H_ */
