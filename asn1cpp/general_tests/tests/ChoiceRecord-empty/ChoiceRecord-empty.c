/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "ForTest.as_n"
 * 	`asn1c -fnative-types`
 */

#include "ChoiceRecord-empty.h"

static asn_TYPE_member_t asn_MBR_ChoiceRecord_empty_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ChoiceRecord_empty, choice.Int),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"int"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ChoiceRecord_empty, choice.real),
		(ASN_TAG_CLASS_UNIVERSAL | (9 << 2)),
		0,
		&asn_DEF_NativeReal,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"real"
		},
};
static asn_TYPE_tag2member_t asn_MAP_ChoiceRecord_empty_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 0 }, /* int at 9 */
    { (ASN_TAG_CLASS_UNIVERSAL | (9 << 2)), 1, 0, 0 } /* real at 10 */
};
static asn_CHOICE_specifics_t asn_SPC_ChoiceRecord_empty_specs_1 = {
	sizeof(struct ChoiceRecord_empty),
	offsetof(struct ChoiceRecord_empty, _asn_ctx),
	offsetof(struct ChoiceRecord_empty, present),
	sizeof(((struct ChoiceRecord_empty *)0)->present),
	asn_MAP_ChoiceRecord_empty_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_ChoiceRecord_empty = {
	"ChoiceRecord-empty",
	"ChoiceRecord-empty",
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
	asn_MBR_ChoiceRecord_empty_1,
	2,	/* Elements count */
	&asn_SPC_ChoiceRecord_empty_specs_1	/* Additional specs */
};

