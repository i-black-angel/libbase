#include <cstdlib>
#include <cstdio>
#include "signalhandler.h"

using namespace std;

namespace base {
	OnQuitFunc SignalHandler::quit = NULL;

	BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)  
	{
		switch (dwCtrlType)
		{
		case CTRL_C_EVENT:
		case CTRL_BREAK_EVENT:
		case CTRL_CLOSE_EVENT:
		case CTRL_SHUTDOWN_EVENT:
			if (NULL != SignalHandler::quit) {
				SignalHandler::quit();
			}
			exit(0);
		}
		return FALSE;
	}  

	bool SignalHandler::handle() {
		::SetConsoleCtrlHandler(HandlerRoutine, TRUE);
		return true;
	}

	void SignalHandler::run() {
		/* do nothing */
	}

}
