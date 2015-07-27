/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <asn_codecs_prim.hpp>
#include <BOOLEAN.hpp>

/*
 * BOOLEAN basic type description.
 */
static const ber_tlv_tag_t asn_DEF_BOOLEAN_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (1 << 2))
};
asn_TYPE_descriptor_t asn_DEF_BOOLEAN = {
	"BOOLEAN",
	"BOOLEAN",
	BOOLEAN_print,
	asn_generic_no_constraint,
	BOOLEAN_decode_ber<BOOLEAN>,
	BOOLEAN_encode_der,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_BOOLEAN_tags,
	sizeof(asn_DEF_BOOLEAN_tags) / sizeof(asn_DEF_BOOLEAN_tags[0]),
	asn_DEF_BOOLEAN_tags,	/* Same as above */
	sizeof(asn_DEF_BOOLEAN_tags) / sizeof(asn_DEF_BOOLEAN_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

asn_enc_rval_t
BOOLEAN_encode_der(asn_TYPE_descriptor_t *td, void *sptr,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
	asn_enc_rval_t erval;
	_BOOLEANType *st = &static_cast<BOOLEAN*>(static_cast<AsnAbstractType*>(sptr))->value;

	erval.encoded = der_write_tags(td, 1, tag_mode, 0, tag, cb, app_key);
	if(erval.encoded == -1) {
		erval.failed_type = td;
		erval.structure_ptr = sptr;
		return erval;
	}

	if(cb) {
		uint8_t bool_value;

		bool_value = *st ? 0xff : 0; /* 0xff mandated by DER */

		if(cb(&bool_value, 1, app_key) < 0) {
			erval.encoded = -1;
			erval.failed_type = td;
			erval.structure_ptr = sptr;
			return erval;
		}
	}

	erval.encoded += 1;

	_ASN_ENCODED_OK(erval);
}

int
BOOLEAN_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
	asn_app_consume_bytes_f *cb, void *app_key) {
	const _BOOLEANType *st = &static_cast<const BOOLEAN*>(static_cast<const AsnAbstractType*>(sptr))->value;;
	const char *buf;
	size_t buflen;

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(st) {
		if(*st) {
			buf = "TRUE";
			buflen = 4;
		} else {
			buf = "FALSE";
			buflen = 5;
		}
	} else {
		buf = "<absent>";
		buflen = 8;
	}

	return (cb(buf, buflen, app_key) < 0) ? -1 : 0;
}
