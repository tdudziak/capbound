#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([dropcap.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h unistd.h getopt.h sys/capability.h sys/prctl.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_MSG_CHECKING(for CAP_LINUX_IMMUTABLE)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <sys/capability.h>]], 
		                    return CAP_LINUX_IMMUTABLE)],
				    AC_MSG_RESULT(yes),
				    AC_MSG_RESULT(no);
				    AC_MSG_ERROR(CAP_LINUX_IMMUTABLE is not defined. Is this a Linux system?))

# Checks for library functions.
AC_CHECK_FUNC(getopt_long, , AC_MSG_ERROR(getopt_long() is missing))
AC_CHECK_FUNC(prctl, , AC_MSG_ERROR(No prctl(). Is this a Linux system?))

AC_CONFIG_FILES([Makefile])
AC_OUTPUT