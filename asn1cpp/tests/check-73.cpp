#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#ifdef SINGLE_UNIT
#include <asn.hpp>
#else
#include <Epyt.hpp>
#endif

using namespace ModuleTestCircularReferences;

int
main(int ac, char **av) {
	Type t;
	Epyt ept;
	Ypet ypt;

	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */

	t.Clear();
  ept.Clear();
  ypt.Clear();

	/*
	 * No plans to fill it up: just checking whether it compiles or not.
	 */

	return 0;
}
