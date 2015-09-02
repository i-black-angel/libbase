#ifndef _DEFINE_H_
#define _DEFINE_H_

#if defined(_WIN32) || defined(_WIN64)
# include <ws2tcpip.h>
# include <winsock2.h>
# include <windows.h>
# include <io.h>
# include <process.h>    /* _beginthreadex */
#elif defined(__linux__)
# include <unistd.h>
# include <stdint.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <pthread.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
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

#endif /* _DEFINE_H_ */
