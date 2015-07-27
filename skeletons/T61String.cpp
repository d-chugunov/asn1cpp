/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <T61String.hpp>

/*
 * T61String basic type description.
 */
static const ber_tlv_tag_t asn_DEF_T61String_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (20 << 2)),	/* [UNIVERSAL 20] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))	/* ... OCTET STRING */
};
asn_TYPE_descriptor_t asn_DEF_T61String = {
	"T61String",
	"T61String",
	OCTET_STRING_print<T61String, std::string>,         /* non-ascii string */
	asn_generic_unknown_constraint,
	OCTET_STRING_decode_ber<T61String, std::string>,    /* Implemented in terms of OCTET STRING */
	OCTET_STRING_encode_der<T61String, std::string>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_T61String_tags,
	sizeof(asn_DEF_T61String_tags)
	  / sizeof(asn_DEF_T61String_tags[0]) - 1,
	asn_DEF_T61String_tags,
	sizeof(asn_DEF_T61String_tags)
	  / sizeof(asn_DEF_T61String_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

