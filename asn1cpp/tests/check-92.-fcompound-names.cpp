#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#ifdef SINGLE_UNIT
#include <asn.hpp>
#else
#include <Everything.hpp>
#endif

using namespace ModuleCircularReferences;

int
main(int ac, char **av) {
	Everything t;

	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */
  
  t.Clear();

	/*
	 * No plans to fill it up: just checking whether it compiles or not.
	 */

	return 0;
}
