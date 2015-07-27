/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_GeneralString_HPP_
#define	_GeneralString_HPP_

#include <OCTET_STRING.hpp>


extern asn_TYPE_descriptor_t asn_DEF_GeneralString;

typedef _OCTET_STRING<&asn_DEF_GeneralString, std::string> GeneralString;	/* Implemented via OCTET STRING */


#endif	/* _GeneralString_HPP_ */
