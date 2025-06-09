#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([lzo-filters], [1.0.0])
AC_CONFIG_AUX_DIR([build-aux])
#AC_CONFIG_SRCDIR([lzo_base.c])
#AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_SEARCH_LIBS([lzo1_compress], [lzo2], [], [AC_MSG_ERROR([lzo2 not found])])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT
