/* 
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */

#include <asn_internal.hpp>
#include <ANY.hpp>
#include <errno.h>

static asn_OCTET_STRING_specifics_t asn_DEF_ANY_specs = {
	asn_OCTET_STRING_specifics_t::ASN_OSUBV_ANY
};
asn_TYPE_descriptor_t asn_DEF_ANY = {
	"ANY",
	"ANY",
	OCTET_STRING_print<ANY, std::vector<uint8_t>>,
	asn_generic_no_constraint,
	OCTET_STRING_decode_ber<ANY, std::vector<uint8_t>>,
	OCTET_STRING_encode_der<ANY, std::vector<uint8_t>>,
	0, /* Use generic outmost tag fetcher */
	0, 0, 0, 0,
	0, 0,	/* No members */
	&asn_DEF_ANY_specs,
};

