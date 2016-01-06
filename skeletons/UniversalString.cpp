/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <UniversalString.hpp>
#include <UTF8String.hpp>

/*
 * UniversalString basic type description.
 */
static const ber_tlv_tag_t asn_DEF_UniversalString_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (28 << 2)),	/* [UNIVERSAL 28] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))	/* ... OCTET STRING */
};
static asn_OCTET_STRING_specifics_t asn_DEF_UniversalString_specs = {
	asn_OCTET_STRING_specifics_t::ASN_OSUBV_U32	/* 32-bits character */
};
asn_TYPE_descriptor_t asn_DEF_UniversalString = {
	"UniversalString",
	"UniversalString",
	UniversalString_print,      /* Convert into UTF8 and print */
	asn_generic_no_constraint,
	OCTET_STRING_decode_ber<UniversalString, std::vector<uint8_t>>,
	OCTET_STRING_encode_der<UniversalString, std::vector<uint8_t>>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_UniversalString_tags,
	sizeof(asn_DEF_UniversalString_tags)
	  / sizeof(asn_DEF_UniversalString_tags[0]) - 1,
	asn_DEF_UniversalString_tags,
	sizeof(asn_DEF_UniversalString_tags)
	  / sizeof(asn_DEF_UniversalString_tags[0]),
	0, 0,	/* No members */
	&asn_DEF_UniversalString_specs
};


static ssize_t
UniversalString__dump(const UniversalString& st,
		asn_app_consume_bytes_f *cb, void *app_key) {
	char scratch[128];			/* Scratchpad buffer */
	char *p = scratch;
	ssize_t wrote = 0;
	const uint8_t *ch;
	const uint8_t *end;

	ch = st.data();
	end = (ch + st.size());
	for(end -= 3; ch < end; ch += 4) {
		uint32_t wc =     (ch[0] << 24)
				| (ch[1] << 16)
				| (ch[2] << 8)
				|  ch[3];	/* 4 bytes */
		if(sizeof(scratch) - (p - scratch) < 6) {
			wrote += p - scratch;
			if(cb(scratch, p - scratch, app_key) < 0)
				return -1;
			p = scratch;
		}
		if(wc < 0x80) {
			*p++ = (char)wc;
		} else if(wc < 0x800) {
			*p++ = 0xc0 | ((wc >> 6));
			*p++ = 0x80 | ((wc & 0x3f));
		} else if(wc < 0x10000) {
			*p++ = 0xe0 | ((wc >> 12));
			*p++ = 0x80 | ((wc >> 6) & 0x3f);
			*p++ = 0x80 | ((wc & 0x3f));
		} else if(wc < 0x200000) {
			*p++ = 0xf0 | ((wc >> 18));
			*p++ = 0x80 | ((wc >> 12) & 0x3f);
			*p++ = 0x80 | ((wc >> 6) & 0x3f);
			*p++ = 0x80 | ((wc & 0x3f));
		} else if(wc < 0x4000000) {
			*p++ = 0xf8 | ((wc >> 24));
			*p++ = 0x80 | ((wc >> 18) & 0x3f);
			*p++ = 0x80 | ((wc >> 12) & 0x3f);
			*p++ = 0x80 | ((wc >> 6) & 0x3f);
			*p++ = 0x80 | ((wc & 0x3f));
		} else {
			*p++ = 0xfc | ((wc >> 30) & 0x1);
			*p++ = 0x80 | ((wc >> 24) & 0x3f);
			*p++ = 0x80 | ((wc >> 18) & 0x3f);
			*p++ = 0x80 | ((wc >> 12) & 0x3f);
			*p++ = 0x80 | ((wc >> 6) & 0x3f);
			*p++ = 0x80 | ((wc & 0x3f));
		}
	}

	wrote += p - scratch;
	if(cb(scratch, p - scratch, app_key) < 0)
		return -1;

	return wrote;
}

int
UniversalString_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
	asn_app_consume_bytes_f *cb, void *app_key) {
	const UniversalString* st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const UniversalString*>(structPtr);
  }

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(!st) return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;

	if(UniversalString__dump(*st, cb, app_key) < 0)
		return -1;

	return 0;
}

