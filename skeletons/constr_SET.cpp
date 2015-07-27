/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>

/* Check that all the mandatory members are present */
static int _SET_is_populated(asn_TYPE_descriptor_t *td, void *st);
#include <constr_SET.hpp>
#include <AsnAbstractType.hpp>


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
 * Tags are canonically sorted in the tag2element map.
 */
static int
_t2e_cmp(const void *ap, const void *bp) {
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
 * The decoder of the SET type.
 */
asn_dec_rval_t
SET_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
	void **struct_ptr, const void *ptr, size_t size, int tag_mode) {
	/*
	 * Bring closer parts of structure description.
	 */
	asn_SET_specifics_t *specs = (asn_SET_specifics_t *)td->specifics;
	asn_TYPE_member_t *elements = td->elements;

	/*
	 * Parts of the structure being constructed.
	 */
	void *st = *struct_ptr;	/* Target structure. */
	asn_struct_ctx_t *ctx;	/* Decoder context */

	ber_tlv_tag_t tlv_tag;	/* T from TLV */
	asn_dec_rval_t rval;	/* Return code from subparsers */

	ssize_t consumed_myself = 0;	/* Consumed bytes from ptr */
	int edx;			/* SET element's index */

	ASN_DEBUG("Decoding %s as SET", td->name);

	if(_ASN_STACK_OVERFLOW_CHECK(opt_codec_ctx))
		_ASN_DECODE_FAILED;

	/*
	 * Create the target structure if it is not present already.
	 */
	if(st == 0) {
		//st = *struct_ptr = CALLOC(1, specs->struct_size);
    ASN_DEBUG("No allocated memory for SET_decode_ber");
		if(st == 0) {
			RETURN(RC_FAIL);
		}
	}
  
  AsnAbstractType* abstractType = static_cast<AsnAbstractType*>(st);
  constr_SET* abstractSet = static_cast<constr_SET*>(abstractType);

	/*
	 * Restore parsing context.
	 */
	ctx = static_cast<asnStructCtx*>(abstractType)->_getStructCtx(); //ctx = (asn_struct_ctx_t *)((char *)st + specs->ctx_offset);
	
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

		rval = ber_check_tags(opt_codec_ctx, td, ctx, ptr, size,
			tag_mode, 1, &ctx->left, 0);
		if(rval.code != RC_OK) {
			ASN_DEBUG("%s tagging check failed: %d",
				td->name, rval.code);
			return rval;
		}

		if(ctx->left >= 0)
			ctx->left += rval.consumed; /* ?Substracted below! */
		ADVANCE(rval.consumed);

		NEXT_PHASE(ctx);

		ASN_DEBUG("Structure advertised %ld bytes, "
			"buffer contains %ld", (long)ctx->left, (long)size);

		/* Fall through */
	case 1:
		/*
		 * PHASE 1.
		 * From the place where we've left it previously,
		 * try to decode the next member from the list of
		 * this structure's elements.
		 * Note that elements in BER may arrive out of
		 * order, yet DER mandates that they shall arive in the
		 * canonical order of their tags. So, there is a room
		 * for optimization.
		 */
	  for(;; ctx->step = 0) {
		const asn_TYPE_tag2member_t *t2m;
		asn_TYPE_tag2member_t key;
		//void *memb_ptr;		/* Pointer to the member */
		//void **memb_ptr2;	/* Pointer to that pointer */
		ssize_t tag_len;	/* Length of TLV's T */

		if(ctx->step & 1) {
			edx = ctx->step >> 1;
			goto microphase2;
		}

		/*
		 * MICROPHASE 1: Synchronize decoding.
		 */

		if(ctx->left == 0)
			/*
			 * No more things to decode.
			 * Exit out of here and check whether all mandatory
			 * elements have been received (in the next phase).
			 */
			break;

		/*
		 * Fetch the T from TLV.
		 */
		tag_len = ber_fetch_tag(ptr, LEFT, &tlv_tag);
		switch(tag_len) {
		case 0: if(!SIZE_VIOLATION) RETURN(RC_WMORE);
			/* Fall through */
		case -1: RETURN(RC_FAIL);
		}

		if(ctx->left < 0 && ((const uint8_t *)ptr)[0] == 0) {
			if(LEFT < 2) {
				if(SIZE_VIOLATION)
					RETURN(RC_FAIL);
				else
					RETURN(RC_WMORE);
			} else if(((const uint8_t *)ptr)[1] == 0) {
				/*
				 * Found the terminator of the
				 * indefinite length structure.
				 * Invoke the generic finalization function.
				 */
				goto phase3;
			}
		}

		key.el_tag = tlv_tag;
		t2m = (const asn_TYPE_tag2member_t *)bsearch(&key,
				specs->tag2el, specs->tag2el_count,
				sizeof(specs->tag2el[0]), _t2e_cmp);
		if(t2m) {
			/*
			 * Found the element corresponding to the tag.
			 */
			edx = t2m->el_no;
			ctx->step = (edx << 1) + 1;
			ASN_DEBUG("Got tag %s (%s), edx %d",
				ber_tlv_tag_string(tlv_tag), td->name, edx);
		} else if(specs->extensible == 0) {
			ASN_DEBUG("Unexpected tag %s "
				"in non-extensible SET %s",
				ber_tlv_tag_string(tlv_tag), td->name);
			RETURN(RC_FAIL);
		} else {
			/* Skip this tag */
			ssize_t skip;

			ASN_DEBUG("Skipping unknown tag %s",
				ber_tlv_tag_string(tlv_tag));

			skip = ber_skip_length(opt_codec_ctx,
				BER_TLV_CONSTRUCTED(ptr),
				(const char *)ptr + tag_len, LEFT - tag_len);

			switch(skip) {
			case 0: if(!SIZE_VIOLATION) RETURN(RC_WMORE);
				/* Fall through */
			case -1: RETURN(RC_FAIL);
			}

			ADVANCE(skip + tag_len);
			continue;  /* Try again with the next tag */
		}

		/*
		 * MICROPHASE 2: Invoke the member-specific decoder.
		 */
	microphase2:

		/*
		 * Check for duplications: must not overwrite
		 * already decoded elements.
		 */
		//if(ASN_SET_ISPRESENT2((char *)st + specs->pres_offset, edx)) {
     if(abstractSet->_isPresent(edx)) {
			ASN_DEBUG("SET %s: Duplicate element %s (%d)",
				td->name, elements[edx].name, edx);
			RETURN(RC_FAIL);
		}
		
		/*
		 * Invoke the member fetch routine according to member's type
		 */
    rval = abstractSet->_getPtrOnMember(edx, true)->_DecodeBer(
                           static_cast<const uint8_t*>(ptr), LEFT, opt_codec_ctx, 
                           elements[edx].type, elements[edx].tag_mode);
		switch(rval.code) {
		case RC_OK:
      abstractSet->_makePresent(edx);
			break;
		case RC_WMORE: /* More data expected */
			if(!SIZE_VIOLATION) {
				ADVANCE(rval.consumed);
				RETURN(RC_WMORE);
			}
			/* Fail through */
		case RC_FAIL: /* Fatal error */
			RETURN(RC_FAIL);
		} /* switch(rval) */
		
		ADVANCE(rval.consumed);
	  }	/* for(all structure members) */

	phase3:
		ctx->phase = 3;
		/* Fall through */
	case 3:
	case 4:	/* Only 00 is expected */
		ASN_DEBUG("SET %s Leftover: %ld, size = %ld",
			td->name, (long)ctx->left, (long)size);

		/*
		 * Skip everything until the end of the SET.
		 */
		while(ctx->left) {
			ssize_t tl, ll;

			tl = ber_fetch_tag(ptr, LEFT, &tlv_tag);
			switch(tl) {
			case 0: if(!SIZE_VIOLATION) RETURN(RC_WMORE);
				/* Fall through */
			case -1: RETURN(RC_FAIL);
			}

			/*
			 * If expected <0><0>...
			 */
			if(ctx->left < 0
				&& ((const uint8_t *)ptr)[0] == 0) {
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
					ctx->phase = 4;
					continue;
				}
			}

			if(specs->extensible == 0 || ctx->phase == 4) {
				ASN_DEBUG("Unexpected continuation "
					"of a non-extensible type %s "
					"(ptr=%02x)",
					td->name, *(const uint8_t *)ptr);
				RETURN(RC_FAIL);
			}

			ll = ber_skip_length(opt_codec_ctx,
				BER_TLV_CONSTRUCTED(ptr),
				(const char *)ptr + tl, LEFT - tl);
			switch(ll) {
			case 0: if(!SIZE_VIOLATION) RETURN(RC_WMORE);
				/* Fall through */
			case -1: RETURN(RC_FAIL);
			}

			ADVANCE(tl + ll);
		}

		ctx->phase = 5;
	case 5:
		/* Check that all mandatory elements are present. */
		if(!_SET_is_populated(td, st))
			RETURN(RC_FAIL);

		NEXT_PHASE(ctx);
	}
	
	RETURN(RC_OK);
}

static int
_SET_is_populated(asn_TYPE_descriptor_t *td, void *st) {
	asn_SET_specifics_t *specs = (asn_SET_specifics_t *)td->specifics;
	int edx;
  constr_SET* abstractSet = 0;
  {
    AsnAbstractType* abstractType = static_cast<AsnAbstractType*>(st);
    abstractSet = static_cast<constr_SET*>(abstractType);
  }

	/*
	 * Check that all mandatory elements are present.
	 */
	for(edx = 0; edx < td->elements_count;
		edx += (8 * sizeof(specs->_mandatory_elements[0]))) {
		unsigned int midx, pres, must;

		midx = edx/(8 * sizeof(specs->_mandatory_elements[0]));
		pres = abstractSet->_getPresenceMap()[midx];
		must = sys_ntohl(specs->_mandatory_elements[midx]);

		if((pres & must) == must) {
			/*
			 * Yes, everything seems to be in place.
			 */
		} else {
			ASN_DEBUG("One or more mandatory elements "
				"of a SET %s %d (%08x.%08x)=%08x "
				"are not present",
				td->name,
				midx,
				pres,
				must,
				(~(pres & must) & must)
			);
			return 0;
		}
	}

	return 1;
}

/*
 * The DER encoder of the SET type.
 */
asn_enc_rval_t
SET_encode_der(asn_TYPE_descriptor_t *td,
	void *sptr, int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
	asn_SET_specifics_t *specs = (asn_SET_specifics_t *)td->specifics;
	size_t computed_size = 0;
	asn_enc_rval_t er;
	int t2m_build_own = (specs->tag2el_count != td->elements_count);
	const asn_TYPE_tag2member_t *t2m;
  asn_TYPE_tag2member_t *t2m_build;
	int t2m_count;
	ssize_t ret;
	int edx;
  
  AsnAbstractType* abstractType = static_cast<AsnAbstractType*>(sptr);
  constr_SET* abstractSet = static_cast<constr_SET*>(abstractType);

	/*
	 * Use existing, or build our own tags map.
	 */
	if(t2m_build_own) {
		t2m_build = (asn_TYPE_tag2member_t *)alloca(
				td->elements_count * sizeof(t2m_build[0]));
		if(!t2m_build) _ASN_ENCODE_FAILED; /* There are such platforms */
		t2m_count = 0;
	} else {
    t2m_build = NULL;
		/*
		 * There is no untagged CHOICE in this SET.
		 * Employ existing table.
		 */
	}

	/*
	 * Gather the length of the underlying members sequence.
	 */
  for(edx = 0; edx < td->elements_count; edx++) {
		asn_TYPE_member_t *elm = &td->elements[edx];
		asn_enc_rval_t tmper;
		const void *memb_ptr;

		/*
		 * Compute the length of the encoding of this member.
		 */
    memb_ptr = abstractSet->_getPtrOnMember(edx, false);
		if(elm->flags & ATF_POINTER) {
			if(!memb_ptr) {
				if(!elm->optional)
					/* Mandatory elements missing */
					_ASN_ENCODE_FAILED;
				if(t2m_build_own) {
					t2m_build[t2m_count].el_no = edx;
					t2m_build[t2m_count].el_tag = 0;
					t2m_count++;
				}
				continue;
			}
		}
    tmper = static_cast<const AsnAbstractType*>(memb_ptr)->_EncodeDer(elm->type, 
			elm->tag_mode, elm->tag,
			0, 0);
		if(tmper.encoded == -1)
			return tmper;
		computed_size += tmper.encoded;

		/*
		 * Remember the outmost tag of this member.
		 */
		if(t2m_build_own) {
			t2m_build[t2m_count].el_no = edx;
			t2m_build[t2m_count].el_tag = asn_TYPE_outmost_tag(
				elm->type, memb_ptr, elm->tag_mode, elm->tag);
			t2m_count++;
		} else {
			/*
			 * No dynamic sorting is necessary.
			 */
		}
	}
	/*
	 * Finalize order of the components.
	 */
	if(t2m_build_own) {
		/*
		 * Sort the underlying members according to their
		 * canonical tags order. DER encoding mandates it.
		 */
		qsort(t2m_build, t2m_count, sizeof(specs->tag2el[0]), _t2e_cmp);
		t2m = t2m_build;
	} else {
		/*
		 * Tags are already sorted by the compiler.
		 */
    t2m = specs->tag2el;
		t2m_count = specs->tag2el_count;
	}
  assert(t2m_count == td->elements_count);

	/*
	 * Encode the TLV for the sequence itself.
	 */
	ret = der_write_tags(td, computed_size, tag_mode, 1, tag, cb, app_key);
	if(ret == -1) _ASN_ENCODE_FAILED;
	er.encoded = computed_size + ret;

	if(!cb) _ASN_ENCODED_OK(er);

	/*
	 * Encode all members.
	 */
	for(edx = 0; edx < td->elements_count; edx++) {
		asn_TYPE_member_t *elm;
		asn_enc_rval_t tmper;
    AsnAbstractType* memb_ptr;

		/* Encode according to the tag order */
		elm = &td->elements[t2m[edx].el_no];
    
    memb_ptr = abstractSet->_getPtrOnMember(t2m[edx].el_no, false);
    if((elm->flags & ATF_POINTER) && !memb_ptr) 
			continue;

		tmper = memb_ptr->_EncodeDer(elm->type, 
			elm->tag_mode, elm->tag,
			cb, app_key);
		if(tmper.encoded == -1)
			return tmper;
		computed_size -= tmper.encoded;
	}

	if(computed_size != 0) {
		/*
		 * Encoded size is not equal to the computed size.
		 */
		_ASN_ENCODE_FAILED;
	}

	_ASN_ENCODED_OK(er);
}

int
SET_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
		asn_app_consume_bytes_f *cb, void *app_key) {
	int edx;
	int ret;
  
	if(!sptr) return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;
  
  const AsnAbstractType* abstractType = static_cast<const AsnAbstractType*>(sptr);
  const constr_SET* abstractSet = static_cast<const constr_SET*>(abstractType);

	/* Dump preamble */
	if(cb(td->name, strlen(td->name), app_key) < 0
	|| cb(" ::= {", 6, app_key) < 0)
		return -1;

	for(edx = 0; edx < td->elements_count; edx++) {
		asn_TYPE_member_t *elm = &td->elements[edx];
		const AsnAbstractType *memb_ptr;

    memb_ptr = abstractSet->_getPtrOnMember(edx);
		if(elm->flags & ATF_POINTER) {
			if(!memb_ptr) {
				if(elm->optional) continue;
				/* Print <absent> line */
				/* Fall through */
			}
		}

		_i_INDENT(1);

		/* Print the member's name and stuff */
		if(cb(elm->name, strlen(elm->name), app_key) < 0
		|| cb(": ", 2, app_key) < 0)
			return -1;

		/* Print the member itself */
    if (!memb_ptr) {
      /* Print <absent> line */
      ret = elm->type->print_struct(elm->type, 0, ilevel + 1,
        cb, app_key);
    } else {
      ret = memb_ptr->_Print(elm->type, ilevel + 1,
        cb, app_key);
    }
		if(ret) return ret;
	}

	ilevel--;
	_i_INDENT(1);

	return (cb("}", 1, app_key) < 0) ? -1 : 0;
  return -1;
}

int
SET_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
		asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	int edx;

	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
  
  const AsnAbstractType* abstractType = static_cast<const AsnAbstractType*>(sptr);
  const constr_SET* abstractSet = static_cast<const constr_SET*>(abstractType);

	/*
	 * Iterate over structure members and check their validity.
	 */
	for(edx = 0; edx < td->elements_count; edx++) {
		asn_TYPE_member_t *elm = &td->elements[edx];
		const AsnAbstractType *memb_ptr;
    
    memb_ptr = abstractSet->_getPtrOnMember(edx);

		if(elm->flags & ATF_POINTER) {
			if(!memb_ptr) {
				if(elm->optional)
					continue;
				_ASN_CTFAIL(app_key, td, sptr,
				"%s: mandatory element %s absent (%s:%d)",
				td->name, elm->name, __FILE__, __LINE__);
				return -1;
			}
		}
    
    int ret = memb_ptr->_CheckConstraints(elm->memb_constraints, elm->type, ctfailcb, app_key);
    if(ret) return ret;
    if(!elm->memb_constraints) {
			/*
			 * Cannot inherit it earlier:
			 * need to make sure we get the updated version.
			 */
			elm->memb_constraints = elm->type->check_constraints;
		}
	}

	return 0;
}
