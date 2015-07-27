#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#include <Int5.hpp>
#include <Str4.hpp>
#include <Utf8-4.hpp>
#include <VisibleIdentifier.hpp>

int
main(int ac, char **av) {
	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */
  
  IdentifierModule::Identifier identifier;
  ModuleNestedConstraintsCheck::VisibleIdentifier visId;
  identifier.Clear();
  visId.Clear();

	/*
	 * No plans to fill it up: just checking whether it compiles or not.
	 */

	return 0;
}
