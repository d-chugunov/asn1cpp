/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SequenceRecord-DirectRef-EXPL+DirectRefRecord-S-I-IO-I-EXPL+SequenceRecord-I-IO-I-EXPL.asn"
 */

#include "SequenceRecord-I-IO-I-EXPL.h"

static asn_TYPE_member_t asn_MBR_SequenceRecord_I_IO_I_EXPL_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SequenceRecord_I_IO_I_EXPL, type),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"type"
		},
	{ ATF_POINTER, 1, offsetof(struct SequenceRecord_I_IO_I_EXPL, type2),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"type2"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SequenceRecord_I_IO_I_EXPL, type3),
		(ASN_TAG_CLASS_CONTEXT | (12 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"type3"
		},
};
static ber_tlv_tag_t asn_DEF_SequenceRecord_I_IO_I_EXPL_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SequenceRecord_I_IO_I_EXPL_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 0, 0, 0 }, /* type at 15 */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 1, 0, 0 }, /* type2 at 16 */
    { (ASN_TAG_CLASS_CONTEXT | (12 << 2)), 2, 0, 0 } /* type3 at 18 */
};
static asn_SEQUENCE_specifics_t asn_SPC_SequenceRecord_I_IO_I_EXPL_specs_1 = {
	sizeof(struct SequenceRecord_I_IO_I_EXPL),
	offsetof(struct SequenceRecord_I_IO_I_EXPL, _asn_ctx),
	asn_MAP_SequenceRecord_I_IO_I_EXPL_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SequenceRecord_I_IO_I_EXPL = {
	"SequenceRecord-I-IO-I-EXPL",
	"SequenceRecord-I-IO-I-EXPL",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SequenceRecord_I_IO_I_EXPL_tags_1,
	sizeof(asn_DEF_SequenceRecord_I_IO_I_EXPL_tags_1)
		/sizeof(asn_DEF_SequenceRecord_I_IO_I_EXPL_tags_1[0]), /* 1 */
	asn_DEF_SequenceRecord_I_IO_I_EXPL_tags_1,	/* Same as above */
	sizeof(asn_DEF_SequenceRecord_I_IO_I_EXPL_tags_1)
		/sizeof(asn_DEF_SequenceRecord_I_IO_I_EXPL_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SequenceRecord_I_IO_I_EXPL_1,
	3,	/* Elements count */
	&asn_SPC_SequenceRecord_I_IO_I_EXPL_specs_1	/* Additional specs */
};
