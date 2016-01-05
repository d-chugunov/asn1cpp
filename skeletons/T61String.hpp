/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_T61String_HPP_
#define	_T61String_HPP_

#include <OCTET_STRING.hpp>

extern asn_TYPE_descriptor_t asn_DEF_T61String;

typedef _OCTET_STRING<&asn_DEF_T61String, std::string> T61String;	/* Implemented via OCTET STRING */

#endif	/* _T61String_HPP_ */
