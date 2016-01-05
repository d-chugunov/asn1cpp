/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
/*
 * This file contains the declaration structure called "ASN.1 Type Definition",
 * which holds all information necessary for encoding and decoding routines.
 * This structure even contains pointer to these encoding and decoding routines
 * for each defined ASN.1 type.
 */
#ifndef	_CONSTR_TYPE_HPP_
#define	_CONSTR_TYPE_HPP_

#include <ber_tlv_length.hpp>
#include <ber_tlv_tag.hpp>

struct asn_TYPE_descriptor_s;	/* Forward declaration */
struct asn_TYPE_member_s;	/* Forward declaration */

/*
 * This type provides the context information for various ASN.1 routines,
 * primarily ones doing decoding. A member _asn_ctx of this type must be
 * included into certain target language's structures, such as compound types.
 */
typedef struct asn_struct_ctx_s {
	short phase;		/* Decoding phase */
	short step;		/* Elementary step of a phase */
	int context;		/* Other context information */
	void *ptr;		/* Decoder-specific stuff (stack elements) */
	ber_tlv_len_t left;	/* Number of bytes left, -1 for indefinite */
} asn_struct_ctx_t;

#include <ber_decoder.hpp>	/* Basic Encoding Rules decoder */
#include <der_encoder.hpp>	/* Distinguished Encoding Rules encoder */
#include <constraints.hpp>	/* Subtype constraints support */

/*
 * Print the structure according to its specification.
 */
typedef int (asn_struct_print_f)(
		struct asn_TYPE_descriptor_s *type_descriptor,
		const void *struct_ptr,
		int level,	/* Indentation level */
		asn_app_consume_bytes_f *callback, void *app_key);

/*
 * Return the outmost tag of the type.
 * If the type is untagged CHOICE, the dynamic operation is performed.
 * NOTE: This function pointer type is only useful internally.
 * Do not use it in your application.
 */
typedef ber_tlv_tag_t (asn_outmost_tag_f)(
		const struct asn_TYPE_descriptor_s *type_descriptor,
		const void *struct_ptr, int tag_mode, ber_tlv_tag_t tag);
/* The instance of the above function type; used internally. */
asn_outmost_tag_f asn_TYPE_outmost_tag;


/*
 * The definitive description of the destination language's structure.
 */
typedef struct asn_TYPE_descriptor_s {
	const char *name;	/* A name of the ASN.1 type. "" in some cases. */
	const char *xml_tag;	/* Name used in XML tag */

	/*
	 * Generalized functions for dealing with the specific type.
	 * May be directly invoked by applications.
	 */
	asn_struct_print_f *print_struct;	/* Human readable output */
	asn_constr_check_f *check_constraints;	/* Constraints validator */
	ber_type_decoder_f *ber_decoder;	/* Generic BER decoder */
	der_type_encoder_f *der_encoder;	/* Canonical DER encoder */

	/***********************************************************************
	 * Internally useful members. Not to be used by applications directly. *
	 **********************************************************************/

	/*
	 * Tags that are expected to occur.
	 */
	asn_outmost_tag_f  *outmost_tag;	/* <optional, internal> */
	const ber_tlv_tag_t *tags;	/* Effective tags sequence for this type */
	int tags_count;		/* Number of tags which are expected */
	const ber_tlv_tag_t *all_tags;/* Every tag for BER/containment */
	int all_tags_count;	/* Number of tags */

	/*
	 * An ASN.1 production type members (members of SEQUENCE, SET, CHOICE).
	 */
	struct asn_TYPE_member_s *elements;
	int elements_count;

	/*
	 * Additional information describing the type, used by appropriate
	 * functions above.
	 */
	const void *specifics;
} asn_TYPE_descriptor_t;

/*
 * This type describes an element of the constructed type,
 * i.e. SEQUENCE, SET, CHOICE, etc.
 */
  enum asn_TYPE_flags_e {
	ATF_NOFLAGS,
	ATF_POINTER	= 0x01,	/* Represented by the pointer */
	ATF_OPEN_TYPE	= 0x02	/* ANY type, without meaningful tag */
  };
typedef struct asn_TYPE_member_s {
	enum asn_TYPE_flags_e flags;	/* Element's presentation flags */
	int optional;	/* Following optional members, including current */
	//int memb_offset;		/* Offset of the element */
	ber_tlv_tag_t tag;		/* Outmost (most immediate) tag */
	int tag_mode;		/* IMPLICIT/no/EXPLICIT tag at current level */
	asn_TYPE_descriptor_t *type;	/* Member type descriptor */
	asn_constr_check_f *memb_constraints;	/* Constraints validator */
	int (*default_value)(int setval, void **sptr);	/* DEFAULT <value> */
	const char *name;			/* ASN.1 identifier of the element */
} asn_TYPE_member_t;

/*
 * BER tag to element number mapping.
 */
typedef struct asn_TYPE_tag2member_s {
	ber_tlv_tag_t el_tag;	/* Outmost tag of the member */
	int el_no;		/* Index of the associated member, base 0 */
	int toff_first;		/* First occurence of the el_tag, relative */
	int toff_last;		/* Last occurence of the el_tag, relatvie */
} asn_TYPE_tag2member_t;

#endif	/* _CONSTR_TYPE_HPP_ */
