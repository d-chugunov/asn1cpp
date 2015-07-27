
dist_check_SCRIPTS = check-assembly.sh

TESTS_ENVIRONMENT= CC="${CC}" CXX="${CXX}" CFLAGS="${TESTSUITE_CFLAGS} ${CFLAGS} -Wno-error=unused-variable" CXXFLAGS="${TESTSUITE_CXXFLAGS} ${CXXFLAGS}" ./check-assembly.sh

TESTS = check-*.cpp
if TEST_64BIT
TESTS += check64-*.cpp
endif

EXTRA_DIST =			\
	check-*.c*		\
	data-62			\
	data-70

clean-local:
	rm -rf test-*
