#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bprocess.h"

namespace base {
	Process::Process() {
	}

	Process::~Process() {
	}

	uint64_t Process::processid() const {
#ifdef _MSC_VER
		return (uint64_t)_getpid();
#else
		return (uint64_t)getpid();
#endif
}

	std::string Process::program() const {
		std::string res;
#ifdef _MSC_VER
		char buffer[MAX_PATH] = {0};
		GetModuleFileName(NULL, buffer, sizeof(buffer));

		char   drive[_MAX_DRIVE]; 
		char   szdir[_MAX_DIR]; 
		char   fname[_MAX_FNAME]; 
		char   ext[_MAX_EXT]; 

		if (0 == _splitpath_s(buffer, drive, szdir, fname, ext)) {
			res = fname;
			res += ext;
		}
#else
		const char *pathname = "/proc/self/exe";
		char buf[512] = {0};
		ssize_t buflen = readlink(pathname, buf, sizeof(buf));
		if (buflen == -1) {
			return res;
		}
		if (buflen < sizeof(buf)) {
			buf[buflen] = '\0';
		}
		const char *delim = DIRECTORY_SEPARATOR;
		char *p = strtok(buf, delim);
		char *resptr = NULL;
		if (NULL != p) {
			res = p;
		}
		while ((p = strtok(NULL, delim))) {
			res = p;
		}
#endif		
		return res;
	}
}
