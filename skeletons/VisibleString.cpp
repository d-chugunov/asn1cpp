/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <VisibleString.hpp>

/*
 * VisibleString basic type description.
 */
static const ber_tlv_tag_t asn_DEF_VisibleString_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (26 << 2)),	/* [UNIVERSAL 26] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))	/* ... OCTET STRING */
};
asn_TYPE_descriptor_t asn_DEF_VisibleString = {
	"VisibleString",
	"VisibleString",
	OCTET_STRING_print_utf8<VisibleString, std::string>,   /* ASCII subset */
	VisibleString_constraint<VisibleString>,
	OCTET_STRING_decode_ber<VisibleString, std::string>,    /* Implemented in terms of OCTET STRING */
	OCTET_STRING_encode_der<VisibleString, std::string>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_VisibleString_tags,
	sizeof(asn_DEF_VisibleString_tags)
	  / sizeof(asn_DEF_VisibleString_tags[0]) - 1,
	asn_DEF_VisibleString_tags,
	sizeof(asn_DEF_VisibleString_tags)
	  / sizeof(asn_DEF_VisibleString_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

