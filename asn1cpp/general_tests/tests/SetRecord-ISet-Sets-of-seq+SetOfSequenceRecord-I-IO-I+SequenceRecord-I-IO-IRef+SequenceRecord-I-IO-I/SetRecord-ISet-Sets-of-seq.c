/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "Simplified.asn"
 */

#include "SetRecord-ISet-Sets-of-seq.h"

static asn_TYPE_member_t asn_MBR_field3_5[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_SequenceRecord_I_IO_I,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_field3_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (17 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_field3_specs_5 = {
	sizeof(struct field3),
	offsetof(struct field3, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_field3_5 = {
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
	asn_DEF_field3_tags_5,
	sizeof(asn_DEF_field3_tags_5)
		/sizeof(asn_DEF_field3_tags_5[0]) - 1, /* 1 */
	asn_DEF_field3_tags_5,	/* Same as above */
	sizeof(asn_DEF_field3_tags_5)
		/sizeof(asn_DEF_field3_tags_5[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_field3_5,
	1,	/* Single element */
	&asn_SPC_field3_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_field4_7[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_SequenceRecord_I_IO_I,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_field4_tags_7[] = {
	(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (17 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_field4_specs_7 = {
	sizeof(struct field4),
	offsetof(struct field4, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_field4_7 = {
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
	asn_DEF_field4_tags_7,
	sizeof(asn_DEF_field4_tags_7)
		/sizeof(asn_DEF_field4_tags_7[0]) - 1, /* 1 */
	asn_DEF_field4_tags_7,	/* Same as above */
	sizeof(asn_DEF_field4_tags_7)
		/sizeof(asn_DEF_field4_tags_7[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_field4_7,
	1,	/* Single element */
	&asn_SPC_field4_specs_7	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_set_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct set, field1),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SetOfSequenceRecord_I_IO_I,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"field1"
		},
	{ ATF_POINTER, 1, offsetof(struct set, field2),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SetOfSequenceRecord_I_IO_I,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"field2"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct set, field3),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		0,
		&asn_DEF_field3_5,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"field3"
		},
	{ ATF_POINTER, 1, offsetof(struct set, field4),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		0,
		&asn_DEF_field4_7,
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
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 0, 0, 0 }, /* field1 at 9 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 1, 0, 0 }, /* field2 at 10 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 2, 0, 0 }, /* field3 at 11 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 3, 0, 0 } /* field4 at 12 */
};
static uint8_t asn_MAP_set_mmap_2[(4 + (8 * sizeof(unsigned int)) - 1) / 8] = {
	(1 << 7) | (0 << 6) | (1 << 5) | (0 << 4)
};
static asn_SET_specifics_t asn_SPC_set_specs_2 = {
	sizeof(struct set),
	offsetof(struct set, _asn_ctx),
	offsetof(struct set, _presence_map),
	asn_MAP_set_tag2el_2,
	4,	/* Count of tags in the map */
	asn_MAP_set_tag2el_2,	/* Same as above */
	4,	/* Count of tags in the CXER map */
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
	4,	/* Elements count */
	&asn_SPC_set_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SetRecord_ISet_Sets_of_seq_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SetRecord_ISet_Sets_of_seq, set),
		(ASN_TAG_CLASS_UNIVERSAL | (17 << 2)),
		0,
		&asn_DEF_set_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"set"
		},
};
static ber_tlv_tag_t asn_DEF_SetRecord_ISet_Sets_of_seq_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (17 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SetRecord_ISet_Sets_of_seq_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (17 << 2)), 0, 0, 0 } /* set at 9 */
};
static uint8_t asn_MAP_SetRecord_ISet_Sets_of_seq_mmap_1[(1 + (8 * sizeof(unsigned int)) - 1) / 8] = {
	(1 << 7)
};
static asn_SET_specifics_t asn_SPC_SetRecord_ISet_Sets_of_seq_specs_1 = {
	sizeof(struct SetRecord_ISet_Sets_of_seq),
	offsetof(struct SetRecord_ISet_Sets_of_seq, _asn_ctx),
	offsetof(struct SetRecord_ISet_Sets_of_seq, _presence_map),
	asn_MAP_SetRecord_ISet_Sets_of_seq_tag2el_1,
	1,	/* Count of tags in the map */
	asn_MAP_SetRecord_ISet_Sets_of_seq_tag2el_1,	/* Same as above */
	1,	/* Count of tags in the CXER map */
	0,	/* Whether extensible */
	(unsigned int *)asn_MAP_SetRecord_ISet_Sets_of_seq_mmap_1	/* Mandatory elements map */
};
asn_TYPE_descriptor_t asn_DEF_SetRecord_ISet_Sets_of_seq = {
	"SetRecord-ISet-Sets-of-seq",
	"SetRecord-ISet-Sets-of-seq",
	SET_free,
	SET_print,
	SET_constraint,
	SET_decode_ber,
	SET_encode_der,
	SET_decode_xer,
	SET_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SetRecord_ISet_Sets_of_seq_tags_1,
	sizeof(asn_DEF_SetRecord_ISet_Sets_of_seq_tags_1)
		/sizeof(asn_DEF_SetRecord_ISet_Sets_of_seq_tags_1[0]), /* 1 */
	asn_DEF_SetRecord_ISet_Sets_of_seq_tags_1,	/* Same as above */
	sizeof(asn_DEF_SetRecord_ISet_Sets_of_seq_tags_1)
		/sizeof(asn_DEF_SetRecord_ISet_Sets_of_seq_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SetRecord_ISet_Sets_of_seq_1,
	1,	/* Elements count */
	&asn_SPC_SetRecord_ISet_Sets_of_seq_specs_1	/* Additional specs */
};

