/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTest2"
 * 	found in "SeqOfT1+SequenceT2seqof+SetT2seqof+ChoiceT2seqof+SetOfT2seqof+SequenceOfT2seqof+ChoiceT1seqofRef.asn"
 */

#ifndef	_SetOfT2seqof_H_
#define	_SetOfT2seqof_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SET_OF.h>
#include <constr_SET_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SeqOfT1;

/* SetOfT2seqof */
typedef struct SetOfT2seqof {
	A_SET_OF(struct SeqOfT1) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetOfT2seqof_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetOfT2seqof;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SeqOfT1.h"

#endif	/* _SetOfT2seqof_H_ */
#include <asn_internal.h>
