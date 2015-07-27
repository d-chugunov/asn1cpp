/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE2"
 * 	found in "External+ExternalASN.asn"
 * 	`asn1c -fskeletons-copy -fnative-types`
 */

#include "ExternalASN.h"

static asn_TYPE_member_t asn_MBR_encoding_5[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ExternalASN__encoding, choice.single_ASN1_type),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_ANY,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"single-ASN1-type"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ExternalASN__encoding, choice.octet_aligned),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"octet-aligned"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ExternalASN__encoding, choice.arbitrary),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"arbitrary"
		},
};
static asn_TYPE_tag2member_t asn_MAP_encoding_tag2el_5[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* single-ASN1-type at 31 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* octet-aligned at 32 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* arbitrary at 33 */
};
static asn_CHOICE_specifics_t asn_SPC_encoding_specs_5 = {
	sizeof(struct ExternalASN__encoding),
	offsetof(struct ExternalASN__encoding, _asn_ctx),
	offsetof(struct ExternalASN__encoding, present),
	sizeof(((struct ExternalASN__encoding *)0)->present),
	asn_MAP_encoding_tag2el_5,
	3,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_encoding_5 = {
	"encoding",
	"encoding",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	0,	/* No PER visible constraints */
	asn_MBR_encoding_5,
	3,	/* Elements count */
	&asn_SPC_encoding_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_ExternalASN_1[] = {
	{ ATF_POINTER, 3, offsetof(struct ExternalASN, direct_reference),
		(ASN_TAG_CLASS_UNIVERSAL | (6 << 2)),
		0,
		&asn_DEF_OBJECT_IDENTIFIER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"direct-reference"
		},
	{ ATF_POINTER, 2, offsetof(struct ExternalASN, indirect_reference),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"indirect-reference"
		},
	{ ATF_POINTER, 1, offsetof(struct ExternalASN, data_value_descriptor),
		(ASN_TAG_CLASS_UNIVERSAL | (7 << 2)),
		0,
		&asn_DEF_ObjectDescriptor,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"data-value-descriptor"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ExternalASN, encoding),
		-1 /* Ambiguous tag (CHOICE?) */,
		0,
		&asn_DEF_encoding_5,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"encoding"
		},
};
static ber_tlv_tag_t asn_DEF_ExternalASN_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (8 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_ExternalASN_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 1, 0, 0 }, /* indirect-reference at 28 */
    { (ASN_TAG_CLASS_UNIVERSAL | (6 << 2)), 0, 0, 0 }, /* direct-reference at 27 */
    { (ASN_TAG_CLASS_UNIVERSAL | (7 << 2)), 2, 0, 0 }, /* data-value-descriptor at 29 */
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 3, 0, 0 }, /* single-ASN1-type at 31 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 3, 0, 0 }, /* octet-aligned at 32 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 3, 0, 0 } /* arbitrary at 33 */
};
static asn_SEQUENCE_specifics_t asn_SPC_ExternalASN_specs_1 = {
	sizeof(struct ExternalASN),
	offsetof(struct ExternalASN, _asn_ctx),
	asn_MAP_ExternalASN_tag2el_1,
	6,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_ExternalASN = {
	"ExternalASN",
	"ExternalASN",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_ExternalASN_tags_1,
	sizeof(asn_DEF_ExternalASN_tags_1)
		/sizeof(asn_DEF_ExternalASN_tags_1[0]) - 1, /* 1 */
	asn_DEF_ExternalASN_tags_1,	/* Same as above */
	sizeof(asn_DEF_ExternalASN_tags_1)
		/sizeof(asn_DEF_ExternalASN_tags_1[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_ExternalASN_1,
	4,	/* Elements count */
	&asn_SPC_ExternalASN_specs_1	/* Additional specs */
};

