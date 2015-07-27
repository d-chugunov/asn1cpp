/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <PrintableString.hpp>

/*
 * ASN.1:1984 (X.409)
 */
static const int _PrintableString_alphabet[256] = {
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/*                  */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/*                  */
 1, 0, 0, 0, 0, 0, 0, 2, 3, 4, 0, 5, 6, 7, 8, 9,	/* .      '() +,-./ */
10,11,12,13,14,15,16,17,18,19,20, 0, 0,21, 0,22,	/* 0123456789:  = ? */
 0,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,	/*  ABCDEFGHIJKLMNO */
38,39,40,41,42,43,44,45,46,47,48, 0, 0, 0, 0, 0,	/* PQRSTUVWXYZ      */
 0,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,	/*  abcdefghijklmno */
64,65,66,67,68,69,70,71,72,73,74, 0, 0, 0, 0, 0,	/* pqrstuvwxyz      */
};
/*
 * PrintableString basic type description.
 */
static const ber_tlv_tag_t asn_DEF_PrintableString_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (19 << 2)),	/* [UNIVERSAL 19] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))	/* ... OCTET STRING */
};
asn_TYPE_descriptor_t asn_DEF_PrintableString = {
	"PrintableString",
	"PrintableString",
	OCTET_STRING_print_utf8<PrintableString, std::string>,	/* ASCII subset */
	PrintableString_constraint,
	OCTET_STRING_decode_ber<PrintableString, std::string>,      /* Implemented in terms of OCTET STRING */
	OCTET_STRING_encode_der<PrintableString, std::string>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_PrintableString_tags,
	sizeof(asn_DEF_PrintableString_tags)
	  / sizeof(asn_DEF_PrintableString_tags[0]) - 1,
	asn_DEF_PrintableString_tags,
	sizeof(asn_DEF_PrintableString_tags)
	  / sizeof(asn_DEF_PrintableString_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};


int
PrintableString_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
		asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const PrintableString *st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const PrintableString*>(structPtr);
  }

	if(st) {
		const uint8_t *buf = reinterpret_cast<const uint8_t*>(st->data());
    const uint8_t *buf_beg = buf;
		const uint8_t *end = buf + st->size();

		/*
		 * Check the alphabet of the PrintableString.
		 * ASN.1:1984 (X.409)
		 */
		for(; buf < end; buf++) {
			if(!_PrintableString_alphabet[*buf]) {
				_ASN_CTFAIL(app_key, td, sptr,
					"%s: value byte %ld (%d) "
					"not in PrintableString alphabet "
					"(%s:%d)",
					td->name,
					(long)((buf - buf_beg) + 1),
					*buf,
					__FILE__, __LINE__);
				return -1;
			}
		}
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}

	return 0;
}
