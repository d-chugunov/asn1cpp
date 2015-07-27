/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SetRecord-OSRef1-OSRef1O+OctetStringRef1+OctetStringRef2+OctetStringRef3+OctetStringRef4.asn"
 */

#ifndef	_SetRecord_OSRef1_OSRef1O_H_
#define	_SetRecord_OSRef1_OSRef1O_H_


#include <asn_application.h>

/* Including external dependencies */
#include "OctetStringRef1.h"
#include <constr_SET.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */

/*
 * Method of determining the components presence
 */
typedef enum SetRecord_OSRef1_OSRef1O_PR {
	SetRecord_OSRef1_OSRef1O_PR_ref1,	/* Member ref1 is present */
	SetRecord_OSRef1_OSRef1O_PR_ref2,	/* Member ref2 is present */
} SetRecord_OSRef1_OSRef1O_PR;

/* SetRecord-OSRef1-OSRef1O */
typedef struct SetRecord_OSRef1_OSRef1O {
	OctetStringRef1_t	 ref1;
	OctetStringRef1_t	*ref2	/* OPTIONAL */;
	
	/* Presence bitmask: ASN_SET_ISPRESENT(pSetRecord_OSRef1_OSRef1O, SetRecord_OSRef1_OSRef1O_PR_x) */
	unsigned int _presence_map
		[((2+(8*sizeof(unsigned int))-1)/(8*sizeof(unsigned int)))];
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetRecord_OSRef1_OSRef1O_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetRecord_OSRef1_OSRef1O;

#ifdef __cplusplus
}
#endif

#endif	/* _SetRecord_OSRef1_OSRef1O_H_ */
#include <asn_internal.h>