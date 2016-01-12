/**
 * @file   bprocess.h
 * @author Shusheng Shao <iblackangel@163.com>
 * @date   Wed Dec  2 11:04:47 2015
 * 
 * @brief  A cross-platform library that provides process's API to get process
 *         ID and program's name
 * 
 * This file is part of libbase package, testing and running on POSIX systems.
 */
#ifndef _BPROCESS_H_
#define _BPROCESS_H_

#include <stdint.h>
#include <string>
#include "define.h"

namespace base {
	class LIBBASE_API Process
	{
	public:
		Process();
		virtual ~Process();

		/** 
		 * Get the process ID of the calling process.
		 * 
		 * @return The process ID
		 */
		uint64_t processid() const;

		
		/** 
		 * Returns the program the process was last started with.
		 * 
		 * @return The program's name
		 */
		std::string program() const;
	};
}

#endif /* _BPROCESS_H_ */
