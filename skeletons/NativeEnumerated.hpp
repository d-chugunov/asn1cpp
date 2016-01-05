/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
/*
 * This type differs from the standard ENUMERATED in that it is modelled using
 * the fixed machine type (long, int, short), so it can hold only values of
 * limited length. There is no type (i.e., NativeEnumerated_t, any integer type
 * will do).
 * This type may be used when integer range is limited by subtype constraints.
 */
#ifndef	_NativeEnumerated_HPP_
#define	_NativeEnumerated_HPP_

#include <NativeInteger.hpp>

extern asn_TYPE_descriptor_t asn_DEF_NativeEnumerated;

typedef _NativeIntegerType _NativeEnumeratedType;
typedef AsnNativePrimitiveType<_NativeEnumeratedType, &asn_DEF_NativeEnumerated> NativeEnumerated;

#endif	/* _NativeEnumerated_HPP_ */
