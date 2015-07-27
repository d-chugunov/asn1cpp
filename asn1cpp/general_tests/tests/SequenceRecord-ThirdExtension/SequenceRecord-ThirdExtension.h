/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "ForTest.as_n"
 */

#ifndef	_SequenceRecord_ThirdExtension_H_
#define	_SequenceRecord_ThirdExtension_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <BOOLEAN.h>
#include <NativeReal.h>
#include <IA5String.h>
#include <BMPString.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SequenceRecord-ThirdExtension */
typedef struct SequenceRecord_ThirdExtension {
	long	 a;
	BOOLEAN_t	*b	/* OPTIONAL */;
	long	*c	/* OPTIONAL */;
	struct d {
		long	 e;
		IA5String_t	 f;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
		BOOLEAN_t	*g	/* OPTIONAL */;
		BMPString_t	*h;
		double	*y;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *d;
	double	 z;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceRecord_ThirdExtension_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceRecord_ThirdExtension;

#ifdef __cplusplus
}
#endif

#endif	/* _SequenceRecord_ThirdExtension_H_ */
#include <asn_internal.h>