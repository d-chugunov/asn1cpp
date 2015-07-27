/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "Choice-SeqWithThisChoice+SeqRecWithThisChoice.asn"
 */

#include "SeqRecWithThisChoice.h"

static asn_TYPE_member_t asn_MBR_SeqRecWithThisChoice_1[] = {
	{ ATF_POINTER, 1, offsetof(struct SeqRecWithThisChoice, ch),
		-1 /* Ambiguous tag (CHOICE?) */,
		0,
		&asn_DEF_Choice_SeqWithThisChoice,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ch"
		},
};
static ber_tlv_tag_t asn_DEF_SeqRecWithThisChoice_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SeqRecWithThisChoice_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 0, 0, 0 } /* seq at 10 */
};
static asn_SEQUENCE_specifics_t asn_SPC_SeqRecWithThisChoice_specs_1 = {
	sizeof(struct SeqRecWithThisChoice),
	offsetof(struct SeqRecWithThisChoice, _asn_ctx),
	asn_MAP_SeqRecWithThisChoice_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SeqRecWithThisChoice = {
	"SeqRecWithThisChoice",
	"SeqRecWithThisChoice",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SeqRecWithThisChoice_tags_1,
	sizeof(asn_DEF_SeqRecWithThisChoice_tags_1)
		/sizeof(asn_DEF_SeqRecWithThisChoice_tags_1[0]), /* 1 */
	asn_DEF_SeqRecWithThisChoice_tags_1,	/* Same as above */
	sizeof(asn_DEF_SeqRecWithThisChoice_tags_1)
		/sizeof(asn_DEF_SeqRecWithThisChoice_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SeqRecWithThisChoice_1,
	1,	/* Elements count */
	&asn_SPC_SeqRecWithThisChoice_specs_1	/* Additional specs */
};

