EXTRA_DIST = readme.txt

AM_CPPFLAGS = \
  -I$(top_srcdir)/include

check_PROGRAMS = rfxcodectest rfxencode test_dwt_rem

rfxcodectest_SOURCES = rfxcodectest.c

rfxencode_SOURCES = rfxencode.c

test_dwt_rem_SOURCES = test_dwt_rem.c

rfxcodectest_LDADD = \
  $(top_builddir)/src/librfxencode.la

rfxencode_LDADD = \
  $(top_builddir)/src/librfxencode.la

test_dwt_rem_LDADD = \
  $(top_builddir)/src/librfxencode.la
