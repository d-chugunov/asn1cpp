/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
/*
 * This type differs from the standard INTEGER in that it is modelled using
 * the fixed machine type (long, int, short), so it can hold only values of
 * limited length. There is no type (i.e., NativeInteger_t, any integer type
 * will do).
 * This type may be used when integer range is limited by subtype constraints.
 */
#ifndef	_NativeInteger_HPP_
#define	_NativeInteger_HPP_

#include <asn_application.hpp>
#include <INTEGER.hpp>

extern asn_TYPE_descriptor_t asn_DEF_NativeInteger;

template <class Type>
asn_struct_print_f NativeInteger_print;
template <class Type>
ber_type_decoder_f NativeInteger_decode_ber;
template <class Type>
der_type_encoder_f NativeInteger_encode_der;

#include <AsnNativePrimitiveType.hpp>


//long is because asn_DEF_NativeInteger_decode_ber uses long
typedef long _NativeIntegerType;
typedef unsigned long _UnsignedNativeIntegerType;
typedef AsnNativePrimitiveType<_NativeIntegerType, &asn_DEF_NativeInteger> NativeInteger;
typedef AsnNativePrimitiveType<_UnsignedNativeIntegerType, &asn_DEF_NativeInteger> UnsignedNativeInteger;


/*
 * Decode INTEGER type.
 */
template <class Type>
asn_dec_rval_t
NativeInteger_decode_ber(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td,
	void **nint_ptr, const void *buf_ptr, size_t size, int tag_mode) {
	asn_INTEGER_specifics_t *specs=(asn_INTEGER_specifics_t *)td->specifics;
	long *native = &static_cast<Type*>(static_cast<AsnAbstractType*>(*nint_ptr))->value;
	asn_dec_rval_t rval;
	ber_tlv_len_t length;

	/*
	 * If the structure is not there, allocate it.
	 */
	if(native == NULL) {
    ASN_DEBUG("No allocated memory for NativeInteger_decode_ber");
			rval.code = RC_FAIL;
			rval.consumed = 0;
			return rval;
	}

	ASN_DEBUG("Decoding %s as INTEGER (tm=%d)",
		td->name, tag_mode);

	/*
	 * Check tags.
	 */
	rval = ber_check_tags(opt_codec_ctx, td, 0, buf_ptr, size,
			tag_mode, 0, &length, 0);
	if(rval.code != RC_OK)
		return rval;

	ASN_DEBUG("%s length is %d bytes", td->name, (int)length);

	/*
	 * Make sure we have this length.
	 */
	buf_ptr = ((const char *)buf_ptr) + rval.consumed;
	size -= rval.consumed;
	if(length > (ber_tlv_len_t)size) {
		rval.code = RC_WMORE;
		rval.consumed = 0;
		return rval;
	}

	/*
	 * ASN.1 encoded INTEGER: buf_ptr, length
	 * Fill the native, at the same time checking for overflow.
	 * If overflow occured, return with RC_FAIL.
	 */
	{
    long l = 0;
    const uint8_t* buf = static_cast<const uint8_t*>(buf_ptr);

		if((specs&&specs->field_unsigned)
			? !INTEGER::ToULong(buf, length, reinterpret_cast<unsigned long&>(l)) /* sic */
			: !INTEGER::ToLong(buf, length, l)) {
			rval.code = RC_FAIL;
			rval.consumed = 0;
			return rval;
		}

		*native = l;
	}

	rval.code = RC_OK;
	rval.consumed += length;

	ASN_DEBUG("Took %ld/%ld bytes to encode %s (%ld)",
		(long)rval.consumed, (long)length, td->name, (long)*native);

	return rval;
}

/*
 * Encode the NativeInteger using the standard INTEGER type DER encoder.
 */
template <class Type>
asn_enc_rval_t
NativeInteger_encode_der(asn_TYPE_descriptor_t *sd, void *ptr,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
	unsigned long native = static_cast<Type*>(static_cast<AsnAbstractType*>(ptr))->value;	/* Disable sign ext. */
  asn_INTEGER_specifics_t *specs=(asn_INTEGER_specifics_t *)sd->specifics;
	asn_enc_rval_t erval;
	INTEGER tmp;
  
  bool success = (specs&&specs->field_unsigned) ? 
    tmp.FromULong(native) :
    tmp.FromLong(*reinterpret_cast<long*>(&native));
  
  if (!success) {
    ASN_DEBUG("Unable to convert Native type to INTEGER");
    erval.encoded = -1;
    erval.failed_type = sd;
    erval.structure_ptr = ptr;
    return erval;
  }

	/* Encode fake INTEGER */
  void* tmpPtr = static_cast<AsnAbstractType*>(&tmp);
  erval = INTEGER_encode_der<INTEGER>(sd, tmpPtr, tag_mode, tag, cb, app_key);
	if(erval.encoded == -1) {
		assert(erval.structure_ptr == tmpPtr);
		erval.structure_ptr = ptr;
	}
	return erval;
}

/*
 * INTEGER specific human-readable output.
 */
template <class Type>
int
NativeInteger_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
	asn_app_consume_bytes_f *cb, void *app_key) {
	asn_INTEGER_specifics_t *specs=(asn_INTEGER_specifics_t *)td->specifics;
	const long *native = &static_cast<const Type*>(static_cast<const AsnAbstractType*>(sptr))->value;
	char scratch[32];	/* Enough for 64-bit int */
	int ret;

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(native) {
		ret = snprintf(scratch, sizeof(scratch),
			(specs && specs->field_unsigned)
			? "%lu" : "%ld", *native);
		assert(ret > 0 && (size_t)ret < sizeof(scratch));
		return (cb(scratch, ret, app_key) < 0) ? -1 : 0;
	} else {
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;
	}
}


#endif	/* _NativeInteger_HPP_ */
