/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SequenceRecord-NSD-NS-NSD-NSD.asn"
 */

#ifndef	_SequenceRecord_NSD_NS_NSD_NSD_H_
#define	_SequenceRecord_NSD_NS_NSD_NSD_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NumericString.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SequenceRecord-NSD-NS-NSD-NSD */
typedef struct SequenceRecord_NSD_NS_NSD_NSD {
	NumericString_t	*val1	/* DEFAULT 12"3 */;
	NumericString_t	 val2;
	NumericString_t	*val3	/* DEFAULT 567 */;
	NumericString_t	*val4;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceRecord_NSD_NS_NSD_NSD_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceRecord_NSD_NS_NSD_NSD;

#ifdef __cplusplus
}
#endif

#endif	/* _SequenceRecord_NSD_NS_NSD_NSD_H_ */
#include <asn_internal.h>
