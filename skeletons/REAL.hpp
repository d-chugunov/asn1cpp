/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	ASN_TYPE_REAL_HPP
#define	ASN_TYPE_REAL_HPP

#include <asn_application.hpp>
#include <asn_codecs_prim.hpp>

extern asn_TYPE_descriptor_t asn_DEF_REAL;

asn_struct_print_f REAL_print;

class REAL : public AsnPrimitiveType<&asn_DEF_REAL> {
public:
  REAL() : AsnPrimitiveType<&asn_DEF_REAL>() { }
  REAL(const REAL& other) : 
              AsnPrimitiveType<&asn_DEF_REAL>(other) { }
  REAL(REAL&& other) noexcept : 
              AsnPrimitiveType<&asn_DEF_REAL>(std::move(other)) { }
  REAL& operator =(const REAL& other) {
    AsnPrimitiveType<&asn_DEF_REAL>::operator =(other);
    return *this;
  }
  REAL& operator =(REAL&& other) noexcept {
    AsnPrimitiveType<&asn_DEF_REAL>::operator =(std::move(other));
    return *this;
  }
  using AsnPrimitiveType::operator =;
  virtual ~REAL() noexcept { }
  /*
   * Convert between native double type and REAL representation (DER).
   * RETURN VALUES:
   *  true: Value converted successfully
   *  false: An error occured while converting the value: invalid format.
   */
  static bool ToDouble(const uint8_t* buf, size_t size, double& d);
  static bool ToDouble(const std::vector<uint8_t>& buf, double& d) { return ToDouble(buf.data(), buf.size(), d); }
  bool ToDouble(double& d) { return ToDouble(this->data(), this->size(), d); }
  bool FromDouble(double d);
};

ssize_t REAL__dump(double d, int canonical, asn_app_consume_bytes_f *cb, void *app_key);

#endif	/* ASN_TYPE_REAL_HPP */
