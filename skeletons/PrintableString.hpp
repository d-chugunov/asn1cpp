/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_PrintableString_HPP_
#define	_PrintableString_HPP_

#include <OCTET_STRING.hpp>

extern asn_TYPE_descriptor_t asn_DEF_PrintableString;

typedef _OCTET_STRING<&asn_DEF_PrintableString, std::string> PrintableString;  /* Implemented via OCTET STRING */

asn_constr_check_f PrintableString_constraint;

#endif	/* _PrintableString_HPP_ */
