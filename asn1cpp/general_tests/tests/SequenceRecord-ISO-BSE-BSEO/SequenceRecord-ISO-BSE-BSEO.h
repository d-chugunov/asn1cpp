/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SequenceRecord-ISO-BSE-BSEO.asn"
 */

#ifndef	_SequenceRecord_ISO_BSE_BSEO_H_
#define	_SequenceRecord_ISO_BSE_BSEO_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum bitString1 {
	bitString1_value1	= 1000,
	bitString1_value2	= 128,
	bitString1_value3	= 937429
} e_bitString1;
typedef enum bitString2 {
	bitString2_value1	= 1000,
	bitString2_value2	= 128,
	bitString2_value3	= 937429
} e_bitString2;

/* SequenceRecord-ISO-BSE-BSEO */
typedef struct SequenceRecord_ISO_BSE_BSEO {
	struct seq {
		BIT_STRING_t	 bitString1;
		BIT_STRING_t	*bitString2	/* OPTIONAL */;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *seq;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceRecord_ISO_BSE_BSEO_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceRecord_ISO_BSE_BSEO;

#ifdef __cplusplus
}
#endif

#endif	/* _SequenceRecord_ISO_BSE_BSEO_H_ */
#include <asn_internal.h>
