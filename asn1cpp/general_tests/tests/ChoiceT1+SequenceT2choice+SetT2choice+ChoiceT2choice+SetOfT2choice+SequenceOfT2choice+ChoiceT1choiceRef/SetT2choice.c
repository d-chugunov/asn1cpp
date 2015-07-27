/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTestTags2"
 * 	found in "ChoiceT1+SequenceT2choice+SetT2choice+ChoiceT2choice+SetOfT2choice+SequenceOfT2choice+ChoiceT1choiceRef.asn"
 */

#include "SetT2choice.h"

static asn_TYPE_member_t asn_MBR_SetT2choice_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SetT2choice, one),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_ChoiceT1,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"one"
		},
	{ ATF_POINTER, 1, offsetof(struct SetT2choice, two),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_ChoiceT1,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"two"
		},
};
static ber_tlv_tag_t asn_DEF_SetT2choice_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (17 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SetT2choice_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* one at 25 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* two at 26 */
};
static uint8_t asn_MAP_SetT2choice_mmap_1[(2 + (8 * sizeof(unsigned int)) - 1) / 8] = {
	(1 << 7) | (0 << 6)
};
static asn_SET_specifics_t asn_SPC_SetT2choice_specs_1 = {
	sizeof(struct SetT2choice),
	offsetof(struct SetT2choice, _asn_ctx),
	offsetof(struct SetT2choice, _presence_map),
	asn_MAP_SetT2choice_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_SetT2choice_tag2el_1,	/* Same as above */
	2,	/* Count of tags in the CXER map */
	0,	/* Whether extensible */
	(unsigned int *)asn_MAP_SetT2choice_mmap_1	/* Mandatory elements map */
};
asn_TYPE_descriptor_t asn_DEF_SetT2choice = {
	"SetT2choice",
	"SetT2choice",
	SET_free,
	SET_print,
	SET_constraint,
	SET_decode_ber,
	SET_encode_der,
	SET_decode_xer,
	SET_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SetT2choice_tags_1,
	sizeof(asn_DEF_SetT2choice_tags_1)
		/sizeof(asn_DEF_SetT2choice_tags_1[0]), /* 1 */
	asn_DEF_SetT2choice_tags_1,	/* Same as above */
	sizeof(asn_DEF_SetT2choice_tags_1)
		/sizeof(asn_DEF_SetT2choice_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SetT2choice_1,
	2,	/* Elements count */
	&asn_SPC_SetT2choice_specs_1	/* Additional specs */
};
