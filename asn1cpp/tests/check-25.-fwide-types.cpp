#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#include <T.hpp>

using namespace ModuleTestMisc;

uint8_t buf1[] = {
	32 | 16,		/* [UNIVERSAL 16], constructed */
	128,	/* L */
	/* a INTEGER */
	2,			/* [UNIVERSAL 2] */
	2,	/* L */
  150,
  70,
	/* b [2] IMPLICIT BOOLEAN */
	128 | 2,		/* [2] */
	1,	/* L */
  0xff,
	/* c NULL */
	5,			/* [UNIVERSAL 5] */
	0,	/* L */
	/* d ENUMERATED */
	10,			/* [UNIVERSAL 10] */
	1,	/* L */
  222,
	/* e OCTET STRING */
	4,			/* [UNIVERSAL 4] */
	3,	/* L */
	'x',
	'y',
	'z',
	/*
	 * X.690 specifies that inner structures must be tagged by
	 * stripping off the outer tag for each subsequent level.
	 */
	/* f [5] IMPLICIT VisibleString */
	128 | 32 | 5,		/* [5], constructed */
	128,	/* L indefinite */
		26,	/* [UNIVERSAL 26] (VisibleString), primitive */
		2,
  'l',
  'o',
		32 | 26,	/* [UNIVERSAL 26], recursively constructed */
		128,
			4,	/* [UNIVERSAL 4] (OCTET STRING), primitive */
			1,
  'v',
			4,	/* [UNIVERSAL 4], primitive */
			2,
  'e',
  '_',
		0,
		0,
		26,	/* [UNIVERSAL 26], primitive */
		2,
  'i',
  't',
	0,
	0,
	/* g BIT STRING */
	3,			/* [UNIVERSAL 3], primitive */
	3,	/* L */
	2,	/* Skip 2 bits */
	147,
	150,	/* => 148 */
	/* h [7] BIT STRING */
	128 | 32 | 7,			/* [7], constructed */
	128,	/* L indefinite */
		3,			/* [UNIVERSAL 3], primitive */
		3,	/* L */
		0,	/* Skip 0 bits */
		140,
		141,
		3,			/* [UNIVERSAL 3], primitive */
		2,	/* L */
		1,	/* Skip 1 bit */
		143,	/* => 142 */
	0,	/* End of h */
	0,
	0,	/* End of the whole structure */
	0,
	/* Three bytes of planned leftover */
	111, 222, 223
};

static void
check(int is_ok, uint8_t *buf, size_t size, size_t consumed) {
	T t;
	asn_dec_rval_t rval;

	fprintf(stderr, "Buf %p (%zd)\n", buf, size);
  rval = t.DecodeBer(buf, size);
	fprintf(stderr, "Returned code %d, consumed %zd, expected %zd\n",
		(int)rval.code, rval.consumed, consumed);

	if(is_ok) {
		assert(rval.code == RC_OK);
		assert(rval.consumed == consumed);

    const char* eStr = "xyz";
		assert(*t.e == std::vector<uint8_t>(eStr, eStr + strlen(eStr)));
		assert(*t.f == "love_it");

		assert(t.g->size() == 2);
		assert(t.g->GetBitsUnused() == 2);
		fprintf(stderr, "%d %d\n", (*t.g)[0], (*t.g)[1]);
		assert((*t.g)[0] == 147);
		assert((*t.g)[1] != 150);
		assert((*t.g)[1] == 148);

		assert(t.h->size() == 3);
		assert(t.h->GetBitsUnused() == 1);
		assert((*t.h)[0] == 140);
		assert((*t.h)[1] == 141);
		assert((*t.h)[2] == 142);
	} else {
		if(rval.code == RC_OK) {
			assert(t.a.size() != 2
			|| !t.d
			|| t.d->size() != 1
			|| !t.e
			|| t.e->size() != 3
			|| !t.f
			|| t.f->size() != 7
			|| !t.g
			|| t.g->size() != 2
			|| !t.h
			|| t.h->size() != 3
			);
		}
		fprintf(stderr, "%zd %zd\n", rval.consumed, consumed);
		assert(rval.consumed <= consumed);
	}
}

static void
try_corrupt(uint8_t *buf, size_t size, int allow_consume) {
	uint8_t *tmp;
	int i;

	fprintf(stderr, "\nCorrupting...\n");

	tmp = (uint8_t*)alloca(size);

	for(i = 0; i < 1000; i++) {
		int loc;
		memcpy(tmp, buf, size);

		/* Corrupt random _non-value_ location. */
		do { loc = random() % size; } while(
			loc == 44	/* bit skips */
			|| loc == 51	/* bit skips */
			|| loc == 56	/* bit skips */
			|| tmp[loc] >= 70);
		do { tmp[loc] = buf[loc] ^ random(); } while(
			(tmp[loc] == buf[loc])
			|| (buf[loc] == 0 && tmp[loc] == 0x80));

		fprintf(stderr, "\nTry %d: corrupting byte %d (%d->%d)\n",
			i, loc, buf[loc], tmp[loc]);

		check(0, tmp, size, allow_consume);
	}
}

static void
partial_read(uint8_t *buf, size_t size) {
	T t;
	asn_dec_rval_t rval;
	size_t i1, i2;
	uint8_t *tbuf1 = (uint8_t*)alloca(size);
	uint8_t *tbuf2 = (uint8_t*)alloca(size);
	uint8_t *tbuf3 = (uint8_t*)alloca(size);

	fprintf(stderr, "\nPartial read sequence...\n");

	/*
	 * Divide the space (size) into three blocks in various combinations:
	 *   |<----->i1<----->i2<----->|
	 *   ^ buf                     ^ buf+size
	 * Try to read block by block.
	 */
	for(i1 = 0; i1 < size; i1++) {
		for(i2 = i1; i2 < size; i2++) {
			uint8_t *chunk1 = buf;
			size_t size1 = i1;
			uint8_t *chunk2 = buf + size1;
			size_t size2 = i2 - i1;
			uint8_t *chunk3 = buf + size1 + size2;
			size_t size3 = size - size1 - size2;

			fprintf(stderr, "\n%d:{%d, %d, %d}...\n",
				(int)size, (int)size1, (int)size2, (int)size3);

			memset(tbuf1, 0, size);
			memset(tbuf2, 0, size);
			memset(tbuf3, 0, size);
			memcpy(tbuf1, chunk1, size1);
			memcpy(tbuf2, chunk2, size2);
			memcpy(tbuf3, chunk3, size3);

			fprintf(stderr, "=> Chunk 1 (%d):\n", (int)size1);
      rval = t.DecodeBer(tbuf1, size1);
			assert(rval.code == RC_WMORE);
			assert(rval.consumed <= size1);
			if(rval.consumed < size1) {
				int leftover = size1 - rval.consumed;
				memcpy(tbuf2, tbuf1 + rval.consumed, leftover);
				memcpy(tbuf2 + leftover, chunk2, size2);
				size2 += leftover;
			}

			fprintf(stderr, "=> Chunk 2 (%d):\n", (int)size2);
      rval = t.DecodeBer(tbuf2, size2);
			assert(rval.code == RC_WMORE);
			assert(rval.consumed <= size2);
			if(rval.consumed < size2) {
				int leftover = size2 - rval.consumed;
				memcpy(tbuf3, tbuf2 + rval.consumed, leftover);
				memcpy(tbuf3 + leftover, chunk3, size3);
				size3 += leftover;
			}

			fprintf(stderr, "=> Chunk 3 (%d):\n", (int)size3);
      rval = t.DecodeBer(tbuf3, size3);
			assert(rval.code == RC_OK);
			assert(rval.consumed == size3);
		}
	}
}

int
main(int ac, char **av) {

	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */

	/* Check that the full buffer may be decoded normally */
	check(1, buf1, sizeof(buf1), sizeof(buf1) - 3);

	/* Check that some types of buffer corruptions will lead to failure */
	try_corrupt(buf1, sizeof(buf1) - 3, sizeof(buf1) - 3);

	/* Split the buffer in parts and check decoder restartability */
	partial_read(buf1, sizeof(buf1) - 3);

	return 0;
}
