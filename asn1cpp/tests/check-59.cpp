#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#include <Choice.hpp>

using namespace ModuleTestExtensibleChoice;

int
main(int ac, char **av) {
	Choice t;

	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */

	t.Clear();

	/*
	 * No plans to fill it up: just checking whether it compiles or not.
	 */

	return 0;
}
