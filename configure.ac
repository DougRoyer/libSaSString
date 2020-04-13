#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_COPYRIGHT([Copyright (C) 2019 Douglas Mark Royer])
AC_PREREQ([2.69])
AC_INIT([libSaSString], [1.0.0], [Support@SoftwareAndServices.US])

AC_CONFIG_HEADERS([include/SaS/String/config.h])

AC_CONFIG_SRCDIR([lib/String.cpp])
AC_CONFIG_AUX_DIR(build-aux)
AC_CONFIG_MACRO_DIRS([m4])

LT_INIT([shared])
AM_INIT_AUTOMAKE([subdir-objects])
AC_ENABLE_SHARED
AC_DISABLE_STATIC

# Checks for programs.
AC_PROG_CXX
AC_PROG_SED
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
	then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support (Unable to build API documentation)])
fi

AC_ARG_ENABLE([debug],
	[AS_HELP_STRING([--enable-debug],
			[whether to include debug symbols (default is no)])],
	[enable_debug=$enableval],
	[enable_debug=no]
)

if test "x$enable_debug" = xyes; then
   dnl Remove all optimization flags from CFLAGS
   changequote({,})
   CFLAGS=`echo "$CFLAGS" | $SED -e 's/-O[0-9s]*//g'`
   CXXFLAGS=`echo "$CXXFLAGS" | $SED -e 's/-O[0-9s]*//g'`

   CFLAGS=`echo "$CFLAGS" | $SED -e 's/-g[0-9]*//g'`
   CXXFLAGS=`echo "$CXXFLAGS" | $SED -e 's/-g[0-9]*//g'`
   changequote([,])

   CFLAGS="$CFLAGS -g -O0"
   CXXFLAGS="$CXXFLAGS -g -O0"
fi

echo "CFLAGS=$CFLAGS"

# Checks for libraries.
AC_CHECK_LIB([tinyxml2],[XMLDocument])
AC_CHECK_LIB([uuid],[uuid_version])
AC_CHECK_LIB([tirpc],[xdr_void])
#AC_CHECK_LIB([SaSssl],[])
#AC_CHECK_LIB([SaScrypto],[])
#AC_CHECK_LIB([licui18n],[])
#AC_CHECK_LIB([licuuc],[])
#AC_CHECK_LIB([icudata],[])

AC_CHECK_FUNCS([alarm])
AC_CHECK_FUNCS([atexit])
AC_CHECK_FUNCS([bzero])
AC_CHECK_FUNCS([endgrent])
AC_CHECK_FUNCS([ftruncate])
AC_CHECK_FUNCS([gethostbyaddr])
AC_CHECK_FUNCS([gethostbyname])
AC_CHECK_FUNCS([gethostname])
AC_CHECK_FUNCS([gettimeofday])
AC_CHECK_FUNCS([inet_ntoa])
AC_CHECK_FUNCS([memmove])
AC_CHECK_FUNCS([munmap])
AC_CHECK_FUNCS([nl_langinfo])
AC_CHECK_FUNCS([putenv])
AC_CHECK_FUNCS([select])
AC_CHECK_FUNCS([setenv])
AC_CHECK_FUNCS([socket])
AC_CHECK_FUNCS([strcasecmp])
AC_CHECK_FUNCS([strcspn])
AC_CHECK_FUNCS([strerror])
AC_CHECK_FUNCS([strncasecmp])
AC_CHECK_FUNCS([strpbrk])
AC_CHECK_FUNCS([strrchr])
AC_CHECK_FUNCS([strstr])
AC_CHECK_FUNCS([strtol])
AC_CHECK_FUNCS([sysinfo])
AC_CHECK_FUNCS([tzset])
AC_CHECK_FUNCS([uname])
AC_CHECK_HEADERS([arpa/inet.h])
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([langinfo.h])
AC_CHECK_HEADERS([locale.h])
AC_CHECK_HEADERS([malloc.h])
AC_CHECK_HEADERS([netdb.h])
AC_CHECK_HEADERS([netinet/in.h])
AC_CHECK_HEADERS([nl_types.h])
AC_CHECK_HEADERS([stddef.h])
AC_CHECK_HEADERS([sys/file.h])
AC_CHECK_HEADERS([sys/ioctl.h])
AC_CHECK_HEADERS([sys/param.h])
AC_CHECK_HEADERS([sys/socket.h])
AC_CHECK_HEADERS([sys/systeminfo.h])
AC_CHECK_HEADERS([sys/time.h])
AC_CHECK_HEADERS([syslog.h])
AC_CHECK_HEADERS([wchar.h])
AC_CHECK_HEADERS([wctype.h])
AC_CHECK_HEADERS([bsd/unistd.h])
AC_CHECK_HEADERS([unicode/gregocal.h])
AC_CHECK_HEADERS([tirpc/rpc/xdr.h])
AC_CHECK_TYPES([ptrdiff_t])

AC_C_INLINE
AC_FUNC_FORK
AC_FUNC_GETGROUPS
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_FUNC_STRERROR_R
AC_STRUCT_TIMEZONE

AC_TYPE_UINT8_T
AC_TYPE_INT8_T
AC_TYPE_UINT16_T
AC_TYPE_INT16_T
AC_TYPE_UINT32_T
AC_TYPE_INT32_T
AC_TYPE_UINT64_T
AC_TYPE_INT64_T

AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_UID_T

# Checks for header files.
AC_CHECK_HEADERS([limits.h memory.h stdlib.h string.h sys/statvfs.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_CHECK_FUNCS([memset mkdir realpath rmdir strchr strdup strspn])

AC_CONFIG_FILES([Makefile
		include/Makefile
		lib/Makefile
		Documentation/Makefile
		])
AM_CONDITIONAL([HAVE_DOXYGEN],
[test -n "$DOXYGEN"])AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([Documentation/Doxyfile])])

AC_OUTPUT
