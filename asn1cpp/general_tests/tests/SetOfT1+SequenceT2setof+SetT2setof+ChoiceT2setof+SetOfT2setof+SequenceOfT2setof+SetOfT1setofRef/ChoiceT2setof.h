/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTest2"
 * 	found in "SetOfT1+SequenceT2setof+SetT2setof+ChoiceT2setof+SetOfT2setof+SequenceOfT2setof+SetOfT1setofRef.asn"
 */

#ifndef	_ChoiceT2setof_H_
#define	_ChoiceT2setof_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SetOfT1.h"
#include <IA5String.h>
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ChoiceT2setof_PR {
	ChoiceT2setof_PR_NOTHING,	/* No components present */
	ChoiceT2setof_PR_one,
	ChoiceT2setof_PR_two
} ChoiceT2setof_PR;

/* ChoiceT2setof */
typedef struct ChoiceT2setof {
	ChoiceT2setof_PR present;
	union ChoiceT2setof_u {
		SetOfT1_t	 one;
		IA5String_t	 two;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ChoiceT2setof_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ChoiceT2setof;

#ifdef __cplusplus
}
#endif

#endif	/* _ChoiceT2setof_H_ */
#include <asn_internal.h>
