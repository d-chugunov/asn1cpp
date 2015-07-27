/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "Choice-IChoiceRealInteger.asn"
 */

#include "Choice-IChoiceRealInteger.h"

static asn_TYPE_member_t asn_MBR_choice_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct choice, choice.real),
		(ASN_TAG_CLASS_UNIVERSAL | (9 << 2)),
		0,
		&asn_DEF_NativeReal,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"real"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct choice, choice.integer),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"integer"
		},
};
static asn_TYPE_tag2member_t asn_MAP_choice_tag2el_2[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 1, 0, 0 }, /* integer at 12 */
    { (ASN_TAG_CLASS_UNIVERSAL | (9 << 2)), 0, 0, 0 } /* real at 10 */
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

static asn_TYPE_member_t asn_MBR_Choice_IChoiceRealInteger_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct Choice_IChoiceRealInteger, choice.choice),
		-1 /* Ambiguous tag (CHOICE?) */,
		0,
		&asn_DEF_choice_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"choice"
		},
};
static asn_TYPE_tag2member_t asn_MAP_Choice_IChoiceRealInteger_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 0 }, /* integer at 12 */
    { (ASN_TAG_CLASS_UNIVERSAL | (9 << 2)), 0, 0, 0 } /* real at 10 */
};
static asn_CHOICE_specifics_t asn_SPC_Choice_IChoiceRealInteger_specs_1 = {
	sizeof(struct Choice_IChoiceRealInteger),
	offsetof(struct Choice_IChoiceRealInteger, _asn_ctx),
	offsetof(struct Choice_IChoiceRealInteger, present),
	sizeof(((struct Choice_IChoiceRealInteger *)0)->present),
	asn_MAP_Choice_IChoiceRealInteger_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_Choice_IChoiceRealInteger = {
	"Choice-IChoiceRealInteger",
	"Choice-IChoiceRealInteger",
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
	asn_MBR_Choice_IChoiceRealInteger_1,
	1,	/* Elements count */
	&asn_SPC_Choice_IChoiceRealInteger_specs_1	/* Additional specs */
};

