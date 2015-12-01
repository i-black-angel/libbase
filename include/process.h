#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <stdint.h>

namespace base {
	class Process
	{
	public:
		Process();
		virtual ~Process();

		uint64_t processid() const;
		const char *program() const;
	};
}

#endif /* _PROCESS_H_ */
