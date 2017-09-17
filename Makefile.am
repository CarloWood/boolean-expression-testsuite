include $(srcdir)/cwm4/root_makefile_top.am

SUBDIRS = @CW_SUBDIRS@

bin_PROGRAMS = boolean_permutations_test boolean_simplification_test

boolean_permutations_test_SOURCES = boolean_permutations_test.cxx

boolean_simplification_test_SOURCES = boolean_simplification_test.cxx

boolean_permutations_test_CXXFLAGS = -fmax-errors=1 -ferror-limit=1 -Wno-unused-command-line-argument @LIBCWD_FLAGS@
boolean_permutations_test_LDADD = ../utils/libutils.la $(top_builddir)/cwds/libcwds.la

boolean_simplification_test_CXXFLAGS = -fmax-errors=1 -ferror-limit=1 -Wno-unused-command-line-argument @LIBCWD_FLAGS@
boolean_simplification_test_LDADD = ../utils/libutils.la $(top_builddir)/cwds/libcwds.la

include $(srcdir)/cwm4/root_makefile_bottom.am
