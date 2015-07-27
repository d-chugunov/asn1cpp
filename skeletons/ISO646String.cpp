/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <ISO646String.hpp>

/*
 * ISO646String basic type description.
 */
static const ber_tlv_tag_t asn_DEF_ISO646String_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (26 << 2)),	/* [UNIVERSAL 26] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))	/* ... OCTET STRING */
};
asn_TYPE_descriptor_t asn_DEF_ISO646String = {
	"ISO646String",
	"ISO646String",
	OCTET_STRING_print_utf8<ISO646String, std::string>,	/* ASCII subset */
	VisibleString_constraint<ISO646String>,
	OCTET_STRING_decode_ber<ISO646String, std::string>,    /* Implemented in terms of OCTET STRING */
	OCTET_STRING_encode_der<ISO646String, std::string>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_ISO646String_tags,
	sizeof(asn_DEF_ISO646String_tags)
	  / sizeof(asn_DEF_ISO646String_tags[0]) - 1,
	asn_DEF_ISO646String_tags,
	sizeof(asn_DEF_ISO646String_tags)
	  / sizeof(asn_DEF_ISO646String_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};
