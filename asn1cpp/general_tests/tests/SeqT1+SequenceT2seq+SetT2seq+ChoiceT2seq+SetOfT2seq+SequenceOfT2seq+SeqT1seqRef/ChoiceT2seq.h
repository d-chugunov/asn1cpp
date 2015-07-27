/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTest2"
 * 	found in "SeqT1+SequenceT2Seq+SetT2seq+ChoiceT2seq+SetOfT2seq+SequenceOfT2seq+ChoiceT1seqRef.asn"
 */

#ifndef	_ChoiceT2seq_H_
#define	_ChoiceT2seq_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SeqT1.h"
#include <IA5String.h>
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ChoiceT2seq_PR {
	ChoiceT2seq_PR_NOTHING,	/* No components present */
	ChoiceT2seq_PR_one,
	ChoiceT2seq_PR_two
} ChoiceT2seq_PR;

/* ChoiceT2seq */
typedef struct ChoiceT2seq {
	ChoiceT2seq_PR present;
	union ChoiceT2seq_u {
		SeqT1_t	 one;
		IA5String_t	 two;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ChoiceT2seq_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ChoiceT2seq;

#ifdef __cplusplus
}
#endif

#endif	/* _ChoiceT2seq_H_ */
#include <asn_internal.h>
