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
#include <LogLine.hpp>
#endif

using namespace ModuleLAPStorage;

uint8_t buf0[] = {
	48,	/* LogLine SEQUENCE */
	24,	/* L */
	22,	/* IA5String */
	4,	/* L */
	/* "zzz\007" */
  122, 122, 122, 7,
	48,	/* varsets SEQUENCE OF VariablePartSet */
	16,	/* L */
	48,	/* VariablePart */
	14,	/* L */
	48,	/* vparts SEQUENCE OF VariablePart */
	7,	/* L */
	49,	/* VariablePart */
	5,
	26,	/* VisibleString */
	3,
	49, 50, 51,	/* 1 2 3 */
	48,	/* ActionItem SEQUENCE */
	3,	/* L */
	10,	/* accept-as ENUMERATED */
	1,	/* L */
	0,
};

uint8_t buf1[] = {
	48,	/* LogLine SEQUENCE */
	19,	/* L */
	22,	/* IA5String */
	6,	/* L */
	/* "static" */
  115, 116, 97, 116, 105, 99,
	48,	/* varsets SEQUENCE OF VariablePartSet */
	9,	/* L */
	48,	/* VariablePart */
	7,	/* L */
	48,	/* vparts SEQUENCE OF VariablePart */
	0,	/* L */
	48,	/* ActionItem SEQUENCE */
	3,	/* L */
	10,	/* accept-as ENUMERATED */
	1,	/* L */
	0,
};

static void
check(LogLine *tp, uint8_t *ptr, size_t size, size_t consumed) {
	asn_dec_rval_t rval;

	fprintf(stderr, "Buf %p (%zd)\n", ptr, size);
  rval = tp->DecodeBer(ptr, size);
	fprintf(stderr, "Returned code %d, consumed %zd\n",	(int)rval.code, rval.consumed);

	assert(rval.code == RC_OK);
	assert(rval.consumed == consumed);
  //tp->Print(std::cerr);
}

static void
check_serialize() {
	LogLine ll;
	VariablePartSet vps;
	VariablePart vp;
	VisibleString vpart;
	asn_enc_rval_t erval;
	int i;

  vpart = "123";

  vp.vset(new class VariablePart::vset());
#ifdef PTR_CHOICE_GETTERS
  vp.vset()->push_back(vpart);
#else
  vp.vset().push_back(vpart);
#endif
	vps.resolution.accept_as = ActionItem::accept_as_unknown;
  vps.vparts.push_back(vp);
  ll.varsets.push_back(vps);
  ll.line_digest = "zzz\007";
  ll.line_digest.resize(4);
  
  //ll.Print(std::cerr);
  std::vector<uint8_t> buf;
  erval = ll.EncodeDer(buf);
	assert(erval.encoded > 1);
	fprintf(stderr, "Encoded in %zd bytes\n", erval.encoded);
	fprintf(stderr, "\n");
	for(i = 0; i < buf.size(); i++) {
		fprintf(stderr, "%d ", buf[i]);
	}
	fprintf(stderr, "\n\n");
	assert(erval.encoded == sizeof(buf0));
	assert(memcmp(buf0, buf.data(), sizeof(buf0)) == 0);
}

int
main(int ac, char **av) {
	LogLine t;

	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */

	check_serialize();
	check(&t, buf0, sizeof(buf0), sizeof(buf0));
	check(&t, buf1, sizeof(buf1), sizeof(buf1));

	return 0;
}
