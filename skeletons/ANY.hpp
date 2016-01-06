/* 
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef ASN_TYPE_ANY_HPP
#define ASN_TYPE_ANY_HPP

#include <OCTET_STRING.hpp>	/* Implemented via OCTET STRING type */


extern asn_TYPE_descriptor_t asn_DEF_ANY;

asn_struct_print_f ANY_print;
ber_type_decoder_f ANY_decode_ber;

class ANY : public _OCTET_STRING<&asn_DEF_ANY> {
public:
  ANY() : _OCTET_STRING() { }
  ANY(const ANY& other) : 
              _OCTET_STRING(other) { }
  ANY(ANY&& other) noexcept : 
              _OCTET_STRING(std::move(other)) { }
  ANY& operator =(const ANY& other) {
    _OCTET_STRING::operator =(other);
    return *this;
  }
  ANY& operator =(ANY&& other) noexcept {
    _OCTET_STRING::operator =(std::move(other));
    return *this;
  }
  using _OCTET_STRING::operator =;
  virtual ~ANY() noexcept { }
  /*
   * Convert another ASN.1 type into the ANY. This implies DER encoding. 
   * Returns true if conversion is successful, and false otherwise.
   */
  bool FromType(const AsnAbstractType& type) {
    std::vector<uint8_t> buffer;
    asn_enc_rval_t erval = type.EncodeDer(buffer);
    if (erval.encoded < 0) {
      return false;
    } else {
      *this = std::move(buffer);
      return true;
    }
  }
  /*
   * Convert another ASN.1 type into the ANY. This implies DER encoding. 
   * Optional parameter isSuccessful will contain true if conversion is 
   * successful, and false otherwise.
   */
  static ANY CreateFromType(const AsnAbstractType& type, bool* isSuccessful = nullptr) {
    ANY any;
    bool result = any.FromType(type);
    if (isSuccessful)
      *isSuccessful = result;
    return std::move(any);
  }
  /* Convert the contents of the ANY type into the specified type. */
  bool ToType(AsnAbstractType& type) const {
    asn_dec_rval_t rval;
    type.Clear();
    rval = type.DecodeBer(*this);
    return RC_OK == rval.code ? true : false;
  }
};

#endif	/* ASN_TYPE_ANY_HPP */
