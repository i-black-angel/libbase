#ifndef _DIRS_H_
#define _DIRS_H_

#include <string>
#include "define.h"

using std::string;

namespace base {
	class LIBBASE_API Dir
	{
	public:
		Dir();
		Dir(const Dir &dir);
		Dir(const string &path);
		virtual ~Dir();

		bool     cd(const string &dirname);
		bool     cdup();
		string   dirname() const;
		bool     exists(const string &name) const;
		bool     exists() const;
		string   filepath(const string &filename) const;
		bool     isreadable() const;
		bool     isroot() const;
		bool     makedir(const string &dirname) const;
		bool     mv(const string &oldname, const string &newname);
		string   path() const;
		bool     remove(const string &filename) const;
		bool     removedir(const string &dirname) const;
		void     set_path(const string &path);
	public:
		static Dir current();
		static string current_path();
		static Dir home();
		static string home_path();
		static Dir root();
		
		/** 
		 * Returns the absolute path of the root directory.
		 * 
		 * For Unix operating systems this returns "/".
		 * For Windows file systems this normally returns "c:/".
		 * 
		 * @return root path string
		 *
		 * @see root(), current_path(), home_path(), and temp_path()
		 */
		static string root_path();
		static Dir temp();
		static string temp_path();
	private:
		string _path;
	};
}

#endif /* _DIRS_H_ */
