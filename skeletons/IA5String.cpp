/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <IA5String.hpp>

/*
 * IA5String basic type description.
 */
static const ber_tlv_tag_t asn_DEF_IA5String_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (22 << 2)),	/* [UNIVERSAL 22] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))	/* ... OCTET STRING */
};
asn_TYPE_descriptor_t asn_DEF_IA5String = {
	"IA5String",
	"IA5String",
	OCTET_STRING_print_utf8<IA5String, std::string>,	/* ASCII subset */
	IA5String_constraint,       /* Constraint on the alphabet */
	OCTET_STRING_decode_ber<IA5String, std::string>,    /* Implemented in terms of OCTET STRING */
  OCTET_STRING_encode_der<IA5String, std::string>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_IA5String_tags,
	sizeof(asn_DEF_IA5String_tags)
	  / sizeof(asn_DEF_IA5String_tags[0]) - 1,
	asn_DEF_IA5String_tags,
	sizeof(asn_DEF_IA5String_tags)
	  / sizeof(asn_DEF_IA5String_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

int
IA5String_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
		asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const IA5String *st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const IA5String*>(structPtr);
  }

	if(st) {
		const uint8_t *buf = reinterpret_cast<const uint8_t*>(st->data());
    const uint8_t *buf_beg = buf;
		const uint8_t *end = buf + st->size();
		/*
		 * IA5String is generally equivalent to 7bit ASCII.
		 * ISO/ITU-T T.50, 1963.
		 */
		for(; buf < end; buf++) {
			if(*buf > 0x7F) {
				_ASN_CTFAIL(app_key, td, sptr,
					"%s: value byte %ld out of range: "
					"%d > 127 (%s:%d)",
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

