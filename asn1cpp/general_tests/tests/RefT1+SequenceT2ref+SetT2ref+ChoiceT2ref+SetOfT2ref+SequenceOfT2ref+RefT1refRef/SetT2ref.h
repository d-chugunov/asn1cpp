/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTest2"
 * 	found in "RefT1+SequenceT2ref+SetT2ref+ChoiceT2ref+SetOfT2ref+SequenceOfT2ref+RefT1refRef.asn"
 */

#ifndef	_SetT2ref_H_
#define	_SetT2ref_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RefT1.h"
#include <constr_SET.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */

/*
 * Method of determining the components presence
 */
typedef enum SetT2ref_PR {
	SetT2ref_PR_one,	/* Member one is present */
	SetT2ref_PR_two,	/* Member two is present */
} SetT2ref_PR;

/* SetT2ref */
typedef struct SetT2ref {
	RefT1_t	 one;
	RefT1_t	*two	/* OPTIONAL */;
	
	/* Presence bitmask: ASN_SET_ISPRESENT(pSetT2ref, SetT2ref_PR_x) */
	unsigned int _presence_map
		[((2+(8*sizeof(unsigned int))-1)/(8*sizeof(unsigned int)))];
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetT2ref_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetT2ref;

#ifdef __cplusplus
}
#endif

#endif	/* _SetT2ref_H_ */
#include <asn_internal.h>
