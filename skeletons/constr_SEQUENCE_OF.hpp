/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_CONSTR_SEQUENCE_OF_HPP_
#define	_CONSTR_SEQUENCE_OF_HPP_

#include <asn_application.hpp>
#include <constr_SET_OF.hpp>		/* Implemented using SET OF */

/*
 * A set specialized functions dealing with the SEQUENCE OF type.
 * Generally implemented using SET OF.
 */
#define	SEQUENCE_OF_print	SET_OF_print
#define	SEQUENCE_OF_constraint	SET_OF_constraint
#define	SEQUENCE_OF_decode_ber	SET_OF_decode_ber
#define	SEQUENCE_OF_decode_xer	SET_OF_decode_xer
#define	SEQUENCE_OF_decode_uper	SET_OF_decode_uper
der_type_encoder_f SEQUENCE_OF_encode_der;

#endif	/* _CONSTR_SET_OF_HPP_ */
