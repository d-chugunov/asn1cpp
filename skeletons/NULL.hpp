/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	NULL_HPP
#define	NULL_HPP

#include <asn_application.hpp>

extern asn_TYPE_descriptor_t asn_DEF_NULL;

asn_struct_print_f NULL_print;
der_type_encoder_f NULL_encode_der;

#include <AsnNativePrimitiveType.hpp>

/*
 * The value of the NULL type is meaningless: see BOOLEAN if you want to
 * carry true/false semantics.
 */
typedef int _NULL_tType;
typedef AsnNativePrimitiveType<_NULL_tType, &asn_DEF_NULL, 2> NULL_t;

#endif	/* NULL_HPP */
