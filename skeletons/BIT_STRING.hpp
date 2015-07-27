/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_BIT_STRING_HPP_
#define	_BIT_STRING_HPP_

#include <OCTET_STRING.hpp>	/* Some help from OCTET STRING */

extern asn_TYPE_descriptor_t asn_DEF_BIT_STRING;

asn_struct_print_f BIT_STRING_print;	/* Human-readable output */
asn_constr_check_f BIT_STRING_constraint;


class BIT_STRING : public _OCTET_STRING<&asn_DEF_BIT_STRING> {
public:
  BIT_STRING() : _OCTET_STRING() { }
  BIT_STRING(const BIT_STRING& other) : _OCTET_STRING(other) {
    bitsUnused = other.bitsUnused;
  }
  BIT_STRING(BIT_STRING&& other) noexcept : _OCTET_STRING(std::move(other)) {
    bitsUnused = other.bitsUnused;
    other.bitsUnused = 0;
  }
  BIT_STRING& operator =(const BIT_STRING& other) {
    _OCTET_STRING::operator =(other);
    bitsUnused = other.bitsUnused;
    return *this;
  }
  BIT_STRING& operator =(BIT_STRING&& other) noexcept {
    _OCTET_STRING::operator =(std::move(other));
    bitsUnused = other.bitsUnused;
    other.bitsUnused = 0;
    return *this;
  }
  using _OCTET_STRING::operator =;
  bool operator ==(const BIT_STRING& other) const {
    if (bitsUnused != other.bitsUnused || this->size() != other.size())
      return false;
    size_t size = this->size();
    size_t nonStrictBytesCount = bitsUnused / 8 + ((bitsUnused % 8) ? 1 : 0);
    for (size_t i = 0; i + nonStrictBytesCount < size; ++i) {
      if ((*this)[i] != other[i])
        return false;
    }
    if (!nonStrictBytesCount || nonStrictBytesCount > size)
      return true;
    else {
      uint8_t mask = 0;
      for (int i = 0; i < bitsUnused % 8; ++i)
        mask |= (1 << i);
      mask = ~mask;
      return ((*this)[size - nonStrictBytesCount] & mask) == 
                (other[size - nonStrictBytesCount] & mask);
    }
  }
  bool operator !=(const BIT_STRING& other) const {
    return !(this->operator ==(other));
  }
  virtual ~BIT_STRING() noexcept { }
  void Clear() override { _OCTET_STRING::Clear(); bitsUnused = 0; }
  void SetBitsUnused(const int bits_unused) { bitsUnused = bits_unused; }
  int GetBitsUnused() const { return bitsUnused; }
private:
  int bitsUnused = 0;/* Unused trailing bits in the last octet (0..7) */
};

#endif	/* _BIT_STRING_HPP_ */
