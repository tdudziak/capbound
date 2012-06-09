#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/capability.h>
#include <sys/prctl.h>

char *program_name;

void
usage(int status)
{
	if (status != 0) {
		fprintf(stderr, "Try `%s --help' for more information.\n",
		        program_name);
	} else {
		printf("Usage: %s COMMAND [ARG]...\n", program_name);
		fputs("Run COMMAND with dropped CAP_LINUX_IMMUTABLE.\n",
		      stdout);
	}

	exit(status);
}

int
main(int argc, char** argv)
{
	program_name = argv[0];

	if(argc < 2) {
		usage(EXIT_FAILURE);
	}

	if (prctl(PR_CAPBSET_DROP, CAP_LINUX_IMMUTABLE, 0, 0, 0)) {
		perror("Error dropping capability");
		return -1;
	}

	execvp(argv[1], &argv[1]);
	return 0; /* unreachable */
}
