#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#ifdef _MSC_VER

#else
# include <unistd.h>
#endif
#include "define.h"
#include "process.h"

namespace base {
	Process::Process() {
	}

	Process::~Process() {
	}

	uint64_t Process::processid() const {
		return (uint64_t)getpid();
	}

	const char *Process::program() const {
		std::string res;
		const char *pathname = "/proc/self/exe";
		char buf[512] = {0};
		ssize_t buflen = readlink(pathname, buf, sizeof(buf));
		if (buflen == -1) {
			return res.c_str();
		}
		if (buflen < sizeof(buf)) {
			buf[buflen] = '\0';
		}
		const char *delim = DIRECTORY_SEPARATOR;
		char *p = strtok(buf, delim);
		if (NULL != p) {
			res = p;
		}
		while ((p = strtok(NULL, delim))) {
			res = p;
		}
		return res.c_str();
	}
}
