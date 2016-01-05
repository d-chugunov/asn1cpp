/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_GeneralizedTime_HPP_
#define	_GeneralizedTime_HPP_

#include <OCTET_STRING.hpp>

extern asn_TYPE_descriptor_t asn_DEF_GeneralizedTime;

asn_struct_print_f GeneralizedTime_print;
asn_constr_check_f GeneralizedTime_constraint;
der_type_encoder_f GeneralizedTime_encode_der;

class GeneralizedTime : public _OCTET_STRING<&asn_DEF_GeneralizedTime> {
public:
  GeneralizedTime() : _OCTET_STRING() { }
  GeneralizedTime(const GeneralizedTime& other) : 
              _OCTET_STRING(other) { }
  GeneralizedTime(GeneralizedTime&& other) noexcept : 
              _OCTET_STRING(std::move(other)) { }
  GeneralizedTime& operator =(const GeneralizedTime& other) {
    _OCTET_STRING::operator =(other);
    return *this;
  }
  GeneralizedTime& operator =(GeneralizedTime&& other) noexcept {
    _OCTET_STRING::operator =(std::move(other));
    return *this;
  }
  using _OCTET_STRING::operator =;
  virtual ~GeneralizedTime() noexcept { }
  /*
   * Convert a GeneralizedTime structure into time_t
   * and optionally into struct tm.
   * If as_gmt is given, the resulting _optional_tm4fill will have a GMT zone,
   * instead of default local one.
   * On error returns -1 and errno set to EINVAL
   */
  time_t ToTime(struct tm *_optional_tm4fill = 0, bool as_gmt = false) const;
  /* A version of the above function also returning the fractions of seconds */
  time_t ToTimeFrac(int *frac_value = 0, int *frac_digits = 0,	/* (value / (10 ^ digits)) */
  	struct tm *_optional_tm4fill = 0, bool as_gmt = false) const;
  /*
   * Another version returning fractions with defined precision
   * For example, parsing of the time ending with ".1" seconds
   * with frac_digits=3 (msec) would yield frac_value = 100.
   */
  time_t ToTimePrec(int *frac_value = 0, int frac_digits = 0,
  	struct tm *_optional_tm4fill = 0, bool as_gmt = false) const;
  /*
   * Convert a struct tm into GeneralizedTime.
   * If force_gmt is given, the resulting GeneralizedTime will be forced
   * into a GMT time zone (encoding ends with a "Z").
   * On error, this function returns false and sets errno.
   */
  bool FromTime(const struct tm& tm, bool force_gmt = false);
  bool FromTimeFrac(const struct tm& tm, int frac_value, 
                    int frac_digits, bool force_gmt = false);
};

#endif	/* _GeneralizedTime_HPP_ */
