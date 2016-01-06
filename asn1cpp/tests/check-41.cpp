#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include <iostream>

#ifdef SINGLE_UNIT
#include <asn.hpp>
#else
#include <T.hpp>
#endif

using namespace ModuleTestIntOptional;

uint8_t buf1[] = {
	32 | (2 << 6),		/* [0], constructed */
	25,	/* L */

	/* string   [0] IMPLICIT UTF8String, */
	(2 << 6),			/* [0] */
	16,	/* L */
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',

	/* beta    [2] IMPLICIT INTEGER OPTIONAL */
	(2 << 6) + 2,			/* [2] */
	5,	/* L */
  0,
  75,
  0x4b,
  75,
  75,
};

uint8_t buf1_reconstr[] = {
	32 | (2 << 6),		/* [0], constructed */
	24,	/* L */

	/* string   [0] IMPLICIT UTF8String, */
	(2 << 6),			/* [0] */
	16,	/* L */
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',

	/* beta    [2] IMPLICIT INTEGER OPTIONAL */
	(2 << 6) + 2,			/* [2] */
	4,	/* L */
  75,
  75,
  75,
  0x4b,
};


static void
check(T *tp, uint8_t *buf, size_t size, size_t consumed) {
	asn_dec_rval_t rval;

	fprintf(stderr, "Buf %p (%zd)\n", buf, size);
  rval = tp->DecodeBer(buf, size);
	fprintf(stderr, "Returned code %d, consumed %zd\n",
		(int)rval.code, rval.consumed);

	assert(rval.code == RC_OK);
	assert(rval.consumed == consumed);

  assert(tp->FetchPresent() == T::PR_seq);
#ifdef PTR_CHOICE_GETTERS
	assert(tp->seq()->string.size() == 16);
	assert(tp->seq()->string == "zzzzzzzzzzzzzzzz");
	assert(!tp->seq()->alpha);
	assert(tp->seq()->beta);
	assert(*tp->seq()->beta == 0x4b4b4b4b);
#else
	assert(tp->seq().string.size() == 16);
	assert(tp->seq().string == "zzzzzzzzzzzzzzzz");
	assert(!tp->seq().alpha);
	assert(tp->seq().beta);
	assert(*tp->seq().beta == 0x4b4b4b4b);
#endif
}

static void
compare(T *tp, uint8_t *cmp_buf, int cmp_buf_size) {
	asn_enc_rval_t erval;
	int i;

	std::vector<uint8_t> buf;

	/*
	 * Try to re-create using DER encoding.
	 */
  erval = tp->EncodeDer(buf);
	assert(erval.encoded != -1);
	if(erval.encoded != cmp_buf_size) {
		printf("%zd != %zd\n", erval.encoded, cmp_buf_size);
	}
	assert(erval.encoded == cmp_buf_size);
	for(i = 0; i < cmp_buf_size; i++) {
		if(buf[i] != cmp_buf[i]) {
			fprintf(stderr, "Recreated buffer content mismatch:\n");
			fprintf(stderr, "Byte %d, %x != %x (%d != %d)\n",
				i,
				buf[i], cmp_buf[i],
				buf[i], cmp_buf[i]
			);
		}
		assert(buf[i] == cmp_buf[i]);
	}
}

static void
partial_read(uint8_t *buf_0, size_t size) {
	T t;
	asn_dec_rval_t rval;
	size_t i1, i2;
	uint8_t *buf_1 = (uint8_t*)alloca(size);
	uint8_t *buf_2 = (uint8_t*)alloca(size);
	uint8_t *buf_3 = (uint8_t*)alloca(size);

	fprintf(stderr, "\nPartial read sequence...\n");

	/*
	 * Divide the space (size) into three blocks in various combinations:
	 *   |<----->i1<----->i2<----->|
	 *   ^ buf_0                    ^ buf_0+size
	 * Try to read block by block.
	 */
	for(i1 = 0; i1 < size; i1++) {
		for(i2 = i1; i2 < size; i2++) {
			uint8_t *chunk1 = buf_0;
			size_t size1 = i1;
			uint8_t *chunk2 = buf_0 + size1;
			size_t size2 = i2 - i1;
			uint8_t *chunk3 = buf_0 + size1 + size2;
			size_t size3 = size - size1 - size2;

			fprintf(stderr, "\n%zd:{%zd, %zd, %zd}...\n",
				size, size1, size2, size3);

			memset(buf_1, 0, size);
			memset(buf_2, 0, size);
			memset(buf_3, 0, size);
			memcpy(buf_1, chunk1, size1);
			memcpy(buf_2, chunk2, size2);
			memcpy(buf_3, chunk3, size3);

			fprintf(stderr, "=> Chunk 1 (%zd):\n", size1);
      rval = t.DecodeBer(buf_1, size1);
			assert(rval.code == RC_WMORE);
			assert(rval.consumed <= size1);
			if(rval.consumed < size1) {
				int leftover = size1 - rval.consumed;
				memcpy(buf_2, buf_1 + rval.consumed, leftover);
				memcpy(buf_2 + leftover, chunk2, size2);
				size2 += leftover;
			}

			fprintf(stderr, "=> Chunk 2 (%zd):\n", size2);
      rval = t.DecodeBer(buf_2, size2);
			assert(rval.code == RC_WMORE);
			assert(rval.consumed <= size2);
			if(rval.consumed < size2) {
				int leftover = size2 - rval.consumed;
				memcpy(buf_3, buf_2 + rval.consumed, leftover);
				memcpy(buf_3 + leftover, chunk3, size3);
				size3 += leftover;
			}

			fprintf(stderr, "=> Chunk 3 (%zd):\n", size3);
      rval = t.DecodeBer(buf_3, size3);
			assert(rval.code == RC_OK);
			assert(rval.consumed == size3);
		}
	}
}

int
main(int ac, char **av) {
	T t;

	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */

	/* Check exact buf1 */
	check(&t, buf1, sizeof(buf1), sizeof(buf1));
	compare(&t, buf1_reconstr, sizeof(buf1_reconstr));
  t.Print(std::cerr);

	/* Check slightly more than buf1 */
	check(&t, buf1, sizeof(buf1) + 10, sizeof(buf1));
	compare(&t, buf1_reconstr, sizeof(buf1_reconstr));
  t.Print(std::cerr);

	/* Split the buffer in parts and check decoder restartability */
	partial_read(buf1, sizeof(buf1));

	return 0;
}
