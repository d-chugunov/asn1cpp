/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTest2"
 * 	found in "SetT1+SequenceT2Set+SetT2set+ChoiceT2set+SetOfT2set+SequenceOfT2set+ChoiceT1setRef.asn"
 */

#ifndef	_SequenceT2set_H_
#define	_SequenceT2set_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SetT1.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SetT1;

/* SequenceT2set */
typedef struct SequenceT2set {
	SetT1_t	 one;
	struct SetT1	*two	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceT2set_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceT2set;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SetT1.h"

#endif	/* _SequenceT2set_H_ */
#include <asn_internal.h>
