/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SequenceRecord-IS-E.asn"
 */

#ifndef	_SequenceRecord_IS_E_H_
#define	_SequenceRecord_IS_E_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum value {
	value_value1	= 0,
	value_value2	= 1,
	value_value3	= 2
} e_value;

/* SequenceRecord-IS-E */
typedef struct SequenceRecord_IS_E {
	struct field {
		long	 value;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} field;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceRecord_IS_E_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_value_3;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_SequenceRecord_IS_E;

#ifdef __cplusplus
}
#endif

#endif	/* _SequenceRecord_IS_E_H_ */
#include <asn_internal.h>
