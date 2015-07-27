#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include <iostream>

#include <T1.hpp>

using namespace ModuleTestTags3;

uint8_t buf1[] = {
	32 | 16,		/* [UNIVERSAL 16], constructed */
	12,	/* L */
	/* INTEGER a */
	((2 << 6) + 0),		/* [0], primitive */
	2,	/* L */
  150,
  70,
	/* b [1] EXPLICIT CHOICE */
	32 | ((2 << 6) + 1),	/* [1] */
	3,	/* L */
	((2 << 6) + 1),		/* [1] */
	1,
  'i',
	/* UTF8String c */
	((2 << 6) + 2),		/* [2], primitive */
	1,	/* L */
  'x'
};

static void
check(int is_ok, uint8_t *buf, size_t size, size_t consumed) {
	T1 t;
	asn_dec_rval_t rval;
	asn_enc_rval_t erval;
	int ret;
	int i;

	fprintf(stderr, "Buf %p\n", buf);
  rval = t.DecodeBer(buf, size);
	fprintf(stderr, "Returned code %d, consumed %d\n",
		(int)rval.code, (int)rval.consumed);

	if(is_ok) {
		assert(rval.code == RC_OK);
		assert(rval.consumed == (size_t)consumed);
		assert(t.a.size() == 2);
		assert(t.b.FetchPresent() == T1::b::PR_n);
#ifdef PTR_CHOICE_GETTERS
		assert(t.b.n()->size() == 1);
		assert((*t.b.n())[0] == 'i');
#else
		assert(t.b.n().size() == 1);
		assert(t.b.n()[0] == 'i');
#endif
		assert(t.c.size() == 1);
		assert(t.c[0] == 'x');

	} else {
		if(rval.code == RC_OK) {
			assert(t.a.size() != 2
				|| t.b.FetchPresent() != T1::b::PR_n
#ifdef PTR_CHOICE_GETTERS
				|| t.b.n()->size() != 1
#else
				|| t.b.n().size() != 1
#endif
				|| t.c.size() != 1
			);
		}
		assert(rval.consumed <= (size_t)consumed);
		return;
	}

	fprintf(stderr, "=> Re-creating using DER encoder <=\n");

	/*
	 * Try to re-create using DER encoding.
	 */
  std::vector<uint8_t> buf2;
  erval = t.EncodeDer(buf2);
	assert(erval.encoded != -1);
	if(erval.encoded != sizeof(buf1)) {
		printf("%d != %d\n", (int)erval.encoded, (int)sizeof(buf1));
	}
	assert(erval.encoded == (ssize_t)sizeof(buf1));
	for(i = 0; i < (ssize_t)sizeof(buf1); i++) {
		if(buf1[i] != buf2[i]) {
			fprintf(stderr, "Recreated buffer content mismatch:\n");
			fprintf(stderr, "Byte %d, %x != %x (%d != %d)\n",
				i,
				buf1[i], buf2[i],
				buf1[i], buf2[i]
			);
		}
		assert(buf1[i] == buf2[i]);
	}

	fprintf(stderr, "=== asn_fprint() ===\n");
  ret = t.Print(std::cerr);
	assert(ret == true);
	fprintf(stderr, "=== EOF ===\n");
}

static void
try_corrupt(uint8_t *buf, size_t size) {
	uint8_t *tmp;
	int i;

	fprintf(stderr, "\nCorrupting...\n");

	tmp = (uint8_t*)alloca(size);

	for(i = 0; i < 1000; i++) {
		int loc;
		memcpy(tmp, buf, size);

		/* Corrupt random _non-value_ location. */
		do { loc = random() % size; } while(tmp[loc] >= 70);
		do { tmp[loc] ^= random(); } while(tmp[loc] == buf[loc]);

		fprintf(stderr, "\nTry %d: corrupting byte %d (%d->%d)\n",
			i, loc, buf[loc], tmp[loc]);

		check(0, tmp, size, size);
	}
}

int
main(int ac, char **av) {

	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */

	check(1, buf1, sizeof(buf1), sizeof(buf1));
	try_corrupt(buf1, sizeof(buf1));
	check(1, buf1, sizeof(buf1) + 10, sizeof(buf1));

	return 0;
}
