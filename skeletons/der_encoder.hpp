/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_DER_ENCODER_HPP_
#define	_DER_ENCODER_HPP_

#include <asn_application.hpp>

struct asn_TYPE_descriptor_s;	/* Forward declaration */

/*
 * Type of the generic DER encoder.
 */
typedef asn_enc_rval_t (der_type_encoder_f)(
		struct asn_TYPE_descriptor_s *type_descriptor,
		void *struct_ptr,	/* Structure to be encoded */
		int tag_mode,		/* {-1,0,1}: IMPLICIT, no, EXPLICIT */
		ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *consume_bytes_cb,	/* Callback */
		void *app_key		/* Arbitrary callback argument */
	);


/*******************************
 * INTERNALLY USEFUL FUNCTIONS *
 *******************************/

/*
 * Write out leading TL[v] sequence according to the type definition.
 */
ssize_t der_write_tags(
		struct asn_TYPE_descriptor_s *type_descriptor,
		size_t struct_length,
		int tag_mode,		/* {-1,0,1}: IMPLICIT, no, EXPLICIT */
		int last_tag_form,	/* {0,!0}: prim, constructed */
		ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *consume_bytes_cb,
		void *app_key
	);

#endif	/* _DER_ENCODER_HPP_ */
