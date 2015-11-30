#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "dirs.h"

// const char *base::get_home_dir(void) {
// #ifdef BASE_HAVE_WINDOWS
// 	return getenv("USERPROFILE");
// #else
// 	return getenv("HOME");
// #endif /* BASE_HAVE_WINDOWS */
// }

// const char *base::get_tmp_dir(void) {
// #ifdef BASE_HAVE_WINDOWS
// 	return getenv("TMP");
// #else
// 	return "/tmp";
// #endif /* BASE_HAVE_WINDOWS */
// }

namespace base {
	Dir::Dir() {
	}

	Dir::Dir(const Dir &dir) {
		this->_path = dir.path();
	}

	Dir::Dir(const string &path) {
		this->_path = path;
	}

	Dir::~Dir() {
	}


	bool Dir::cd(const string &dirname) {
		if (0 != chdir(dirname.c_str()))
			return false;
		_path = current_path();
		return true;
	}

	bool Dir::cdup() {
		if (0 != chdir(".."))
			return false;
		_path = current_path();
		return true;
	}

	string Dir::dirname() const {
		if (_path.empty()) {
			return _path;
		}
		string res;
		char str[1024] = {0};
		strcpy(str, _path.c_str());
	    const char *delim = "/";
		char *p = strtok(str, delim);
		if (NULL != p) {
			res = p;
		}
		while ((p = strtok(NULL, delim))) {
			res = p;
		}
		return res;
	}

	bool Dir::exists(const string &name) const {
		if (0 != access(name.c_str(), F_OK)) {
			return false;
		}
		return true;
	}

	bool Dir::exists() const {
		if (0 != access(_path.c_str(), F_OK)) {
			return false;
		}
		return true;
	}

	string Dir::filepath(const string &filename) const {
		string::size_type idx = filename.find_last_of("/");
		if (string::npos == idx)
			return filename;
		return filename.substr(0, idx + 1);
	}

	bool Dir::isreadable() const {
		if (0 != access(_path.c_str(), F_OK | R_OK)) {
			return false;
		}
		return true;
	}

	bool Dir::isroot() const {
		return (_path == "/");
	}

	bool Dir::makedir(const string &dirname) const {
		if (0 != mkdir(dirname.c_str(), 0755)) {
			return false;
		}
		return true;
	}

	bool Dir::mv(const string &oldname, const string &newname) {
		if (0 != rename(oldname.c_str(), newname.c_str()))
			return false;
		return true;
	}

	string Dir::path() const {
		return this->_path;
	}

	bool Dir::remove(const string &filename) const {
		if (0 != unlink(filename.c_str())) {
			return false;
		}
		return true;
	}

	bool Dir::removedir(const string &dirname) const {
		if (0 != rmdir(dirname.c_str())) {
			return false;
		}
		return true;
	}

	void Dir::set_path(const string &path) {
		this->_path = path;
	}

	Dir Dir::current() {
		Dir dir(current_path());
		return dir;
	}

	string Dir::current_path() {
		string curpath;
		char buf[512] = {0};
		if ( NULL != getcwd(buf, sizeof(buf)) ) {
			curpath = buf;
		}
		return curpath;
	}

	Dir Dir::home() {
		Dir dir(home_path());
		return dir;
	}

	string Dir::home_path() {
		string homepath = getenv("HOME");
		return homepath;
	}

	Dir Dir::root() {
		Dir dir(root_path());
		return dir;
	}

	string Dir::root_path() {
		string rootpath = "/";
		return rootpath;
	}

	Dir Dir::temp() {
		Dir dir(temp_path());
		return dir;
	}

	string Dir::temp_path() {
		string tmppath = "/tmp";
		return tmppath;
	}
	
}
