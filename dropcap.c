#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <error.h>
#include <string.h>

#include <sys/capability.h>
#include <sys/prctl.h>

static struct option long_options[] = {
	{"capabilities", required_argument, 0, 'c'},
	{"help", no_argument, 0, 'h'},
	{"version", no_argument, 0, 'v'},
	{0, 0, 0, 0}
};

const char* usage_message = "\
Run COMMAND with dropped CAP_LINUX_IMMUTABLE.\n\
\n\
  -c, --capabilities=CAPS  drop only capabilities CAPS\n\
  -h, --help               display this help and exit\n\
  -v, --version            output version information and exit\n\
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

void
drop_capabilities(const char* capspec)
{
	char *buff = strdup(capspec);
	char *start = buff, *end;
	int last_arg = 0;
	cap_value_t cap_current;

	/* don't do anything for an empty list of capabilities */
	if (strlen(capspec) == 0)
		return;

	while (!last_arg)
	{
		end = strchr(start, ',');

		if (end == NULL)
			last_arg = 1;
		else
			*end = '\0';

		if (cap_from_name(start, &cap_current) < 0)
			error(EXIT_FAILURE, 0, "invalid capability name `%s'",
			      start);

		/* drop this capability */
		if (prctl(PR_CAPBSET_DROP, cap_current, 0, 0, 0)) {
			perror("Error dropping capability");
			exit(EXIT_FAILURE);
		}

		start = end+1;
	}

	free(buff);
}

int
main(int argc, char** argv)
{
	char *capspec = "";
	program_name = argv[0];

	while (1) {
		int idx;
		switch (getopt_long(argc, argv, "+c:vh", long_options, &idx))
		{
		case -1:
			goto getopt_end;

		case 'h':
			usage(EXIT_SUCCESS);

		case 'v':
			puts(version_message);
			exit(EXIT_SUCCESS);

		case 'c':
			capspec = strdup(optarg);
			break;

		default:
			usage(EXIT_FAILURE);
		}
	}
getopt_end:

	if(argc <= optind) {
		error(0, 0, "missing COMMAND");
		usage(EXIT_FAILURE);
	}

	drop_capabilities(capspec);
	execvp(argv[optind], &argv[optind]);
	return EXIT_SUCCESS; /* unreachable */
}
