/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTest2"
 * 	found in "SetOfT1+SequenceT2setof+SetT2setof+ChoiceT2setof+SetOfT2setof+SequenceOfT2setof+SetOfT1setofRef.asn"
 */

#include "SequenceT2setof.h"

static asn_TYPE_member_t asn_MBR_SequenceT2setof_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SequenceT2setof, one),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SetOfT1,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"one"
		},
	{ ATF_POINTER, 1, offsetof(struct SequenceT2setof, two),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SetOfT1,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"two"
		},
};
static ber_tlv_tag_t asn_DEF_SequenceT2setof_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SequenceT2setof_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* one at 16 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* two at 17 */
};
static asn_SEQUENCE_specifics_t asn_SPC_SequenceT2setof_specs_1 = {
	sizeof(struct SequenceT2setof),
	offsetof(struct SequenceT2setof, _asn_ctx),
	asn_MAP_SequenceT2setof_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SequenceT2setof = {
	"SequenceT2setof",
	"SequenceT2setof",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SequenceT2setof_tags_1,
	sizeof(asn_DEF_SequenceT2setof_tags_1)
		/sizeof(asn_DEF_SequenceT2setof_tags_1[0]), /* 1 */
	asn_DEF_SequenceT2setof_tags_1,	/* Same as above */
	sizeof(asn_DEF_SequenceT2setof_tags_1)
		/sizeof(asn_DEF_SequenceT2setof_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SequenceT2setof_1,
	2,	/* Elements count */
	&asn_SPC_SequenceT2setof_specs_1	/* Additional specs */
};

