/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "Simplified.asn"
 */

#ifndef	_SequenceRecord_I_IO_I_H_
#define	_SequenceRecord_I_IO_I_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SequenceRecord-I-IO-I */
typedef struct SequenceRecord_I_IO_I {
	long	 type;
	long	*type2	/* OPTIONAL */;
	long	 type3;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceRecord_I_IO_I_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceRecord_I_IO_I;

#ifdef __cplusplus
}
#endif

#endif	/* _SequenceRecord_I_IO_I_H_ */
#include <asn_internal.h>
