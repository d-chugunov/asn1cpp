/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_ISO646String_HPP_
#define	_ISO646String_HPP_

#include <asn_application.hpp>
#include <VisibleString.hpp>

extern asn_TYPE_descriptor_t asn_DEF_ISO646String;

typedef _VisibleString<&asn_DEF_ISO646String> ISO646String;	/* Implemented using VisibleString*/

#endif	/* _ISO646String_HPP_ */
