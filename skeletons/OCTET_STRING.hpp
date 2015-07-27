/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_OCTET_STRING_HPP_
#define	_OCTET_STRING_HPP_

#include <asn_application.hpp>
#include <asn_codecs_prim.hpp>

extern asn_TYPE_descriptor_t asn_DEF_OCTET_STRING;

void OCTET_STRING_free_decode_time_stack(void*& ptr);
void* OCTET_STRING_copy_decode_time_stack(void* ptr);

template <class Type, class ValueType>
asn_struct_print_f OCTET_STRING_print;

template <class Type, class ValueType>
asn_struct_print_f OCTET_STRING_print_utf8;

template <class Type, class ValueType>
ber_type_decoder_f OCTET_STRING_decode_ber;
  
template <class Type, class ValueType>
der_type_encoder_f OCTET_STRING_encode_der;

/*
 * Class for managing decoding context of OCTET STRING. Don't use it directly.
 */
template<asn_TYPE_descriptor_t* typeDescriptorPtr, class ValueType = std::vector<uint8_t>>
class asnStructCtxOS : public AsnPrimitiveType<typeDescriptorPtr, ValueType> {
private:
  asn_struct_ctx_t _asn_ctx;
protected:
  asnStructCtxOS() { _initCtx(); }
  asnStructCtxOS(const asnStructCtxOS&) = delete;
  asnStructCtxOS(asnStructCtxOS&&) = delete;
  asnStructCtxOS& operator =(const asnStructCtxOS& other) {
    _copyAsnCtx(this->_asn_ctx, other._asn_ctx);
    AsnPrimitiveType<typeDescriptorPtr, ValueType>::operator =(other);
    return *this;
  }
  asnStructCtxOS& operator =(asnStructCtxOS&& other) noexcept {
    _moveAsnCtx(this->_asn_ctx, std::move(other._asn_ctx));
    AsnPrimitiveType<typeDescriptorPtr, ValueType>::operator =(std::move(other));
    return *this;
  }
  void _initCtx() { memset(&_asn_ctx, 0, sizeof(_asn_ctx)); }
  void Clear() override {
    FreeDecodeTimeStack();
    _initCtx();
    AsnPrimitiveType<typeDescriptorPtr, ValueType>::Clear();
  }
  using AsnPrimitiveType<typeDescriptorPtr, ValueType>::operator =;
public:
  virtual ~asnStructCtxOS() noexcept { FreeDecodeTimeStack(); }
private:
  asn_struct_ctx_t* _getStructCtx() { return &_asn_ctx; }
  void FreeDecodeTimeStack() {
    OCTET_STRING_free_decode_time_stack(_asn_ctx.ptr);
    _asn_ctx.ptr = nullptr;
  }
  static void _copyAsnCtx(asn_struct_ctx_t& myCtx, const asn_struct_ctx_t& otherCtx) {
    myCtx = otherCtx;
    myCtx.ptr = OCTET_STRING_copy_decode_time_stack(otherCtx.ptr);
  }
  static void _moveAsnCtx(asn_struct_ctx_t& myCtx, asn_struct_ctx_t&& otherCtx) {
    myCtx = otherCtx;
    memset(&otherCtx, 0, sizeof(otherCtx));
  }
  template <class T, class S>
  friend ber_type_decoder_f OCTET_STRING_decode_ber;
};

template<asn_TYPE_descriptor_t* typeDescriptorPtr, class ValueType = std::vector<uint8_t>>
class _OCTET_STRING : public asnStructCtxOS<typeDescriptorPtr, ValueType>
{
public:
  _OCTET_STRING() : asnStructCtxOS<typeDescriptorPtr, ValueType>() { }
  _OCTET_STRING(const _OCTET_STRING& other) : 
              asnStructCtxOS<typeDescriptorPtr, ValueType>() { 
    *this = other;
  }
  _OCTET_STRING(_OCTET_STRING&& other) noexcept : 
             asnStructCtxOS<typeDescriptorPtr, ValueType>() { 
    *this = std::move(other);
  }
  _OCTET_STRING& operator =(const _OCTET_STRING& other) {
    asnStructCtxOS<typeDescriptorPtr, ValueType>::operator =(other);
    return *this;
  }
  _OCTET_STRING& operator =(_OCTET_STRING&& other) noexcept {
    asnStructCtxOS<typeDescriptorPtr, ValueType>::operator =(std::move(other));
    return *this;
  }
  using asnStructCtxOS<typeDescriptorPtr, ValueType>::operator =;
  virtual ~_OCTET_STRING() noexcept { }
  void Clear() override {
    asnStructCtxOS<typeDescriptorPtr, ValueType>::Clear();
  }
};

typedef _OCTET_STRING<&asn_DEF_OCTET_STRING> OCTET_STRING;

/****************************
 * Internally useful stuff. *
 ****************************/

typedef const struct asn_OCTET_STRING_specifics_s {
	/*
	 * Target structure description.
	 */

	enum asn_OS_Subvariant {
		ASN_OSUBV_ANY,	/* The open type (ANY) */
		ASN_OSUBV_BIT,	/* BIT STRING */
		ASN_OSUBV_STR,	/* String types, not {BMP,Universal}String  */
		ASN_OSUBV_U16,	/* 16-bit character (BMPString) */
		ASN_OSUBV_U32	/* 32-bit character (UniversalString) */
	} subvariant;
} asn_OCTET_STRING_specifics_t;

template <class ValueType>
asn_dec_rval_t
OCTET_STRING_decode_ber_impl(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td, AsnAbstractType* structPtr,
	ValueType *st, asn_struct_ctx_t *ctx, const void *buf_ptr, size_t size, int tag_mode);

template <class Type, class ValueType>
asn_dec_rval_t
OCTET_STRING_decode_ber(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td,
	void **sptr, const void *buf_ptr, size_t size, int tag_mode) {
	asn_OCTET_STRING_specifics_t *specs = td->specifics
				? (asn_OCTET_STRING_specifics_t *)td->specifics
				: nullptr;
  Type* st = 0;
  asn_struct_ctx_t *ctx;
	asn_OCTET_STRING_specifics_t::asn_OS_Subvariant type_variant = 
          specs ? specs->subvariant : asn_OCTET_STRING_specifics_t::ASN_OSUBV_STR;
  
	ASN_DEBUG("Decoding %s as %s (frame %ld)",
		td->name,
		(type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_STR) ?
			"OCTET STRING" : "OS-SpecialCase",
		(long)size);
  (void)type_variant;

	if(*sptr == NULL) {
    ASN_DEBUG("No allocated memory for OCTET_STRING_decode_ber");
    asn_dec_rval_t tmprval;
		tmprval.code = RC_FAIL;
		tmprval.consumed = 0;
		return tmprval;
  }
  
  AsnAbstractType* structPtr = static_cast<AsnAbstractType*>(*sptr);

  st = static_cast<decltype(st)>(structPtr);
  
  /* Restore parsing context */
  ctx = st->_getStructCtx();
  
  asn_dec_rval_t ret = OCTET_STRING_decode_ber_impl(opt_codec_ctx, td, 
          structPtr,
          static_cast<ValueType*>(st), 
          ctx, buf_ptr, size, tag_mode);
  
  if (ret.code == RC_OK)
    st->FreeDecodeTimeStack();
  return ret;
}

template <class Type>
asn_enc_rval_t
OCTET_STRING_encode_der_impl(asn_TYPE_descriptor_t *td,
  void* sptr,
  AsnAbstractType* structPtr,
	Type *st,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key);

template <class Type, class ValueType>
asn_enc_rval_t
OCTET_STRING_encode_der(asn_TYPE_descriptor_t *td, void *sptr,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
  Type* st = 0;
  AsnAbstractType* structPtr = static_cast<AsnAbstractType*>(sptr);
  st = static_cast<decltype(st)>(structPtr);
  
  
  return OCTET_STRING_encode_der_impl(td, sptr, structPtr, static_cast<ValueType*>(st), tag_mode, tag, cb, app_key);
}

template <class Type, class ValueType>
int
OCTET_STRING_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
	asn_app_consume_bytes_f *cb, void *app_key) {
	static const char *h2c = "0123456789ABCDEF";
	const ValueType* st = 0;
	char scratch[16 * 3 + 4];
	char *p = scratch;
	const uint8_t *buf;
	const uint8_t *end;
	size_t i;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<decltype(st)>(static_cast<const Type*>(structPtr));
  }

	(void)td;	/* Unused argument */

	if(!st)
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;

	/*
	 * Dump the contents of the buffer in hexadecimal.
	 */
	buf = reinterpret_cast<const uint8_t*>(st->data());
	end = buf + st->size();
	for(i = 0; buf < end; buf++, i++) {
		if(!(i % 16) && (i || st->size() > 16)) {
			if(cb(scratch, p - scratch, app_key) < 0)
				return -1;
			_i_INDENT(1);
			p = scratch;
		}
		*p++ = h2c[(*buf >> 4) & 0x0F];
		*p++ = h2c[*buf & 0x0F];
		*p++ = 0x20;
	}

	if(p > scratch) {
		p--;	/* Remove the tail space */
		if(cb(scratch, p - scratch, app_key) < 0)
			return -1;
	}

	return 0;
}

template <class Type, class ValueType>
int
OCTET_STRING_print_utf8(asn_TYPE_descriptor_t *td, const void *sptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	const ValueType* st = 0;
  
  if (sptr) {
    const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
    st = static_cast<decltype(st)>(static_cast<const Type*>(structPtr));
  }

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(st) {
		return (cb(st->data(), st->size(), app_key) < 0) ? -1 : 0;
	} else {
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;
	}
}

#endif	/* _OCTET_STRING_HPP_ */
