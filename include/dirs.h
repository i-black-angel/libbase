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
		bool     exists() const;
		bool     isreadable() const;
		bool     isroot() const;
		string   path() const;
		void     set_path(const string &path);

		// Dir& operator=(const Dir &rhs);
		
	public:
		static bool exists(const string &name);
		static string filepath(const string &filename);
		static bool makedir(const string &dirname);
		static bool mv(const string &oldname, const string &newname);
		static bool remove(const string &filename);
		static bool removedir(const string &dirname);
		
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
		static Dir runtime();
		static string runtime_path();
		static Dir temp();
		static string temp_path();
	private:
		std::string _path;
	};
}

#endif /* _DIRS_H_ */
