/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SOME-MODULE"
 * 	found in "SequenceRecord-BS-BSO-BSRef-BSRefO+BitStringRef.asn"
 */

#ifndef	_BitStringRef_H_
#define	_BitStringRef_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* BitStringRef */
typedef BIT_STRING_t	 BitStringRef_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_BitStringRef;
asn_struct_free_f BitStringRef_free;
asn_struct_print_f BitStringRef_print;
asn_constr_check_f BitStringRef_constraint;
ber_type_decoder_f BitStringRef_decode_ber;
der_type_encoder_f BitStringRef_encode_der;
xer_type_decoder_f BitStringRef_decode_xer;
xer_type_encoder_f BitStringRef_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _BitStringRef_H_ */
#include <asn_internal.h>