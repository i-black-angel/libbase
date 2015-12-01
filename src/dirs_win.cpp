#include "dirs.h"

#ifdef _MSC_VER
# pragma warning (push)
# pragma warning (disable: 4996)
#endif

#define RW_OK  0x6
#define R_OK   0x4
#define W_OK   0x2
#define X_OK   0x1
#define F_OK   0x0

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
	    const char *delim = "\\";
		char *p = strtok(str, delim);
		if (NULL != p) {
			res = p;
		}
		while ((p = strtok(NULL, delim))) {
			res = p;
		}
		return res;
	}

	bool Dir::exists(const string &name) {
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

	string Dir::filepath(const string &filename) {
		string res;
		string::size_type idx = filename.find_last_of("\\");
		if (string::npos == idx)
			return res;
		if (0 == idx) {
			res = filename.substr(0, idx + 1);
		} else {
			res = filename.substr(0, idx);
		}
		return res;
	}

	bool Dir::isreadable() const {
		if (0 != access(_path.c_str(), F_OK | R_OK)) {
			return false;
		}
		return true;
	}

	bool Dir::isroot() const {
		return (_path == root_path());
	}

	bool Dir::makedir(const string &dirname) {
		if (0 != mkdir(dirname.c_str())) {
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

	bool Dir::remove(const string &filename) {
		if (0 != unlink(filename.c_str())) {
			return false;
		}
		return true;
	}

	bool Dir::removedir(const string &dirname) {
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
		string homepath = getenv("USERPROFILE");
		return homepath;
	}

	Dir Dir::root() {
		Dir dir(root_path());
		return dir;
	}

	string Dir::root_path() {
		string rootpath = getenv("SystemDrive");
		return rootpath;
	}

	Dir Dir::runtime() {
		Dir dir(runtime_path());
		return dir;
	}
	
	string Dir::runtime_path() {
		char szPath[MAX_PATH] = {0};
		if (GetModuleFileName(NULL, szPath, MAX_PATH)) {
			PathRemoveFileSpec(szPath);
		}
		string res = szPath;
		return res;
	}
	
	Dir Dir::temp() {
		Dir dir(temp_path());
		return dir;
	}

	string Dir::temp_path() {
		string tmppath = getenv("TMP");
		return tmppath;
	}	
}

#ifdef _MSC_VER
# pragma warning (pop)
#endif
