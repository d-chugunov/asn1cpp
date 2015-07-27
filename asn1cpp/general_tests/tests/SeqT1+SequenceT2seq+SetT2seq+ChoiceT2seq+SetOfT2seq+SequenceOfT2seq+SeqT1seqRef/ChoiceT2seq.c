/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTest2"
 * 	found in "SeqT1+SequenceT2Seq+SetT2seq+ChoiceT2seq+SetOfT2seq+SequenceOfT2seq+ChoiceT1seqRef.asn"
 */

#include "ChoiceT2seq.h"

static asn_TYPE_member_t asn_MBR_ChoiceT2seq_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ChoiceT2seq, choice.one),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SeqT1,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"one"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ChoiceT2seq, choice.two),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IA5String,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"two"
		},
};
static asn_TYPE_tag2member_t asn_MAP_ChoiceT2seq_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* one at 27 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* two at 28 */
};
static asn_CHOICE_specifics_t asn_SPC_ChoiceT2seq_specs_1 = {
	sizeof(struct ChoiceT2seq),
	offsetof(struct ChoiceT2seq, _asn_ctx),
	offsetof(struct ChoiceT2seq, present),
	sizeof(((struct ChoiceT2seq *)0)->present),
	asn_MAP_ChoiceT2seq_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_ChoiceT2seq = {
	"ChoiceT2seq",
	"ChoiceT2seq",
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
	asn_MBR_ChoiceT2seq_1,
	2,	/* Elements count */
	&asn_SPC_ChoiceT2seq_specs_1	/* Additional specs */
};

