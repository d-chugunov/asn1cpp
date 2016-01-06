/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_VisibleString_HPP_
#define	_VisibleString_HPP_

#include <OCTET_STRING.hpp>

template <asn_TYPE_descriptor_t* typeDescriptorPtr>
using _VisibleString = _OCTET_STRING<typeDescriptorPtr, std::string>;

extern asn_TYPE_descriptor_t asn_DEF_VisibleString;

typedef _VisibleString<&asn_DEF_VisibleString> VisibleString;  /* Implemented via OCTET STRING */

template <class Type>
asn_constr_check_f VisibleString_constraint;

template <class Type>
int
VisibleString_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
		asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const Type *st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<decltype(st)>(structPtr);
  }

	if(st) {
		const uint8_t *buf = reinterpret_cast<const uint8_t*>(st->data());
    const uint8_t *buf_beg = buf;
		const uint8_t *end = buf + st->size();

		/*
		 * Check the alphabet of the VisibleString.
		 * ISO646, ISOReg#6
		 * The alphabet is a subset of ASCII between the space
		 * and "~" (tilde).
		 */
		for(; buf < end; buf++) {
			if(*buf < 0x20 || *buf > 0x7e) {
				_ASN_CTFAIL(app_key, td, sptr,
					"%s: value byte %ld (%d) "
					"not in VisibleString alphabet (%s:%d)",
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

#endif	/* _VisibleString_HPP_ */
