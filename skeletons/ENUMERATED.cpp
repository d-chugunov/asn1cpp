/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <ENUMERATED.hpp>
#include <asn_codecs_prim.hpp>	/* Encoder and decoder of a primitive type */

/*
 * ENUMERATED basic type description.
 */
static const ber_tlv_tag_t asn_DEF_ENUMERATED_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_ENUMERATED = {
	"ENUMERATED",
	"ENUMERATED",
	INTEGER_print<ENUMERATED>,			/* Implemented in terms of INTEGER */
	asn_generic_no_constraint,
	ber_decode_primitive<ENUMERATED>,
	INTEGER_encode_der<ENUMERATED>,		/* Implemented in terms of INTEGER */
	0, /* Use generic outmost tag fetcher */
	asn_DEF_ENUMERATED_tags,
	sizeof(asn_DEF_ENUMERATED_tags) / sizeof(asn_DEF_ENUMERATED_tags[0]),
	asn_DEF_ENUMERATED_tags,	/* Same as above */
	sizeof(asn_DEF_ENUMERATED_tags) / sizeof(asn_DEF_ENUMERATED_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};


