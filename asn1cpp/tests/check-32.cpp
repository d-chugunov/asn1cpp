#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#include <Programming.hpp>
#include <SeqWithMandatory.hpp>
#include <SeqWithOptional.hpp>

using namespace ModuleTestSequenceSimple;

int
main(int ac, char **av) {
	Programming p;
	SeqWithMandatory swm;
	SeqWithOptional swo;
	Error err;
	asn_enc_rval_t erv;
	asn_dec_rval_t drv;
	std::vector<uint8_t> buf;

	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */

	/*
	 * No plans to fill Programming_t up:
	 * just checking whether it compiles or not.
	 */
  p.Clear();

	/*
	 * Construct a dummy sequence:
	 * SeqWithMandatory ::= {
	 * 	seqOfMan [0] EXPLICIT SEQUENCE OF Error
	 * }
	 */
  swm.someString = "Oley";
  swm.seqOfMan.push_back(err);

	/*
	 * Encode the sequence.
	 */
  erv = swm.EncodeDer(buf);
	assert(erv.encoded > 0);
  buf.reserve(erv.encoded);
	buf[erv.encoded] = '\0';

	/*
	 * Try to decode it using a compatible type.
	 */
  drv = swo.DecodeBer(buf);
	assert(drv.code == RC_OK);
	assert((ssize_t)drv.consumed == erv.encoded);
	assert(swo.seqOfOpt != 0);
	
#ifdef INSECURE_POINTERS
	delete swo.seqOfOpt;
	swo.seqOfOpt = 0;
#else
	swo.seqOfOpt.reset();
#endif

  erv = swo.EncodeDer(buf);
	assert(erv.encoded > 0);
  buf.reserve(erv.encoded);
	buf[erv.encoded] = '\0';

	swm.Clear();
  drv = swm.DecodeBer(buf);
	assert(drv.code != RC_OK);
	swo.Clear();
  drv = swo.DecodeBer(buf);
	assert(drv.code == RC_OK);
	assert((ssize_t)drv.consumed == erv.encoded);
	assert(!swo.seqOfOpt);
  
	printf("Finished\n");

	return 0;
}
