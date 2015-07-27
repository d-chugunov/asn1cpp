/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_UniversalString_HPP_
#define	_UniversalString_HPP_

#include <OCTET_STRING.hpp>

extern asn_TYPE_descriptor_t asn_DEF_UniversalString;

typedef _OCTET_STRING<&asn_DEF_UniversalString> UniversalString;  /* Implemented via OCTET STRING */

asn_struct_print_f UniversalString_print;	/* Human-readable output */

#endif	/* _UniversalString_HPP_ */
