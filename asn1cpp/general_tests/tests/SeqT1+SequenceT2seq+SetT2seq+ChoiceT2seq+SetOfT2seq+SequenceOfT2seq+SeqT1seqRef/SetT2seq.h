/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ModuleTest2"
 * 	found in "SeqT1+SequenceT2Seq+SetT2seq+ChoiceT2seq+SetOfT2seq+SequenceOfT2seq+ChoiceT1seqRef.asn"
 */

#ifndef	_SetT2seq_H_
#define	_SetT2seq_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SeqT1.h"
#include <constr_SET.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */

/*
 * Method of determining the components presence
 */
typedef enum SetT2seq_PR {
	SetT2seq_PR_one,	/* Member one is present */
	SetT2seq_PR_two,	/* Member two is present */
} SetT2seq_PR;

/* Forward declarations */
struct SeqT1;

/* SetT2seq */
typedef struct SetT2seq {
	SeqT1_t	 one;
	struct SeqT1	*two	/* OPTIONAL */;
	
	/* Presence bitmask: ASN_SET_ISPRESENT(pSetT2seq, SetT2seq_PR_x) */
	unsigned int _presence_map
		[((2+(8*sizeof(unsigned int))-1)/(8*sizeof(unsigned int)))];
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetT2seq_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetT2seq;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SeqT1.h"

#endif	/* _SetT2seq_H_ */
#include <asn_internal.h>
