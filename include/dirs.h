#ifndef _DIRS_H_
#define _DIRS_H_

#include "define.h"

namespace base {
	/** 
	 * return home directory without last '\\' or '/'
	 * 
	 * @return home dir
	 */
	LIBBASE_API const char *get_home_dir(void);

	/** 
	 * return temp directory without last '\\' or '/'
	 * 
	 * @return 
	 */
	LIBBASE_API const char *get_tmp_dir(void);
}

#endif /* _DIRS_H_ */
