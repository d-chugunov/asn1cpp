/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_UTF8String_HPP_
#define	_UTF8String_HPP_

#include <OCTET_STRING.hpp>

extern asn_TYPE_descriptor_t asn_DEF_UTF8String;

/* Implemented via OCTET STRING */
class UTF8String : public _OCTET_STRING<&asn_DEF_UTF8String, std::string> {
public:
  UTF8String() : _OCTET_STRING() { }
  UTF8String(const UTF8String& other) : 
              _OCTET_STRING(other) { }
  UTF8String(UTF8String&& other) noexcept : 
              _OCTET_STRING(std::move(other)) { }
  UTF8String& operator =(const UTF8String& other) {
    _OCTET_STRING::operator =(other);
    return *this;
  }
  UTF8String& operator =(UTF8String&& other) noexcept {
    _OCTET_STRING::operator =(std::move(other));
    return *this;
  }
  using _OCTET_STRING::operator =;
  virtual ~UTF8String() noexcept { }
  /*
   * Returns length of the given UTF-8 string in characters,
   * or a negative error code:
   * -1:	UTF-8 sequence truncated 
   * -2:	Illegal UTF-8 sequence start
   * -3:	Continuation expectation failed
   * -4:	Not minimal length encoding
   * -5:	Invalid arguments
   */
  ssize_t GetLength() const {
    return __process(0);
  }
  static ssize_t GetLength(const UTF8String* st);
  /*
   * Convert the UTF-8 string into a sequence of wide characters.
   * Returns the number of characters necessary.
   * In case of conversion error, 0 is returned.
   */
  size_t ToWCS(std::vector<uint32_t>& dst) const {
    ssize_t ret = __process(&dst);
		return (ret < 0) ? 0 : ret;
  }
private:
  ssize_t __process(std::vector<uint32_t> *dst) const;
};

asn_struct_print_f UTF8String_print;
asn_constr_check_f UTF8String_constraint;

#endif	/* _UTF8String_HPP_ */
