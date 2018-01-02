AM_CPPFLAGS = -iquote $(top_srcdir) -iquote $(top_srcdir)/cwds

bin_PROGRAMS = boolean_permutations_test boolean_simplification_test boolean_truth_test boolean_usage_test

boolean_permutations_test_SOURCES = boolean_permutations_test.cxx

boolean_simplification_test_SOURCES = boolean_simplification_test.cxx

boolean_truth_test_SOURCES = boolean_truth_test.cxx

boolean_usage_test_SOURCES = boolean_usage_test.cxx

boolean_permutations_test_CXXFLAGS = -O3 -fmax-errors=1 -ferror-limit=1 -Wno-unused-command-line-argument @LIBCWD_FLAGS@
boolean_permutations_test_LDADD = ../boolean-expression/libboolean_expression.la ../utils/libutils.la $(top_builddir)/cwds/libcwds.la

boolean_simplification_test_CXXFLAGS = -fmax-errors=1 -ferror-limit=1 -Wno-unused-command-line-argument @LIBCWD_FLAGS@
boolean_simplification_test_LDADD = ../boolean-expression/libboolean_expression.la ../utils/libutils.la $(top_builddir)/cwds/libcwds.la

boolean_truth_test_CXXFLAGS = -fmax-errors=1 -ferror-limit=1 -Wno-unused-command-line-argument @LIBCWD_FLAGS@
boolean_truth_test_LDADD = ../boolean-expression/libboolean_expression.la ../utils/libutils.la $(top_builddir)/cwds/libcwds.la

boolean_usage_test_CXXFLAGS = -fmax-errors=1 -ferror-limit=1 -Wno-unused-command-line-argument @LIBCWD_FLAGS@
boolean_usage_test_LDADD = ../boolean-expression/libboolean_expression.la ../utils/libutils.la $(top_builddir)/cwds/libcwds.la
