/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTest2"
 * 	found in "SeqOfT1+SequenceT2seqof+SetT2seqof+ChoiceT2seqof+SetOfT2seqof+SequenceOfT2seqof+ChoiceT1seqofRef.asn"
 */

#ifndef	_SequenceT2seqof_H_
#define	_SequenceT2seqof_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SeqOfT1.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SeqOfT1;

/* SequenceT2seqof */
typedef struct SequenceT2seqof {
	SeqOfT1_t	 one;
	struct SeqOfT1	*two	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceT2seqof_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceT2seqof;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SeqOfT1.h"

#endif	/* _SequenceT2seqof_H_ */
#include <asn_internal.h>
