/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_ASN1_CONSTRAINTS_VALIDATOR_HPP_
#define	_ASN1_CONSTRAINTS_VALIDATOR_HPP_

#include <asn_system.hpp>		/* Platform-dependent types */

struct asn_TYPE_descriptor_s;		/* Forward declaration */

/*
 * Generic type for constraint checking callback,
 * associated with every type descriptor.
 */
typedef int (asn_constr_check_f)(
	struct asn_TYPE_descriptor_s *type_descriptor,
	const void *struct_ptr,
	asn_app_constraint_failed_f *optional_callback,	/* Log the error */
	void *optional_app_key		/* Opaque key passed to a callback */
	);

/*******************************
 * INTERNALLY USEFUL FUNCTIONS *
 *******************************/

asn_constr_check_f asn_generic_no_constraint;	/* No constraint whatsoever */
asn_constr_check_f asn_generic_unknown_constraint; /* Not fully supported */

/*
 * Invoke the callback with a complete error message.
 */
#define	_ASN_CTFAIL	if(ctfailcb) ctfailcb

#endif	/* _ASN1_CONSTRAINTS_VALIDATOR_HPP_ */
