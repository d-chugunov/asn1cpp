/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "Simplified.a_sn"
 */

#ifndef	_SeqOfSequenceRecord_I_IO_I_H_
#define	_SeqOfSequenceRecord_I_IO_I_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SequenceRecord_I_IO_I;

/* SeqOfSequenceRecord-I-IO-I */
typedef struct SeqOfSequenceRecord_I_IO_I {
	A_SEQUENCE_OF(struct SequenceRecord_I_IO_I) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SeqOfSequenceRecord_I_IO_I_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SeqOfSequenceRecord_I_IO_I;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SequenceRecord-I-IO-IRef.h"

#endif	/* _SeqOfSequenceRecord_I_IO_I_H_ */
#include <asn_internal.h>
