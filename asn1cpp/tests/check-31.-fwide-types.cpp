#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include <iostream>

#include <Forest.hpp>

using namespace ModuleTestSetOfSimple;

uint8_t buf1[] = {
	32 | 17,		/* [UNIVERSAL 17], constructed */
	128,	/* L, indefinite */

	32 | 16,		/* [UNIVERSAL 16], constructed */
	6,	/* L */

	/* height INTEGER */
	2,			/* [UNIVERSAL 2] */
	1,	/* L */
  100,
	/* width INTEGER */
	2,			/* [UNIVERSAL 2] */
	1,	/* L */
  80,

	32 | 16,		/* [UNIVERSAL 16], constructed */
	6,	/* L */

	/* height INTEGER */
	2,			/* [UNIVERSAL 2] */
	1,	/* L */
  110,
	/* width INTEGER */
	2,			/* [UNIVERSAL 2] */
	1,	/* L */
  82,

	0,	/* End of forest */
	0
};

uint8_t buf1_reconstr[] = {
	32 | 17,		/* [UNIVERSAL 17], constructed */
	16,	/* L */

	32 | 16,		/* [UNIVERSAL 16], constructed */
	6,	/* L */

	/* height INTEGER */
	2,			/* [UNIVERSAL 2] */
	1,	/* L */
  100,
	/* width INTEGER */
	2,			/* [UNIVERSAL 2] */
	1,	/* L */
  80,

	32 | 16,		/* [UNIVERSAL 16], constructed */
	6,	/* L */

	/* height INTEGER */
	2,			/* [UNIVERSAL 2] */
	1,	/* L */
  110,
	/* width INTEGER */
	2,			/* [UNIVERSAL 2] */
	1,	/* L */
  82

};

size_t buf_pos;
static int bytes_compare(const void *bufferp, size_t size, void *key) {
	const uint8_t *buffer = (uint8_t*)bufferp;
	assert(buf_pos + size <= sizeof(buf1_reconstr));

	(void)key;	/* Unused argument */

	fprintf(stderr,  "  writing %zd (%zd)\n", size, buf_pos + size);

	for(; size; buf_pos++, size--, buffer++) {
		if(buf1_reconstr[buf_pos] != *buffer) {
			fprintf(stderr,
				"Byte %zd is different: %d != %d (%x != %x)\n",
				buf_pos,
				*buffer, buf1_reconstr[buf_pos],
				*buffer, buf1_reconstr[buf_pos]
			);
			assert(buf1_reconstr[buf_pos] == *buffer);
		}
	}

	return 0;
}

static void
check(int is_ok, uint8_t *buf, size_t size, size_t consumed) {
	Forest t;
	asn_dec_rval_t rval;

	fprintf(stderr, "Buf %p\n", buf);
  rval = t.DecodeBer(buf, size);
	fprintf(stderr, "Returned code %d, consumed %d\n",
		(int)rval.code, (int)rval.consumed);

	if(is_ok) {
		assert(rval.code == RC_OK);
		assert(rval.consumed == consumed);

		assert(t.size() == 2);
		assert(t[0].height.size() == 1);
		assert(t[0].width.size() == 1);
		assert(t[1].height.size() == 1);
		assert(t[1].width.size() == 1);
	} else {
		if(rval.code == RC_OK) {
			assert(t.size() != 2
			|| t[0].height.size() != 1
			|| t[0].width.size() != 1
			|| t[1].height.size() != 1
			|| t[1].width.size() != 1
			);
		}
		assert(rval.consumed <= consumed);
		return;
	}

	/*
	 * Try to re-create the buffer.
	 */
  std::vector<uint8_t> buf1_reconstr_(buf1_reconstr, buf1_reconstr + sizeof(buf1_reconstr));
  std::vector<uint8_t> encodeBuf;
  t.EncodeDer(encodeBuf);
	assert(encodeBuf == buf1_reconstr_);

  t.Print(std::cerr);
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
		do { tmp[loc] = buf[loc] ^ random(); } while(
			(tmp[loc] == buf[loc])
			|| (buf[loc] == 0 && tmp[loc] == 0x80));

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
	check(1, buf1, sizeof(buf1) + 20, sizeof(buf1));

	return 0;
}
