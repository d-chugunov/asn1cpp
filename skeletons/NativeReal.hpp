/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
/*
 * This type differs from the standard REAL in that it is modelled using
 * the fixed machine type (double), so it can hold only values of
 * limited precision. There is no explicit type (i.e., NativeReal_t).
 * Use of this type is normally enabled by -fnative-types.
 */
#ifndef	NativeReal_HPP
#define	NativeReal_HPP

#include <asn_application.hpp>

extern asn_TYPE_descriptor_t asn_DEF_NativeReal;

asn_struct_print_f NativeReal_print;
ber_type_decoder_f NativeReal_decode_ber;
der_type_encoder_f NativeReal_encode_der;

#include <AsnNativePrimitiveType.hpp>

//double is because asn_DEF_NativeReal_decode_ber uses double
typedef double _NativeRealType;
typedef AsnNativePrimitiveType<_NativeRealType, &asn_DEF_NativeReal> NativeReal;

#endif	/* NativeReal_HPP */
