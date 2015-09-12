#ifndef _SIGNALHANDLER_H_
#define _SIGNALHANDLER_H_

#include <stdexcept>
#include "thread.h"

namespace base {
	class LIBBASE_API SignalHandler : public IRunnable
	{
	public:
		SignalHandler() {
			static int SIGNAL_HANDLER_INSTANCE_TIMES = 0;
			if ((SIGNAL_HANDLER_INSTANCE_TIMES++) != 0) {
				throw std::runtime_error(
					"misuse: SignalHandler should only be instance once!");
			}
			_thread = new Thread(this);
		}
		virtual ~SignalHandler() {
			if (NULL != _thread) {
				delete _thread; _thread = NULL;
			}
		}

		bool handle();
	protected:
		virtual void run();
		
		/** 
		 * TODO::implement this func on sub-class
		 */
		virtual void quit() { }
	private:
#ifndef BASE_HAVE_WINDOWS
		sigset_t _mask;
#endif /* BASE_HAVE_WINDOWS */
		Thread *_thread;
	};
}

#endif /* _SIGNALHANDLER_H_ */
