/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */

#ifndef	_INTEGER_HPP_
#define	_INTEGER_HPP_

#include <asn_application.hpp>
#include <asn_codecs_prim.hpp>
#include <errno.h>

/* Map with <tag> to integer value association */
typedef struct asn_INTEGER_enum_map_s {
	long		 nat_value;	/* associated native integer value */
	size_t		 enum_len;	/* strlen("tag") */
	const char	*enum_name;	/* "tag" */
} asn_INTEGER_enum_map_t;

/* This type describes an enumeration for INTEGER and ENUMERATED types */
typedef const struct asn_INTEGER_specifics_s {
	const asn_INTEGER_enum_map_t *value2enum;	/* N -> "tag"; sorted by N */
	const unsigned int *enum2value;		/* "tag" => N; sorted by tag */
	int map_count;				/* Elements in either map */
	int extension;				/* This map is extensible */
	int strict_enumeration;			/* Enumeration set is fixed */
	int field_width;			/* Size of native integer */
	int field_unsigned;			/* Signed=0, unsigned=1 */
} asn_INTEGER_specifics_t;

template <class Type>
asn_struct_print_f INTEGER_print;
template <class Type>
der_type_encoder_f INTEGER_encode_der;

template <asn_TYPE_descriptor_t* typeDescriptorPtr>
class _INTEGER : public AsnPrimitiveType<typeDescriptorPtr> {
public:
  _INTEGER() : AsnPrimitiveType<typeDescriptorPtr>() { }
  _INTEGER(const _INTEGER& other) : 
              AsnPrimitiveType<typeDescriptorPtr>(other) { }
  _INTEGER(_INTEGER&& other) noexcept : 
              AsnPrimitiveType<typeDescriptorPtr>(std::move(other)) { }
  _INTEGER& operator =(const _INTEGER& other) {
    AsnPrimitiveType<typeDescriptorPtr>::operator =(other);
    return *this;
  }
  _INTEGER& operator =(_INTEGER&& other) noexcept {
    AsnPrimitiveType<typeDescriptorPtr>::operator =(std::move(other));
    return *this;
  }
  using AsnPrimitiveType<typeDescriptorPtr>::operator =;
  virtual ~_INTEGER() noexcept { }
  /*
   * Returns true if it was possible to convert, false otherwise.
   * false/ERANGE: Value encoded is out of range for long representation
   */
  static bool ToLong(const uint8_t* buf, size_t size, long& l);
  static bool ToLong(const std::vector<uint8_t>& buf, long& l) { return ToLong(buf.data(), buf.size(), l); }
  static bool ToULong(const uint8_t* buf, size_t size, unsigned long& l);
  static bool ToULong(const std::vector<uint8_t>& buf, unsigned long& l) { return ToULong(buf.data(), buf.size(), l); }
  bool ToLong(long& l) const {
    return ToLong(this->data(), this->size(), l);
  }
  bool ToULong(unsigned long& l) const {
    return ToULong(this->data(), this->size(), l);
  }
  bool FromLong(long l);
  bool FromULong(unsigned long l);
private:
  static ssize_t __dump(const asn_TYPE_descriptor_t *td, const std::vector<uint8_t> *st, asn_app_consume_bytes_f *cb, void *app_key, int plainOrXER);
  /*
   * Convert the integer value into the corresponding enumeration map entry.
   */
  static const asn_INTEGER_enum_map_t *_map_value2enum(asn_INTEGER_specifics_t *specs, long value);
  static int __compar_value2enum(const void *kp, const void *am);
  
  template <class Type>
  friend asn_struct_print_f INTEGER_print;
};

extern asn_TYPE_descriptor_t asn_DEF_INTEGER;

typedef _INTEGER<&asn_DEF_INTEGER> INTEGER;

/* A a reified version of strtol(3) with nicer error reporting. */
enum asn_strtol_result_e {
    ASN_STRTOL_ERROR_RANGE = -3,  /* Input outside of numeric range for long type */
    ASN_STRTOL_ERROR_INVAL = -2,  /* Invalid data encountered (e.g., "+-") */
    ASN_STRTOL_EXPECT_MORE = -1,  /* More data expected (e.g. "+") */
    ASN_STRTOL_OK          =  0,  /* Conversion succeded, number ends at (*end) */
    ASN_STRTOL_EXTRA_DATA  =  1,  /* Conversion succeded, but the string has extra stuff */
};
enum asn_strtol_result_e asn_strtol_lim(const char *str, const char **end, long *l);

template <asn_TYPE_descriptor_t* typeDescriptorPtr>
bool _INTEGER<typeDescriptorPtr>::ToLong(const uint8_t* buf, 
                                         size_t size, long& l) 
{
  const uint8_t *b, *end;
  
  /* Sanity checking */
  if(!buf) {
		errno = EINVAL;
		return -1;
	}

	/* Cache the begin/end of the buffer */
	b = buf;	/* Start of the INTEGER buffer */
	end = b + size;	/* Where to stop */

	if(size > sizeof(long)) {
		const uint8_t *end1 = end - 1;
		/*
		 * Slightly more advanced processing,
		 * able to >sizeof(long) bytes,
		 * when the actual value is small
		 * (0x0000000000abcdef would yield a fine 0x00abcdef)
		 */
		/* Skip out the insignificant leading bytes */
		for(; b < end1; b++) {
			switch(*b) {
			case 0x00: if((b[1] & 0x80) == 0) continue; break;
			case 0xff: if((b[1] & 0x80) != 0) continue; break;
			}
			break;
		}

		size = end - b;
		if(size > sizeof(long)) {
			/* Still cannot fit the long */
			errno = ERANGE;
			return false;
		}
	}

	/* Shortcut processing of a corner case */
	if(end == b) {
		l = 0;
		return true;
	}

	/* Perform the sign initialization */
	/* Actually l = -(*b >> 7); gains nothing, yet unreadable! */
	if((*b >> 7)) l = -1; else l = 0;

	/* Conversion engine */
	for(; b < end; b++)
		l = (l << 8) | *b;

	return true;
}

template <asn_TYPE_descriptor_t* typeDescriptorPtr>
bool _INTEGER<typeDescriptorPtr>::ToULong(const uint8_t* buf, 
                                          size_t size, unsigned long& l) 
{
  const uint8_t *b, *end;
  
  /* Sanity checking */
	if(!buf) {
		errno = EINVAL;
		return -1;
	}

	b = buf;
	end = b + size;

	/* If all extra leading bytes are zeroes, ignore them */
	for(; size > sizeof(unsigned long); b++, size--) {
		if(*b) {
			/* Value won't fit unsigned long */
			errno = ERANGE;
			return false;
		}
	}

	/* Conversion engine */
	for(l = 0; b < end; b++)
		l = (l << 8) | *b;

	return true;
}

template <asn_TYPE_descriptor_t* typeDescriptorPtr>
bool _INTEGER<typeDescriptorPtr>::FromULong(unsigned long value) {
	uint8_t *end;
	uint8_t *b;
	int shr;

	if(value <= LONG_MAX)
		return FromLong(value);
  
  std::vector<uint8_t>& buf(*this);

  buf.resize(1 + sizeof(value));

	end = buf.data() + (sizeof(value) + 1);
	buf[0] = 0;
	for(b = buf.data() + 1, shr = (sizeof(long)-1)*8; b < end; shr -= 8, b++)
		*b = (uint8_t)(value >> shr);

	return true;
}

template <asn_TYPE_descriptor_t* typeDescriptorPtr>
bool _INTEGER<typeDescriptorPtr>::FromLong(long value) {
	uint8_t *bp;
	uint8_t *p;
	uint8_t *pstart;
	uint8_t *pend1;
	int littleEndian = 1;	/* Run-time detection */
	int add;
  
  std::vector<uint8_t>& buf(*this);
  buf.resize(sizeof(value));

	if(*(char *)&littleEndian) {
		pstart = (uint8_t *)&value + sizeof(value) - 1;
		pend1 = (uint8_t *)&value;
		add = -1;
	} else {
		pstart = (uint8_t *)&value;
		pend1 = pstart + sizeof(value) - 1;
		add = 1;
	}

	/*
	 * If the contents octet consists of more than one octet,
	 * then bits of the first octet and bit 8 of the second octet:
	 * a) shall not all be ones; and
	 * b) shall not all be zero.
	 */
	for(p = pstart; p != pend1; p += add) {
		switch(*p) {
		case 0x00: if((*(p+add) & 0x80) == 0)
				continue;
			break;
		case 0xff: if((*(p+add) & 0x80))
				continue;
			break;
		}
		break;
	}
	/* Copy the integer body */
	for(pstart = p, bp = buf.data(), pend1 += add; p != pend1; p += add)
		*bp++ = *p;

	buf.resize(bp - buf.data());

	return true;
}

/*
 * Encode INTEGER type using DER.
 */
template<class Type>
asn_enc_rval_t
INTEGER_encode_der(asn_TYPE_descriptor_t *td, void *sptr,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
	Type *st = 0;
  
  {
    AsnAbstractType* structPtr = static_cast<AsnAbstractType*>(sptr);
    st = static_cast<Type*>(structPtr);
  }

	ASN_DEBUG("%s %s as INTEGER (tm=%d)",
		cb?"Encoding":"Estimating", td->name, tag_mode);

	/*
	 * Canonicalize integer in the buffer.
	 * (Remove too long sign extension, remove some first 0x00 bytes)
	 */
		uint8_t *buf = st->data();
		uint8_t *end1 = buf + st->size() - 1;
		int shift;

		/* Compute the number of superfluous leading bytes */
		for(; buf < end1; buf++) {
			/*
			 * If the contents octets of an integer value encoding
			 * consist of more than one octet, then the bits of the
			 * first octet and bit 8 of the second octet:
			 * a) shall not all be ones; and
			 * b) shall not all be zero.
			 */
			switch(*buf) {
			case 0x00: if((buf[1] & 0x80) == 0)
					continue;
				break;
			case 0xff: if((buf[1] & 0x80))
					continue;
				break;
			}
			break;
		}
    
		/* Remove leading superfluous bytes from the integer */
		shift = buf - st->data();
		if(shift) {
			uint8_t *nb = st->data();
			uint8_t *end;
      
      size_t newSize = st->size() - shift; /* New size, minus bad bytes */

			end = nb + newSize;

			for(; nb < end; nb++, buf++)
				*nb = *buf;
      
      st->resize(newSize);
		}
    

	return der_encode_primitive<Type>(td, sptr, tag_mode, tag, cb, app_key);
}

/*
 * INTEGER specific human-readable output.
 */
template <class Type>
int
INTEGER_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
	asn_app_consume_bytes_f *cb, void *app_key) {
	const Type *st = 0;
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const Type*>(structPtr);
  }
	ssize_t ret;

	(void)td;
	(void)ilevel;

	if(!st)
		ret = cb("<absent>", 8, app_key);
	else
		ret = Type::__dump(td, st, cb, app_key, 0);

	return (ret < 0) ? -1 : 0;
}

/*
 * INTEGER specific human-readable output.
 */
template <asn_TYPE_descriptor_t* typeDescriptorPtr>
ssize_t
_INTEGER<typeDescriptorPtr>::__dump(const asn_TYPE_descriptor_t *td, const std::vector<uint8_t> *st, asn_app_consume_bytes_f *cb, void *app_key, int plainOrXER) {
	asn_INTEGER_specifics_t *specs=(asn_INTEGER_specifics_t *)td->specifics;
	char scratch[32];	/* Enough for 64-bit integer */
	const uint8_t *buf = st->data();
	const uint8_t *buf_end = buf + st->size();
	signed long value;
	ssize_t wrote = 0;
	char *p;
	int ret;
  
  if (!st) {
    ret = -1;
  } else {
    if(specs && specs->field_unsigned) {
      ret = INTEGER::ToULong(*st, *(unsigned long *)&value) ? 0 : -1;
    } else {
      ret = INTEGER::ToLong(*st, value) ? 0 : -1;
    }
  }

	/* Simple case: the integer size is small */
	if(ret == 0) {
		const asn_INTEGER_enum_map_t *el;
		size_t scrsize;
		char *scr;

		el = (value >= 0 || !specs || !specs->field_unsigned)
			? _map_value2enum(specs, value) : 0;
		if(el) {
			scrsize = el->enum_len + 32;
			scr = (char *)alloca(scrsize);
			if(plainOrXER == 0)
				ret = snprintf(scr, scrsize,
					"%ld (%s)", value, el->enum_name);
			else
				ret = snprintf(scr, scrsize,
					"<%s/>", el->enum_name);
		} else if(plainOrXER && specs && specs->strict_enumeration) {
			ASN_DEBUG("ASN.1 forbids dealing with "
				"unknown value of ENUMERATED type");
			errno = EPERM;
			return -1;
		} else {
			scrsize = sizeof(scratch);
			scr = scratch;
			ret = snprintf(scr, scrsize,
				(specs && specs->field_unsigned)
				?"%lu":"%ld", value);
		}
		assert(ret > 0 && (size_t)ret < scrsize);
		return (cb(scr, ret, app_key) < 0) ? -1 : ret;
	} else if(plainOrXER && specs && specs->strict_enumeration) {
		/*
		 * Here and earlier, we cannot encode the ENUMERATED values
		 * if there is no corresponding identifier.
		 */
		ASN_DEBUG("ASN.1 forbids dealing with "
			"unknown value of ENUMERATED type");
		errno = EPERM;
		return -1;
	}

	/* Output in the long xx:yy:zz... format */
	/* TODO: replace with generic algorithm (Knuth TAOCP Vol 2, 4.3.1) */
	for(p = scratch; buf < buf_end; buf++) {
		const char * const h2c = "0123456789ABCDEF";
		if((p - scratch) >= (ssize_t)(sizeof(scratch) - 4)) {
			/* Flush buffer */
			if(cb(scratch, p - scratch, app_key) < 0)
				return -1;
			wrote += p - scratch;
			p = scratch;
		}
		*p++ = h2c[*buf >> 4];
		*p++ = h2c[*buf & 0x0F];
		*p++ = 0x3a;	/* ":" */
	}
	if(p != scratch)
		p--;	/* Remove the last ":" */

	wrote += p - scratch;
	return (cb(scratch, p - scratch, app_key) < 0) ? -1 : wrote;
}

/*
 * Convert the integer value into the corresponding enumeration map entry.
 */
template <asn_TYPE_descriptor_t* typeDescriptorPtr>
int
_INTEGER<typeDescriptorPtr>::__compar_value2enum(const void *kp, const void *am) {
	long a = *(const long *)kp;
	const asn_INTEGER_enum_map_t *el = (const asn_INTEGER_enum_map_t *)am;
	long b = el->nat_value;
	if(a < b) return -1;
	else if(a == b) return 0;
	else return 1;
}

template <asn_TYPE_descriptor_t* typeDescriptorPtr>
const asn_INTEGER_enum_map_t *
_INTEGER<typeDescriptorPtr>::_map_value2enum(asn_INTEGER_specifics_t *specs, long value) {
	int count = specs ? specs->map_count : 0;
	if(!count) return 0;
	return (asn_INTEGER_enum_map_t *)bsearch(&value, specs->value2enum,
		count, sizeof(specs->value2enum[0]),
		__compar_value2enum);
}

#endif	/* _INTEGER_HPP_ */
