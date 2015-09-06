#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>
#include "define.h"

using namespace std;

namespace base {
	LIBBASE_API void split(const string &content, const string &delim, vector<string> *retarr);
	LIBBASE_API const char *getaddr(const char *cp);
}

#endif /* _UTILS_H_ */
