#ifndef _NETIPC_H_
#define _NETIPC_H_

#include "define.h"
#include "mutex.h"

namespace base {
#ifndef BASE_HAVE_WINDOWS
# ifndef INVALID_SOCKET
#  define INVALID_SOCKET (socket_t)(~0)
# endif /* INVALID_SOCKET */
#endif /* BASE_HAVE_WINDOWS */

	class TCPBase
	{
	public:
		TCPBase() { _sockfd = INVALID_SOCKET; }
		virtual ~TCPBase() { Close(); }
		virtual int Close();
	protected:
		Mutex _mutex;
		socket_t _sockfd;
	};
	
	class TCPServer : public TCPBase
	{
	public:
		TCPServer();
		virtual ~TCPServer();
		int Init(in_port_t port);
		int Listen();
	protected:
		/** 
		 * implemented in sub-class, but first of all,
		 * do not run long time operates in this function
		 * 
		 * @param fd connected client file description
		 */
		virtual void HandleConnect(socket_t fd) { }
	private:
		in_port_t _port;
	};

	class TCPClient : public TCPBase
	{
	public:
		TCPClient();
		virtual ~TCPClient();
		int Init();
		int Connect(const char *ipaddr, in_port_t port);
		// using 'char *' instead of 'void *' to compate stupid Windows OS
		ssize_t Send(const char *buf, size_t bufsize);
		ssize_t Recv(char *buf, size_t bufsize);
	};
}

#endif /* _NETIPC_H_ */
