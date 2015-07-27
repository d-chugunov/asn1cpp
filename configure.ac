AC_INIT([asn1cpp], [0.3.2], [chugunovdima@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_PROG_LIBTOOL

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_YACC
AM_PROG_LEX
AC_PATH_PROG(AR, ar, ar, $PATH:/usr/ucb:/usr/ccs/bin)	dnl for Solaris

case "$host_os" in
cygwin)
	case "$target" in
	*mingw*)
		CC="$CC -mno-cygwin"
	esac
	;;
esac

AC_ARG_ENABLE(Werror,
  [  --enable-Werror         abort compilation after any C compiler warning],
	enable_werror=$enableval, enable_werror=no)
if test x$enable_werror = xyes; then
  TESTSUITE_CFLAGS="-Werror -W -Wpointer-arith"
  TESTSUITE_CXXFLAGS="-Werror -W -Wpointer-arith"
  ADD_CFLAGS="-Werror -W -Wpointer-arith"
fi
AC_SUBST(ADD_CFLAGS)
AC_SUBST(TESTSUITE_CFLAGS)
AC_SUBST(TESTSUITE_CXXFLAGS)

AX_CHECK_COMPILE_FLAG([-Wall], [CFLAGS="$CFLAGS -Wall"])
AX_CHECK_COMPILE_FLAG([-Wcast-qual], [CFLAGS="$CFLAGS -Wcast-qual"])
AX_CHECK_COMPILE_FLAG([-Wchar-subscripts],
                      [CFLAGS="$CFLAGS -Wchar-subscripts"])
AX_CHECK_COMPILE_FLAG([-Wmissing-prototypes],
                      [CFLAGS="$CFLAGS -Wmissing-prototypes"])
AX_CHECK_COMPILE_FLAG([-Wmissing-declarations],
                      [CFLAGS="$CFLAGS -Wmissing-declarations"])

dnl There are legitimate uses for these features, disable warnings/errors.
AX_CHECK_COMPILE_FLAG([-Wno-error=cast-align],
                      [CFLAGS="$CFLAGS -Wno-error=cast-align"])
AX_CHECK_COMPILE_FLAG([-Wno-error=visibility],
                      [CFLAGS="$CFLAGS -Wno-error=visibility"])
AX_CHECK_COMPILE_FLAG([-Wno-error=parentheses-equality],
                      [CFLAGS="$CFLAGS -Wno-error=parentheses-equality"])
AX_CHECK_COMPILE_FLAG([-fno-strict-overflow],
                      [CFLAGS="$CFLAGS -fno-strict-overflow"])

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(sys/param.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_BIGENDIAN
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_STRUCT_TM
AC_CHECK_TYPE(intmax_t, int64_t)

dnl Test if we should check features that depend on 64-bitness.
AC_MSG_CHECKING(size of long is longer than 32 bit)
AS_VAR_PUSHDEF([WIDE_LONG], [WIDE_LONG])
AC_TRY_COMPILE([#include "confdefs.h"
#include <sys/types.h>
], [switch (0) case 0: case (sizeof ($1) >= 8):;],
    WIDE_LONG=yes, WIDE_LONG=no)
AC_MSG_RESULT($WIDE_LONG)
AM_CONDITIONAL([TEST_64BIT], [test x$WIDE_LONG = xyes])
AS_VAR_POPDEF([WIDE_LONG])

dnl For mingw
AC_SEARCH_LIBS(getopt, iberty)

AC_CHECK_FUNCS(strtoimax strtoll)
AC_CHECK_FUNCS(mergesort)
AC_CHECK_FUNCS(mkstemps)
AC_CHECK_FUNCS(alloca strcasecmp)
AC_CHECK_FUNCS(timegm)
AC_TRY_LINK_FUNC([symlink],[AC_DEFINE([HAVE_SYMLINK], 1, [Define to 1 if you have the symlink function.])])

AC_OUTPUT(				\
skeletons/tests/Makefile		\
libasn1compiler/Makefile		\
libasn1parser/Makefile			\
libasn1print/Makefile			\
asn1cpp/tests/Makefile			\
asn1cpp/general_tests/Makefile          \
asn1cpp/constraints_tests/Makefile      \
libasn1fix/Makefile			\
doc/docsrc/Makefile			\
skeletons/Makefile			\
tests/Makefile				\
asn1cpp/Makefile			\
doc/Makefile				\
asn1cpp.spec				\
Makefile				\
)

