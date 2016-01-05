/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef NATIVEPRIMITIVETYPE_HPP
#define	NATIVEPRIMITIVETYPE_HPP

#include <asn_codecs_prim.hpp>

/* This class is only for primitive C/C++ types such as long, double and so on. 
 * comparisonType == 0 for number comparison
 * comparisonType == 1 for BOOLEAN comparison
 * compasironType == 2 for NULL comparison
 */
template <class ValueType, asn_TYPE_descriptor_t* typeDescriptorPtr, int comparisonType = 0>
class AsnNativePrimitiveType : public AsnAbstractType {
public:
  AsnNativePrimitiveType() : AsnAbstractType() { }
  explicit AsnNativePrimitiveType(const ValueType value) : 
               AsnAbstractType(), value(value) { }
  AsnNativePrimitiveType(const AsnNativePrimitiveType& other) : 
                      AsnAbstractType(other) { 
    this->value = other.value; 
  }
  AsnNativePrimitiveType(AsnNativePrimitiveType&& other) noexcept : 
           AsnAbstractType(std::move(other)) { 
    this->value = std::move(other.value); 
    other.value = 0;
  }
  AsnNativePrimitiveType& operator =(const AsnNativePrimitiveType& other) { 
    this->value = other.value; 
    AsnAbstractType::operator =(other);
    return *this;
  }
  AsnNativePrimitiveType& operator =(AsnNativePrimitiveType&& other) noexcept { 
    this->value = std::move(other.value); 
    other.value = 0;
    AsnAbstractType::operator =(std::move(other));
    return *this;
  }
  virtual ~AsnNativePrimitiveType() noexcept { }
  void Clear() override { value = 0; AsnAbstractType::Clear(); }
  operator ValueType() const { return value; }
  AsnNativePrimitiveType& operator =(const ValueType newValue) { 
    this->value = newValue; 
    return *this;
  }
  AsnNativePrimitiveType& operator ++() {
    ++this->value;
    return *this;
  }
  AsnNativePrimitiveType& operator --() {
    --this->value;
    return *this;
  }
  AsnNativePrimitiveType operator++(int) {
    AsnNativePrimitiveType tmp(*this);
    operator ++();
    return tmp;
  }
  AsnNativePrimitiveType operator--(int) {
    AsnNativePrimitiveType tmp(*this);
    operator --();
    return tmp;
  }
  bool operator ==(const AsnNativePrimitiveType& other) const {
    if (2 == comparisonType)
      return true;
    else if (1 == comparisonType)
      return (this->value && other.value) || (!this->value && !other.value);
    else
      return this->value == other.value;
  }
  bool operator !=(const AsnNativePrimitiveType& other) const {
    return !(this->operator ==(other));
  }
private:
  asn_TYPE_descriptor_t* _getDefaultTypeDescriptorPtr() const override { return typeDescriptorPtr; }
protected:
  ValueType value = 0; 
  
  template <class Type>
  friend ber_type_decoder_f BOOLEAN_decode_ber;
  friend der_type_encoder_f BOOLEAN_encode_der;
  friend asn_struct_print_f BOOLEAN_print;
  template <class Type>
  friend asn_struct_print_f NativeInteger_print;
  template <class Type>
  friend ber_type_decoder_f NativeInteger_decode_ber;
  template <class Type>
  friend der_type_encoder_f NativeInteger_encode_der;
  friend asn_struct_print_f NativeReal_print;
  friend ber_type_decoder_f NativeReal_decode_ber;
  friend der_type_encoder_f NativeReal_encode_der;
};

#endif	/* NATIVEPRIMITIVETYPE_HPP */

