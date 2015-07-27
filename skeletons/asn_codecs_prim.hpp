/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	ASN_CODECS_PRIM_HPP
#define	ASN_CODECS_PRIM_HPP

#include <asn_application.hpp>
#include <AsnAbstractType.hpp>

/* Do not use this type directly! */
template <asn_TYPE_descriptor_t* typeDescriptorPtr, class ValueType = std::vector<uint8_t>>
class AsnPrimitiveType : public AsnAbstractType, public ValueType {
public:
  AsnPrimitiveType() : AsnAbstractType(), ValueType() { }
  AsnPrimitiveType(const AsnPrimitiveType& other) : 
            AsnAbstractType(other), ValueType(other) { }
  AsnPrimitiveType(AsnPrimitiveType&& other) noexcept : 
      AsnAbstractType(std::move(other)), ValueType(std::move(other)) { }
  AsnPrimitiveType& operator =(const AsnPrimitiveType& other) { 
    ValueType::operator =(other);
    AsnAbstractType::operator =(other);
    return *this;
  }
  AsnPrimitiveType& operator =(AsnPrimitiveType&& other) noexcept { 
    ValueType::operator =(std::move(other));
    AsnAbstractType::operator =(std::move(other));
    return *this;
  }
  using ValueType::operator =;
  virtual ~AsnPrimitiveType() noexcept { }
  void Clear() override { this->clear(); AsnAbstractType::Clear(); }
private:
  asn_TYPE_descriptor_t* _getDefaultTypeDescriptorPtr() const override { return typeDescriptorPtr; }
};

template <class Type>
ber_type_decoder_f ber_decode_primitive;
template <class Type>
der_type_encoder_f der_encode_primitive;

/*
 * Decode an always-primitive type.
 */
template <class Type>
asn_dec_rval_t
ber_decode_primitive(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td,
	void **sptr, const void *buf_ptr, size_t size, int tag_mode) {
	Type *st = 0;
	asn_dec_rval_t rval;
	ber_tlv_len_t length = 0; // =0 to avoid [incorrect] warning.
  
  /*
	 * If the structure is not there, allocate it.
	 */
	if(*sptr == NULL) {
    ASN_DEBUG("No allocated memory for ber_decode_primitive");
      _ASN_DECODE_FAILED;
	}
  
  {
    AsnAbstractType* structPtr = static_cast<AsnAbstractType*>(*sptr);
    st = static_cast<decltype(st)>(structPtr);
  }

	ASN_DEBUG("Decoding %s as plain primitive (tm=%d)",
		td->name, tag_mode);

	/*
	 * Check tags and extract value length.
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

  st->reserve(length + 1);
  st->resize(length);

	memcpy(st->data(), buf_ptr, length);
	(*st)[length] = '\0';		/* Just in case */

	rval.code = RC_OK;
	rval.consumed += length;

	ASN_DEBUG("Took %ld/%ld bytes to encode %s",
		(long)rval.consumed,
		(long)length, td->name);

	return rval;
}

/*
 * Encode an always-primitive type using DER.
 */
template <class Type>
asn_enc_rval_t
der_encode_primitive(asn_TYPE_descriptor_t *td, void *sptr,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
	asn_enc_rval_t erval;
	Type *st = 0;
  
  {
    AsnAbstractType* structPtr = static_cast<AsnAbstractType*>(sptr);
    st = static_cast<decltype(st)>(structPtr);
  }

	ASN_DEBUG("%s %s as a primitive type (tm=%d)",
		cb?"Encoding":"Estimating", td->name, tag_mode);

	erval.encoded = der_write_tags(td, st->size(), tag_mode, 0, tag,
		cb, app_key);
	ASN_DEBUG("%s wrote tags %d", td->name, (int)erval.encoded);
	if(erval.encoded == -1) {
		erval.failed_type = td;
		erval.structure_ptr = sptr;
		return erval;
	}

	if(cb) {
		if(cb(st->data(), st->size(), app_key) < 0) {
			erval.encoded = -1;
			erval.failed_type = td;
			erval.structure_ptr = sptr;
			return erval;
		}
	} 
//  else {
//		assert(st->size() == 0);
//	}

	erval.encoded += st->size();
	_ASN_ENCODED_OK(erval);
}

#endif	/* ASN_CODECS_PRIM_HPP */
