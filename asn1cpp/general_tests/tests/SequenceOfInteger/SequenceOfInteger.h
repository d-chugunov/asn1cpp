/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SequenceOfInteger.asn"
 */

#ifndef	_SequenceOfInteger_H_
#define	_SequenceOfInteger_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SequenceOfInteger */
typedef struct SequenceOfInteger {
	A_SEQUENCE_OF(long) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceOfInteger_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceOfInteger;

#ifdef __cplusplus
}
#endif

#endif	/* _SequenceOfInteger_H_ */
#include <asn_internal.h>
