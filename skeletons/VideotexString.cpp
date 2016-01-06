/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <VideotexString.hpp>

/*
 * VideotexString basic type description.
 */
static const ber_tlv_tag_t asn_DEF_VideotexString_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (21 << 2)),	/* [UNIVERSAL 21] IMPLICIT */
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))	/* ... OCTET STRING */
};
asn_TYPE_descriptor_t asn_DEF_VideotexString = {
	"VideotexString",
	"VideotexString",
	OCTET_STRING_print<VideotexString, std::string>,         /* non-ascii string */
	asn_generic_unknown_constraint,
	OCTET_STRING_decode_ber<VideotexString, std::string>,    /* Implemented in terms of OCTET STRING */
	OCTET_STRING_encode_der<VideotexString, std::string>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_VideotexString_tags,
	sizeof(asn_DEF_VideotexString_tags)
	  / sizeof(asn_DEF_VideotexString_tags[0]) - 1,
	asn_DEF_VideotexString_tags,
	sizeof(asn_DEF_VideotexString_tags)
	  / sizeof(asn_DEF_VideotexString_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

