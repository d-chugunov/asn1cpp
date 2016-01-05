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

uint8_t buf0[] = {
	32 | ((2 << 6) + 1),		/* [1], constructed */
	18,

	/* string   [0] IMPLICIT UTF8String, */
	(2 << 6),			/* [0] */
	16,	/* L */
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
};

uint8_t buf0_reconstr[] = {
	32 | ((2 << 6) + 1),		/* [1], constructed */
	18,

	/* string   [0] IMPLICIT UTF8String, */
	(2 << 6),			/* [0] */
	16,	/* L */
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
};



uint8_t buf1[] = {
	32 | (2 << 6),		/* [0], constructed */
	0x80 | 1,	/* L */
	134,

	/* string   [0] IMPLICIT UTF8String, */
	(2 << 6),			/* [0] */
	0x80 | 1,	/* L */
	128,
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',

	/* alpha    [1] IMPLICIT INTEGER OPTIONAL */
	(2 << 6) + 1,			/* [1] */
	1,	/* L */
  75,
};

uint8_t buf1_reconstr[] = {
        32 | (2 << 6),          /* [0], constructed */
	0x80 | 1,	/* L */
	134,

        /* string   [0] IMPLICIT UTF8String, */
        (2 << 6),                       /* [0] */
        0x80 | 1,       /* L */
        128,
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',

        /* alpha    [1] IMPLICIT INTEGER OPTIONAL */
        (2 << 6) + 1,                   /* [1] */
        1,      /* L */
  75,
};

uint8_t buf2[] = {
	32 | ((2 << 6) + 1),		/* [1], constructed */
	0x80 | 1,	/* L */
	134,

	/* string   [0] IMPLICIT UTF8String, */
	(2 << 6),			/* [0] */
	0x80 | 1,	/* L */
	128,
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',

	/* beta    [2] IMPLICIT INTEGER OPTIONAL */
	(2 << 6) + 2,			/* [2] */
	1,	/* L */
  75,
};

uint8_t buf2_reconstr[] = {
        32 | ((2 << 6) + 1),          /* [1], constructed */
	0x80 | 1,	/* L */
	134,

        /* string   [0] IMPLICIT UTF8String, */
        (2 << 6),                       /* [0] */
        0x80 | 1,       /* L */
        128,
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',
 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z',

        /* beta    [2] IMPLICIT INTEGER OPTIONAL */
        (2 << 6) + 2,                   /* [2] */
        1,      /* L */
  75,
};





static void
check(T *tp, uint8_t *buf, size_t size, size_t consumed) {
	asn_dec_rval_t rval;
	int ret;

	fprintf(stderr, "Buf %p (%zd)\n", buf, size);
  rval = tp->DecodeBer(buf, size);
	fprintf(stderr, "Returned code %d, consumed %zd\n",
		(int)rval.code, rval.consumed);

	assert(rval.code == RC_OK);
	assert(rval.consumed == consumed);

	fprintf(stderr, "=== asn_fprint() ===\n");
  ret = tp->Print(std::cerr);
	assert(ret == true);
	fprintf(stderr, "=== END ===\n");
	assert(ret == true);

	/*
	assert(tp->string.size == 128);
	assert(strncmp(tp->string.buf, "zz") == 0);
	assert(strcmp((char *)tp->b.choice.b1.buf, "z") == 0
		&& strcmp((char *)tp->b.choice.b2.buf, "z") == 0);
	*/
}

static void
compare(T *tp, uint8_t *cmp_buf, size_t cmp_buf_size) {
	asn_enc_rval_t erval;
	size_t i;

	std::vector<uint8_t> buffer;

	/*
	 * Try to re-create using DER encoding.
	 */
  erval = tp->EncodeDer(buffer);
	assert(erval.encoded != -1);
	if(erval.encoded != (ssize_t)cmp_buf_size) {
		printf("%zd != %zd\n", erval.encoded, cmp_buf_size);
	}
	assert(erval.encoded == (ssize_t)cmp_buf_size);
	for(i = 0; i < cmp_buf_size; i++) {
		if(buffer[i] != cmp_buf[i]) {
			fprintf(stderr, "Recreated buffer content mismatch:\n");
			fprintf(stderr, "Byte %d, %x != %x (%d != %d)\n",
				(int)i,
				buffer[i], cmp_buf[i],
				buffer[i], cmp_buf[i]
			);
		}
		assert(buffer[i] == cmp_buf[i]);
	}
}

static void
partial_read(uint8_t *data, size_t size) {
	T t;
	asn_dec_rval_t rval;
	size_t i1, i2;
	uint8_t *data1 = (uint8_t*)alloca(size);
	uint8_t *data2 = (uint8_t*)alloca(size);
	uint8_t *data3 = (uint8_t*)alloca(size);

	fprintf(stderr, "\nPartial read sequence...\n");

	/*
	 * Divide the space (size) into three blocks in various combinations:
	 *   |<----->i1<----->i2<----->|
	 *   ^ data                    ^ data+size
	 * Try to read block by block.
	 */
	for(i1 = 0; i1 < size; i1++) {
		for(i2 = i1; i2 < size; i2++) {
			uint8_t *chunk1 = data;
			size_t size1 = i1;
			uint8_t *chunk2 = data + size1;
			size_t size2 = i2 - i1;
			uint8_t *chunk3 = data + size1 + size2;
			size_t size3 = size - size1 - size2;

			fprintf(stderr, "\n%zd:{%zd, %zd, %zd}...\n",
				size, size1, size2, size3);

			memset(data1, 0, size);
			memset(data2, 0, size);
			memset(data3, 0, size);
			memcpy(data1, chunk1, size1);
			memcpy(data2, chunk2, size2);
			memcpy(data3, chunk3, size3);

			fprintf(stderr, "=> Chunk 1 (%zd):\n", size1);
      rval = t.DecodeBer(data1, size1);
			assert(rval.code == RC_WMORE);
			assert(rval.consumed <= size1);
			if(rval.consumed < size1) {
				int leftover = size1 - rval.consumed;
				memcpy(data2, data1 + rval.consumed, leftover);
				memcpy(data2 + leftover, chunk2, size2);
				size2 += leftover;
			}

			fprintf(stderr, "=> Chunk 2 (%zd):\n", size2);
      rval = t.DecodeBer(data2, size2);
			assert(rval.code == RC_WMORE);
			assert(rval.consumed <= size2);
			if(rval.consumed < size2) {
				int leftover = size2 - rval.consumed;
				memcpy(data3, data2 + rval.consumed, leftover);
				memcpy(data3 + leftover, chunk3, size3);
				size3 += leftover;
			}

			fprintf(stderr, "=> Chunk 3 (%zd):\n", size3);
      rval = t.DecodeBer(data3, size3);
			assert(rval.code == RC_OK);
			assert(rval.consumed == size3);
		}
	}
}

int
main() {
	T t;

	/* Check exact buf0 */
	check(&t, buf0, sizeof(buf0), sizeof(buf0));
	compare(&t, buf0_reconstr, sizeof(buf0_reconstr));

	/* Check exact buf1 */
	check(&t, buf1, sizeof(buf1), sizeof(buf1));
	compare(&t, buf1_reconstr, sizeof(buf1_reconstr));

	/* Check slightly more than buf1 */
	check(&t, buf1, sizeof(buf1) + 10, sizeof(buf1));
	compare(&t, buf1_reconstr, sizeof(buf1_reconstr));

	/* Check exact buf2 */
	check(&t, buf2, sizeof(buf2), sizeof(buf2));
	compare(&t, buf2_reconstr, sizeof(buf2_reconstr));

	/* Check slightly more than buf2 */
	check(&t, buf2, sizeof(buf2) + 10, sizeof(buf2));
	compare(&t, buf2_reconstr, sizeof(buf2_reconstr));

	/* Split the buffer in parts and check decoder restartability */
	partial_read(buf0, sizeof(buf0));

	return 0;
}
