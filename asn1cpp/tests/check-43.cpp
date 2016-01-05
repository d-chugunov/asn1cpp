#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#ifdef SINGLE_UNIT
#include <asn.hpp>
#else
#include <Test-structure-1.hpp>
#include <Choice-1.hpp>
#endif

using namespace ModuleRecursion;

int
main(int ac, char **av) {
	Test_structure_1 ts1;
	Choice_1 cs1;

	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */

  ts1.Clear();
  cs1.Clear();

	/*
	 * No plans to fill it up: just checking whether it compiles or not.
	 */

	return 0;
}
