#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.62)
AC_INIT([travistest], [0.1], [K.vanderSloot@let.ru.nl])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADER([config.h])

AC_PROG_CXX( [clang++-5.0] )

# use libtool
AC_PROG_LIBTOOL
LT_INIT

# when running tests, use CXX
AC_LANG([C++])

# Checks for libraries.

if test $prefix = "NONE"; then
   prefix="$ac_default_prefix"
fi


# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_OPENMP
AC_MSG_NOTICE([ARGL:$ac_cv_prog_cxx_openmp])
if test "x$ac_cv_prog_cxx_openmp" != "x"; then
  if test "x$ac_cv_prog_cxx_openmp" != "xunsupported"; then
    CXXFLAGS="$CXXFLAGS $OPENMP_CXXFLAGS"
    AC_DEFINE([HAVE_OPENMP], [1] , [Define to 1 if you have OpenMP] )
  else
    AC_MSG_NOTICE([We don't have OpenMP for Clang. Multithreaded operation is disabled])
  fi
fi

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

PKG_CHECK_MODULES( [TEXTCAT],
  [libexttextcat],
  [TEXTCAT_FOUND=1
   CXXFLAGS="$CXXFLAGS $TEXTCAT_CFLAGS"
   LIBS="$TEXTCAT_LIBS $LIBS"],
  [PKG_CHECK_MODULES( [TEXTCAT],
   [libtextcat],
   [TEXTCAT_FOUND=1
    CXXFLAGS="$CXXFLAGS $TEXTCAT_CFLAGS"
    LIBS="$TEXTCAT_LIBS $LIBS"],
   [TEXTCAT_FOUND=0]
   )]
 )

if test $TEXTCAT_FOUND = 1; then
   AC_DEFINE([HAVE_TEXTCAT], [1], [textcat])
else
# final resort... for OSX at least
   AC_CHECK_HEADERS([libtextcat/textcat.h],
	[CXXFLAGS="$CXXFLAGS -I$prefix/include"
	 AC_SEARCH_LIBS([textcat_Init],
	  [textcat],
	  [AC_DEFINE([HAVE_TEXTCAT], [1], [textcat])],
          [AC_MSG_NOTICE([textcat library not available])])],
        [AC_MSG_NOTICE([textcat include file not available])])
fi

PKG_CHECK_MODULES([ICU], [icu-uc >= 50 icu-io] )
CXXFLAGS="$CXXFLAGS $ICU_CFLAGS"
LIBS="$ICU_LIBS $LIBS"

AC_OUTPUT([
  Makefile
  m4/Makefile
  src/Makefile
])
