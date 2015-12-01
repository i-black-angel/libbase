#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _MSC_VER
# include <sys/stat.h>
# include <unistd.h>
#endif
#include "dirs.h"

#ifdef _MSC_VER
# pragma warning (push)
# pragma warning (disable: 4996)
#endif

#ifdef _MSC_VER
# define RW_OK  0x6
# define R_OK   0x4
# define W_OK   0x2
# define X_OK   0x1
# define F_OK   0x0
#endif

namespace base {	
	Dir::Dir() {
		_pathptr = new string();
	}

	Dir::Dir(const Dir &dir) {
		_pathptr = new string();
		*_pathptr = dir.path();
	}

	Dir::Dir(const string &path) {
		_pathptr = new string();
		*_pathptr = path;
	}

	Dir& Dir::operator=(const Dir &rhs) {
		// Check for self-assignment!
		if (this == &rhs)
			return *this;
		_pathptr = new string();
		*_pathptr = rhs.path();
		return *this;
	}
	
	Dir::~Dir() {
		if (NULL != _pathptr) {
			delete _pathptr; _pathptr = NULL;
		}	
	}

	bool Dir::cd(const string &dirname) {
		if (0 != chdir(dirname.c_str()))
			return false;
		*_pathptr = current_path();
		return true;
	}

	bool Dir::cdup() {
		if (0 != chdir(".."))
			return false;
		*_pathptr = current_path();
		return true;
	}

	string Dir::dirname() const {
		string res;
		if (_pathptr->empty()) {
			return res;
		}
		char str[1024] = {0};
		strcpy(str, _pathptr->c_str());
		const char *delim = DIRECTORY_SEPARATOR;
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
		if (0 != access(_pathptr->c_str(), F_OK)) {
			return false;
		}
		return true;
	}

	string Dir::filepath(const string &filename) {
		string res;
		string::size_type idx = filename.find_last_of(DIRECTORY_SEPARATOR);
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
		if (0 != access(_pathptr->c_str(), F_OK | R_OK)) {
			return false;
		}
		return true;
	}

	bool Dir::isroot() const {
		return (*_pathptr == root_path());
	}

	bool Dir::makedir(const string &dirname) {
#ifdef _MSC_VER
		if (0 != _mkdir(dirname.c_str())) {
			return false;
		}					
#else
		if (0 != mkdir(dirname.c_str(), 0755)) {
			return false;
		}			
#endif
		return true;
	}

	bool Dir::mv(const string &oldname, const string &newname) {
		if (0 != rename(oldname.c_str(), newname.c_str()))
			return false;
		return true;
	}

	string Dir::path() const {
		return *_pathptr;
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
		*_pathptr = path;
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
#ifdef _MSC_VER
		string homepath = getenv("USERPROFILE");
#else
		string homepath = getenv("HOME");

#endif
		return homepath;
	}

	Dir Dir::root() {
		Dir dir(root_path());
		return dir;
	}

	string Dir::root_path() {
#ifdef _MSC_VER
		string rootpath = getenv("SystemDrive");		
#else
		string rootpath = "/";			
#endif
		return rootpath;
	}

	Dir Dir::runtime() {
		Dir dir(runtime_path());
		return dir;
	}
	
	string Dir::runtime_path() {
#ifdef _MSC_VER
		char szPath[MAX_PATH] = {0};
		if (GetModuleFileName(NULL, szPath, MAX_PATH)) {
			PathRemoveFileSpec(szPath);
		}
		string res = szPath;		
#else
		string res;
		const char *pathname = "/proc/self/exe";
		char buf[512] = {0};
		ssize_t buflen = readlink(pathname, buf, sizeof(buf));
		if (buflen == -1) {
			return res;
		}
		if (buflen < sizeof(buf)) {
			buf[buflen] = '\0';
		}
		res = filepath(string(buf));			
#endif
		return res;
	}
	
	Dir Dir::temp() {
		Dir dir(temp_path());
		return dir;
	}

	string Dir::temp_path() {
#ifdef _MSC_VER
		string tmppath = getenv("TMP");		
#else
		string tmppath = "/tmp";			
#endif
		return tmppath;
	}
}

#ifdef _MSC_VER
# pragma warning (pop)
#endif
