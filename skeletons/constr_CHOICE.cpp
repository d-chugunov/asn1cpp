/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <constr_CHOICE.hpp>

#include "AsnAbstractType.hpp"

/*
 * Number of bytes left for this structure.
 * (ctx->left) indicates the number of bytes _transferred_ for the structure.
 * (size) contains the number of bytes in the buffer passed.
 */
#define	LEFT	((size<(size_t)ctx->left)?size:(size_t)ctx->left)

/*
 * If the subprocessor function returns with an indication that it wants
 * more data, it may well be a fatal decoding problem, because the
 * size is constrained by the <TLV>'s L, even if the buffer size allows
 * reading more data.
 * For example, consider the buffer containing the following TLVs:
 * <T:5><L:1><V> <T:6>...
 * The TLV length clearly indicates that one byte is expected in V, but
 * if the V processor returns with "want more data" even if the buffer
 * contains way more data than the V processor have seen.
 */
#define	SIZE_VIOLATION	(ctx->left >= 0 && (size_t)ctx->left <= size)

/*
 * This macro "eats" the part of the buffer which is definitely "consumed",
 * i.e. was correctly converted into local representation or rightfully skipped.
 */
#undef	ADVANCE
#define	ADVANCE(num_bytes)	do {		\
		size_t num = num_bytes;		\
		ptr = ((const char *)ptr) + num;\
		size -= num;			\
		if(ctx->left >= 0)		\
			ctx->left -= num;	\
		consumed_myself += num;		\
	} while(0)

/*
 * Switch to the next phase of parsing.
 */
#undef	NEXT_PHASE
#define	NEXT_PHASE(ctx)	do {			\
		ctx->phase++;			\
		ctx->step = 0;			\
	} while(0)

/*
 * Return a standardized complex structure.
 */
#undef	RETURN
#define	RETURN(_code)	do {			\
		rval.code = _code;		\
		rval.consumed = consumed_myself;\
		return rval;			\
	} while(0)

/*
 * Tags are canonically sorted in the tag to member table.
 */
static int
_search4tag(const void *ap, const void *bp) {
	const asn_TYPE_tag2member_t *a = (const asn_TYPE_tag2member_t *)ap;
	const asn_TYPE_tag2member_t *b = (const asn_TYPE_tag2member_t *)bp;

	int a_class = BER_TAG_CLASS(a->el_tag);
	int b_class = BER_TAG_CLASS(b->el_tag);

	if(a_class == b_class) {
		ber_tlv_tag_t a_value = BER_TAG_VALUE(a->el_tag);
		ber_tlv_tag_t b_value = BER_TAG_VALUE(b->el_tag);

		if(a_value == b_value)
			return 0;
		else if(a_value < b_value)
			return -1;
		else
			return 1;
	} else if(a_class < b_class) {
		return -1;
	} else {
		return 1;
	}
}

/*
 * The decoder of the CHOICE type.
 */
asn_dec_rval_t
CHOICE_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
	void **struct_ptr, const void *ptr, size_t size, int tag_mode) {
	/*
	 * Bring closer parts of structure description.
	 */
	asn_CHOICE_specifics_t *specs = (asn_CHOICE_specifics_t *)td->specifics;
	asn_TYPE_member_t *elements = td->elements;

	/*
	 * Parts of the structure being constructed.
	 */
	void *st = *struct_ptr;	/* Target structure. */
	asn_struct_ctx_t *ctx;	/* Decoder context */

	ber_tlv_tag_t tlv_tag;	/* T from TLV */
	ssize_t tag_len;	/* Length of TLV's T */
	asn_dec_rval_t rval;	/* Return code from subparsers */

	ssize_t consumed_myself = 0;	/* Consumed bytes from ptr */

	ASN_DEBUG("Decoding %s as CHOICE", td->name);

	/*
	 * Create the target structure if it is not present already.
	 */
	if(st == 0) {
    ASN_DEBUG("No allocated memory for CHOICE_decode_ber");
			RETURN(RC_FAIL);
	}
  
  AsnAbstractType* structPtr = static_cast<AsnAbstractType*>(*struct_ptr);
  
  constr_CHOICE* iChoice = static_cast<constr_CHOICE*>(structPtr);

	/*
	 * Restore parsing context.
	 */
	ctx = static_cast<asnStructCtx*>(structPtr)->_getStructCtx(); //(asn_struct_ctx_t *)((char *)st + specs->ctx_offset);
	
	/*
	 * Start to parse where left previously
	 */
	switch(ctx->phase) {
	case 0:
		/*
		 * PHASE 0.
		 * Check that the set of tags associated with given structure
		 * perfectly fits our expectations.
		 */

		if(tag_mode || td->tags_count) {
			rval = ber_check_tags(opt_codec_ctx, td, ctx, ptr, size,
				tag_mode, -1, &ctx->left, 0);
			if(rval.code != RC_OK) {
				ASN_DEBUG("%s tagging check failed: %d",
					td->name, rval.code);
				return rval;
			}

			if(ctx->left >= 0) {
				/* ?Substracted below! */
				ctx->left += rval.consumed;
			}
			ADVANCE(rval.consumed);
		} else {
			ctx->left = -1;
		}

		NEXT_PHASE(ctx);

		ASN_DEBUG("Structure consumes %ld bytes, buffer %ld",
			(long)ctx->left, (long)size);

		/* Fall through */
	case 1:
		/*
		 * Fetch the T from TLV.
		 */
		tag_len = ber_fetch_tag(ptr, LEFT, &tlv_tag);
		ASN_DEBUG("In %s CHOICE tag length %d", td->name, (int)tag_len);
		switch(tag_len) {
		case 0: if(!SIZE_VIOLATION) RETURN(RC_WMORE);
			/* Fall through */
		case -1: RETURN(RC_FAIL);
		}

		do {
			const asn_TYPE_tag2member_t *t2m;
			asn_TYPE_tag2member_t key;

			key.el_tag = tlv_tag;
			t2m = (const asn_TYPE_tag2member_t *)bsearch(&key,
					specs->tag2el, specs->tag2el_count,
					sizeof(specs->tag2el[0]), _search4tag);
			if(t2m) {
				/*
				 * Found the element corresponding to the tag.
				 */
				NEXT_PHASE(ctx);
				ctx->step = t2m->el_no;
				break;
			} else if(specs->ext_start == -1) {
				ASN_DEBUG("Unexpected tag %s "
					"in non-extensible CHOICE %s",
					ber_tlv_tag_string(tlv_tag), td->name);
				RETURN(RC_FAIL);
			} else {
				/* Skip this tag */
				ssize_t skip;

				ASN_DEBUG("Skipping unknown tag %s",
					ber_tlv_tag_string(tlv_tag));

				skip = ber_skip_length(opt_codec_ctx,
					BER_TLV_CONSTRUCTED(ptr),
					(const char *)ptr + tag_len,
					LEFT - tag_len);

				switch(skip) {
				case 0: if(!SIZE_VIOLATION) RETURN(RC_WMORE);
					/* Fall through */
				case -1: RETURN(RC_FAIL);
				}

				ADVANCE(skip + tag_len);
				RETURN(RC_OK);
			}
		} while(0);

	case 2:
		/*
		 * PHASE 2.
		 * Read in the element.
		 */
	    do {
		asn_TYPE_member_t *elm;/* CHOICE's element */
		elm = &elements[ctx->step];
		/* Set presence to be able to free it properly at any time */
    iChoice->_setPresent(ctx->step + 1);
		/*
		 * Invoke the member fetch routine according to member's type
		 */
    rval = iChoice->_getPtrOnMember(ctx->step, true)->_DecodeBer(
                                  static_cast<const uint8_t*>(ptr), LEFT, 
                                  opt_codec_ctx, elm->type, elm->tag_mode);
		switch(rval.code) {
		case RC_OK:
			break;
		case RC_WMORE: /* More data expected */
			if(!SIZE_VIOLATION) {
				ADVANCE(rval.consumed);
				RETURN(RC_WMORE);
			}
			RETURN(RC_FAIL);
		case RC_FAIL: /* Fatal error */
			RETURN(rval.code);
		} /* switch(rval) */
		
		ADVANCE(rval.consumed);
	  } while(0);

		NEXT_PHASE(ctx);

		/* Fall through */
	case 3:
		ASN_DEBUG("CHOICE %s Leftover: %ld, size = %ld, tm=%d, tc=%d",
			td->name, (long)ctx->left, (long)size,
			tag_mode, td->tags_count);

		if(ctx->left > 0) {
			/*
			 * The type must be fully decoded
			 * by the CHOICE member-specific decoder.
			 */
			RETURN(RC_FAIL);
		}

		if(ctx->left == -1
		&& !(tag_mode || td->tags_count)) {
			/*
			 * This is an untagged CHOICE.
			 * It doesn't contain nothing
			 * except for the member itself, including all its tags.
			 * The decoding is completed.
			 */
			NEXT_PHASE(ctx);
			break;
		}

		/*
		 * Read in the "end of data chunks"'s.
		 */
		while(ctx->left < 0) {
			ssize_t tl;

			tl = ber_fetch_tag(ptr, LEFT, &tlv_tag);
			switch(tl) {
			case 0: if(!SIZE_VIOLATION) RETURN(RC_WMORE);
				/* Fall through */
			case -1: RETURN(RC_FAIL);
			}

			/*
			 * Expected <0><0>...
			 */
			if(((const uint8_t *)ptr)[0] == 0) {
				if(LEFT < 2) {
					if(SIZE_VIOLATION)
						RETURN(RC_FAIL);
					else
						RETURN(RC_WMORE);
				} else if(((const uint8_t *)ptr)[1] == 0) {
					/*
					 * Correctly finished with <0><0>.
					 */
					ADVANCE(2);
					ctx->left++;
					continue;
				}
			} else {
				ASN_DEBUG("Unexpected continuation in %s",
					td->name);
				RETURN(RC_FAIL);
			}

			/* UNREACHABLE */
		}

		NEXT_PHASE(ctx);
	case 4:
		/* No meaningful work here */
		break;
	}
	
	RETURN(RC_OK);
}

asn_enc_rval_t
CHOICE_encode_der(asn_TYPE_descriptor_t *td, void *sptr,
		int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	asn_TYPE_member_t *elm;	/* CHOICE element */
	asn_enc_rval_t erval;
	size_t computed_size = 0;
	int present;

	if(!sptr) _ASN_ENCODE_FAILED;
  
  AsnAbstractType* structPtr = static_cast<AsnAbstractType*>(sptr);
  constr_CHOICE* iChoice = static_cast<constr_CHOICE*>(structPtr);

	ASN_DEBUG("%s %s as CHOICE",
		cb?"Encoding":"Estimating", td->name);

//	present = _fetch_present_idx(sptr,
//		specs->pres_offset, specs->pres_size);
  present = iChoice->_fetchPresent();

	/*
	 * If the structure was not initialized, it cannot be encoded:
	 * can't deduce what to encode in the choice type.
	 */
	if(present <= 0 || present > td->elements_count) {
		if(present == 0 && td->elements_count == 0) {
			/* The CHOICE is empty?! */
			erval.encoded = 0;
			_ASN_ENCODED_OK(erval);
		}
		_ASN_ENCODE_FAILED;
	}

	/*
	 * Seek over the present member of the structure.
	 */
  AsnAbstractType* memb_ptr = iChoice->_getPtrOnMember(present - 1, false);
	elm = &td->elements[present-1];
	if(elm->flags & ATF_POINTER) {
		if(!memb_ptr) {
			if(elm->optional) {
				erval.encoded = 0;
				_ASN_ENCODED_OK(erval);
			}
			/* Mandatory element absent */
			_ASN_ENCODE_FAILED;
		}
	} 

	/*
	 * If the CHOICE itself is tagged EXPLICIT:
	 * T ::= [2] EXPLICIT CHOICE { ... }
	 * Then emit the appropriate tags.
	 */
	if(tag_mode == 1 || td->tags_count) {
		/*
		 * For this, we need to pre-compute the member.
		 */
		ssize_t ret;

		/* Encode member with its tag */
    erval = memb_ptr->_EncodeDer(elm->type, elm->tag_mode, elm->tag, 0, 0);
		if(erval.encoded == -1)
			return erval;

		/* Encode CHOICE with parent or my own tag */
		ret = der_write_tags(td, erval.encoded, tag_mode, 1, tag,
			cb, app_key);
		if(ret == -1)
			_ASN_ENCODE_FAILED;
		computed_size += ret;
	}

	/*
	 * Encode the single underlying member.
	 */
	erval = memb_ptr->_EncodeDer(elm->type, elm->tag_mode, elm->tag, cb, app_key);
	if(erval.encoded == -1)
		return erval;

	ASN_DEBUG("Encoded CHOICE member in %ld bytes (+%ld)",
		(long)erval.encoded, (long)computed_size);

	erval.encoded += computed_size;

	return erval;
}

ber_tlv_tag_t
CHOICE_outmost_tag(const asn_TYPE_descriptor_t *td, const void *ptr, int tag_mode, ber_tlv_tag_t tag) {
	int present;

	assert(tag_mode == 0); (void)tag_mode;
	assert(tag == 0); (void)tag;

	/*
	 * Figure out which CHOICE element is encoded.
	 */
  const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(ptr);
  const constr_CHOICE* iChoice = static_cast<const constr_CHOICE*>(structPtr);
  present = iChoice->_fetchPresent();
	//present = _fetch_present_idx(ptr, specs->pres_offset, specs->pres_size);

	if(present > 0 || present <= td->elements_count) {
		const asn_TYPE_member_t *elm = &td->elements[present-1];
		const void *memb_ptr;

    memb_ptr = iChoice->_getPtrOnMember(present - 1);

		return asn_TYPE_outmost_tag(elm->type, memb_ptr,
			elm->tag_mode, elm->tag);
	} else {
		return (ber_tlv_tag_t)-1;
	}
}

int
CHOICE_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
		asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	int present;

	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
  
  const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
  const constr_CHOICE* iChoice = static_cast<const constr_CHOICE*>(structPtr);

	/*
	 * Figure out which CHOICE element is encoded.
	 */
	present = iChoice->_fetchPresent();
	if(present > 0 && present <= td->elements_count) {
		asn_TYPE_member_t *elm = &td->elements[present-1];
		const AsnAbstractType *memb_ptr;

    memb_ptr = iChoice->_getPtrOnMember(present - 1);
		if(elm->flags & ATF_POINTER) {
			if(!memb_ptr) {
				if(elm->optional)
					return 0;
				_ASN_CTFAIL(app_key, td, sptr,
					"%s: mandatory CHOICE element %s absent (%s:%d)",
					td->name, elm->name, __FILE__, __LINE__);
				return -1;
			}
		}
    
    int ret = memb_ptr->_CheckConstraints(elm->memb_constraints, elm->type, ctfailcb, app_key);
    if(!elm->memb_constraints) {
			/*
			 * Cannot inherit it earlier:
			 * need to make sure we get the updated version.
			 */
			elm->memb_constraints = elm->type->check_constraints;
		}
    return ret;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: no CHOICE element given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

int
CHOICE_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
		asn_app_consume_bytes_f *cb, void *app_key) {
	int present;

	if(!sptr) return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;
  
  const AsnAbstractType* structPtr = static_cast<const AsnAbstractType*>(sptr);
  const constr_CHOICE* iChoice = static_cast<const constr_CHOICE*>(structPtr);

	/*
	 * Figure out which CHOICE element is encoded.
	 */
  present = iChoice->_fetchPresent();

	/*
	 * Print that element.
	 */
	if(present > 0 && present <= td->elements_count) {
		asn_TYPE_member_t *elm = &td->elements[present-1];
		const AsnAbstractType *memb_ptr;

    memb_ptr = iChoice->_getPtrOnMember(present - 1);
		if(elm->flags & ATF_POINTER) {
			if(!memb_ptr) return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;
		}

		/* Print member's name and stuff */
		if(1) {
			if(cb(elm->name, strlen(elm->name), app_key) < 0
			|| cb(": ", 2, app_key) < 0)
				return -1;
		}

		return memb_ptr->_Print(elm->type, ilevel,
			cb, app_key);
	} else {
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;
	}
}

