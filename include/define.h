/**
 * Copyright 2017 Shusheng Shao <iblackangel@163.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _DEFINE_H_
#define _DEFINE_H_

#include "platform.h"

#include <stdint.h>

#ifdef BASE_HAVE_WINDOWS
# include <ws2tcpip.h>
# include <winsock2.h>
# include <windows.h>
# include <io.h>
# include <process.h>    /* _beginthreadex */
# include <direct.h>     /* _getcwd */
# include <shlwapi.h>	 /* PathRemoveFileSpec */

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS	// stupid MSFT "deprecation" warning
#endif

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "shlwapi.lib")
#else
# include <unistd.h>
# include <stdint.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <pthread.h>
#endif

#ifdef BASE_HAVE_WINDOWS
# ifndef __socket_t_defined
#  define __socket_t_defined
typedef SOCKET socket_t;
# endif
typedef     uint32_t       in_addr_t;
typedef     uint16_t       in_port_t;
typedef     size_t         ssize_t;
/* Standard file descriptors.  */
# define	STDIN_FILENO	0	/* Standard input.  */
# define	STDOUT_FILENO	1	/* Standard output.  */
# define	STDERR_FILENO	2	/* Standard error output.  */
# define    getcwd          _getcwd
# define    chdir           _chdir
# define    mkdir           _mkdir
# define    rmdir           _rmdir
# define    snprintf        _snprintf_s
# define    useconds_t      DWORD
# define    sleep(n)        Sleep((n) * 1000)
# define    usleep(n)       Sleep((n) / 1000)
# define    close           _close
# define    DIRECTORY_SEPARATOR   "\\"
#else  /* non-windows */
# ifndef __socket_t_defined
#  define __socket_t_defined
typedef int socket_t;
# endif
# define    closesocket     close
# define    DIRECTORY_SEPARATOR   "/"
#endif

#ifndef __byte_defined
# define __byte_defined
typedef unsigned char byte;
#endif

#define BASE_OK     0
#define BASE_ERROR  1

#ifndef _MSC_VER
# define WINAPI
# define CALLBACK
#endif

#endif /* _DEFINE_H_ */
