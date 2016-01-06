/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <constr_TYPE.hpp>
#include <errno.h>

/*
 * Version of the ASN.1 infrastructure shipped with compiler.
 */
int get_asn1cpp_environment_version() { return ASN1CPP_ENVIRONMENT_VERSION; }

/*
 * Return the outmost tag of the type.
 */
ber_tlv_tag_t
asn_TYPE_outmost_tag(const asn_TYPE_descriptor_t *type_descriptor,
		const void *struct_ptr, int tag_mode, ber_tlv_tag_t tag) {

	if(tag_mode)
		return tag;

	if(type_descriptor->tags_count)
		return type_descriptor->tags[0];

	return type_descriptor->outmost_tag(type_descriptor, struct_ptr, 0, 0);
}

/*
 * Some compilers do not support variable args macros.
 * This function is a replacement of ASN_DEBUG() macro.
 */
void ASN_DEBUG_f(const char *fmt, ...);
void ASN_DEBUG_f(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}
