#include <cstdlib>
#include <cstdio>
#include "signalhandler.h"

using namespace std;

OnQuitFunc base::SignalHandler::quit = NULL;

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)  
{
	switch (dwCtrlType)
	{
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        // before_interrupt_quit_func();
		// OnQuitFunc();
		if (NULL != base::SignalHandler::quit) {
			base::SignalHandler::quit();
		}
        return TRUE;
    }
	return FALSE;
}  

bool base::SignalHandler::handle() {
	::SetConsoleCtrlHandler(HandlerRoutine, TRUE);
	return true;
}

void base::SignalHandler::run() {
	/* do nothing */
}
