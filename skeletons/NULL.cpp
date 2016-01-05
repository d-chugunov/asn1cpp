/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <asn_codecs_prim.hpp>
#include <NULL.hpp>
#include <BOOLEAN.hpp>	/* Implemented in terms of BOOLEAN type */

/*
 * NULL basic type description.
 */
static const ber_tlv_tag_t asn_DEF_NULL_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (5 << 2))
};
asn_TYPE_descriptor_t asn_DEF_NULL = {
	"NULL",
	"NULL",
	NULL_print,
	asn_generic_no_constraint,
	BOOLEAN_decode_ber<NULL_t>,	/* Implemented in terms of BOOLEAN */
	NULL_encode_der,	/* Special handling of DER encoding */
	0, /* Use generic outmost tag fetcher */
	asn_DEF_NULL_tags,
	sizeof(asn_DEF_NULL_tags) / sizeof(asn_DEF_NULL_tags[0]),
	asn_DEF_NULL_tags,	/* Same as above */
	sizeof(asn_DEF_NULL_tags) / sizeof(asn_DEF_NULL_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

asn_enc_rval_t
NULL_encode_der(asn_TYPE_descriptor_t *td, void *ptr,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
	asn_enc_rval_t erval;

	erval.encoded = der_write_tags(td, 0, tag_mode, 0, tag, cb, app_key);
	if(erval.encoded == -1) {
		erval.failed_type = td;
		erval.structure_ptr = ptr;
	}

	_ASN_ENCODED_OK(erval);
}

int
NULL_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
	asn_app_consume_bytes_f *cb, void *app_key) {

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(sptr) {
		return (cb("<present>", 9, app_key) < 0) ? -1 : 0;
	} else {
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;
	}
}

