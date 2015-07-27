/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */

#include "asn_internal.hpp"
#include "constraints.hpp"

int
asn_generic_no_constraint(asn_TYPE_descriptor_t *type_descriptor,
	const void *struct_ptr, asn_app_constraint_failed_f *cb, void *key) {

	(void)type_descriptor;	/* Unused argument */
	(void)struct_ptr;	/* Unused argument */
	(void)cb;	/* Unused argument */
	(void)key;	/* Unused argument */

	/* Nothing to check */
	return 0;
}

int
asn_generic_unknown_constraint(asn_TYPE_descriptor_t *type_descriptor,
	const void *struct_ptr, asn_app_constraint_failed_f *cb, void *key) {

	(void)type_descriptor;	/* Unused argument */
	(void)struct_ptr;	/* Unused argument */
	(void)cb;	/* Unused argument */
	(void)key;	/* Unused argument */

	/* Unknown how to check */
	return 0;
}

