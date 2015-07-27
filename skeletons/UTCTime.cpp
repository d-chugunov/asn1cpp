/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <UTCTime.hpp>
#include <GeneralizedTime.hpp>
#include <errno.h>

//#ifdef	__CYGWIN__
//#include "/usr/include/time.h"
//#else
#include <time.h>
//#endif	/* __CYGWIN__ */

#ifndef	__ASN_INTERNAL_TEST_MODE__

/*
 * UTCTime basic type description.
 */
static const ber_tlv_tag_t asn_DEF_UTCTime_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (23 << 2)),	/* [UNIVERSAL 23] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (26 << 2)),  /* [UNIVERSAL 26] IMPLICIT ...*/
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))    /* ... OCTET STRING */
};
asn_TYPE_descriptor_t asn_DEF_UTCTime = {
	"UTCTime",
	"UTCTime",
	UTCTime_print,
	UTCTime_constraint,
	OCTET_STRING_decode_ber<UTCTime, std::vector<uint8_t>>,    /* Implemented in terms of OCTET STRING */
	OCTET_STRING_encode_der<UTCTime, std::vector<uint8_t>>,    /* Implemented in terms of OCTET STRING */
	0, /* Use generic outmost tag fetcher */
	asn_DEF_UTCTime_tags,
	sizeof(asn_DEF_UTCTime_tags)
	  / sizeof(asn_DEF_UTCTime_tags[0]) - 2,
	asn_DEF_UTCTime_tags,
	sizeof(asn_DEF_UTCTime_tags)
	  / sizeof(asn_DEF_UTCTime_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

#endif	/* __ASN_INTERNAL_TEST_MODE__ */

/*
 * Check that the time looks like the time.
 */
int
UTCTime_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
		asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const UTCTime *st = 0;
	time_t tloc;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const UTCTime*>(structPtr);
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

int
UTCTime_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
		asn_app_consume_bytes_f *cb, void *app_key) {
	const UTCTime* st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<const UTCTime*>(structPtr);
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

time_t
UTCTime::ToTime(struct tm *_tm, bool as_gmt) const {
  static const size_t MAX_BUFFER_SIZE = 24;
	GeneralizedTime gt;

	if(this->size() < 11 || this->size() >= ((int)MAX_BUFFER_SIZE - 2)) {
		errno = EINVAL;
		return -1;
	}
  gt.resize(this->size() + 2);
	memcpy(gt.data() + 2, this->data(), this->size());
	if((*this)[0] > 0x35) {
		/* 19xx */
		gt[0] = 0x31;
		gt[1] = 0x39;
	} else {
		/* 20xx */
		gt[0] = 0x32;
		gt[1] = 0x30;
	}
  
  return gt.ToTime(_tm, as_gmt);
}

bool UTCTime::FromTime(const struct tm& tm, bool force_gmt) {
  GeneralizedTime gt;

	if (!gt.FromTime(tm, force_gmt))
    return false;

	assert(gt.size() >= 2);
  const std::vector<uint8_t>& buf(gt);
  this->resize(buf.size() - 1);
  memcpy(this->data(), (char*)buf.data() + 2, buf.size() - 1);
  this->pop_back();

	return true;
}

