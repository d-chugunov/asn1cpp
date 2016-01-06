/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <RELATIVE-OID.hpp>
#include <OCTET_STRING.hpp>
#include <asn_codecs_prim.hpp>	/* Encoder and decoder of a primitive type */
#include <limits.h>	/* for CHAR_BIT */
#include <errno.h>

/*
 * RELATIVE-OID basic type description.
 */
static const ber_tlv_tag_t asn_DEF_RELATIVE_OID_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (13 << 2))
};
asn_TYPE_descriptor_t asn_DEF_RELATIVE_OID = {
	"RELATIVE-OID",
	"RELATIVE_OID",
	RELATIVE_OID_print,
	asn_generic_no_constraint,
	ber_decode_primitive<RELATIVE_OID>,
	der_encode_primitive<RELATIVE_OID>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_RELATIVE_OID_tags,
	sizeof(asn_DEF_RELATIVE_OID_tags)
	    / sizeof(asn_DEF_RELATIVE_OID_tags[0]),
	asn_DEF_RELATIVE_OID_tags,	/* Same as above */
	sizeof(asn_DEF_RELATIVE_OID_tags)
	    / sizeof(asn_DEF_RELATIVE_OID_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

static ssize_t
RELATIVE_OID__dump_body(const std::vector<uint8_t>& st, asn_app_consume_bytes_f *cb, void *app_key) {
	ssize_t wrote = 0;
	ssize_t ret;
	int startn;
	size_t i;

	for(i = 0, startn = 0; i < st.size(); i++) {
		uint8_t b = st[i];
		if((b & 0x80))			/* Continuation expected */
			continue;
		if(startn) {
			/* Separate arcs */
			if(cb(".", 1, app_key) < 0)
				return -1;
			wrote++;
		}

		ret = OBJECT_IDENTIFIER__dump_arc(&st[startn],
			i - startn + 1, 0, cb, app_key);
		if(ret < 0) return -1;
		wrote += ret;

		startn = i + 1;
	}

	return wrote;
}

int
RELATIVE_OID_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
	asn_app_consume_bytes_f *cb, void *app_key) {
	const RELATIVE_OID* st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const RELATIVE_OID*>(structPtr);
  }

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(!st)
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;

	/* Dump preamble */
	if(cb("{ ", 2, app_key) < 0)
		return -1;

	if(RELATIVE_OID__dump_body(*st, cb, app_key) < 0)
		return -1;

	return (cb(" }", 2, app_key) < 0) ? -1 : 0;
}


