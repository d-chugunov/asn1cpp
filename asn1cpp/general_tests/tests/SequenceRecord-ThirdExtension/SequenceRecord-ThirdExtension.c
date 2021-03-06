/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "ForTest.as_n"
 */

#include "SequenceRecord-ThirdExtension.h"

static asn_TYPE_member_t asn_MBR_d_5[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct d, e),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"e"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct d, f),
		(ASN_TAG_CLASS_UNIVERSAL | (22 << 2)),
		0,
		&asn_DEF_IA5String,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"f"
		},
	{ ATF_POINTER, 3, offsetof(struct d, g),
		(ASN_TAG_CLASS_UNIVERSAL | (1 << 2)),
		0,
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"g"
		},
	{ ATF_POINTER, 2, offsetof(struct d, h),
		(ASN_TAG_CLASS_UNIVERSAL | (30 << 2)),
		0,
		&asn_DEF_BMPString,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"h"
		},
	{ ATF_POINTER, 1, offsetof(struct d, y),
		(ASN_TAG_CLASS_UNIVERSAL | (9 << 2)),
		0,
		&asn_DEF_NativeReal,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"y"
		},
};
static ber_tlv_tag_t asn_DEF_d_tags_5[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_d_tag2el_5[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (1 << 2)), 2, 0, 0 }, /* g at 15 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 0 }, /* e at 13 */
    { (ASN_TAG_CLASS_UNIVERSAL | (9 << 2)), 4, 0, 0 }, /* y at 17 */
    { (ASN_TAG_CLASS_UNIVERSAL | (22 << 2)), 1, 0, 0 }, /* f at 19 */
    { (ASN_TAG_CLASS_UNIVERSAL | (30 << 2)), 3, 0, 0 } /* h at 16 */
};
static asn_SEQUENCE_specifics_t asn_SPC_d_specs_5 = {
	sizeof(struct d),
	offsetof(struct d, _asn_ctx),
	asn_MAP_d_tag2el_5,
	5,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	1,	/* Start extensions */
	6	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_d_5 = {
	"d",
	"d",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_d_tags_5,
	sizeof(asn_DEF_d_tags_5)
		/sizeof(asn_DEF_d_tags_5[0]), /* 1 */
	asn_DEF_d_tags_5,	/* Same as above */
	sizeof(asn_DEF_d_tags_5)
		/sizeof(asn_DEF_d_tags_5[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_d_5,
	5,	/* Elements count */
	&asn_SPC_d_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SequenceRecord_ThirdExtension_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SequenceRecord_ThirdExtension, a),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"a"
		},
	{ ATF_POINTER, 3, offsetof(struct SequenceRecord_ThirdExtension, b),
		(ASN_TAG_CLASS_UNIVERSAL | (1 << 2)),
		0,
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"b"
		},
	{ ATF_POINTER, 2, offsetof(struct SequenceRecord_ThirdExtension, c),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"c"
		},
	{ ATF_POINTER, 1, offsetof(struct SequenceRecord_ThirdExtension, d),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_d_5,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"d"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SequenceRecord_ThirdExtension, z),
		(ASN_TAG_CLASS_UNIVERSAL | (9 << 2)),
		0,
		&asn_DEF_NativeReal,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"z"
		},
};
static ber_tlv_tag_t asn_DEF_SequenceRecord_ThirdExtension_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SequenceRecord_ThirdExtension_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (1 << 2)), 1, 0, 0 }, /* b at 10 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 1 }, /* a at 9 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 2, -1, 0 }, /* c at 11 */
    { (ASN_TAG_CLASS_UNIVERSAL | (9 << 2)), 4, 0, 0 }, /* z at 21 */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 3, 0, 0 } /* d at 13 */
};
static asn_SEQUENCE_specifics_t asn_SPC_SequenceRecord_ThirdExtension_specs_1 = {
	sizeof(struct SequenceRecord_ThirdExtension),
	offsetof(struct SequenceRecord_ThirdExtension, _asn_ctx),
	asn_MAP_SequenceRecord_ThirdExtension_tag2el_1,
	5,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SequenceRecord_ThirdExtension = {
	"SequenceRecord-ThirdExtension",
	"SequenceRecord-ThirdExtension",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SequenceRecord_ThirdExtension_tags_1,
	sizeof(asn_DEF_SequenceRecord_ThirdExtension_tags_1)
		/sizeof(asn_DEF_SequenceRecord_ThirdExtension_tags_1[0]), /* 1 */
	asn_DEF_SequenceRecord_ThirdExtension_tags_1,	/* Same as above */
	sizeof(asn_DEF_SequenceRecord_ThirdExtension_tags_1)
		/sizeof(asn_DEF_SequenceRecord_ThirdExtension_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SequenceRecord_ThirdExtension_1,
	5,	/* Elements count */
	&asn_SPC_SequenceRecord_ThirdExtension_specs_1	/* Additional specs */
};

