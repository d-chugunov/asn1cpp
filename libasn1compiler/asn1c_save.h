#ifndef	_ASN1C_SAVE_H_
#define	_ASN1C_SAVE_H_

#include <asn1c_internal.h>

int asn1c_save_compiled_output(arg_t *arg, const char *datadir,
	int argc, int optc, char **argv);

void asn1c_set_single_unit(const char* filename);

#endif	/* _ASN1C_SAVE_H_ */
