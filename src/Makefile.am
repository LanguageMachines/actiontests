AM_CPPFLAGS = -I@top_srcdir@/include
AM_CXXFLAGS = -DSYSCONF_PATH=\"$(datadir)\" -std=c++17 -W -Wall -pedantic -O3 -g

#bin_PROGRAMS = main fork unicode
bin_PROGRAMS = unicode

# main_SOURCES = main.cxx
# fork_SOURCES = fork.cxx
unicode_SOURCES = unicode.cxx

#check_PROGRAMS = main fork unicode
check_PROGRAMS =  unicode

TESTS = tst.sh
EXTRA_DIST = tst.sh
