/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SequenceRecord-USD-US-USD-USD.asn"
 */

#ifndef	_SequenceRecord_USD_US_USD_USD_H_
#define	_SequenceRecord_USD_US_USD_USD_H_


#include <asn_application.h>

/* Including external dependencies */
#include <UniversalString.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SequenceRecord-USD-US-USD-USD */
typedef struct SequenceRecord_USD_US_USD_USD {
	UniversalString_t	*val1	/* DEFAULT 12"3 */;
	UniversalString_t	 val2;
	UniversalString_t	*val3	/* DEFAULT 567 */;
	UniversalString_t	*val4;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceRecord_USD_US_USD_USD_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceRecord_USD_US_USD_USD;

#ifdef __cplusplus
}
#endif

#endif	/* _SequenceRecord_USD_US_USD_USD_H_ */
#include <asn_internal.h>
