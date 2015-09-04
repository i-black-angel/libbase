#include "dirs.h"
#include <stdlib.h>

const char *base::get_home_dir(void) {
#ifdef BASE_HAVE_WINDOWS
	return getenv("USERPROFILE");
#else
	return getenv("HOME");
#endif /* BASE_HAVE_WINDOWS */
}

const char *base::get_tmp_dir(void) {
#ifdef BASE_HAVE_WINDOWS
	return getenv("TMP");
#else
	return "/tmp";
#endif /* BASE_HAVE_WINDOWS */
}
