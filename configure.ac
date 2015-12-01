#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libbase], [2.1.0], [iblackangel@163.com])
AC_CONFIG_SRCDIR([src/ConvertUTF.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

lt_current="2"
lt_revision="1"
lt_age="0"
LTLDFLAGS="-version-info ${lt_current}:${lt_revision}:${lt_age}"
AC_SUBST(LTLDFLAGS)
 
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_AR
AC_PROG_LIBTOOL

# Checks for libraries.
# Add bellow content if you need to link with another library
# PKG_CHECK_MODULES([HELLO], [libhello >= 1.0])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netdb.h stdint.h sys/socket.h sys/time.h unistd.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MKTIME
AC_FUNC_STRTOD
AC_CHECK_FUNCS([gettimeofday memmove memset strerror strtol])

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 src/Makefile])
AC_CONFIG_FILES([libbase.pc])
AC_OUTPUT
