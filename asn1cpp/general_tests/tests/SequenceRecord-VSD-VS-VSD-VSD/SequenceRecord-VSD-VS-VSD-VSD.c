/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SequenceRecord-VSD-VS-VSD-VSD.asn"
 */

#include "SequenceRecord-VSD-VS-VSD-VSD.h"

static int asn_DFL_2_set(int set_value, void **sptr) {
	static uint8_t defv[] = { 0x31, 0x32, 0x22, 0x33, 0 };
	VisibleString_t *st = *sptr;
	
	if(!st) {
		if(!set_value) return -1;	/* Not a default value */
		st = (*sptr = CALLOC(1, sizeof(*st)));
		if(!st) return -1;
	}
	
	if(set_value) {
		uint8_t *ptr = MALLOC(sizeof(defv));
		if(!ptr) return -1;
		memcpy(ptr, &defv, sizeof(defv));
		FREEMEM(st->buf);
		st->buf = ptr;
		st->size = sizeof(defv) - 1;
		return 0;
	} else {
		if(st->size != (sizeof(defv) - 1)
		|| memcmp(st->buf, &defv, sizeof(defv) - 1))
			return 0;
		return 1;
	}
	
}
static int asn_DFL_4_set(int set_value, void **sptr) {
	static uint8_t defv[] = "567";
	VisibleString_t *st = *sptr;
	
	if(!st) {
		if(!set_value) return -1;	/* Not a default value */
		st = (*sptr = CALLOC(1, sizeof(*st)));
		if(!st) return -1;
	}
	
	if(set_value) {
		uint8_t *ptr = MALLOC(sizeof(defv));
		if(!ptr) return -1;
		memcpy(ptr, &defv, sizeof(defv));
		FREEMEM(st->buf);
		st->buf = ptr;
		st->size = sizeof(defv) - 1;
		return 0;
	} else {
		if(st->size != (sizeof(defv) - 1)
		|| memcmp(st->buf, &defv, sizeof(defv) - 1))
			return 0;
		return 1;
	}
	
}
static int asn_DFL_5_set(int set_value, void **sptr) {
	static uint8_t defv[] = "78*/9";
	VisibleString_t *st = *sptr;
	
	if(!st) {
		if(!set_value) return -1;	/* Not a default value */
		st = (*sptr = CALLOC(1, sizeof(*st)));
		if(!st) return -1;
	}
	
	if(set_value) {
		uint8_t *ptr = MALLOC(sizeof(defv));
		if(!ptr) return -1;
		memcpy(ptr, &defv, sizeof(defv));
		FREEMEM(st->buf);
		st->buf = ptr;
		st->size = sizeof(defv) - 1;
		return 0;
	} else {
		if(st->size != (sizeof(defv) - 1)
		|| memcmp(st->buf, &defv, sizeof(defv) - 1))
			return 0;
		return 1;
	}
	
}
static asn_TYPE_member_t asn_MBR_SequenceRecord_VSD_VS_VSD_VSD_1[] = {
	{ ATF_POINTER, 1, offsetof(struct SequenceRecord_VSD_VS_VSD_VSD, val1),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_VisibleString,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		asn_DFL_2_set,	/* DEFAULT "12"3" */
		"val1"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SequenceRecord_VSD_VS_VSD_VSD, val2),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_VisibleString,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"val2"
		},
	{ ATF_POINTER, 2, offsetof(struct SequenceRecord_VSD_VS_VSD_VSD, val3),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_VisibleString,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		asn_DFL_4_set,	/* DEFAULT "567" */
		"val3"
		},
	{ ATF_POINTER, 1, offsetof(struct SequenceRecord_VSD_VS_VSD_VSD, val4),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_VisibleString,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		asn_DFL_5_set,	/* DEFAULT */
		"val4"
		},
};
static ber_tlv_tag_t asn_DEF_SequenceRecord_VSD_VS_VSD_VSD_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SequenceRecord_VSD_VS_VSD_VSD_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* val1 at 9 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* val2 at 10 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* val3 at 11 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* val4 at 12 */
};
static asn_SEQUENCE_specifics_t asn_SPC_SequenceRecord_VSD_VS_VSD_VSD_specs_1 = {
	sizeof(struct SequenceRecord_VSD_VS_VSD_VSD),
	offsetof(struct SequenceRecord_VSD_VS_VSD_VSD, _asn_ctx),
	asn_MAP_SequenceRecord_VSD_VS_VSD_VSD_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SequenceRecord_VSD_VS_VSD_VSD = {
	"SequenceRecord-VSD-VS-VSD-VSD",
	"SequenceRecord-VSD-VS-VSD-VSD",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SequenceRecord_VSD_VS_VSD_VSD_tags_1,
	sizeof(asn_DEF_SequenceRecord_VSD_VS_VSD_VSD_tags_1)
		/sizeof(asn_DEF_SequenceRecord_VSD_VS_VSD_VSD_tags_1[0]), /* 1 */
	asn_DEF_SequenceRecord_VSD_VS_VSD_VSD_tags_1,	/* Same as above */
	sizeof(asn_DEF_SequenceRecord_VSD_VS_VSD_VSD_tags_1)
		/sizeof(asn_DEF_SequenceRecord_VSD_VS_VSD_VSD_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SequenceRecord_VSD_VS_VSD_VSD_1,
	4,	/* Elements count */
	&asn_SPC_SequenceRecord_VSD_VS_VSD_VSD_specs_1	/* Additional specs */
};
