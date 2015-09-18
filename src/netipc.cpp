#include "netipc.h"
#include "utils.h"

int base::TCPBase::Close() {
	int res = 0;
	_mutex.lock();
	if (INVALID_SOCKET != _sockfd) {
#ifdef BASE_HAVE_WINDOWS
		res = closesocket(_sockfd);
#else
		res = close(_sockfd);
#endif /* BASE_HAVE_WINDOWS */
		_sockfd = INVALID_SOCKET;
	}
	_mutex.unlock();
	return res;
}

base::TCPServer::TCPServer() 
{
	
}

base::TCPServer::~TCPServer()
{
	
}

int base::TCPServer::Init(in_port_t port) {
	_port = port;
	_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (_sockfd < 0) {
		// perror("socket error");
		return 1;
	}

	// port reuse, again, using (char *) instead of (void *) to compate win
	int opt = 1;
	setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
	
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(_port);
	int res = bind(_sockfd, (const sockaddr *)&addr, sizeof(addr));
	if (res < 0) {
		// perror("bind error");
		return 1;
	}
	return 0;
}

int base::TCPServer::Listen() {
	int res = listen(_sockfd, 1024);
	if (res < 0) {
		// perror("listen error");
		return 1;
	}

	for (; ; ) {
		socket_t clientfd;
		struct sockaddr_in client_addr;
		socklen_t len = sizeof(client_addr);
		clientfd = accept(_sockfd, (struct sockaddr *)&client_addr, &len);
		if (clientfd < 0) {
			// perror("accept error");
			return 1;
		}
		HandleConnect(clientfd);
	}
	return 0;
}

base::TCPClient::TCPClient()
{
}

base::TCPClient::~TCPClient()
{
}

int base::TCPClient::Init()
{
	_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (_sockfd < 0) {
		// perror("socket error");
		return 1;
	}
	return 0;
}

int base::TCPClient::Connect(const char *ipaddr, in_port_t port)
{
	const char *ipaddr32 = getaddr(ipaddr);
	struct in_addr ipv4addr;
	inet_pton(AF_INET, ipaddr32, &ipv4addr);
	
	struct sockaddr_in addrin;
	addrin.sin_family = AF_INET;
	addrin.sin_port = htons(port);
	addrin.sin_addr.s_addr = ipv4addr.s_addr;
	return connect(_sockfd, (const struct sockaddr *)&addrin, sizeof(addrin));
}

ssize_t base::TCPClient::Send(const char *buf, size_t bufsize) {
	return send(_sockfd, buf, bufsize, 0);
}

ssize_t base::TCPClient::Recv(char *buf, size_t bufsize) {
	return recv(_sockfd, buf, bufsize, 0);
}

