/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <OBJECT_IDENTIFIER.hpp>
#include <OCTET_STRING.hpp>
#include <limits.h>	/* for CHAR_BIT */
#include <errno.h>

/*
 * OBJECT IDENTIFIER basic type description.
 */
static const ber_tlv_tag_t asn_DEF_OBJECT_IDENTIFIER_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (6 << 2))
};
asn_TYPE_descriptor_t asn_DEF_OBJECT_IDENTIFIER = {
	"OBJECT IDENTIFIER",
	"OBJECT_IDENTIFIER",
	OBJECT_IDENTIFIER_print,
	OBJECT_IDENTIFIER_constraint,
	ber_decode_primitive<OBJECT_IDENTIFIER>,
	der_encode_primitive<OBJECT_IDENTIFIER>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_OBJECT_IDENTIFIER_tags,
	sizeof(asn_DEF_OBJECT_IDENTIFIER_tags)
	    / sizeof(asn_DEF_OBJECT_IDENTIFIER_tags[0]),
	asn_DEF_OBJECT_IDENTIFIER_tags,	/* Same as above */
	sizeof(asn_DEF_OBJECT_IDENTIFIER_tags)
	    / sizeof(asn_DEF_OBJECT_IDENTIFIER_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};


int
OBJECT_IDENTIFIER_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
		asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const OBJECT_IDENTIFIER *st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const OBJECT_IDENTIFIER*>(structPtr);
  }

	if(st) {
		if(st->size() < 1) {
			_ASN_CTFAIL(app_key, td, sptr,
				"%s: at least one numerical value "
				"expected (%s:%d)",
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

int OBJECT_IDENTIFIER_get_single_arc(const uint8_t *arcbuf, unsigned int arclen, 
                              signed int add, void *rvbufp, unsigned int rvsize) 
{
	unsigned LE GCC_NOTUSED = 1; /* Little endian (x86) */
	const uint8_t *arcend = arcbuf + arclen;	/* End of arc */
	unsigned int cache = 0;	/* No more than 14 significant bits */
	unsigned char *rvbuf = (unsigned char *)rvbufp;
	unsigned char *rvstart = rvbuf;	/* Original start of the value buffer */
	int inc;	/* Return value growth direction */

	rvsize *= CHAR_BIT;	/* bytes to bits */
	arclen *= 7;		/* bytes to bits */

	/*
	 * The arc has the number of bits
	 * cannot be represented using supplied return value type.
	 */
	if(arclen > rvsize) {
		if(arclen > (rvsize + CHAR_BIT)) {
			errno = ERANGE;	/* Overflow */
			return -1;
		} else {
			/*
			 * Even if the number of bits in the arc representation
			 * is higher than the width of supplied * return value
			 * type, there is still possible to fit it when there
			 * are few unused high bits in the arc value
			 * representaion.
			 * 
			 * Moreover, there is a possibility that the
			 * number could actually fit the arc space, given
			 * that add is negative, but we don't handle
			 * such "temporary lack of precision" situation here.
			 * May be considered as a bug.
			 */
			uint8_t mask = (0xff << (7-(arclen - rvsize))) & 0x7f;
			if((*arcbuf & mask)) {
				errno = ERANGE;	/* Overflow */
				return -1;
			}
			/* Fool the routine computing unused bits */
			arclen -= 7;
			cache = *arcbuf & 0x7f;
			arcbuf++;
		}
	}

	/* Faster path for common size */
	if(rvsize == (CHAR_BIT * sizeof(unsigned long))) {
		unsigned long accum;
		/* Gather all bits into the accumulator */
		for(accum = cache; arcbuf < arcend; arcbuf++)
			accum = (accum << 7) | (*arcbuf & ~0x80);
		if(accum < (unsigned)-add) {
			errno = ERANGE;	/* Overflow */
			return -1;
		}
		*(unsigned long *)(void *)rvbuf = accum + add;	/* alignment OK! */
		return 0;
	}

#ifndef	WORDS_BIGENDIAN
	if(*(unsigned char *)&LE) {	/* Little endian (x86) */
		/* "Convert" to big endian */
		rvbuf += rvsize / CHAR_BIT - 1;
		rvstart--;
		inc = -1;	/* Descending */
	} else
#endif	/* !WORDS_BIGENDIAN */
		inc = +1;	/* Big endian is known [at compile time] */

	{
		int bits;	/* typically no more than 3-4 bits */

		/* Clear the high unused bits */
		for(bits = rvsize - arclen;
			bits > CHAR_BIT;
				rvbuf += inc, bits -= CHAR_BIT)
				*rvbuf = 0;

		/* Fill the body of a value */
		for(; arcbuf < arcend; arcbuf++) {
			cache = (cache << 7) | (*arcbuf & 0x7f);
			bits += 7;
			if(bits >= CHAR_BIT) {
				bits -= CHAR_BIT;
				*rvbuf = (cache >> bits);
				rvbuf += inc;
			}
		}
		if(bits) {
			*rvbuf = cache;
			rvbuf += inc;
		}
	}

	if(add) {
		for(rvbuf -= inc; rvbuf != rvstart; rvbuf -= inc) {
			int v = add + *rvbuf;
			if(v & (-1 << CHAR_BIT)) {
				*rvbuf = (unsigned char)(v + (1 << CHAR_BIT));
				add = -1;
			} else {
				*rvbuf = v;
				break;
			}
		}
		if(rvbuf == rvstart) {
			/* No space to carry over */
			errno = ERANGE;	/* Overflow */
			return -1;
		}
	}

	return 0;
}

/*
 * Save the single value as an object identifier arc.
 */
int OBJECT_IDENTIFIER_set_single_arc(uint8_t *arcbuf, const void *arcval, 
                                unsigned int arcval_size, int prepared_order) 
{
	/*
	 * The following conditions must hold:
	 * assert(arcval);
	 * assert(arcval_size > 0);
	 * assert(arcval_size <= 16);
	 * assert(arcbuf);
	 */
#ifdef	WORDS_BIGENDIAN
	const unsigned isLittleEndian = 0;
#else
	unsigned LE = 1;
	unsigned isLittleEndian = *(char *)&LE;
#endif
	const uint8_t *tend, *tp;
	unsigned int cache;
	uint8_t *bp = arcbuf;
	int bits;
	uint8_t buffer[16];

	if(isLittleEndian && !prepared_order) {
		const uint8_t *a = (const unsigned char *)arcval + arcval_size - 1;
		const uint8_t *aend = (const uint8_t *)arcval;
		uint8_t *msb = buffer + arcval_size - 1;
		uint8_t *tb;
		for(tb = buffer; a >= aend; tb++, a--)
			if((*tb = *a) && (tb < msb))
				msb = tb;
		tend = &buffer[arcval_size];
		tp = msb;	/* Most significant non-zero byte */
	} else {
		/* Look for most significant non-zero byte */
		tend = (const unsigned char *)arcval + arcval_size;
		for(tp = (const uint8_t *)arcval; tp < tend - 1; tp++)
			if(*tp) break;
	}

	/*
	 * Split the value in 7-bits chunks.
	 */
	bits = ((tend - tp) * CHAR_BIT) % 7;
	if(bits) {
		cache = *tp >> (CHAR_BIT - bits);
		if(cache) {
			*bp++ = cache | 0x80;
			cache = *tp++;
			bits = CHAR_BIT - bits;
		} else {
			bits = -bits;
		}
	} else {
		cache = 0;
	}
	for(; tp < tend; tp++) {
		cache = (cache << CHAR_BIT) + *tp;
		bits += CHAR_BIT;
		while(bits >= 7) {
			bits -= 7;
			*bp++ = 0x80 | (cache >> bits);
		}
	}
	if(bits) *bp++ = cache;
	bp[-1] &= 0x7f;	/* Clear the last bit */

	return bp - arcbuf;
}


ssize_t
OBJECT_IDENTIFIER__dump_arc(const uint8_t *arcbuf, int arclen, int add,
		asn_app_consume_bytes_f *cb, void *app_key) {
	char scratch[64];	/* Conservative estimate */
	unsigned long accum;	/* Bits accumulator */
	char *p;		/* Position in the scratch buffer */

	if(OBJECT_IDENTIFIER_get_single_arc(arcbuf, arclen, add,
			&accum, sizeof(accum)))
		return -1;

	if(accum) {
		ssize_t len;

		/* Fill the scratch buffer in reverse. */
		p = scratch + sizeof(scratch);
		for(; accum; accum /= 10)
			*(--p) = (char)(accum % 10) + 0x30; /* Put a digit */

		len = sizeof(scratch) - (p - scratch);
		if(cb(p, len, app_key) < 0)
			return -1;
		return len;
	} else {
		*scratch = 0x30;
		if(cb(scratch, 1, app_key) < 0)
			return -1;
		return 1;
	}
}

static ssize_t
OBJECT_IDENTIFIER__dump_body(const std::vector<uint8_t>& st, asn_app_consume_bytes_f *cb, void *app_key) {
	ssize_t wrote_len = 0;
	int startn;
	int add = 0;
	size_t i;

	for(i = 0, startn = 0; i < st.size(); i++) {
		uint8_t b = st[i];
		if((b & 0x80))			/* Continuation expected */
			continue;

		if(startn == 0) {
			/*
			 * First two arcs are encoded through the backdoor.
			 */
			if(i) {
				add = -80;
				if(cb("2", 1, app_key) < 0) return -1;
			} else if(b <= 39) {
				add = 0;
				if(cb("0", 1, app_key) < 0) return -1;
			} else if(b < 79) {
				add = -40;
				if(cb("1", 1, app_key) < 0) return -1;
			} else {
				add = -80;
				if(cb("2", 1, app_key) < 0) return -1;
			}
			wrote_len += 1;
		}

		if(cb(".", 1, app_key) < 0)	/* Separate arcs */
			return -1;

		add = OBJECT_IDENTIFIER__dump_arc(&st[startn],
				i - startn + 1, add, cb, app_key);
		if(add < 0) return -1;
		wrote_len += 1 + add;
		startn = i + 1;
		add = 0;
	}

	return wrote_len;
}

int
OBJECT_IDENTIFIER_print(asn_TYPE_descriptor_t *td, const void *sptr,
	int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	const OBJECT_IDENTIFIER* st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const OBJECT_IDENTIFIER*>(structPtr);
  }

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(!st)
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;

	/* Dump preamble */
	if(cb("{ ", 2, app_key) < 0)
		return -1;

	if(OBJECT_IDENTIFIER__dump_body(*st, cb, app_key) < 0)
		return -1;

	return (cb(" }", 2, app_key) < 0) ? -1 : 0;
}

