/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTest1"
 * 	found in "SetT1+SequenceT2Set+SetT2set+ChoiceT2set+SetOfT2set+SequenceOfT2set+ChoiceT1setRef.asn"
 */

#ifndef	_SetT1_H_
#define	_SetT1_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SET.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */

/*
 * Method of determining the components presence
 */
typedef enum SetT1_PR {
	SetT1_PR_first,	/* Member first is present */
	SetT1_PR_second,	/* Member second is present */
} SetT1_PR;

/* SetT1 */
typedef struct SetT1 {
	long	 first;
	long	 second;
	
	/* Presence bitmask: ASN_SET_ISPRESENT(pSetT1, SetT1_PR_x) */
	unsigned int _presence_map
		[((2+(8*sizeof(unsigned int))-1)/(8*sizeof(unsigned int)))];
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetT1_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetT1;

#ifdef __cplusplus
}
#endif

#endif	/* _SetT1_H_ */
#include <asn_internal.h>
