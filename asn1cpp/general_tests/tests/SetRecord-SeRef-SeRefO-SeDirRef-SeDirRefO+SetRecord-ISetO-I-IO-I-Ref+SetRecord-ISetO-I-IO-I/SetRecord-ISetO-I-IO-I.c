/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SetRecord-SeRef-SeRefO-SeDirRef-SeDirRefO+SetRecord-ISetO-I-IO-I-Ref+SetRecord-ISetO-I-IO-I.asn"
 */

#include "SetRecord-ISetO-I-IO-I.h"

static asn_TYPE_member_t asn_MBR_set_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct set, type),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"type"
		},
	{ ATF_POINTER, 1, offsetof(struct set, type2),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"type2"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct set, type3),
		(ASN_TAG_CLASS_CONTEXT | (12 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"type3"
		},
};
static ber_tlv_tag_t asn_DEF_set_tags_2[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (17 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_set_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 0, 0, 0 }, /* type at 19 */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 1, 0, 0 }, /* type2 at 20 */
    { (ASN_TAG_CLASS_CONTEXT | (12 << 2)), 2, 0, 0 } /* type3 at 22 */
};
static uint8_t asn_MAP_set_mmap_2[(3 + (8 * sizeof(unsigned int)) - 1) / 8] = {
	(1 << 7) | (0 << 6) | (1 << 5)
};
static asn_SET_specifics_t asn_SPC_set_specs_2 = {
	sizeof(struct set),
	offsetof(struct set, _asn_ctx),
	offsetof(struct set, _presence_map),
	asn_MAP_set_tag2el_2,
	3,	/* Count of tags in the map */
	asn_MAP_set_tag2el_2,	/* Same as above */
	3,	/* Count of tags in the CXER map */
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
	3,	/* Elements count */
	&asn_SPC_set_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SetRecord_ISetO_I_IO_I_1[] = {
	{ ATF_POINTER, 1, offsetof(struct SetRecord_ISetO_I_IO_I, set),
		(ASN_TAG_CLASS_UNIVERSAL | (17 << 2)),
		0,
		&asn_DEF_set_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"set"
		},
};
static ber_tlv_tag_t asn_DEF_SetRecord_ISetO_I_IO_I_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (17 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SetRecord_ISetO_I_IO_I_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (17 << 2)), 0, 0, 0 } /* set at 19 */
};
static uint8_t asn_MAP_SetRecord_ISetO_I_IO_I_mmap_1[(1 + (8 * sizeof(unsigned int)) - 1) / 8] = {
	(0 << 7)
};
static asn_SET_specifics_t asn_SPC_SetRecord_ISetO_I_IO_I_specs_1 = {
	sizeof(struct SetRecord_ISetO_I_IO_I),
	offsetof(struct SetRecord_ISetO_I_IO_I, _asn_ctx),
	offsetof(struct SetRecord_ISetO_I_IO_I, _presence_map),
	asn_MAP_SetRecord_ISetO_I_IO_I_tag2el_1,
	1,	/* Count of tags in the map */
	asn_MAP_SetRecord_ISetO_I_IO_I_tag2el_1,	/* Same as above */
	1,	/* Count of tags in the CXER map */
	0,	/* Whether extensible */
	(unsigned int *)asn_MAP_SetRecord_ISetO_I_IO_I_mmap_1	/* Mandatory elements map */
};
asn_TYPE_descriptor_t asn_DEF_SetRecord_ISetO_I_IO_I = {
	"SetRecord-ISetO-I-IO-I",
	"SetRecord-ISetO-I-IO-I",
	SET_free,
	SET_print,
	SET_constraint,
	SET_decode_ber,
	SET_encode_der,
	SET_decode_xer,
	SET_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SetRecord_ISetO_I_IO_I_tags_1,
	sizeof(asn_DEF_SetRecord_ISetO_I_IO_I_tags_1)
		/sizeof(asn_DEF_SetRecord_ISetO_I_IO_I_tags_1[0]), /* 1 */
	asn_DEF_SetRecord_ISetO_I_IO_I_tags_1,	/* Same as above */
	sizeof(asn_DEF_SetRecord_ISetO_I_IO_I_tags_1)
		/sizeof(asn_DEF_SetRecord_ISetO_I_IO_I_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SetRecord_ISetO_I_IO_I_1,
	1,	/* Elements count */
	&asn_SPC_SetRecord_ISetO_I_IO_I_specs_1	/* Additional specs */
};

