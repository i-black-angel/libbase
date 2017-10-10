/**
 * Copyright 2017 Shusheng Shao <iblackangel@163.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "dir.h"

BASE_BEGIN_NAMESPACE

#ifdef BASE_OS_WIN
static std::string driveSpec(const std::string &path)
{
	if (path.size() < 2)
		return std::string();
	char c = path.at(0);
	if (c < 'a' && c > 'z' && c < 'A' && c > 'Z')
		return std::string();
	if (path.at(1) != ':')
		return std::string();
	return path.substr(0, 2);
}
#endif

Dir::Dir(const Dir &other)
{
	_path = other._path;
}

Dir::Dir(const std::string &path)
{
	setPath(path);
}

Dir::~Dir()
{
}


Dir &Dir::operator=(const Dir &other)
{
	_path = other._path;
	return *this;
}

Dir &Dir::operator=(const std::string &path)
{
	setPath(path);
	return *this;
}


void Dir::setPath(const std::string &path)
{
	_path = path;
}

std::string Dir::path() const
{
	return _path;
}

std::string Dir::absolutePath() const
{
}

std::string Dir::canonicalPath() const
{
}

std::string Dir::dirName() const
{
}

std::string Dir::filePath(const std::string &fileName) const
{
}

std::string Dir::absoluteFilePath(const std::string &fileName) const
{
}

std::string Dir::relativeFilePath(const std::string &fileName) const
{
}

bool Dir::cd(const std::string &dirName)
{
}

bool Dir::cdUp()
{
	return cd("..");
}

bool Dir::mkdir(const std::string &dirName) const
{
}

bool Dir::rmdir(const std::string &dirName) const
{
}

bool Dir::mkpath(const std::string &dirPath) const
{
}

bool Dir::rmpath(const std::string &dirPath) const
{
}
    
bool Dir::removeRecursively()
{
}

bool Dir::isReadable() const
{
}

bool Dir::exists() const
{
}

bool Dir::isRoot() const
{
}

bool Dir::operator==(const Dir &dir) const
{
	// case insensitive
	return _path == dir._path;
}

bool Dir::remove(const std::string &fileName)
{
}

bool Dir::rename(const std::string &oldName, const std::string &newName)
{
}

bool Dir::exists(const std::string &name) const
{
}

char Dir::separator()
{
#ifdef BASE_OS_WIN
	return '\\';
#else
	return '/';
#endif
}

bool Dir::setCurrent(const std::string &path)
{
}

std::string Dir::currentPath()
{
}

std::string Dir::homePath()
{
#ifdef BASE_OS_WIN
	std::string ret = getenv("USERPROFILE");
	if (ret.empty() || !exists(ret)) {
		ret = std::string(getenv("HOMEDRIVE"))
			+ std::string(getenv("HOMEPATH"));
		if (ret.empty() || !exists(ret)) {
			ret = std::string(getenv("HOME"));
			if (ret.empty() || !exists(ret))
				ret = rootPath();
		}
	}
	return ret;
#else
	std::string home = getenv("HOME");
	if (home.empty())
		home = rootPath();
	return cleanPath(home);
#endif
}

std::string Dir::rootPath()
{
#ifdef BASE_OS_WIN
	std::string ret = getenv("SystemDrive");
	if (ret.empty())
		ret = std::string("c:");
	ret.append('/');
	return ret;
#else
	return std::string("/");
#endif
}

std::string Dir::tempPath()
{
#ifdef BASE_OS_WIN
	wchar_t tempPath[MAX_PATH];
	const DWORD len = GetTempPath(MAX_PATH, tempPath);
	if (len) {
		wchar_t longTempPath[MAX_PATH];
		const DWORD longLen = GetLongPathName(tempPath, longTempPath, MAX_PATH);
		// ret = longLen && longLen < MAX_PATH ?
				
	}
#else
	std::string temp = getenv("TMPDIR");
	if (temp.empty())
		temp = std::string("/tmp");
	return cleanPath(temp);
#endif
}

std::string Dir::cleanPath(const std::string &path)
{
	return path;
}

void Dir::refresh() const
{
}

BASE_END_NAMESPACE


