/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_NumericString_HPP_
#define	_NumericString_HPP_

#include <OCTET_STRING.hpp>

extern asn_TYPE_descriptor_t asn_DEF_NumericString;

typedef _OCTET_STRING<&asn_DEF_NumericString, std::string> NumericString;	/* Implemented via OCTET STRING */

asn_constr_check_f NumericString_constraint;

#endif	/* _NumericString_HPP_ */
