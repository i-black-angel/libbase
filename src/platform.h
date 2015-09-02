#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#if defined(_WIN32) || defined(_WIN64)
# ifndef BASE_HAVE_WINDOWS
#  define BASE_HAVE_WINDOWS
# endif
#else
# ifndef BASE_HAVE_LINUX
#  define BASE_HAVE_LINUX
# endif
#endif

#endif /* _PLATFORM_H_ */
