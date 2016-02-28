/*
 * system.c
 *
 * rotinas de inicialização e configuração do sistema operacional
 *
 */

#if __DEBUG__
#include <stdio.h>
#include <assert.h>
#endif

#define __USE_BSD 1
#include <signal.h>

#include "common/boolean.h"
#include "sys/sys_common.h"

static void imp_signal_exit_handler(int s)
{
	switch(s)
	{
		case SIGQUIT:
		case SIGILL:
		case SIGTRAP:
//		case SIGABRT:
		case SIGBUS:
		case SIGFPE:
		case SIGSEGV:
		case SIGXCPU:
		case SIGXFSZ:
		case SIGSYS:
			fprintf(stderr, _("Received signal %d. Aborting...\n"), s);
			sys_exit(-1);

		default:
			printf(_("Received signal %d. Exiting...\n"), s);
			sys_exit(0);
	}
}

static void imp_signal_exit_handler_init()
{
	signal(SIGHUP, imp_signal_exit_handler);
	signal(SIGINT, imp_signal_exit_handler);
	signal(SIGQUIT, imp_signal_exit_handler);
	signal(SIGILL, imp_signal_exit_handler);
	signal(SIGTRAP, imp_signal_exit_handler);
//	signal(SIGABRT, imp_signal_exit_handler);
	signal(SIGBUS, imp_signal_exit_handler);
	signal(SIGFPE, imp_signal_exit_handler);
//	signal(SIGKILL, imp_signal_exit_handler);
	signal(SIGUSR1, imp_signal_exit_handler);
	signal(SIGSEGV, imp_signal_exit_handler);
	signal(SIGUSR2, imp_signal_exit_handler);
	signal(SIGPIPE, imp_signal_exit_handler);
	signal(SIGALRM, imp_signal_exit_handler);
	signal(SIGTERM, imp_signal_exit_handler);
	signal(SIGXCPU, imp_signal_exit_handler);
	signal(SIGXFSZ, imp_signal_exit_handler);
	signal(SIGVTALRM, imp_signal_exit_handler);
	signal(SIGPROF, imp_signal_exit_handler);
	signal(SIGPOLL, imp_signal_exit_handler);
	signal(SIGSYS, imp_signal_exit_handler);

	siginterrupt(false, SIGSTOP);
	siginterrupt(false, SIGTSTP);
	siginterrupt(false, SIGTTIN);
	siginterrupt(false, SIGTTOU);
}

int sys_system_init()
{
	imp_signal_exit_handler_init();

	return 0;
}

int sys_system_fini()
{
	return 0;
}

/* EOF */
