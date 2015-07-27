/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_UTCTime_HPP_
#define	_UTCTime_HPP_

#include <OCTET_STRING.hpp>


extern asn_TYPE_descriptor_t asn_DEF_UTCTime;

class UTCTime : public _OCTET_STRING<&asn_DEF_UTCTime> {
public:
  UTCTime() : _OCTET_STRING() { }
  UTCTime(const UTCTime& other) : 
              _OCTET_STRING(other) { }
  UTCTime(UTCTime&& other) noexcept : 
              _OCTET_STRING(std::move(other)) { }
  UTCTime& operator =(const UTCTime& other) {
    _OCTET_STRING::operator =(other);
    return *this;
  }
  UTCTime& operator =(UTCTime&& other) noexcept {
    _OCTET_STRING::operator =(std::move(other));
    return *this;
  }
  using _OCTET_STRING::operator =;
  virtual ~UTCTime() noexcept { }
  /* See GeneralizedTime::ToTime */
  time_t ToTime(struct tm *_optional_tm4fill = 0, bool as_gmt = false) const;
  /* See GeneralizedTime::FromTime */
  bool FromTime(const struct tm& tm, bool force_gmt = false);
};

asn_struct_print_f UTCTime_print;
asn_constr_check_f UTCTime_constraint;

#endif	/* _UTCTime_HPP_ */
