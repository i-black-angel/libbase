#include <signal.h>
#include <cstdlib>
#include <cstdio>
#include "signalhandler.h"

using namespace std;

OnQuitFunc base::SignalHandler::quit = NULL;

bool base::SignalHandler::handle() {
	sigemptyset(&_mask);
	sigaddset(&_mask, SIGINT);
	sigaddset(&_mask, SIGTERM);
	sigaddset(&_mask, SIGQUIT);

	sigset_t old;
	if (pthread_sigmask(SIG_BLOCK, &_mask, &old) != 0)
		return false;
		
	// start new thread
	if (_thread->start() != 0) return false;
		
	return true;
}

void base::SignalHandler::run() {
	/* what you need to do, just imagine this function is an new main() */
	int signo, err;
	err = sigwait(&_mask, &signo);
	if (0 != err) {
		fprintf(stderr, "sigwait failed: %d\n", err);
		exit(1);
	}
	// using subclass func quit()
	// quit();
	if (NULL != quit) {
		quit();
	}
	
	// exit all process
	exit(0);
}
