/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "module.asn"
 * 	`asn1c -fnative-types`
 */

#ifndef	_SomeRecord_IO_I_I_Automatic_H_
#define	_SomeRecord_IO_I_I_Automatic_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SomeRecord-IO-I-I-Automatic */
typedef struct SomeRecord_IO_I_I_Automatic {
	long	*type	/* OPTIONAL */;
	long	 type2;
	long	 type3;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SomeRecord_IO_I_I_Automatic_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SomeRecord_IO_I_I_Automatic;

#ifdef __cplusplus
}
#endif

#endif	/* _SomeRecord_IO_I_I_Automatic_H_ */
#include <asn_internal.h>
