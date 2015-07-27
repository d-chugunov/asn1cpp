/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_IA5String_HPP_
#define	_IA5String_HPP_

#include <OCTET_STRING.hpp>

/*
 * IA5String ASN.1 type definition.
 */
extern asn_TYPE_descriptor_t asn_DEF_IA5String;

typedef _OCTET_STRING<&asn_DEF_IA5String, std::string> IA5String;  /* Implemented via OCTET STRING */

asn_constr_check_f IA5String_constraint;

#endif	/* _IA5String_HPP_ */
