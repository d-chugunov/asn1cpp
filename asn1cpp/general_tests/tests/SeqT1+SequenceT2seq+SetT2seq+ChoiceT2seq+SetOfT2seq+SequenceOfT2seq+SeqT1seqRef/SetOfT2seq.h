/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTest2"
 * 	found in "SeqT1+SequenceT2Seq+SetT2seq+ChoiceT2seq+SetOfT2seq+SequenceOfT2seq+ChoiceT1seqRef.asn"
 */

#ifndef	_SetOfT2seq_H_
#define	_SetOfT2seq_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SET_OF.h>
#include <constr_SET_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SeqT1;

/* SetOfT2seq */
typedef struct SetOfT2seq {
	A_SET_OF(struct SeqT1) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetOfT2seq_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetOfT2seq;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SeqT1.h"

#endif	/* _SetOfT2seq_H_ */
#include <asn_internal.h>