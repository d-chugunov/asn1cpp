/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <BIT_STRING.hpp>
#include <asn_internal.hpp>

/*
 * BIT STRING basic type description.
 */
static const ber_tlv_tag_t asn_DEF_BIT_STRING_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (3 << 2))
};
static asn_OCTET_STRING_specifics_t asn_DEF_BIT_STRING_specs = {
	asn_OCTET_STRING_specifics_t::ASN_OSUBV_BIT
};
asn_TYPE_descriptor_t asn_DEF_BIT_STRING = {
	"BIT STRING",
	"BIT_STRING",
	BIT_STRING_print,
	BIT_STRING_constraint,
	OCTET_STRING_decode_ber<BIT_STRING, std::vector<uint8_t>>,   /* Implemented in terms of OCTET STRING */
	OCTET_STRING_encode_der<BIT_STRING, std::vector<uint8_t>>,   /* Implemented in terms of OCTET STRING */
	0, /* Use generic outmost tag fetcher */
	asn_DEF_BIT_STRING_tags,
	sizeof(asn_DEF_BIT_STRING_tags)
	  / sizeof(asn_DEF_BIT_STRING_tags[0]),
	asn_DEF_BIT_STRING_tags,	/* Same as above */
	sizeof(asn_DEF_BIT_STRING_tags)
	  / sizeof(asn_DEF_BIT_STRING_tags[0]),
	0, 0,	/* No members */
	&asn_DEF_BIT_STRING_specs
};

/*
 * BIT STRING generic constraint.
 */
int
BIT_STRING_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
		asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const BIT_STRING *st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const BIT_STRING*>(structPtr);
  }

	if(st) {
		if((st->size() == 0 && st->GetBitsUnused())
		|| st->GetBitsUnused() < 0 || st->GetBitsUnused() > 7) {
			_ASN_CTFAIL(app_key, td, sptr,
				"%s: invalid padding byte (%s:%d)",
				td->name, __FILE__, __LINE__);
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

/*
 * BIT STRING specific contents printer.
 */
int
BIT_STRING_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
		asn_app_consume_bytes_f *cb, void *app_key) {
	const char * const h2c = "0123456789ABCDEF";
	char scratch[64];
	const BIT_STRING* st = 0;
	const uint8_t *buf;
  const uint8_t *buf_beg;
	const uint8_t *end;
	char *p = scratch;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const BIT_STRING*>(structPtr);
  }

	(void)td;	/* Unused argument */

	if(!st)
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;

	ilevel++;
	buf = st->data();
  buf_beg = buf;
	end = buf + st->size();

	/*
	 * Hexadecimal dump.
	 */
	for(; buf < end; buf++) {
		if((buf - buf_beg) % 16 == 0 && (st->size() > 16)
				&& buf != buf_beg) {
			_i_INDENT(1);
			/* Dump the string */
			if(cb(scratch, p - scratch, app_key) < 0) return -1;
			p = scratch;
		}
		*p++ = h2c[*buf >> 4];
		*p++ = h2c[*buf & 0x0F];
		*p++ = 0x20;
	}

	if(p > scratch) {
		p--;	/* Eat the tailing space */

		if((st->size() > 16)) {
			_i_INDENT(1);
		}

		/* Dump the incomplete 16-bytes row */
		if(cb(scratch, p - scratch, app_key) < 0)
			return -1;
	}
  
  if (cb(" (bits unused: ", 15, app_key) < 0)
    return -1;
  
  snprintf(scratch, sizeof(scratch), "%d", st->GetBitsUnused());
  if (cb(scratch, strlen(scratch), app_key) < 0)
    return -1;
  
  if (cb(")", 1, app_key) < 0)
    return -1;

	return 0;
}

