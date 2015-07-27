/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <GeneralString.hpp>

/*
 * GeneralString basic type description.
 */
static const ber_tlv_tag_t asn_DEF_GeneralString_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (27 << 2)),	/* [UNIVERSAL 27] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))	/* ... OCTET STRING */
};
asn_TYPE_descriptor_t asn_DEF_GeneralString = {
	"GeneralString",
	"GeneralString",
	OCTET_STRING_print<GeneralString, std::string>,         /* non-ascii string */
	asn_generic_unknown_constraint,
	OCTET_STRING_decode_ber<GeneralString, std::string>,    /* Implemented in terms of OCTET STRING */
	OCTET_STRING_encode_der<GeneralString, std::string>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_GeneralString_tags,
	sizeof(asn_DEF_GeneralString_tags)
	  / sizeof(asn_DEF_GeneralString_tags[0]) - 1,
	asn_DEF_GeneralString_tags,
	sizeof(asn_DEF_GeneralString_tags)
	  / sizeof(asn_DEF_GeneralString_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

