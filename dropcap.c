#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <error.h>

#include <sys/capability.h>
#include <sys/prctl.h>

static struct option long_options[] = {
	{"help", no_argument, 0, 'h'},
	{"version", no_argument, 0, 'v'},
	{0, 0, 0, 0}
};

const char* usage_message = "\
Run COMMAND with dropped CAP_LINUX_IMMUTABLE.\n\
\n\
  -h, --help     display this help and exit\n\
  -v, --version  output version information and exit\n\
";

const char* version_message = "dropcap 0.1";

char *program_name;

void
usage(int status)
{
	if (status != 0) {
		fprintf(stderr, "Try `%s --help' for more information.\n",
		        program_name);
	} else {
		printf("Usage: %s [OPTION] COMMAND [ARG...]\n", program_name);
		puts(usage_message);
	}

	exit(status);
}

int
main(int argc, char** argv)
{
	program_name = argv[0];

	while (1) {
		int idx;
		switch (getopt_long(argc, argv, "+vh", long_options, &idx)) {
		case -1:
			goto getopt_end;

		case 'h':
			usage(EXIT_SUCCESS);

		case 'v':
			puts(version_message);
			exit(EXIT_SUCCESS);

		default:
			usage(EXIT_FAILURE);
		}
	}
getopt_end:

	if(argc <= optind) {
		error(0, 0, "missing COMMAND");
		usage(EXIT_FAILURE);
	}

	if (prctl(PR_CAPBSET_DROP, CAP_LINUX_IMMUTABLE, 0, 0, 0)) {
		perror("Error dropping capability");
		return -1;
	}

	execvp(argv[optind], &argv[optind]);
	return EXIT_SUCCESS; /* unreachable */
}
