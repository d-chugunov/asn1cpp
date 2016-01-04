
dist_check_SCRIPTS = check-assembly.sh

TESTS_ENVIRONMENT= CXX="${CXX}" CFLAGS="${TESTSUITE_CFLAGS} ${CFLAGS} -Wno-error=unused-variable" CXXFLAGS="${TESTSUITE_CXXFLAGS} ${CXXFLAGS}" ./check-assembly.sh

TESTS = main.cpp


EXTRA_DIST =			\
	tests			\
	*.cpp

clean-local:
	rm -rf secure-ptrs
	rm -rf secure-ptrs-no-switch
	rm -rf insecure-ptrs
	rm -rf insecure-ptrs-no-switch
	rm -rf secure-ptrs-ptr-choice-getters
