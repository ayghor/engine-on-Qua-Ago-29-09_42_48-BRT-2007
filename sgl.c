/*
 * single.c
 *
 * arquivo raiz da rogi engine.
 *
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>

#define _GNU_SOURCE 1
#include <getopt.h>
#undef _GNU_SOURCE

#include "common/boolean.h"
#include "sys/sys_system.h"
#include "single/sgl_main.h"

#define _(s) ((s))

char* program_name = NULL;

const char* version_message =
	"%s version development\n";

#define print_version() printf((_(version_message)), program_name)

const char* usage_message =
	"Usage: %s [option]...\n";

#define print_usage() printf((_(usage_message)), program_name)

const char* help_message =
	"Usage: %s [option]...\n"
	"rogi engine\n"
	"\n"
	"Mandatory arguments to long options are mandatory for short options too.\n"
	"\n"
	"  -V, --version\tPrint version string and exit.\n"
	"  -h, --help\tPrint this help message and exit.\n"
	"  -v, --verbose\tExplain what is being done.\n"
	"\n"
	"Returns 0 on success and -1 on error\n"
	"\n"
	"rogi <rogi@linuxmail.org>.\n";

#define print_help() printf(_(help_message), program_name)

bool verbose = false;

int main(int argc, char** argv)
{
	struct option longopts[] =
	{
		{"version",	no_argument,		NULL,	'V'},
		{"help",	no_argument,		NULL,	'h'},
		{"verbose",	no_argument,		NULL,	'v'},
		{NULL,		no_argument,		NULL,	'\0'}
	};

	char shortopts[] = "Vh:v";

	int opt;

	program_name = argv[0];

	optind = 0;
	opterr = true;
	opt = getopt_long(argc, argv, shortopts, longopts, &optind);
	while(opt != -1)
	{
		switch(opt)
		{
			/* -V, --version*/
			case 'V':
				print_version();
				return 0;

			/* -h, --help */
			case 'h':
				print_help();
				return 0;

			/* -v, --verbose */
			case 'v':
				verbose = true;
				break;

			/* opção inválida */
			case '?':
				return -1;
		}

		opt = getopt_long(argc, argv, shortopts, longopts, &optind);
	}

/*	if(argc - optind < 1)
		sys_err(_("Too few arguments. See --help for usage information."));

	if(argc - optind > 1)
		sys_err(_("Too many arguments. See --help for usage information."));*/

	sys_system_init();
	sgl_run();

	return 0;
}

/* EOF */
