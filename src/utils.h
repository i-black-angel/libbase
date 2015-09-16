#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>
#include "define.h"

using namespace std;

namespace base {
	LIBBASE_API void split(const string &content, const string &delim, vector<string> *retarr);

	/** 
	 * use \c getaddr function to parse \c cp to an direct ipaddr,
	 * e.g. if \c cp means "www.163.com", using this function can get
	 * its direct ip address, may be "14.215.100.95" or anymore
	 * 
	 * @param cp host ipaddr or direct ipaddr
	 * 
	 * @return 
	 */
	LIBBASE_API const char *getaddr(const char *cp);

	/** 
	 * get an availabe port \c get_available_port
	 * 
	 * @param port the available port number
	 * 
	 * @return true if success, otherwise false
	 */
	LIBBASE_API bool get_available_port(in_port_t &port);
}

#endif /* _UTILS_H_ */
