/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
/*
 * Read the NativeReal.hpp for the explanation wrt. differences between
 * REAL and NativeReal.
 * Basically, both are decoders and encoders of ASN.1 REAL type, but this
 * implementation deals with the standard (machine-specific) representation
 * of them instead of using the platform-independent buffer.
 */
#include <asn_internal.hpp>
#include <NativeReal.hpp>
#include <REAL.hpp>
#include <OCTET_STRING.hpp>

/*
 * NativeReal basic type description.
 */
static const ber_tlv_tag_t asn_DEF_NativeReal_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (9 << 2))
};
asn_TYPE_descriptor_t asn_DEF_NativeReal = {
	"REAL",			/* The ASN.1 type is still REAL */
	"REAL",
	NativeReal_print,
	asn_generic_no_constraint,
	NativeReal_decode_ber,
	NativeReal_encode_der,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_NativeReal_tags,
	sizeof(asn_DEF_NativeReal_tags) / sizeof(asn_DEF_NativeReal_tags[0]),
	asn_DEF_NativeReal_tags,	/* Same as above */
	sizeof(asn_DEF_NativeReal_tags) / sizeof(asn_DEF_NativeReal_tags[0]),
	0, 0,	/* No members */
	0	/* No specifics */
};

/*
 * Decode REAL type.
 */
asn_dec_rval_t
NativeReal_decode_ber(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td,
	void **dbl_ptr, const void *buf_ptr, size_t size, int tag_mode) {
	double *Dbl = &static_cast<NativeReal*>(static_cast<AsnAbstractType*>(*dbl_ptr))->value;
	asn_dec_rval_t rval;
	ber_tlv_len_t length;

	/*
	 * If the structure is not there, allocate it.
	 */
	if(Dbl == NULL) {
    ASN_DEBUG("No allocated memory for NativeReal_decode_ber");
			rval.code = RC_FAIL;
			rval.consumed = 0;
			return rval;
	}

	ASN_DEBUG("Decoding %s as REAL (tm=%d)",
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
	 * ASN.1 encoded REAL: buf_ptr, length
	 * Fill the Dbl, at the same time checking for overflow.
	 * If overflow occured, return with RC_FAIL.
	 */
	{
		struct BufPtrAndSizeStruct {
      uint8_t *buf;  
      int size;      
    } tmp;
		union {
			const void *constbuf;
			void *nonconstbuf;
		} unconst_buf;
		double d;

		unconst_buf.constbuf = buf_ptr;
		tmp.buf = (uint8_t *)unconst_buf.nonconstbuf;
		tmp.size = length;

		if(length < (ber_tlv_len_t)size) {
			int ret;
			uint8_t saved_byte = tmp.buf[tmp.size];
			tmp.buf[tmp.size] = '\0';
			ret = REAL::ToDouble(tmp.buf, tmp.size, d);
			tmp.buf[tmp.size] = saved_byte;
			if(!ret) {
				rval.code = RC_FAIL;
				rval.consumed = 0;
				return rval;
			}
		} else if(length < 48 /* Enough for longish %f value. */) {
			tmp.buf = (uint8_t*)alloca(length + 1);
			tmp.size = length;
			memcpy(tmp.buf, buf_ptr, length);
			tmp.buf[tmp.size] = '\0';
			if(!REAL::ToDouble(tmp.buf, tmp.size, d)) {
				rval.code = RC_FAIL;
				rval.consumed = 0;
				return rval;
			}
		} else {
			/* This should probably never happen: impractically long value */
			tmp.buf = (uint8_t*)CALLOC(1, length + 1);
			tmp.size = length;
			if(tmp.buf) memcpy(tmp.buf, buf_ptr, length);
			if(!tmp.buf || !REAL::ToDouble(tmp.buf, tmp.size, d)) {
				FREEMEM(tmp.buf);
				rval.code = RC_FAIL;
				rval.consumed = 0;
				return rval;
			}
			FREEMEM(tmp.buf);
		}

		*Dbl = d;
	}

	rval.code = RC_OK;
	rval.consumed += length;

	ASN_DEBUG("Took %ld/%ld bytes to encode %s (%f)",
		(long)rval.consumed, (long)length, td->name, *Dbl);

	return rval;
}

/*
 * Encode the NativeReal using the standard REAL type DER encoder.
 */
asn_enc_rval_t
NativeReal_encode_der(asn_TYPE_descriptor_t *td, void *ptr,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
	double Dbl = static_cast<NativeReal*>(static_cast<AsnAbstractType*>(ptr))->value;
	asn_enc_rval_t erval;
	REAL tmp;

	/* Prepare a temporary clean structure */

	if(!tmp.FromDouble(Dbl)) {
		erval.encoded = -1;
		erval.failed_type = td;
		erval.structure_ptr = ptr;
		return erval;
	}
	
	/* Encode a fake REAL */
  void* tmpPtr = static_cast<AsnAbstractType*>(&tmp);
	erval = der_encode_primitive<REAL>(td, tmpPtr, tag_mode, tag, cb, app_key);
	if(erval.encoded == -1) {
		assert(erval.structure_ptr == tmpPtr);
		erval.structure_ptr = ptr;
	}

	return erval;
}

/*
 * REAL specific human-readable output.
 */
int
NativeReal_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
	asn_app_consume_bytes_f *cb, void *app_key) {
	const double *Dbl = &static_cast<const NativeReal *>(static_cast<const AsnAbstractType*>(sptr))->value;

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(!Dbl) return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;

	return (REAL__dump(*Dbl, 0, cb, app_key) < 0) ? -1 : 0;
}


