/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SequenceRecord-IS-IEO.asn"
 */

#include "SequenceRecord-IS-IEO.h"

static asn_TYPE_member_t asn_MBR_field_2[] = {
	{ ATF_POINTER, 1, offsetof(struct field, value),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"value"
		},
};
static ber_tlv_tag_t asn_DEF_field_tags_2[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_field_tag2el_2[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 0 } /* value at 13 */
};
static asn_SEQUENCE_specifics_t asn_SPC_field_specs_2 = {
	sizeof(struct field),
	offsetof(struct field, _asn_ctx),
	asn_MAP_field_tag2el_2,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_field_2 = {
	"field",
	"field",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_field_tags_2,
	sizeof(asn_DEF_field_tags_2)
		/sizeof(asn_DEF_field_tags_2[0]), /* 1 */
	asn_DEF_field_tags_2,	/* Same as above */
	sizeof(asn_DEF_field_tags_2)
		/sizeof(asn_DEF_field_tags_2[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_field_2,
	1,	/* Elements count */
	&asn_SPC_field_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SequenceRecord_IS_IEO_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SequenceRecord_IS_IEO, field),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_field_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"field"
		},
};
static ber_tlv_tag_t asn_DEF_SequenceRecord_IS_IEO_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SequenceRecord_IS_IEO_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 0, 0, 0 } /* field at 16 */
};
static asn_SEQUENCE_specifics_t asn_SPC_SequenceRecord_IS_IEO_specs_1 = {
	sizeof(struct SequenceRecord_IS_IEO),
	offsetof(struct SequenceRecord_IS_IEO, _asn_ctx),
	asn_MAP_SequenceRecord_IS_IEO_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SequenceRecord_IS_IEO = {
	"SequenceRecord-IS-IEO",
	"SequenceRecord-IS-IEO",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SequenceRecord_IS_IEO_tags_1,
	sizeof(asn_DEF_SequenceRecord_IS_IEO_tags_1)
		/sizeof(asn_DEF_SequenceRecord_IS_IEO_tags_1[0]), /* 1 */
	asn_DEF_SequenceRecord_IS_IEO_tags_1,	/* Same as above */
	sizeof(asn_DEF_SequenceRecord_IS_IEO_tags_1)
		/sizeof(asn_DEF_SequenceRecord_IS_IEO_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SequenceRecord_IS_IEO_1,
	1,	/* Elements count */
	&asn_SPC_SequenceRecord_IS_IEO_specs_1	/* Additional specs */
};

