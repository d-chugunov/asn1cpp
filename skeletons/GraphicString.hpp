/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_GraphicString_HPP_
#define	_GraphicString_HPP_

#include <OCTET_STRING.hpp>

template <asn_TYPE_descriptor_t* typeDescriptorPtr>
using _GraphicString = _OCTET_STRING<typeDescriptorPtr, std::string>;

extern asn_TYPE_descriptor_t asn_DEF_GraphicString;

typedef _GraphicString<&asn_DEF_GraphicString> GraphicString;	/* Implemented via OCTET STRING */

#endif	/* _GraphicString_HPP_ */
