/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_VideotexString_HPP_
#define	_VideotexString_HPP_

#include <OCTET_STRING.hpp>

extern asn_TYPE_descriptor_t asn_DEF_VideotexString;

typedef _OCTET_STRING<&asn_DEF_VideotexString, std::string> VideotexString;  /* Implemented via OCTET STRING */

#endif	/* _VideotexString_HPP_ */
