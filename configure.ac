#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([travistest],[0.1],[K.vanderSloot@home.nl])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])

AX_REQUIRE_DEFINED([AX_CXX_COMPILE_STDCXX_17])

SYSCONFDIR=$sysconfdir
AC_SUBST([SYSCONFDIR])

AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_17

# use libtool
LT_INIT
AC_PROG_LN_S

# when running tests, use CXX
AC_LANG([C++])

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([pow])
AC_FUNC_FORK

if test $prefix = "NONE"; then
   prefix="$ac_default_prefix"
fi

PKG_PROG_PKG_CONFIG

if test "x$PKG_CONFIG_PATH" = x; then
    export PKG_CONFIG_PATH="$prefix/lib/pkgconfig"
else
    export PKG_CONFIG_PATH="$prefix/lib/pkgconfig:$PKG_CONFIG_PATH"
fi

AC_OSX_PKG( [icu4c] )
AC_MSG_NOTICE([pkg-config: PATH=$PKG_CONFIG_PATH])

PKG_CHECK_MODULES([ICU], [icu-uc >= 50 icu-io] )
CXXFLAGS="$CXXFLAGS $ICU_CFLAGS"
LIBS="$ICU_LIBS $LIBS"

AC_CONFIG_FILES([
  Makefile
  m4/Makefile
  src/Makefile
])
AC_OUTPUT
