
SUBDIRS = . tests general_tests constraints_tests

AM_CFLAGS = @ADD_CFLAGS@
AM_CPPFLAGS = \
	-I${top_srcdir}/libasn1compiler	\
	-I${top_srcdir}/libasn1parser	\
	-I${top_srcdir}/libasn1print	\
	-I${top_srcdir}/libasn1fix	\
	-I${top_srcdir}/skeletons	\
	-DDATADIR=\"$(pkgdatadir)\"

asn1cpp_LDADD =	\
	$(top_builddir)/libasn1parser/libasn1parser.la	\
	$(top_builddir)/libasn1print/libasn1print.la	\
	$(top_builddir)/libasn1fix/libasn1fix.la	\
	$(top_builddir)/libasn1compiler/libasn1compiler.la

bin_PROGRAMS = asn1cpp

asn1cpp_SOURCES = asn1c.c

noinst_HEADERS = sys-common.h

dist_man1_MANS = asn1cpp.1

