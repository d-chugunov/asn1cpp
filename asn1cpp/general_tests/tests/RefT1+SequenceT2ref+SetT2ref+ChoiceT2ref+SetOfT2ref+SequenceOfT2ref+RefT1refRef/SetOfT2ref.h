/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTest2"
 * 	found in "RefT1+SequenceT2ref+SetT2ref+ChoiceT2ref+SetOfT2ref+SequenceOfT2ref+RefT1refRef.asn"
 */

#ifndef	_SetOfT2ref_H_
#define	_SetOfT2ref_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RefT1.h"
#include <asn_SET_OF.h>
#include <constr_SET_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SetOfT2ref */
typedef struct SetOfT2ref {
	A_SET_OF(RefT1_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetOfT2ref_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetOfT2ref;

#ifdef __cplusplus
}
#endif

#endif	/* _SetOfT2ref_H_ */
#include <asn_internal.h>
