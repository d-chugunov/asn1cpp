/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_ENUMERATED_HPP_
#define	_ENUMERATED_HPP_

#include <INTEGER.hpp>

extern asn_TYPE_descriptor_t asn_DEF_ENUMERATED;

typedef _INTEGER<&asn_DEF_ENUMERATED> ENUMERATED; /* Implemented via INTEGER */

#endif	/* _ENUMERATED_HPP_ */
