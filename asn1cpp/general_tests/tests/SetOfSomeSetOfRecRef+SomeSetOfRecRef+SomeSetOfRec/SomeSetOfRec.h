/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SetOfSomeSetOfRecRef+SomeSetOfRecRef+SomeSetOfRec.asn"
 */

#ifndef	_SomeSetOfRec_H_
#define	_SomeSetOfRec_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SET_OF.h>
#include <constr_SET_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SetOfSomeSetOfRecRef;

/* SomeSetOfRec */
typedef struct SomeSetOfRec {
	A_SET_OF(struct SetOfSomeSetOfRecRef) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SomeSetOfRec_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SomeSetOfRec;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SetOfSomeSetOfRecRef.h"

#endif	/* _SomeSetOfRec_H_ */
#include <asn_internal.h>
