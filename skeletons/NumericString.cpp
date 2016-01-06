/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <NumericString.hpp>

/*
 * NumericString basic type description.
 */
static const ber_tlv_tag_t asn_DEF_NumericString_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (18 << 2)),	/* [UNIVERSAL 18] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))	/* ... OCTET STRING */
};
asn_TYPE_descriptor_t asn_DEF_NumericString = {
	"NumericString",
	"NumericString",
	OCTET_STRING_print_utf8<NumericString, std::string>,   /* ASCII subset */
	NumericString_constraint,
	OCTET_STRING_decode_ber<NumericString, std::string>,    /* Implemented in terms of OCTET STRING */
	OCTET_STRING_encode_der<NumericString, std::string>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_NumericString_tags,
	sizeof(asn_DEF_NumericString_tags)
	  / sizeof(asn_DEF_NumericString_tags[0]) - 1,
	asn_DEF_NumericString_tags,
	sizeof(asn_DEF_NumericString_tags)
	  / sizeof(asn_DEF_NumericString_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

int
NumericString_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
		asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const NumericString *st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const NumericString*>(structPtr);
  }

	if(st) {
		const uint8_t *buf = reinterpret_cast<const uint8_t*>(st->data());
    const uint8_t *buf_beg = buf;
		const uint8_t *end = buf + st->size();

		/*
		 * Check the alphabet of the NumericString.
		 * ASN.1:1984 (X.409)
		 */
		for(; buf < end; buf++) {
			switch(*buf) {
			case 0x20:
			case 0x30: case 0x31: case 0x32: case 0x33: case 0x34:
			case 0x35: case 0x36: case 0x37: case 0x38: case 0x39:
				continue;
			}
			_ASN_CTFAIL(app_key, td, sptr,
				"%s: value byte %ld (%d) "
				"not in NumericString alphabet (%s:%d)",
				td->name,
				(long)((buf - buf_beg) + 1),
				*buf,
				__FILE__, __LINE__);
			return -1;
		}
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}

	return 0;
}
