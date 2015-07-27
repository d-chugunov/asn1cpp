/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SetRecord-OSRef1-OSRef1O+OctetStringRef1+OctetStringRef2+OctetStringRef3+OctetStringRef4.asn"
 */

#include "SetRecord-OSRef1-OSRef1O.h"

static asn_TYPE_member_t asn_MBR_SetRecord_OSRef1_OSRef1O_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SetRecord_OSRef1_OSRef1O, ref1),
		(ASN_TAG_CLASS_CONTEXT | (50 << 2)),
		0,
		&asn_DEF_OctetStringRef1,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ref1"
		},
	{ ATF_POINTER, 1, offsetof(struct SetRecord_OSRef1_OSRef1O, ref2),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OctetStringRef1,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ref2"
		},
};
static ber_tlv_tag_t asn_DEF_SetRecord_OSRef1_OSRef1O_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (17 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SetRecord_OSRef1_OSRef1O_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 1, 0, 0 }, /* ref2 at 10 */
    { (ASN_TAG_CLASS_CONTEXT | (50 << 2)), 0, 0, 0 } /* ref1 at 9 */
};
static uint8_t asn_MAP_SetRecord_OSRef1_OSRef1O_mmap_1[(2 + (8 * sizeof(unsigned int)) - 1) / 8] = {
	(1 << 7) | (0 << 6)
};
static asn_SET_specifics_t asn_SPC_SetRecord_OSRef1_OSRef1O_specs_1 = {
	sizeof(struct SetRecord_OSRef1_OSRef1O),
	offsetof(struct SetRecord_OSRef1_OSRef1O, _asn_ctx),
	offsetof(struct SetRecord_OSRef1_OSRef1O, _presence_map),
	asn_MAP_SetRecord_OSRef1_OSRef1O_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_SetRecord_OSRef1_OSRef1O_tag2el_1,	/* Same as above */
	2,	/* Count of tags in the CXER map */
	0,	/* Whether extensible */
	(unsigned int *)asn_MAP_SetRecord_OSRef1_OSRef1O_mmap_1	/* Mandatory elements map */
};
asn_TYPE_descriptor_t asn_DEF_SetRecord_OSRef1_OSRef1O = {
	"SetRecord-OSRef1-OSRef1O",
	"SetRecord-OSRef1-OSRef1O",
	SET_free,
	SET_print,
	SET_constraint,
	SET_decode_ber,
	SET_encode_der,
	SET_decode_xer,
	SET_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SetRecord_OSRef1_OSRef1O_tags_1,
	sizeof(asn_DEF_SetRecord_OSRef1_OSRef1O_tags_1)
		/sizeof(asn_DEF_SetRecord_OSRef1_OSRef1O_tags_1[0]), /* 1 */
	asn_DEF_SetRecord_OSRef1_OSRef1O_tags_1,	/* Same as above */
	sizeof(asn_DEF_SetRecord_OSRef1_OSRef1O_tags_1)
		/sizeof(asn_DEF_SetRecord_OSRef1_OSRef1O_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SetRecord_OSRef1_OSRef1O_1,
	2,	/* Elements count */
	&asn_SPC_SetRecord_OSRef1_OSRef1O_specs_1	/* Additional specs */
};
