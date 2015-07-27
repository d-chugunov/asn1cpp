/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SetRecord-ISet-Sets-of-enumerated.asn"
 * 	`asn1c -fnative-types`
 */

#include "SetRecord-ISet-Sets-of-enumerated.h"

static int
Member_4_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	/* Replace with underlying type checker */
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	return td->check_constraints(td, sptr, ctfailcb, app_key);
}

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static void
Member_4_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
	td->free_struct    = asn_DEF_NativeEnumerated.free_struct;
	td->print_struct   = asn_DEF_NativeEnumerated.print_struct;
	td->ber_decoder    = asn_DEF_NativeEnumerated.ber_decoder;
	td->der_encoder    = asn_DEF_NativeEnumerated.der_encoder;
	td->xer_decoder    = asn_DEF_NativeEnumerated.xer_decoder;
	td->xer_encoder    = asn_DEF_NativeEnumerated.xer_encoder;
	td->uper_decoder   = asn_DEF_NativeEnumerated.uper_decoder;
	td->uper_encoder   = asn_DEF_NativeEnumerated.uper_encoder;
	if(!td->per_constraints)
		td->per_constraints = asn_DEF_NativeEnumerated.per_constraints;
	td->elements       = asn_DEF_NativeEnumerated.elements;
	td->elements_count = asn_DEF_NativeEnumerated.elements_count;
     /* td->specifics      = asn_DEF_NativeEnumerated.specifics;	// Defined explicitly */
}

static void
Member_4_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	Member_4_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
Member_4_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	Member_4_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
Member_4_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	Member_4_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
Member_4_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	Member_4_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
Member_4_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	Member_4_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
Member_4_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	Member_4_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static int
Member_9_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	/* Replace with underlying type checker */
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	return td->check_constraints(td, sptr, ctfailcb, app_key);
}

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static void
Member_9_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
	td->free_struct    = asn_DEF_NativeEnumerated.free_struct;
	td->print_struct   = asn_DEF_NativeEnumerated.print_struct;
	td->ber_decoder    = asn_DEF_NativeEnumerated.ber_decoder;
	td->der_encoder    = asn_DEF_NativeEnumerated.der_encoder;
	td->xer_decoder    = asn_DEF_NativeEnumerated.xer_decoder;
	td->xer_encoder    = asn_DEF_NativeEnumerated.xer_encoder;
	td->uper_decoder   = asn_DEF_NativeEnumerated.uper_decoder;
	td->uper_encoder   = asn_DEF_NativeEnumerated.uper_encoder;
	if(!td->per_constraints)
		td->per_constraints = asn_DEF_NativeEnumerated.per_constraints;
	td->elements       = asn_DEF_NativeEnumerated.elements;
	td->elements_count = asn_DEF_NativeEnumerated.elements_count;
     /* td->specifics      = asn_DEF_NativeEnumerated.specifics;	// Defined explicitly */
}

static void
Member_9_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	Member_9_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
Member_9_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	Member_9_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
Member_9_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	Member_9_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
Member_9_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	Member_9_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
Member_9_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	Member_9_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
Member_9_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	Member_9_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_INTEGER_enum_map_t asn_MAP_Member_value2enum_4[] = {
	{ 1,	6,	"value1" },
	{ 2,	6,	"value2" },
	{ 3,	6,	"value3" }
};
static unsigned int asn_MAP_Member_enum2value_4[] = {
	0,	/* value1(1) */
	1,	/* value2(2) */
	2	/* value3(3) */
};
static asn_INTEGER_specifics_t asn_SPC_Member_specs_4 = {
	asn_MAP_Member_value2enum_4,	/* "tag" => N; sorted by tag */
	asn_MAP_Member_enum2value_4,	/* N => "tag"; sorted by N */
	3,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_Member_tags_4[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_Member_4 = {
	"ENUMERATED",
	"ENUMERATED",
	Member_4_free,
	Member_4_print,
	Member_4_constraint,
	Member_4_decode_ber,
	Member_4_encode_der,
	Member_4_decode_xer,
	Member_4_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_Member_tags_4,
	sizeof(asn_DEF_Member_tags_4)
		/sizeof(asn_DEF_Member_tags_4[0]), /* 1 */
	asn_DEF_Member_tags_4,	/* Same as above */
	sizeof(asn_DEF_Member_tags_4)
		/sizeof(asn_DEF_Member_tags_4[0]), /* 1 */
	0,	/* No PER visible constraints */
	0, 0,	/* Defined elsewhere */
	&asn_SPC_Member_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_field3_3[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (10 << 2)),
		0,
		&asn_DEF_Member_4,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_field3_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (17 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_field3_specs_3 = {
	sizeof(struct SetRecord_ISet_Sets_of_enumerated__set__field3),
	offsetof(struct SetRecord_ISet_Sets_of_enumerated__set__field3, _asn_ctx),
	1,	/* XER encoding is XMLValueList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_field3_3 = {
	"field3",
	"field3",
	SET_OF_free,
	SET_OF_print,
	SET_OF_constraint,
	SET_OF_decode_ber,
	SET_OF_encode_der,
	SET_OF_decode_xer,
	SET_OF_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_field3_tags_3,
	sizeof(asn_DEF_field3_tags_3)
		/sizeof(asn_DEF_field3_tags_3[0]) - 1, /* 1 */
	asn_DEF_field3_tags_3,	/* Same as above */
	sizeof(asn_DEF_field3_tags_3)
		/sizeof(asn_DEF_field3_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_field3_3,
	1,	/* Single element */
	&asn_SPC_field3_specs_3	/* Additional specs */
};

static asn_INTEGER_enum_map_t asn_MAP_Member_value2enum_9[] = {
	{ 1,	6,	"value1" },
	{ 2,	6,	"value2" },
	{ 3,	6,	"value3" }
};
static unsigned int asn_MAP_Member_enum2value_9[] = {
	0,	/* value1(1) */
	1,	/* value2(2) */
	2	/* value3(3) */
};
static asn_INTEGER_specifics_t asn_SPC_Member_specs_9 = {
	asn_MAP_Member_value2enum_9,	/* "tag" => N; sorted by tag */
	asn_MAP_Member_enum2value_9,	/* N => "tag"; sorted by N */
	3,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_Member_tags_9[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_Member_9 = {
	"ENUMERATED",
	"ENUMERATED",
	Member_9_free,
	Member_9_print,
	Member_9_constraint,
	Member_9_decode_ber,
	Member_9_encode_der,
	Member_9_decode_xer,
	Member_9_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_Member_tags_9,
	sizeof(asn_DEF_Member_tags_9)
		/sizeof(asn_DEF_Member_tags_9[0]), /* 1 */
	asn_DEF_Member_tags_9,	/* Same as above */
	sizeof(asn_DEF_Member_tags_9)
		/sizeof(asn_DEF_Member_tags_9[0]), /* 1 */
	0,	/* No PER visible constraints */
	0, 0,	/* Defined elsewhere */
	&asn_SPC_Member_specs_9	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_field4_8[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (10 << 2)),
		0,
		&asn_DEF_Member_9,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_field4_tags_8[] = {
	(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (17 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_field4_specs_8 = {
	sizeof(struct SetRecord_ISet_Sets_of_enumerated__set__field4),
	offsetof(struct SetRecord_ISet_Sets_of_enumerated__set__field4, _asn_ctx),
	1,	/* XER encoding is XMLValueList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_field4_8 = {
	"field4",
	"field4",
	SET_OF_free,
	SET_OF_print,
	SET_OF_constraint,
	SET_OF_decode_ber,
	SET_OF_encode_der,
	SET_OF_decode_xer,
	SET_OF_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_field4_tags_8,
	sizeof(asn_DEF_field4_tags_8)
		/sizeof(asn_DEF_field4_tags_8[0]) - 1, /* 1 */
	asn_DEF_field4_tags_8,	/* Same as above */
	sizeof(asn_DEF_field4_tags_8)
		/sizeof(asn_DEF_field4_tags_8[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_field4_8,
	1,	/* Single element */
	&asn_SPC_field4_specs_8	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_set_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SetRecord_ISet_Sets_of_enumerated__set, field3),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		0,
		&asn_DEF_field3_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"field3"
		},
	{ ATF_POINTER, 1, offsetof(struct SetRecord_ISet_Sets_of_enumerated__set, field4),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		0,
		&asn_DEF_field4_8,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"field4"
		},
};
static ber_tlv_tag_t asn_DEF_set_tags_2[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (17 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_set_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 0, 0, 0 }, /* field3 at 15 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 1, 0, 0 } /* field4 at 21 */
};
static uint8_t asn_MAP_set_mmap_2[(2 + (8 * sizeof(unsigned int)) - 1) / 8] = {
	(1 << 7) | (0 << 6)
};
static asn_SET_specifics_t asn_SPC_set_specs_2 = {
	sizeof(struct SetRecord_ISet_Sets_of_enumerated__set),
	offsetof(struct SetRecord_ISet_Sets_of_enumerated__set, _asn_ctx),
	offsetof(struct SetRecord_ISet_Sets_of_enumerated__set, _presence_map),
	asn_MAP_set_tag2el_2,
	2,	/* Count of tags in the map */
	asn_MAP_set_tag2el_2,	/* Same as above */
	2,	/* Count of tags in the CXER map */
	0,	/* Whether extensible */
	(unsigned int *)asn_MAP_set_mmap_2	/* Mandatory elements map */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_set_2 = {
	"set",
	"set",
	SET_free,
	SET_print,
	SET_constraint,
	SET_decode_ber,
	SET_encode_der,
	SET_decode_xer,
	SET_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_set_tags_2,
	sizeof(asn_DEF_set_tags_2)
		/sizeof(asn_DEF_set_tags_2[0]), /* 1 */
	asn_DEF_set_tags_2,	/* Same as above */
	sizeof(asn_DEF_set_tags_2)
		/sizeof(asn_DEF_set_tags_2[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_set_2,
	2,	/* Elements count */
	&asn_SPC_set_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SetRecord_ISet_Sets_of_enumerated_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SetRecord_ISet_Sets_of_enumerated, set),
		(ASN_TAG_CLASS_UNIVERSAL | (17 << 2)),
		0,
		&asn_DEF_set_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"set"
		},
};
static ber_tlv_tag_t asn_DEF_SetRecord_ISet_Sets_of_enumerated_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (17 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SetRecord_ISet_Sets_of_enumerated_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (17 << 2)), 0, 0, 0 } /* set at 15 */
};
static uint8_t asn_MAP_SetRecord_ISet_Sets_of_enumerated_mmap_1[(1 + (8 * sizeof(unsigned int)) - 1) / 8] = {
	(1 << 7)
};
static asn_SET_specifics_t asn_SPC_SetRecord_ISet_Sets_of_enumerated_specs_1 = {
	sizeof(struct SetRecord_ISet_Sets_of_enumerated),
	offsetof(struct SetRecord_ISet_Sets_of_enumerated, _asn_ctx),
	offsetof(struct SetRecord_ISet_Sets_of_enumerated, _presence_map),
	asn_MAP_SetRecord_ISet_Sets_of_enumerated_tag2el_1,
	1,	/* Count of tags in the map */
	asn_MAP_SetRecord_ISet_Sets_of_enumerated_tag2el_1,	/* Same as above */
	1,	/* Count of tags in the CXER map */
	0,	/* Whether extensible */
	(unsigned int *)asn_MAP_SetRecord_ISet_Sets_of_enumerated_mmap_1	/* Mandatory elements map */
};
asn_TYPE_descriptor_t asn_DEF_SetRecord_ISet_Sets_of_enumerated = {
	"SetRecord-ISet-Sets-of-enumerated",
	"SetRecord-ISet-Sets-of-enumerated",
	SET_free,
	SET_print,
	SET_constraint,
	SET_decode_ber,
	SET_encode_der,
	SET_decode_xer,
	SET_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SetRecord_ISet_Sets_of_enumerated_tags_1,
	sizeof(asn_DEF_SetRecord_ISet_Sets_of_enumerated_tags_1)
		/sizeof(asn_DEF_SetRecord_ISet_Sets_of_enumerated_tags_1[0]), /* 1 */
	asn_DEF_SetRecord_ISet_Sets_of_enumerated_tags_1,	/* Same as above */
	sizeof(asn_DEF_SetRecord_ISet_Sets_of_enumerated_tags_1)
		/sizeof(asn_DEF_SetRecord_ISet_Sets_of_enumerated_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SetRecord_ISet_Sets_of_enumerated_1,
	1,	/* Elements count */
	&asn_SPC_SetRecord_ISet_Sets_of_enumerated_specs_1	/* Additional specs */
};
