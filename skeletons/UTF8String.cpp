/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <UTF8String.hpp>

/*
 * UTF8String basic type description.
 */
static const ber_tlv_tag_t asn_DEF_UTF8String_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (12 << 2)),	/* [UNIVERSAL 12] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2)),	/* ... OCTET STRING */
};
asn_TYPE_descriptor_t asn_DEF_UTF8String = {
	"UTF8String",
	"UTF8String",
	UTF8String_print,
	UTF8String_constraint,      /* Check for invalid codes, etc. */
	OCTET_STRING_decode_ber<UTF8String, std::string>,    /* Implemented in terms of OCTET STRING */
	OCTET_STRING_encode_der<UTF8String, std::string>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_UTF8String_tags,
	sizeof(asn_DEF_UTF8String_tags)
	  / sizeof(asn_DEF_UTF8String_tags[0]) - 1,
	asn_DEF_UTF8String_tags,
	sizeof(asn_DEF_UTF8String_tags)
	  / sizeof(asn_DEF_UTF8String_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

/*
 * This is the table of length expectations.
 * The second half of this table is only applicable to the long sequences.
 */
static int UTF8String_ht[2][16] = {
	{ /* 0x0 ... 0x7 */
	  /* 0000..0111 */
	  1, 1, 1, 1, 1, 1, 1, 1,
	  /* 1000..1011(0), 1100..1101(2), 1110(3), 1111(-1) */
	  0, 0, 0, 0, 2, 2, 3, -1 },
	{ /* 0xF0 .. 0xF7 */
	  /* 11110000..11110111 */
	  4, 4, 4, 4, 4, 4, 4, 4,
	  5, 5, 5, 5, 6, 6, -1, -1 }
};
static int32_t UTF8String_mv[7] = { 0, 0,
	0x00000080,
	0x00000800,
	0x00010000,
	0x00200000,
	0x04000000
};

/* Internal aliases for return codes */
#define	U8E_TRUNC	-1	/* UTF-8 sequence truncated */
#define	U8E_ILLSTART	-2	/* Illegal UTF-8 sequence start */
#define	U8E_NOTCONT	-3	/* Continuation expectation failed */
#define	U8E_NOTMIN	-4	/* Not minimal length encoding */
#define	U8E_EINVAL	-5	/* Invalid arguments */

int
UTF8String_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
		asn_app_constraint_failed_f *ctfailcb, void *app_key) {
  const UTF8String *st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const UTF8String*>(structPtr);
  }
	ssize_t len = UTF8String::GetLength(st);
	switch(len) {
	case U8E_EINVAL:
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given", td->name);
		break;
	case U8E_TRUNC:
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: truncated UTF-8 sequence (%s:%d)",
			td->name, __FILE__, __LINE__);
		break;
	case U8E_ILLSTART:
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: UTF-8 illegal start of encoding (%s:%d)",
			td->name, __FILE__, __LINE__);
		break;
	case U8E_NOTCONT:
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: UTF-8 not continuation (%s:%d)",
			td->name, __FILE__, __LINE__);
		break;
	case U8E_NOTMIN:
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: UTF-8 not minimal sequence (%s:%d)",
			td->name, __FILE__, __LINE__);
		break;
	}
	return (len < 0) ? -1 : 0;
}

ssize_t UTF8String::__process(std::vector<uint32_t>* dst) const {
	size_t length;
	const uint8_t *buf = reinterpret_cast<const uint8_t*>(this->data());
	const uint8_t *end = buf + this->size();

	for(length = 0; buf < end; length++) {
		int ch = *buf;
		const uint8_t *cend;
		int32_t value;
		int want;

		/* Compute the sequence length */
		want = UTF8String_ht[0][ch >> 4];
		switch(want) {
		case -1:
			/* Second half of the table, long sequence */
			want = UTF8String_ht[1][ch & 0x0F];
			if(want != -1) break;
			/* Fall through */
		case 0:
			return U8E_ILLSTART;
		}

		/* assert(want >= 1 && want <= 6) */

		/* Check character sequence length */
		if(buf + want > end) return U8E_TRUNC;

		value = ch & (0xff >> want);
		cend = buf + want;
		for(buf++; buf < cend; buf++) {
			ch = *buf;
			if(ch < 0x80 || ch > 0xbf) return U8E_NOTCONT;
			value = (value << 6) | (ch & 0x3F);
		}
		if(value < UTF8String_mv[want])
			return U8E_NOTMIN;
		if(dst)
      dst->push_back(value); /* Record value */
	}

	if(dst) dst->push_back(0);	/* zero-terminate */

	return length;
}

ssize_t UTF8String::GetLength(const UTF8String* st) {
  return st ? st->GetLength() : U8E_EINVAL;
}

int
UTF8String_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
	asn_app_consume_bytes_f *cb, void *app_key) {
	const UTF8String* st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const UTF8String*>(structPtr);
  }

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(st) {
		return (cb(st->data(), st->size(), app_key) < 0) ? -1 : 0;
	} else {
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;
	}
}