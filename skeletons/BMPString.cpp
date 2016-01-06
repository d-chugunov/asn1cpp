/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <BMPString.hpp>
#include <UTF8String.hpp>

/*
 * BMPString basic type description.
 */
static const ber_tlv_tag_t asn_DEF_BMPString_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (30 << 2)),	/* [UNIVERSAL 30] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))	/* ... OCTET STRING */
};
static asn_OCTET_STRING_specifics_t asn_DEF_BMPString_specs = {
	asn_OCTET_STRING_specifics_t::ASN_OSUBV_U16	/* 16-bits character */
};
asn_TYPE_descriptor_t asn_DEF_BMPString = {
	"BMPString",
	"BMPString",
	BMPString_print,
	asn_generic_no_constraint,  /* No constraint by default */
	OCTET_STRING_decode_ber<BMPString, std::vector<uint8_t>>,
	OCTET_STRING_encode_der<BMPString, std::vector<uint8_t>>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_BMPString_tags,
	sizeof(asn_DEF_BMPString_tags)
	  / sizeof(asn_DEF_BMPString_tags[0]) - 1,
	asn_DEF_BMPString_tags,
	sizeof(asn_DEF_BMPString_tags)
	  / sizeof(asn_DEF_BMPString_tags[0]),
	0, 0,	/* No members */
	&asn_DEF_BMPString_specs
};

/*
 * BMPString specific contents printer.
 */
static ssize_t
BMPString__dump(const BMPString *st,
		asn_app_consume_bytes_f *cb, void *app_key) {
	char scratch[128];			/* Scratchpad buffer */
	char *p = scratch;
	ssize_t wrote = 0;
	const uint8_t *ch;
	const uint8_t *end;

	ch = st->data();
	end = (ch + st->size());
	for(end--; ch < end; ch += 2) {
		uint16_t wc = (ch[0] << 8) | ch[1];	/* 2 bytes */
		if(sizeof(scratch) - (p - scratch) < 3) {
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
		} else {
			*p++ = 0xe0 | ((wc >> 12));
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
BMPString_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
		asn_app_consume_bytes_f *cb, void *app_key) {
	const BMPString *st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const BMPString*>(structPtr);
  }

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(!st)
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;

	if(BMPString__dump(st, cb, app_key) < 0)
		return -1;

	return 0;
}

