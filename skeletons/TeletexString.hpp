/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_TeletexString_HPP_
#define	_TeletexString_HPP_

#include <OCTET_STRING.hpp>

extern asn_TYPE_descriptor_t asn_DEF_TeletexString;

typedef _OCTET_STRING<&asn_DEF_TeletexString, std::string> TeletexString;	/* Implemented via OCTET STRING */

#endif	/* _TeletexString_HPP_ */
