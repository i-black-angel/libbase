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
#ifndef _BASE_DIR_H_
#define _BASE_DIR_H_

#include <base/platformdef.h>

BASE_BEGIN_NAMESPACE

class Dir
{
public:
    Dir(const Dir &);
    Dir(const std::string &path = std::string());
    virtual ~Dir();

    Dir &operator=(const Dir &);
    Dir &operator=(const std::string &path);

    void setPath(const std::string &path);
    std::string path() const;
    std::string absolutePath() const;
    std::string canonicalPath() const;

    std::string dirName() const;
    std::string filePath(const std::string &fileName) const;
    std::string absoluteFilePath(const std::string &fileName) const;
    std::string relativeFilePath(const std::string &fileName) const;

    bool cd(const std::string &dirName);
    bool cdUp();
    bool mkdir(const std::string &dirName) const;
    bool rmdir(const std::string &dirName) const;
    bool mkpath(const std::string &dirPath) const;
    bool rmpath(const std::string &dirPath) const;
    
    bool removeRecursively();

    bool isReadable() const;
    bool exists() const;
    bool isRoot() const;

    bool operator==(const Dir &dir) const;
    inline bool operator!=(const Dir &dir) const { return !operator==(dir); }

    bool remove(const std::string &fileName);
    bool rename(const std::string &oldName, const std::string &newName);
    bool exists(const std::string &name) const;

    static char separator();
    static bool setCurrent(const std::string &path);
    static inline Dir current() { return Dir(currentPath()); }
    static inline Dir home() { return Dir(homePath()); }
    static inline Dir root() { return Dir(rootPath()); }
    static inline Dir temp() { return Dir(tempPath()); }

    static std::string currentPath();
    static std::string homePath();
    static std::string rootPath();
    static std::string tempPath();
    static std::string cleanPath(const std::string &path);
    void refresh() const;

protected:
    // explicit Dir();

private:
    std::string _path;
};

BASE_END_NAMESPACE

#endif