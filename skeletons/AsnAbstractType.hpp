/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */

#ifndef ASNABSTRACTTYPE_HPP
#define	ASNABSTRACTTYPE_HPP

#include <asn_internal.hpp>
#include <vector>
#include <memory>
#include <stdexcept>
#include <ostream>

class AsnAbstractType {
private:
  /*
   * The result of the last BER decoding. BER decoding function will call the 
   * Clear method before decoding if this field equals to RC_OK.
   */
  asn_dec_rval_code_e    _lastBerDecodingResult = RC_WMORE;
#ifdef ENABLE_ANOTHER_PRINT_FUNC
  /* 
   * _anotherPrintFunc may contain pointer on user-defined print function 
   * for a particular object. If this pointer isn't 0, _Print will call this 
   * function instead of a function from type descriptor. Copy, move and clear 
   * operations don't affect this pointer. Use function CheckConstraints to set
   * or reset this pointer.
   */
  asn_struct_print_f* _anotherPrintFunc{0};
#endif
protected:
  AsnAbstractType() { }
  AsnAbstractType(const AsnAbstractType& other) { *this = other; }
  AsnAbstractType(AsnAbstractType&& other) noexcept {
    *this = std::move(other);
  }
  AsnAbstractType& operator =(const AsnAbstractType& other) {
    this->_lastBerDecodingResult = other._lastBerDecodingResult;
    return *this;
  }
  AsnAbstractType& operator =(AsnAbstractType&& other) noexcept {
    this->_lastBerDecodingResult = other._lastBerDecodingResult;
    other.AsnAbstractType::Clear();
    return *this;
  }
public:
  virtual ~AsnAbstractType() noexcept { }
  /*
   * Clears content of this object.
   * 
   * Note: all descendants must call this method Clear in the case of its
   * overriding since in the other case there will not be opportunity
   * to use the same class for the next decoding.
   */
  virtual void Clear() { 
    _lastBerDecodingResult = RC_WMORE;
  }
  /*
   * The BER decoder.
   */
  asn_dec_rval_t DecodeBer(const uint8_t* buf, size_t size) {
    asn_codec_ctx_t s_codec_ctx;
    memset(&s_codec_ctx, 0, sizeof(s_codec_ctx));
    s_codec_ctx.max_stack_size = _ASN_DEFAULT_STACK_MAX;
    return _DecodeBer(buf, size, &s_codec_ctx, this->_getDefaultTypeDescriptorPtr(), 0);
  }
  /*
   * The BER decoder.
   */
  asn_dec_rval_t DecodeBer(const std::vector<uint8_t>& buffer) {
    return DecodeBer(reinterpret_cast<const uint8_t*>(buffer.data()), buffer.size());
  }
  /*
   * The DER encoder.
   */
  asn_enc_rval_t EncodeDer(std::vector<uint8_t>& buffer) const;
  /*
   * The DER encoder.
   */
  asn_enc_rval_t EncodeDer(std::ostream& out) const;
  /*
   * Prints out the contents of the structure into the stream in a human 
   * readable form.
   * RETURN VALUES:
   * 	 true: The structure is printed.
   * 	 false: Problem dumping the structure.
   */
  bool Print(std::ostream& out) const;
  /*
   * Validate the structure according to the ASN.1 constraints.
   * 
   * ctfailcb  Log the error
   * app_key   Opaque key passed to a callback
   * 
   * RETURN VALUES:
   * This function returns true in case all ASN.1 constraints are met
   * and false if one or more constraints were failed.
   */
  bool CheckConstraints(asn_app_constraint_failed_f* ctfailcb = 0, void* app_key = 0) const;
#ifdef ENABLE_ANOTHER_PRINT_FUNC
  /*
   * Replaces a print function for this object on user-defined print function.
   */
  void ChangePrintFunc(asn_struct_print_f* anotherPrintFunc = 0) {
    this->_anotherPrintFunc = anotherPrintFunc;
  }
  /*
   * Returns a pointer to a function which replaces a print function for 
   * this object.
   */
  asn_struct_print_f* GetAnotherPrintFunc() const { return this->_anotherPrintFunc; }
#endif
private:
  virtual asn_TYPE_descriptor_t* _getDefaultTypeDescriptorPtr() const = 0;
  /* 
   * These functions are for internal purposes. Don't use them directly.
   */
  asn_dec_rval_t _DecodeBer(const uint8_t* buf, size_t size, 
                           asn_codec_ctx_t *opt_codec_ctx, 
                           asn_TYPE_descriptor_t *td, 
                           int tag_mode);
  asn_enc_rval_t _EncodeDer(asn_TYPE_descriptor_t *td, int tag_mode,
                 ber_tlv_tag_t tag, 
                 asn_app_consume_bytes_f *consume_bytes, void *app_key) const;
  int _Print(asn_TYPE_descriptor_t *td, int ilevel,
                            asn_app_consume_bytes_f *cb, void *app_key) const;
  int _CheckConstraints(asn_constr_check_f *memb_constraints = 0, asn_TYPE_descriptor_t *td = 0, 
            asn_app_constraint_failed_f *ctfailcb = 0, void *app_key = 0) const;
  
  static int _EncodeDerBufferCb(const void* buffer, size_t size, void* key);
  static int _EncodeDerOstreamCb(const void* buffer, size_t size, void* key);
  static int _PrintOstreamCb(const void* buffer, size_t size, void* key);
  
//  template <class Type, class ValueType> 
//  friend asn_struct_print_f OCTET_STRING_print;
  friend asn_struct_print_f CHOICE_print;
  friend asn_constr_check_f CHOICE_constraint;
  friend ber_type_decoder_f CHOICE_decode_ber;
  friend der_type_encoder_f CHOICE_encode_der;
  friend asn_struct_print_f SEQUENCE_print;
  friend asn_constr_check_f SEQUENCE_constraint;
  friend ber_type_decoder_f SEQUENCE_decode_ber;
  friend der_type_encoder_f SEQUENCE_encode_der;
  friend asn_struct_print_f SET_OF_print;
  friend asn_constr_check_f SET_OF_constraint;
  friend ber_type_decoder_f SET_OF_decode_ber;
  friend der_type_encoder_f SET_OF_encode_der;
  friend der_type_encoder_f SEQUENCE_OF_encode_der;
  friend asn_struct_print_f SET_print;
  friend asn_constr_check_f SET_constraint;
  friend ber_type_decoder_f SET_decode_ber;
  friend der_type_encoder_f SET_encode_der;
};

/*
 * The means by which it becomes possible to print the content of the record
 * into the stream without calling the method Print. For example 
 * std::cout << record;
 */
std::ostream& operator <<(std::ostream& out, const AsnAbstractType& asnType);


/*
 * Class for managing decoding context of structural types where 
 * simple copying will be enough. Don't use it directly.
 */
class asnStructCtx : public AsnAbstractType {
private:
  asn_struct_ctx_t _asn_ctx;
protected:
  asnStructCtx() { _initCtx(); }
  asnStructCtx(const asnStructCtx&) = default;
  asnStructCtx(asnStructCtx&& other) noexcept : AsnAbstractType(std::move(other)) {
    _asn_ctx = std::move(other._asn_ctx);
    other._initCtx();
  }
  asnStructCtx& operator = (const asnStructCtx&) = default;
  asnStructCtx& operator = (asnStructCtx&& other) noexcept {
    _asn_ctx = std::move(other._asn_ctx);
    other._initCtx();
    AsnAbstractType::operator =(std::move(other));
    return *this;
  }
  void _initCtx() { memset(&_asn_ctx, 0, sizeof(_asn_ctx)); }
  void Clear() override { _initCtx(); AsnAbstractType::Clear(); }
public:
  virtual ~asnStructCtx() noexcept {}
private:
  asn_struct_ctx_t* _getStructCtx() { return &_asn_ctx; }
  
  friend ber_type_decoder_f SEQUENCE_decode_ber;
  friend ber_type_decoder_f SET_decode_ber;
  friend ber_type_decoder_f SET_OF_decode_ber;
  friend ber_type_decoder_f CHOICE_decode_ber;
};

#ifdef __CYGWIN__

/*
 * GCC 4.8.3 in Cygwin says that to_string is not the member of std
 */ 
#include <sstream>
#include <string>
#include <iostream>
namespace std {
template <typename T>
    std::string to_string(T value) {
        std::ostringstream ss;
        ss << value;
        return ss.str();
    }
}
#endif

#endif	

