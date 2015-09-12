#include "utils.h"

void base::split(const string &content, const string &delim, vector<string> *retarr) {
	if (NULL == retarr) return;
	string split_content = content;
	string::size_type key_point = string::npos;
	while ((key_point = split_content.find_first_of(delim)) != string::npos) {
		if (key_point > 0) {
			retarr->push_back(split_content.substr(0, key_point));
		} else {
			retarr->push_back("");
		}
		split_content = split_content.substr(key_point + 1);
	}
	if (split_content.size() > 0) {
		retarr->push_back(split_content);
	} else {
		retarr->push_back("");
	}
}

const char *base::getaddr(const char *cp) {
	struct addrinfo *ailist = NULL, *aip = NULL;
	struct addrinfo hint;
	hint.ai_flags = 0;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;

	getaddrinfo(cp, NULL, &hint, &ailist);

	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		struct sockaddr_in *addr = (sockaddr_in *)aip->ai_addr;
		return inet_ntoa(addr->sin_addr);
	}
	return cp;
}

bool base::get_availabe_port(in_port_t &port) {
	bool result = true;

	// create a socket
	socket_t sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

	// create a sockaddr, and set port to 0
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = 0;

	// bind
	int err = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if ( 0 != err ) {
		result = false;
		closesocket(sockfd);
		return result;
	}

	// using getsockname return available port
	struct sockaddr_in connaddr;
	socklen_t len = sizeof(connaddr);
	err = getsockname(sockfd, (struct sockaddr *)&connaddr, &len);
	if (0 != err) {
		result = false;
		closesocket(sockfd);
		return result;
	}

	// parse port
	port = ntohs(connaddr.sin_port);

	closesocket(sockfd);
	return result;
}
