/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_BMPString_HPP_
#define	_BMPString_HPP_

#include <OCTET_STRING.hpp>

extern asn_TYPE_descriptor_t asn_DEF_BMPString;

typedef _OCTET_STRING<&asn_DEF_BMPString> BMPString;  /* Implemented via OCTET STRING */

asn_struct_print_f BMPString_print;	/* Human-readable output */

#endif	/* _BMPString_HPP_ */
