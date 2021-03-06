/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "ForTest.as_n"
 */

#ifndef	_SetRecord_ExtensionRootType_H_
#define	_SetRecord_ExtensionRootType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SET.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */

/*
 * Method of determining the components presence
 */
typedef enum SetRecord_ExtensionRootType_PR {
	SetRecord_ExtensionRootType_PR_a,	/* Member a is present */
	SetRecord_ExtensionRootType_PR_b,	/* Member b is present */
} SetRecord_ExtensionRootType_PR;

/* SetRecord-ExtensionRootType */
typedef struct SetRecord_ExtensionRootType {
	long	 a;
	long	 b;
	
	/* Presence bitmask: ASN_SET_ISPRESENT(pSetRecord_ExtensionRootType, SetRecord_ExtensionRootType_PR_x) */
	unsigned int _presence_map
		[((2+(8*sizeof(unsigned int))-1)/(8*sizeof(unsigned int)))];
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetRecord_ExtensionRootType_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetRecord_ExtensionRootType;

#ifdef __cplusplus
}
#endif

#endif	/* _SetRecord_ExtensionRootType_H_ */
#include <asn_internal.h>
