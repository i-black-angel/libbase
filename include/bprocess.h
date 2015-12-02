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
		
		uint64_t processid() const;
		std::string program() const;
	};
}

#endif /* _BPROCESS_H_ */
