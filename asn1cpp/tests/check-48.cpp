#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <iostream>

#include <UserIdentifier.hpp>

using namespace ModuleSetChoiceExtensibility;

std::vector<uint8_t> buf;

static int
save_object(UserIdentifier *bs) {
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

	buf.push_back(123);	/* Finalize with garbage */

  bs->Print(std::cerr);
  fprintf(stderr, "\n");

	printf("OUT: [");
	for(i = 0; i < buf.size(); i++)
		printf(" %02x", buf[i]);
	printf("]\n");

	return 0;
}

static int
load_object(UserIdentifier *bs) {
	asn_dec_rval_t rval;

	fprintf(stderr, "\nLOADING OBJECT OF SIZE %d\n", buf.size());

  rval = bs->DecodeBer(buf);
	assert(rval.code == RC_OK);

  bs->Print(std::cerr);
  fprintf(stderr, "\n");

	return (rval.code == RC_OK)?0:-1;
}

int
main() {
	UserIdentifier user;
	UserIdentifier user_new;
	int ret;

  user.phoneNumber(new IA5String());
#ifdef PTR_CHOICE_GETTERS
  *user.phoneNumber() = "0123456789";
#else
  user.phoneNumber() = "0123456789";
#endif

	/* Save->Load must succeed */
	save_object(&user);
	ret = load_object(&user_new);

	assert(user_new.FetchPresent() == UserIdentifier::PR_phoneNumber);

	assert(ret == 0);

	printf("OK\n");

	return ret;
}
