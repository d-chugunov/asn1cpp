/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SequenceRecord-IS-OI-OIO-OIRef-OIRefO+ObjectIdentifierRef.asn"
 */

#include "SequenceRecord-IS-OI-OIO-OIRef-OIRefO.h"

static asn_TYPE_member_t asn_MBR_seq_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct seq, objectIdentifier1),
		(ASN_TAG_CLASS_UNIVERSAL | (6 << 2)),
		0,
		&asn_DEF_OBJECT_IDENTIFIER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"objectIdentifier1"
		},
	{ ATF_POINTER, 1, offsetof(struct seq, objectIdentifier2),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OBJECT_IDENTIFIER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"objectIdentifier2"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct seq, objectIdentifier3),
		(ASN_TAG_CLASS_UNIVERSAL | (6 << 2)),
		0,
		&asn_DEF_ObjectIdentifierRef,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"objectIdentifier3"
		},
	{ ATF_POINTER, 1, offsetof(struct seq, objectIdentifier4),
		(ASN_TAG_CLASS_UNIVERSAL | (6 << 2)),
		0,
		&asn_DEF_ObjectIdentifierRef,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"objectIdentifier4"
		},
};
static ber_tlv_tag_t asn_DEF_seq_tags_2[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_seq_tag2el_2[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (6 << 2)), 0, 0, 2 }, /* objectIdentifier1 at 10 */
    { (ASN_TAG_CLASS_UNIVERSAL | (6 << 2)), 2, -1, 1 }, /* objectIdentifier3 at 12 */
    { (ASN_TAG_CLASS_UNIVERSAL | (6 << 2)), 3, -2, 0 }, /* objectIdentifier4 at 13 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* objectIdentifier2 at 11 */
};
static asn_SEQUENCE_specifics_t asn_SPC_seq_specs_2 = {
	sizeof(struct seq),
	offsetof(struct seq, _asn_ctx),
	asn_MAP_seq_tag2el_2,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_seq_2 = {
	"seq",
	"seq",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_seq_tags_2,
	sizeof(asn_DEF_seq_tags_2)
		/sizeof(asn_DEF_seq_tags_2[0]), /* 1 */
	asn_DEF_seq_tags_2,	/* Same as above */
	sizeof(asn_DEF_seq_tags_2)
		/sizeof(asn_DEF_seq_tags_2[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_seq_2,
	4,	/* Elements count */
	&asn_SPC_seq_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SequenceRecord_IS_OI_OIO_OIRef_OIRefO, seq),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_seq_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"seq"
		},
};
static ber_tlv_tag_t asn_DEF_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 0, 0, 0 } /* seq at 10 */
};
static asn_SEQUENCE_specifics_t asn_SPC_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_specs_1 = {
	sizeof(struct SequenceRecord_IS_OI_OIO_OIRef_OIRefO),
	offsetof(struct SequenceRecord_IS_OI_OIO_OIRef_OIRefO, _asn_ctx),
	asn_MAP_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SequenceRecord_IS_OI_OIO_OIRef_OIRefO = {
	"SequenceRecord-IS-OI-OIO-OIRef-OIRefO",
	"SequenceRecord-IS-OI-OIO-OIRef-OIRefO",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_tags_1,
	sizeof(asn_DEF_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_tags_1)
		/sizeof(asn_DEF_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_tags_1[0]), /* 1 */
	asn_DEF_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_tags_1,	/* Same as above */
	sizeof(asn_DEF_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_tags_1)
		/sizeof(asn_DEF_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_1,
	1,	/* Elements count */
	&asn_SPC_SequenceRecord_IS_OI_OIO_OIRef_OIRefO_specs_1	/* Additional specs */
};

