/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SequenceRecord-IS-VisS-VisSO-VisSRefWithTag-VisSRefWithTagO+VisibleStringRefWithTag.asn"
 */

#ifndef	_SequenceRecord_IS_VisS_VisSO_VisSRefWithTag_VisSRefWithTagO_H_
#define	_SequenceRecord_IS_VisS_VisSO_VisSRefWithTag_VisSRefWithTagO_H_


#include <asn_application.h>

/* Including external dependencies */
#include <VisibleString.h>
#include "VisibleStringRefWithTag.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SequenceRecord-IS-VisS-VisSO-VisSRefWithTag-VisSRefWithTagO */
typedef struct SequenceRecord_IS_VisS_VisSO_VisSRefWithTag_VisSRefWithTagO {
	struct seq {
		VisibleString_t	 str1;
		VisibleString_t	*str2	/* OPTIONAL */;
		VisibleStringRefWithTag_t	 str3;
		VisibleStringRefWithTag_t	*str4	/* OPTIONAL */;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} seq;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceRecord_IS_VisS_VisSO_VisSRefWithTag_VisSRefWithTagO_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceRecord_IS_VisS_VisSO_VisSRefWithTag_VisSRefWithTagO;

#ifdef __cplusplus
}
#endif

#endif	/* _SequenceRecord_IS_VisS_VisSO_VisSRefWithTag_VisSRefWithTagO_H_ */
#include <asn_internal.h>