#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(capbound, 0.1, tomasz.dudziak@gmail.com)
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([capbound.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(cap, cap_from_name, , AC_MSG_ERROR([libcap is required for this program]))

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h unistd.h getopt.h sys/capability.h sys/prctl.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNC(getopt_long, , AC_MSG_ERROR(getopt_long() is missing))
AC_CHECK_FUNC(prctl, , AC_MSG_ERROR(No prctl(). Is this a Linux system?))

AC_DEFINE([DEFAULT_CAPABILITIES], ["CAP_SYS_MODULE,CAP_SYS_RAWIO"],
	  [Default capabilities to drop])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
