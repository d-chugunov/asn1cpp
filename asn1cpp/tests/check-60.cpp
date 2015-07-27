#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#include <T1.hpp>
#include <T2.hpp>
#include <iostream>

using namespace ModuleTestANY;

std::vector<uint8_t> buf;

static int
save_object(AsnAbstractType *bs) {
	asn_enc_rval_t rval; /* Return value */
	int i;

  rval = bs->EncodeDer(buf);
	if (rval.encoded == -1) {
		fprintf(stderr,
			"Cannot encode %s: %s\n",
			rval.failed_type->name, strerror(errno));
		assert(rval.encoded != -1);
		return -1;	/* JIC */
	}

	buf.push_back(0xab);	/* Finalize with garbage */

  bs->Print(std::cerr);

	printf("OUT: [");
	for(i = 0; i < buf.size(); i++)
		printf(" %02x", buf[i]);
	printf("]\n");

	return 0;
}

static int
load_object(AsnAbstractType *bs) {
	asn_dec_rval_t rval;

	fprintf(stderr, "\nLOADING OBJECT OF SIZE %d\n", buf.size());

  rval = bs->DecodeBer(buf);
	assert(rval.code == RC_OK);

  bs->Print(std::cerr);

	return (rval.code == RC_OK)?0:-1;
}

/* [3] IMPLICIT SEQUENCE { b BOOLEAN } */
uint8_t test_any_buf1[] = { 0xa3, 0x80, /* [3], constructed, indefinite */
	0x01, 0x01, 0xff,	/* b BOOLEAN ::= TRUE */
	0x00, 0x00 /* End of content octets */ };

/* b BOOLEAN */
uint8_t test_any_buf2[] = { 0x01, 0x01, 0x13 };

int
main() {
	T1 t1, t1_new;
	T2 t2, t2_new;
	int ret;

	/*
	 * Test the T1 with constructed indefinite length ANY encoding.
	 */

	t1.i = 112233;
  t1.any.insert(t1.any.end(), test_any_buf1, test_any_buf1 + sizeof(test_any_buf1));

	/* Save->Load must succeed */
	save_object(&t1);
	ret = load_object(&t1_new);

	assert(ret == 0);
	assert(t1_new.i == 112233);
	assert(t1_new.any.size() == (ssize_t)sizeof(test_any_buf1));
	assert(t1_new.any == std::vector<uint8_t>(test_any_buf1, test_any_buf1 + sizeof(test_any_buf1)));

	/*
	 * Test the T1 with primitive encoding.
	 */
  t1.Clear();
  t1_new.Clear();
	t1.i = -112233;
	t1.any.insert(t1.any.end(), test_any_buf2, test_any_buf2 + sizeof(test_any_buf2));

	/* Save->Load must succeed */
	save_object(&t1);
	ret = load_object(&t1_new);

	assert(ret == 0);
	assert(t1_new.i == -112233);
	assert(t1_new.any.size() == (ssize_t)sizeof(test_any_buf2));
	assert(t1_new.any == std::vector<uint8_t>(test_any_buf2, test_any_buf2 + sizeof(test_any_buf2)));

	/*
	 * Test the T2 empty sequence.
	 */
	t2.i = 332211;
#ifdef INSECURE_POINTERS
	delete t2.any;
	t2.any = new ANY();
#else
  t2.any.reset(new ANY());
#endif

	/* Save->Load must succeed */
	save_object(&t2);
	ret = load_object(&t2_new);

	assert(ret == 0);
	assert(t2_new.i == 332211);
	assert(t2_new.any->size() == 0);

	/*
	 * Test the T2 sequence.
	 */
  t2.Clear();
  t2_new.Clear();

	t2.i = 332211;
#ifdef INSECURE_POINTERS
	delete t2.any;
	t2.any = new ANY();
#else
  t2.any.reset(new ANY());
#endif
  t2.any->insert(t2.any->end(), test_any_buf1, test_any_buf1 + sizeof(test_any_buf1));

	/* Save->Load must succeed */
	save_object(&t2);
	ret = load_object(&t2_new);

	assert(ret == 0);
	assert(t2_new.i == 332211);
	assert(t2_new.any->size() == (ssize_t)sizeof(test_any_buf1));
	assert(*t2_new.any == std::vector<uint8_t>(test_any_buf1, test_any_buf1 + sizeof(test_any_buf1)));

	/*
	 * Test the T2 sequence with primitive encoding.
	 */
  t2.Clear();
  t2_new.Clear();
	t2.i = 0;
#ifdef INSECURE_POINTERS
	delete t2.any;
	t2.any = new ANY();
#else
  t2.any.reset(new ANY());
#endif
  t2.any->insert(t2.any->end(), test_any_buf2, test_any_buf2 + sizeof(test_any_buf2));

	/* Save->Load must succeed */
	save_object(&t2);
	ret = load_object(&t2_new);

	assert(ret == 0);
	assert(t2_new.i == 0);
	assert(t2_new.any->size() == (ssize_t)sizeof(test_any_buf2));
	assert(*t2_new.any == std::vector<uint8_t>(test_any_buf2, test_any_buf2 + sizeof(test_any_buf2)));

	/*
	 * Test T2 with ANY element omitted.
	 */
#ifdef INSECURE_POINTERS
  delete t2.any;
  t2.any = 0;
#else
  t2.any.reset();
#endif
  t2_new.Clear();

	save_object(&t2);
	ret = load_object(&t2_new);

	assert(ret == 0);
	assert(t2_new.i == 0);
	assert(!t2_new.any);

	printf("OK\n");

	return ret;
}
