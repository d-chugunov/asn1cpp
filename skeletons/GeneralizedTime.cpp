/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#define	_POSIX_PTHREAD_SEMANTICS	/* for Sun */
#define	_REENTRANT			/* for Sun */
#include <asn_internal.hpp>
#include <GeneralizedTime.hpp>
#include <errno.h>

//#ifdef	__CYGWIN__
//#include "/usr/include/time.h"
//#else
#include <time.h>
//#endif	/* __CYGWIN__ */

#if	defined(_WIN32)
#pragma message( "PLEASE STOP AND READ!")
#pragma message( "  localtime_r is implemented via localtime(), which may be not thread-safe.")
#pragma message( "  gmtime_r is implemented via gmtime(), which may be not thread-safe.")
#pragma message( "  ")
#pragma message( "  You must fix the code by inserting appropriate locking")
#pragma message( "  if you want to use  GeneralizedTime::ToTime() or UTCTime::ToTime().")
#pragma message( "PLEASE STOP AND READ!")

static struct tm *localtime_r(const time_t *tloc, struct tm *result) {
	struct tm *tm;
	if((tm = localtime(tloc)))
		return memcpy(result, tm, sizeof(struct tm));
	return 0;
}

static struct tm *gmtime_r(const time_t *tloc, struct tm *result) {
	struct tm *tm;
	if((tm = gmtime(tloc)))
		return memcpy(result, tm, sizeof(struct tm));
	return 0;
}

#define	tzset()	_tzset()
#define	putenv(c)	_putenv(c)
#define	_EMULATE_TIMEGM

#endif	/* _WIN32 */

#if	defined(sun) || defined(_sun_) || defined(__solaris__)
#define	_EMULATE_TIMEGM
#endif

/*
 * Where to look for offset from GMT, Phase I.
 * Several platforms are known.
 */
#if defined(__FreeBSD__)				\
	|| (defined(__GNUC__) && defined(__APPLE_CC__))	\
	|| (defined __GLIBC__ && __GLIBC__ >= 2) \
  || defined(__CYGWIN__)
#undef	HAVE_TM_GMTOFF
#define	HAVE_TM_GMTOFF
#endif	/* BSDs and newer glibc */

/*
 * Where to look for offset from GMT, Phase II.
 */
#ifdef	HAVE_TM_GMTOFF
#define	GMTOFF(tm)	((tm).tm_gmtoff)
#else	/* HAVE_TM_GMTOFF */
#define	GMTOFF(tm)	(-timezone)
#endif	/* HAVE_TM_GMTOFF */

#if	defined(_WIN32)
#pragma message( "PLEASE STOP AND READ!")
#pragma message( "  timegm() is implemented via getenv(\"TZ\")/setenv(\"TZ\"), which may be not thread-safe.")
#pragma message( "  ")
#pragma message( "  You must fix the code by inserting appropriate locking")
#pragma message( "  if you want to use asn_GT2time() or asn_UT2time().")
#pragma message( "PLEASE STOP AND READ!")
#else
#if	(defined(_EMULATE_TIMEGM) || !defined(HAVE_TM_GMTOFF))
#warning "PLEASE STOP AND READ!"
#warning "  timegm() is implemented via getenv(\"TZ\")/setenv(\"TZ\"), which may be not thread-safe."
#warning "  "
#warning "  You must fix the code by inserting appropriate locking"
#warning "  if you want to use GeneralizedTime::ToTime() or UTCTime::ToTime()."
#warning "PLEASE STOP AND READ!"
#endif	/* _EMULATE_TIMEGM */
#endif

/*
 * Override our GMTOFF decision for other known platforms.
 */
//#ifdef __CYGWIN__
//#undef	GMTOFF
//static long GMTOFF(struct tm a){
//	struct tm *lt;
//	time_t local_time, gmt_time;
//	long zone;
//
//	tzset();
//	gmt_time = time (NULL);
//
//	lt = gmtime(&gmt_time);
//
//	local_time = mktime(lt);
//	return (gmt_time - local_time);
//}
//#define	_EMULATE_TIMEGM
//
//#endif	/* __CYGWIN__ */

#define	ATZVARS do {							\
	char tzoldbuf[64];						\
	char *tzold
#define	ATZSAVETZ do {							\
	tzold = getenv("TZ");						\
	if(tzold) {							\
		size_t tzlen = strlen(tzold);				\
		if(tzlen < sizeof(tzoldbuf)) {				\
			tzold = memcpy(tzoldbuf, tzold, tzlen + 1);	\
		} else {						\
			char *dupptr = tzold;				\
			tzold = MALLOC(tzlen + 1);			\
			if(tzold) memcpy(tzold, dupptr, tzlen + 1);	\
		}							\
		setenv("TZ", "UTC", 1);					\
	}								\
	tzset();							\
} while(0)
#define	ATZOLDTZ do {							\
	if (tzold) {							\
		setenv("TZ", tzold, 1);					\
		*tzoldbuf = 0;						\
		if(tzold != tzoldbuf)					\
			FREEMEM(tzold);					\
	} else {							\
		unsetenv("TZ");						\
	}								\
	tzset();							\
} while(0); } while(0);

#ifndef HAVE_TIMEGM
#ifdef	_EMULATE_TIMEGM
static time_t timegm(struct tm *tm) {
	time_t tloc;
	ATZVARS;
	ATZSAVETZ;
	tloc = mktime(tm);
	ATZOLDTZ;
	return tloc;
}
#endif	/* _EMULATE_TIMEGM */
#endif


#ifndef	__ASN_INTERNAL_TEST_MODE__

/*
 * GeneralizedTime basic type description.
 */
static const ber_tlv_tag_t asn_DEF_GeneralizedTime_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (24 << 2)),	/* [UNIVERSAL 24] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (26 << 2)),  /* [UNIVERSAL 26] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))    /* ... OCTET STRING */
};
asn_TYPE_descriptor_t asn_DEF_GeneralizedTime = {
	"GeneralizedTime",
	"GeneralizedTime",
	GeneralizedTime_print,
	GeneralizedTime_constraint, /* Check validity of time */
	OCTET_STRING_decode_ber<GeneralizedTime, std::vector<uint8_t>>,    /* Implemented in terms of OCTET STRING */
	GeneralizedTime_encode_der,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_GeneralizedTime_tags,
	sizeof(asn_DEF_GeneralizedTime_tags)
	  / sizeof(asn_DEF_GeneralizedTime_tags[0]) - 2,
	asn_DEF_GeneralizedTime_tags,
	sizeof(asn_DEF_GeneralizedTime_tags)
	  / sizeof(asn_DEF_GeneralizedTime_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

#endif	/* __ASN_INTERNAL_TEST_MODE__ */

/*
 * Check that the time looks like the time.
 */
int
GeneralizedTime_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
		asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const GeneralizedTime *st = 0;
	time_t tloc;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const GeneralizedTime*>(structPtr);
  }

	errno = EPERM;			/* Just an unlikely error code */
	tloc = st ? st->ToTime(0, 0) : -1;
	if(tloc == -1 && errno != EPERM) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: Invalid time format: %s (%s:%d)",
			td->name, strerror(errno), __FILE__, __LINE__);
		return -1;
	}

	return 0;
}

asn_enc_rval_t
GeneralizedTime_encode_der(asn_TYPE_descriptor_t *td, void *sptr,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
	asn_enc_rval_t erval;
	int fv, fd;	/* seconds fraction value and number of digits */
	struct tm tm;
	time_t tloc;
  GeneralizedTime* genTime = 0;
  AsnAbstractType* structPtr = static_cast<AsnAbstractType*>(sptr);
  genTime = static_cast<GeneralizedTime*>(structPtr);

	/*
	 * Encode as a canonical DER.
	 */
	errno = EPERM;
  tloc = genTime->ToTimeFrac(&fv, &fd, &tm, true);  /* Recognize time */
	if(tloc == -1 && errno != EPERM)
		/* Failed to recognize time. Fail completely. */
		_ASN_ENCODE_FAILED;

  /* Save time canonically */
  GeneralizedTime st;
	if(!st.FromTimeFrac(tm, fv, fd, true)) 
    _ASN_ENCODE_FAILED;	/* Something went wrong. */
  
  AsnAbstractType* stRef = &st;

	erval = OCTET_STRING_encode_der<GeneralizedTime, std::vector<uint8_t>>(td, stRef, tag_mode, tag, cb, app_key);

	return erval;
}

int
GeneralizedTime_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
	asn_app_consume_bytes_f *cb, void *app_key) {
	const GeneralizedTime* st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const GeneralizedTime*>(structPtr);
  }

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(st) {
		char buf[32];
		struct tm tm;
		int ret;

		errno = EPERM;
		if(st->ToTime(&tm, 1) == -1 && errno != EPERM)
			return (cb("<bad-value>", 11, app_key) < 0) ? -1 : 0;

		ret = snprintf(buf, sizeof(buf),
			"%04d-%02d-%02d %02d:%02d:%02d (GMT)",
			tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
			tm.tm_hour, tm.tm_min, tm.tm_sec);
		assert(ret > 0 && ret < (int)sizeof(buf));
		return (cb(buf, ret, app_key) < 0) ? -1 : 0;
	} else {
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;
	}
}

time_t GeneralizedTime::ToTime(struct tm *ret_tm, bool as_gmt) const {
	return ToTimeFrac(0, 0, ret_tm, as_gmt);
}

time_t
GeneralizedTime::ToTimePrec(int *frac_value, int frac_digits, 
                            struct tm *ret_tm, bool as_gmt) const
{
	time_t tloc;
	int fv, fd = 0;

	if(frac_value)
		tloc = ToTimeFrac(&fv, &fd, ret_tm, as_gmt);
	else
		return ToTimeFrac(0, 0, ret_tm, as_gmt);
	if(fd == 0 || frac_digits <= 0) {
		*frac_value = 0;
	} else {
		while(fd > frac_digits)
			fv /= 10, fd--;
		while(fd < frac_digits) {
			if(fv < INT_MAX / 10) {
				fv *= 10;
				fd++;
			} else {
				/* Too long precision request */
				fv = 0;
				break;
			}
		}

		*frac_value = fv;
	}

	return tloc;
}

time_t
GeneralizedTime::ToTimeFrac(int *frac_value, int *frac_digits, 
                            struct tm *ret_tm, bool as_gmt) const
{
	struct tm tm_s;
	const uint8_t *buf;
	const uint8_t *end;
	int gmtoff_h = 0;
	int gmtoff_m = 0;
	int gmtoff = 0;	/* h + m */
	int offset_specified = 0;
	int fvalue = 0;
	int fdigits = 0;
	time_t tloc;

  
  buf = static_cast<const uint8_t*>(this->data());
  end = buf + this->size();
    
	if(this->size() < 10) {
		errno = EINVAL;
		return -1;
	}

	/*
	 * Decode first 10 bytes: "AAAAMMJJhh"
	 */
	memset(&tm_s, 0, sizeof(tm_s));
#undef	B2F
#undef	B2T
#define	B2F(var)	do {					\
		unsigned ch = *buf;				\
		if(ch < 0x30 || ch > 0x39) {			\
			errno = EINVAL;				\
			return -1;				\
		} else {					\
			var = var * 10 + (ch - 0x30);		\
			buf++;					\
		}						\
	} while(0)
#define	B2T(var)	B2F(tm_s.var)

	B2T(tm_year);	/* 1: A */
	B2T(tm_year);	/* 2: A */
	B2T(tm_year);	/* 3: A */
	B2T(tm_year);	/* 4: A */
	B2T(tm_mon);	/* 5: M */
	B2T(tm_mon);	/* 6: M */
	B2T(tm_mday);	/* 7: J */
	B2T(tm_mday);	/* 8: J */
	B2T(tm_hour);	/* 9: h */
	B2T(tm_hour);	/* 0: h */

	if(buf == end) goto local_finish;

	/*
	 * Parse [mm[ss[(.|,)ffff]]]
	 *        ^^
	 */
	switch(*buf) {
	case 0x30: case 0x31: case 0x32: case 0x33: case 0x34:
	case 0x35: case 0x36: case 0x37: case 0x38: case 0x39:
		tm_s.tm_min = (*buf++) - 0x30;
		if(buf == end) { errno = EINVAL; return -1; }
		B2T(tm_min);
		break;
	case 0x2B: case 0x2D:	/* +, - */
		goto offset;
	case 0x5A:		/* Z */
		goto utc_finish;
	default:
		errno = EINVAL;
		return -1;
	}

	if(buf == end) goto local_finish;

	/*
	 * Parse [mm[ss[(.|,)ffff]]]
	 *           ^^
	 */
	switch(*buf) {
	case 0x30: case 0x31: case 0x32: case 0x33: case 0x34:
	case 0x35: case 0x36: case 0x37: case 0x38: case 0x39:
		tm_s.tm_sec = (*buf++) - 0x30;
		if(buf == end) { errno = EINVAL; return -1; }
		B2T(tm_sec);
		break;
	case 0x2B: case 0x2D:	/* +, - */
		goto offset;
	case 0x5A:		/* Z */
		goto utc_finish;
	default:
		errno = EINVAL;
		return -1;
	}

	if(buf == end) goto local_finish;

	/*
	 * Parse [mm[ss[(.|,)ffff]]]
	 *               ^ ^
	 */
	switch(*buf) {
	case 0x2C: case 0x2E: /* (.|,) */
		/*
		 * Process fractions of seconds.
		 */
		for(buf++; buf < end; buf++) {
			int v = *buf;
			/* GCC 4.x is being too smart without volatile */
			switch(v) {
			case 0x30: case 0x31: case 0x32: case 0x33: case 0x34:
			case 0x35: case 0x36: case 0x37: case 0x38: case 0x39:
				if(fvalue < INT_MAX/10) {
					fvalue = fvalue * 10 + (v - 0x30);
					fdigits++;
				} else {
					/* Not enough precision, ignore */
				}
				continue;
			default:
				break;
			}
			break;
		}
	}

	if(buf == end) goto local_finish;

	switch(*buf) {
	case 0x2B: case 0x2D:	/* +, - */
		goto offset;
	case 0x5A:		/* Z */
		goto utc_finish;
	default:
		errno = EINVAL;
		return -1;
	}


offset:

	if(end - buf < 3) {
		errno = EINVAL;
		return -1;
	}
	buf++;
	B2F(gmtoff_h);
	B2F(gmtoff_h);
	if(buf[-3] == 0x2D)	/* Negative */
		gmtoff = -1;
	else
		gmtoff = 1;

	if((end - buf) == 2) {
		B2F(gmtoff_m);
		B2F(gmtoff_m);
	} else if(end != buf) {
		errno = EINVAL;
		return -1;
	}

	gmtoff = gmtoff * (3600 * gmtoff_h + 60 * gmtoff_m);

	/* Fall through */
utc_finish:

	offset_specified = 1;

	/* Fall through */
local_finish:

	/*
	 * Validation.
	 */
	if((tm_s.tm_mon > 12 || tm_s.tm_mon < 1)
	|| (tm_s.tm_mday > 31 || tm_s.tm_mday < 1)
	|| (tm_s.tm_hour > 23)
	|| (tm_s.tm_sec > 60)
	) {
		errno = EINVAL;
		return -1;
	}

	/* Canonicalize */
	tm_s.tm_mon -= 1;	/* 0 - 11 */
	tm_s.tm_year -= 1900;
	tm_s.tm_isdst = -1;

	tm_s.tm_sec -= gmtoff;

	/*** AT THIS POINT tm_s is either GMT or local (unknown) ****/

	if(offset_specified) {
		tloc = timegm(&tm_s);
	} else {
		/*
		 * Without an offset (or "Z"),
		 * we can only guess that it is a local zone.
		 * Interpret it in this fashion.
		 */
		tloc = mktime(&tm_s);
	}
	if(tloc == -1) {
		errno = EINVAL;
		return -1;
	}

	if(ret_tm) {
		if(as_gmt) {
			if(offset_specified) {
				*ret_tm = tm_s;
			} else {
				if(gmtime_r(&tloc, ret_tm) == 0) {
					errno = EINVAL;
					return -1;
				}
			}
		} else {
			if(localtime_r(&tloc, ret_tm) == 0) {
				errno = EINVAL;
				return -1;
			}
		}
	}

	/* Fractions of seconds */
	if(frac_value) *frac_value = fvalue;
	if(frac_digits) *frac_digits = fdigits;

	return tloc;
}

bool GeneralizedTime::FromTime(const struct tm& tm, bool force_gmt) {
	return FromTimeFrac(tm, 0, 0, force_gmt);
}

bool GeneralizedTime::FromTimeFrac(const struct tm &tmRef, int frac_value, 
                                   int frac_digits, bool force_gmt)
{
  const struct tm* tm = &tmRef;
	struct tm tm_s;
	long gmtoff;
	const unsigned int buf_size =
		4 + 2 + 2	/* yyyymmdd */
		+ 2 + 2 + 2	/* hhmmss */
		+ 1 + 6		/* .ffffff */
		+ 1 + 4		/* +hhmm */
		+ 1		/* '\0' */
		;
	std::vector<uint8_t> buf;
	char *p;
	int size;

	/* Check arguments */
	if(!tm) {
		errno = EINVAL;
		return 0;
	}

	/* Pre-allocate a buffer of sufficient yet small length */
  buf.resize(buf_size);

	gmtoff = GMTOFF(*tm);

	if(force_gmt && gmtoff) {
		tm_s = *tm;
		tm_s.tm_sec -= gmtoff;
		timegm(&tm_s);	/* Fix the time */
		tm = &tm_s;
#ifdef	HAVE_TM_GMTOFF
		assert(!GMTOFF(tm_s));	/* Will fix itself */
#else	/* !HAVE_TM_GMTOFF */
		gmtoff = 0;
#endif
	}

	size = snprintf(reinterpret_cast<char*>(buf.data()), buf_size, 
    "%04d%02d%02d%02d%02d%02d",
		tm->tm_year + 1900,
		tm->tm_mon + 1,
		tm->tm_mday,
		tm->tm_hour,
		tm->tm_min,
		tm->tm_sec
	);
	if(size != 14) {
		/* Could be assert(size == 14); */
		errno = EINVAL;
		return 0;
	}

	p = reinterpret_cast<char*>(buf.data()) + size;

	/*
	 * Deal with fractions.
	 */
	if(frac_value > 0 && frac_digits > 0) {
		char *end = p + 1 + 6;	/* '.' + maximum 6 digits */
		char *z = p;
		long fbase;
		*z++ = '.';

		/* Place bounds on precision */
		while(frac_digits-- > 6)
			frac_value /= 10;

		/* emulate fbase = pow(10, frac_digits) */
		for(fbase = 1; frac_digits--;)
			fbase *= 10;

		do {
			int digit = frac_value / fbase;
			if(digit > 9) { z = 0; break; }
			*z++ = digit + 0x30;
			frac_value %= fbase;
			fbase /= 10;
		} while(fbase > 0 && frac_value > 0 && z < end);
		if(z) {
			for(--z; *z == 0x30; --z);	/* Strip zeroes */
			p = z + (*z != '.');
			size = p - reinterpret_cast<char*>(buf.data());
		}
	}

	if(force_gmt) {
		*p++ = 0x5a;	/* "Z" */
		*p++ = 0;
		size++;
	} else {
		int ret;
		gmtoff %= 86400;
		ret = snprintf(p, buf_size - size, "%+03ld%02ld",
			gmtoff / 3600, labs(gmtoff % 3600) / 60);
		if(ret != 5) {
			errno = EINVAL;
			return 0;
		}
		size += ret;
	}

  this->swap(buf);
  this->resize(size);

	return true;
}

