/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SetOfSelfRec.asn"
 */

#ifndef	_SetOfSelfRec_H_
#define	_SetOfSelfRec_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SET_OF.h>
#include <constr_SET_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SetOfSelfRec;

/* SetOfSelfRec */
typedef struct SetOfSelfRec {
	A_SET_OF(struct SetOfSelfRec) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetOfSelfRec_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetOfSelfRec;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SetOfSelfRec.h"

#endif	/* _SetOfSelfRec_H_ */
#include <asn_internal.h>