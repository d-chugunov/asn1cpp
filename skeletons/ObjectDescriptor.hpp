/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_ObjectDescriptor_HPP_
#define	_ObjectDescriptor_HPP_

#include <GraphicString.hpp>

extern asn_TYPE_descriptor_t asn_DEF_ObjectDescriptor;

typedef _GraphicString<&asn_DEF_ObjectDescriptor> ObjectDescriptor;  /* Implemented via GraphicString */

#endif	/* _ObjectDescriptor_HPP_ */
