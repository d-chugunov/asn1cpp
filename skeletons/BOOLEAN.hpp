/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_BOOLEAN_HPP_
#define	_BOOLEAN_HPP_

#include <asn_application.hpp>

extern asn_TYPE_descriptor_t asn_DEF_BOOLEAN;

asn_struct_print_f BOOLEAN_print;
template <class Type>
ber_type_decoder_f BOOLEAN_decode_ber;
der_type_encoder_f BOOLEAN_encode_der;

#include <AsnNativePrimitiveType.hpp>

/*
 * The underlying integer may contain various values, but everything
 * non-zero is capped to 0xff by the DER encoder. The BER decoder may
 * yield non-zero values different from 1, beware.
 */
typedef int _BOOLEANType;
typedef AsnNativePrimitiveType<_BOOLEANType, &asn_DEF_BOOLEAN, 1> BOOLEAN;


/*
 * Decode BOOLEAN type.
 */
template <class Type>
asn_dec_rval_t
BOOLEAN_decode_ber(asn_codec_ctx_t *opt_codec_ctx,
		asn_TYPE_descriptor_t *td,
		void **bool_value, const void *buf_ptr, size_t size,
		int tag_mode) {
	_BOOLEANType *st = &static_cast<Type*>(static_cast<AsnAbstractType*>(*bool_value))->value;
	asn_dec_rval_t rval;
	ber_tlv_len_t length;
	ber_tlv_len_t lidx;

	if(st == NULL) {
      ASN_DEBUG("No allocated memory for BOOLEAN_decode_ber");
			rval.code = RC_FAIL;
			rval.consumed = 0;
			return rval;
	}

	ASN_DEBUG("Decoding %s as BOOLEAN (tm=%d)",
		td->name, tag_mode);

	/*
	 * Check tags.
	 */
	rval = ber_check_tags(opt_codec_ctx, td, 0, buf_ptr, size,
		tag_mode, 0, &length, 0);
	if(rval.code != RC_OK)
		return rval;

	ASN_DEBUG("Boolean length is %d bytes", (int)length);

	buf_ptr = ((const char *)buf_ptr) + rval.consumed;
	size -= rval.consumed;
	if(length > (ber_tlv_len_t)size) {
		rval.code = RC_WMORE;
		rval.consumed = 0;
		return rval;
	}

	/*
	 * Compute boolean value.
	 */
	for(*st = 0, lidx = 0;
		(lidx < length) && *st == 0; lidx++) {
		/*
		 * Very simple approach: read bytes until the end or
		 * value is already TRUE.
		 * BOOLEAN is not supposed to contain meaningful data anyway.
		 */
		*st |= ((const uint8_t *)buf_ptr)[lidx];
	}

	rval.code = RC_OK;
	rval.consumed += length;

	ASN_DEBUG("Took %ld/%ld bytes to encode %s, value=%d",
		(long)rval.consumed, (long)length,
		td->name, *st);
	
	return rval;
}

#endif	/* _BOOLEAN_HPP_ */
