/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <GraphicString.hpp>

/*
 * GraphicString basic type description.
 */
static const ber_tlv_tag_t asn_DEF_GraphicString_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (25 << 2)),	/* [UNIVERSAL 25] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))	/* ... OCTET STRING */
};
asn_TYPE_descriptor_t asn_DEF_GraphicString = {
	"GraphicString",
	"GraphicString",
	OCTET_STRING_print<GraphicString, std::string>,         /* non-ascii string */
	asn_generic_unknown_constraint,
	OCTET_STRING_decode_ber<GraphicString, std::string>,    /* Implemented in terms of OCTET STRING */
	OCTET_STRING_encode_der<GraphicString, std::string>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_GraphicString_tags,
	sizeof(asn_DEF_GraphicString_tags)
	  / sizeof(asn_DEF_GraphicString_tags[0]) - 1,
	asn_DEF_GraphicString_tags,
	sizeof(asn_DEF_GraphicString_tags)
	  / sizeof(asn_DEF_GraphicString_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

