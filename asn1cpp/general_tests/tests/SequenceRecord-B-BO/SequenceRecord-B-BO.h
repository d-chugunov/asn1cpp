/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SequenceRecord-B-BO.asn"
 */

#ifndef	_SequenceRecord_B_BO_H_
#define	_SequenceRecord_B_BO_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BOOLEAN.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SequenceRecord-B-BO */
typedef struct SequenceRecord_B_BO {
	BOOLEAN_t	 bool1;
	BOOLEAN_t	*bool2	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceRecord_B_BO_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceRecord_B_BO;

#ifdef __cplusplus
}
#endif

#endif	/* _SequenceRecord_B_BO_H_ */
#include <asn_internal.h>
