/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <INTEGER.hpp>
#include <asn_codecs_prim.hpp>	/* Encoder and decoder of a primitive type */
#include <errno.h>

/*
 * INTEGER basic type description.
 */
static const ber_tlv_tag_t asn_DEF_INTEGER_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (2 << 2))
};
asn_TYPE_descriptor_t asn_DEF_INTEGER = {
	"INTEGER",
	"INTEGER",
	INTEGER_print<INTEGER>,
	asn_generic_no_constraint,
	ber_decode_primitive<INTEGER>,
	INTEGER_encode_der<INTEGER>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_INTEGER_tags,
	sizeof(asn_DEF_INTEGER_tags) / sizeof(asn_DEF_INTEGER_tags[0]),
	asn_DEF_INTEGER_tags,	/* Same as above */
	sizeof(asn_DEF_INTEGER_tags) / sizeof(asn_DEF_INTEGER_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

/*
 * Parse the number in the given string until the given *end position,
 * returning the position after the last parsed character back using the
 * same (*end) pointer.
 * WARNING: This behavior is different from the standard strtol(3).
 */
enum asn_strtol_result_e
asn_strtol_lim(const char *str, const char **end, long *lp) {
	int sign = 1;
	long l;

	const long upper_boundary = LONG_MAX / 10;
	long last_digit_max = LONG_MAX % 10;

	if(str >= *end) return ASN_STRTOL_ERROR_INVAL;

	switch(*str) {
	case '-':
		last_digit_max++;
		sign = -1;
	case '+':
		str++;
		if(str >= *end) {
			*end = str;
			return ASN_STRTOL_EXPECT_MORE;
		}
	}

	for(l = 0; str < (*end); str++) {
		switch(*str) {
		case 0x30: case 0x31: case 0x32: case 0x33: case 0x34:
		case 0x35: case 0x36: case 0x37: case 0x38: case 0x39: {
			int d = *str - '0';
			if(l < upper_boundary) {
				l = l * 10 + d;
			} else if(l == upper_boundary) {
				if(d <= last_digit_max) {
					if(sign > 0) {
						l = l * 10 + d;
					} else {
						sign = 1;
						l = -l * 10 - d;
					}
				} else {
					*end = str;
					return ASN_STRTOL_ERROR_RANGE;
				}
			} else {
				*end = str;
				return ASN_STRTOL_ERROR_RANGE;
			}
		    }
		    continue;
		default:
		    *end = str;
		    *lp = sign * l;
		    return ASN_STRTOL_EXTRA_DATA;
		}
	}

	*end = str;
	*lp = sign * l;
	return ASN_STRTOL_OK;
}

