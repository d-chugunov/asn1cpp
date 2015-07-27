/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "Integer-Enumeration.asn"
 */

#ifndef	_Integer_Enumeration_H_
#define	_Integer_Enumeration_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Integer_Enumeration {
	Integer_Enumeration_value1	= 0,
	Integer_Enumeration_value2	= 1,
	Integer_Enumeration_value3	= 2
} e_Integer_Enumeration;

/* Integer-Enumeration */
typedef long	 Integer_Enumeration_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Integer_Enumeration;
asn_struct_free_f Integer_Enumeration_free;
asn_struct_print_f Integer_Enumeration_print;
asn_constr_check_f Integer_Enumeration_constraint;
ber_type_decoder_f Integer_Enumeration_decode_ber;
der_type_encoder_f Integer_Enumeration_encode_der;
xer_type_decoder_f Integer_Enumeration_decode_xer;
xer_type_encoder_f Integer_Enumeration_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _Integer_Enumeration_H_ */
#include <asn_internal.h>
