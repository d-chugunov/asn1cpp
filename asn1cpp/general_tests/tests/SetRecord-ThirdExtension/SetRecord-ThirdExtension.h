/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "ForTest.as_n"
 */

#ifndef	_SetRecord_ThirdExtension_H_
#define	_SetRecord_ThirdExtension_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <BOOLEAN.h>
#include <NativeReal.h>
#include <IA5String.h>
#include <BMPString.h>
#include <constr_SET.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */

/*
 * Method of determining the components presence
 */
typedef enum SetRecord_ThirdExtension_PR {
	SetRecord_ThirdExtension_PR_a,	/* Member a is present */
	SetRecord_ThirdExtension_PR_b,	/* Member b is present */
	SetRecord_ThirdExtension_PR_c,	/* Member c is present */
	SetRecord_ThirdExtension_PR_d,	/* Member d is present */
	SetRecord_ThirdExtension_PR_z,	/* Member z is present */
} SetRecord_ThirdExtension_PR;

/*
 * Method of determining the components presence
 */
typedef enum d_PR {
	d_PR_e,	/* Member e is present */
	d_PR_f,	/* Member f is present */
	d_PR_g,	/* Member g is present */
	d_PR_h,	/* Member h is present */
	d_PR_y,	/* Member y is present */
} d_PR;

/* SetRecord-ThirdExtension */
typedef struct SetRecord_ThirdExtension {
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
		
		/* Presence bitmask: ASN_SET_ISPRESENT(pd, d_PR_x) */
		unsigned int _presence_map
			[((5+(8*sizeof(unsigned int))-1)/(8*sizeof(unsigned int)))];
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *d;
	double	 z;
	
	/* Presence bitmask: ASN_SET_ISPRESENT(pSetRecord_ThirdExtension, SetRecord_ThirdExtension_PR_x) */
	unsigned int _presence_map
		[((5+(8*sizeof(unsigned int))-1)/(8*sizeof(unsigned int)))];
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetRecord_ThirdExtension_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetRecord_ThirdExtension;

#ifdef __cplusplus
}
#endif

#endif	/* _SetRecord_ThirdExtension_H_ */
#include <asn_internal.h>
