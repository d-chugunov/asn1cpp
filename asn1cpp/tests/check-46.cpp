#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#include <T.hpp>

using namespace ModuleRedefineType;

uint8_t buf1[] = {
	32 | ((2 << 6) + 3),	/* [3], constructed */
	5,
	((2 << 6) + 5),	/* [5], primitive */
	3,	/* L */
  'a',
  'b',
  'c',
};

static void
check(uint8_t *buf, size_t size, size_t consumed) {
	T t;
	asn_dec_rval_t rval;

	fprintf(stderr, "Buf %p\n", buf);
  rval = t.DecodeBer(buf, size);
	fprintf(stderr, "Returned code %d, consumed %zd\n",
		(int)rval.code, rval.consumed);

	assert(rval.code == RC_OK);
	assert(rval.consumed == consumed);
}

int
main(int ac, char **av) {

	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */

	check(buf1, sizeof(buf1), sizeof(buf1));

	return 0;
}

