/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "Choice-IChoicePS-IA5.asn"
 */

#include "Choice-IChoicePS-IA5.h"

static asn_TYPE_member_t asn_MBR_choice_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct choice, choice.str1),
		(ASN_TAG_CLASS_UNIVERSAL | (19 << 2)),
		0,
		&asn_DEF_PrintableString,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"str1"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct choice, choice.str2),
		(ASN_TAG_CLASS_UNIVERSAL | (22 << 2)),
		0,
		&asn_DEF_IA5String,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"str2"
		},
};
static asn_TYPE_tag2member_t asn_MAP_choice_tag2el_2[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (19 << 2)), 0, 0, 0 }, /* str1 at 10 */
    { (ASN_TAG_CLASS_UNIVERSAL | (22 << 2)), 1, 0, 0 } /* str2 at 11 */
};
static asn_CHOICE_specifics_t asn_SPC_choice_specs_2 = {
	sizeof(struct choice),
	offsetof(struct choice, _asn_ctx),
	offsetof(struct choice, present),
	sizeof(((struct choice *)0)->present),
	asn_MAP_choice_tag2el_2,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_choice_2 = {
	"choice",
	"choice",
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
	asn_MBR_choice_2,
	2,	/* Elements count */
	&asn_SPC_choice_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_Choice_IChoicePS_IA5_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct Choice_IChoicePS_IA5, choice.choice),
		-1 /* Ambiguous tag (CHOICE?) */,
		0,
		&asn_DEF_choice_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"choice"
		},
};
static asn_TYPE_tag2member_t asn_MAP_Choice_IChoicePS_IA5_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (19 << 2)), 0, 0, 0 }, /* str1 at 10 */
    { (ASN_TAG_CLASS_UNIVERSAL | (22 << 2)), 0, 0, 0 } /* str2 at 11 */
};
static asn_CHOICE_specifics_t asn_SPC_Choice_IChoicePS_IA5_specs_1 = {
	sizeof(struct Choice_IChoicePS_IA5),
	offsetof(struct Choice_IChoicePS_IA5, _asn_ctx),
	offsetof(struct Choice_IChoicePS_IA5, present),
	sizeof(((struct Choice_IChoicePS_IA5 *)0)->present),
	asn_MAP_Choice_IChoicePS_IA5_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_Choice_IChoicePS_IA5 = {
	"Choice-IChoicePS-IA5",
	"Choice-IChoicePS-IA5",
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
	asn_MBR_Choice_IChoicePS_IA5_1,
	1,	/* Elements count */
	&asn_SPC_Choice_IChoicePS_IA5_specs_1	/* Additional specs */
};

