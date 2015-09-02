#ifndef _DEFINE_H_
#define _DEFINE_H_

#include "platform.h"

#ifdef BASE_HAVE_WINDOWS
# include <ws2tcpip.h>
# include <winsock2.h>
# include <windows.h>
# include <io.h>
# include <process.h>    /* _beginthreadex */
#else
# include <unistd.h>
# include <stdint.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <pthread.h>
#endif

#ifdef BASE_HAVE_WINDOWS
# ifdef DLL_EXPORT				// add '-DDLL_EXPORT' when compile on win32
#  ifndef LIBBASE_API
#   define LIBBASE_API  __declspec(dllexport)
#  endif
# else
#  ifndef LIBBASE_API
#   define LIBBASE_API  __declspec(dllimport)
#  endif
# endif
#else   /* non-windows */
# define LIBBASE_API
#endif

#ifdef BASE_HAVE_WINDOWS
# pragma comment(lib,"ws2_32.lib")
#endif /* BASE_HAVE_WINDOWS */

#ifdef BASE_HAVE_WINDOWS
# ifndef __socket_t_defined
#  define __socket_t_defined
typedef SOCKET socket_t;
# endif
/* Standard file descriptors.  */
# define	STDIN_FILENO	0	/* Standard input.  */
# define	STDOUT_FILENO	1	/* Standard output.  */
# define	STDERR_FILENO	2	/* Standard error output.  */
# define     sleep(n)       Sleep((n) * 1000)
# define     usleep(n)      Sleep((n) / 1000)
# define     snprintf       _snprintf
#else  /* non-windows */
# ifndef __socket_t_defined
#  define __socket_t_defined
typedef int socket_t;
# endif
#endif

#ifndef __byte_defined
# define __byte_defined
typedef unsigned char byte;
#endif

#define BASE_OK     0
#define BASE_ERROR  1

#endif /* _DEFINE_H_ */
