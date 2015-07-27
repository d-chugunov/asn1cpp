/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.hpp>
#include <OCTET_STRING.hpp>
#include <BIT_STRING.hpp>	/* for .bits_unused member */
#include <errno.h>

#include "asn_codecs_prim.hpp"

/*
 * OCTET STRING basic type description.
 */
static const ber_tlv_tag_t asn_DEF_OCTET_STRING_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))
};
static const asn_OCTET_STRING_specifics_t asn_DEF_OCTET_STRING_specs = {
	asn_OCTET_STRING_specifics_t::ASN_OSUBV_STR
};
asn_TYPE_descriptor_t asn_DEF_OCTET_STRING = {
	"OCTET STRING",		/* Canonical name */
	"OCTET_STRING",		/* XML tag name */
	OCTET_STRING_print<OCTET_STRING, std::vector<uint8_t>>,	/* non-ascii stuff, generally */
	asn_generic_no_constraint,
	OCTET_STRING_decode_ber<OCTET_STRING, std::vector<uint8_t>>,
	OCTET_STRING_encode_der<OCTET_STRING, std::vector<uint8_t>>,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_OCTET_STRING_tags,
	sizeof(asn_DEF_OCTET_STRING_tags)
	  / sizeof(asn_DEF_OCTET_STRING_tags[0]),
	asn_DEF_OCTET_STRING_tags,	/* Same as above */
	sizeof(asn_DEF_OCTET_STRING_tags)
	  / sizeof(asn_DEF_OCTET_STRING_tags[0]),
	0, 0,	/* No members */
	&asn_DEF_OCTET_STRING_specs
};

#undef	_CH_PHASE
#undef	NEXT_PHASE
#undef	PREV_PHASE
#define	_CH_PHASE(ctx, inc) do {					\
		if(ctx->phase == 0)					\
			ctx->context = 0;				\
		ctx->phase += inc;					\
	} while(0)
#define	NEXT_PHASE(ctx)	_CH_PHASE(ctx, +1)
#define	PREV_PHASE(ctx)	_CH_PHASE(ctx, -1)

#undef	ADVANCE
#define	ADVANCE(num_bytes)	do {					\
		size_t num = (num_bytes);				\
		buf_ptr = ((const char *)buf_ptr) + num;		\
		size -= num;						\
		consumed_myself += num;					\
	} while(0)

#undef	RETURN
#define	RETURN(_code)	do {						\
		asn_dec_rval_t tmprval;					\
		tmprval.code = _code;					\
		tmprval.consumed = consumed_myself;			\
		return tmprval;						\
	} while(0)

#undef	APPEND
#define	APPEND(bufptr, bufsize)	do {					\
		size_t _bs = (bufsize);		/* Append size */	\
		size_t _ns = ctx->context;	/* Allocated now */	\
		size_t _es = st->size() + _bs;	/* Expected size */	\
		/* int is really a typeof(st->size): */			\
		if((int)_es < 0) RETURN(RC_FAIL);			\
		if(_ns <= _es) {					\
			/* Be nice and round to the memory allocator */	\
			do { _ns = _ns ? _ns << 1 : 16; }		\
			    while(_ns <= _es);				\
			/* int is really a typeof(st->size): */		\
			if((int)_ns < 0) RETURN(RC_FAIL);		\
      st->reserve(_ns);                  \
      ctx->context = _ns;                 \
			ASN_DEBUG("Reallocating into %ld", (long)_ns);	\
		}							\
    size_t oldSize = st->size();                  \
    st->resize(_es);                              \
		memcpy(const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(st->data())) + oldSize, bufptr, _bs);		\
		/* Convenient nul-termination */			\
    st->reserve(_es + 1);      \
		(*st)[_es] = '\0';					\
	} while(0)

/*
 * The main reason why ASN.1 is still alive is that too much time and effort
 * is necessary for learning it more or less adequately, thus creating a gut
 * necessity to demonstrate that aquired skill everywhere afterwards.
 * No, I am not going to explain what the following stuff is.
 */
struct _stack_el {
	ber_tlv_len_t	left;	/* What's left to read (or -1) */
	ber_tlv_len_t	got;	/* What was actually processed */
	int	cont_level;	/* Depth of subcontainment */
	int	want_nulls;	/* Want null "end of content" octets? */
	int	bits_chopped;	/* Flag in BIT STRING mode */
	ber_tlv_tag_t	tag;	/* For debugging purposes */
	struct _stack_el *prev;
	struct _stack_el *next;
};
struct _stack {
	struct _stack_el *tail;
	struct _stack_el *cur_ptr;
};

static struct _stack_el *
OS__add_stack_el(struct _stack *st) {
	struct _stack_el *nel;

	/*
	 * Reuse the old stack frame or allocate a new one.
	 */
	if(st->cur_ptr && st->cur_ptr->next) {
		nel = st->cur_ptr->next;
		nel->bits_chopped = 0;
		nel->got = 0;
		/* Retain the nel->cont_level, it's correct. */
	} else {
		nel = (struct _stack_el *)CALLOC(1, sizeof(struct _stack_el));
		if(nel == NULL)
			return NULL;
	
		if(st->tail) {
			/* Increase a subcontainment depth */
			nel->cont_level = st->tail->cont_level + 1;
			st->tail->next = nel;
		}
		nel->prev = st->tail;
		st->tail = nel;
	}

	st->cur_ptr = nel;

	return nel;
}

static struct _stack *
_new_stack() {
	return (struct _stack *)CALLOC(1, sizeof(struct _stack));
}

#define CAST_TO_BIT_STRING(bitString, asnAbstractTypeStruct)                  \
  BIT_STRING* bitString = static_cast<BIT_STRING*>(asnAbstractTypeStruct);

/*
 * Decode OCTET STRING type.
 */
template <class ValueType>
asn_dec_rval_t
OCTET_STRING_decode_ber_impl(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td, AsnAbstractType* structPtr,
	ValueType *st, asn_struct_ctx_t *ctx, const void *buf_ptr, size_t size, int tag_mode) {
	asn_OCTET_STRING_specifics_t *specs = td->specifics
				? (asn_OCTET_STRING_specifics_t *)td->specifics
				: &asn_DEF_OCTET_STRING_specs;
	asn_dec_rval_t rval;
	ssize_t consumed_myself = 0;
	struct _stack *stck;		/* Expectations stack structure */
	struct _stack_el *sel = 0;	/* Stack element */
	int tlv_constr;
	asn_OCTET_STRING_specifics_t::asn_OS_Subvariant type_variant = specs->subvariant;
  
	switch(ctx->phase) {
	case 0:
		/*
		 * Check tags.
		 */
		rval = ber_check_tags(opt_codec_ctx, td, ctx,
			buf_ptr, size, tag_mode, -1,
			&ctx->left, &tlv_constr);
		if(rval.code != RC_OK)
			return rval;

		if(tlv_constr) {
			/*
			 * Complex operation, requires stack of expectations.
			 */
			ctx->ptr = _new_stack();
			if(ctx->ptr) {
				stck = (struct _stack *)ctx->ptr;
			} else {
				RETURN(RC_FAIL);
			}
		} else {
			/*
			 * Jump into stackless primitive decoding.
			 */
			_CH_PHASE(ctx, 3);
			if(type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_ANY && tag_mode != 1)
				APPEND(buf_ptr, rval.consumed);
			ADVANCE(rval.consumed);
			goto phase3;
		}

		NEXT_PHASE(ctx);
		/* Fall through */
	case 1:
	phase1:
		/*
		 * Fill the stack with expectations.
		 */
		stck = (struct _stack *)ctx->ptr;
		sel = stck->cur_ptr;
	  do {
		ber_tlv_tag_t tlv_tag;
		ber_tlv_len_t tlv_len;
		ber_tlv_tag_t expected_tag;
		ssize_t tl, ll, tlvl;
				/* This one works even if (sel->left == -1) */
		ssize_t Left = ((!sel||(size_t)sel->left >= size)
					?(ssize_t)size:sel->left);


		ASN_DEBUG("%p, s->l=%ld, s->wn=%ld, s->g=%ld\n", sel,
			(long)(sel?sel->left:0),
			(long)(sel?sel->want_nulls:0),
			(long)(sel?sel->got:0)
		);
		if(sel && sel->left <= 0 && sel->want_nulls == 0) {
			if(sel->prev) {
				struct _stack_el *prev = sel->prev;
				if(prev->left != -1) {
					if(prev->left < sel->got)
						RETURN(RC_FAIL);
					prev->left -= sel->got;
				}
				prev->got += sel->got;
				sel = stck->cur_ptr = prev;
				if(!sel) break;
				tlv_constr = 1;
				continue;
			} else {
				sel = stck->cur_ptr = 0;
				break;	/* Nothing to wait */
			}
		}

		tl = ber_fetch_tag(buf_ptr, Left, &tlv_tag);
		ASN_DEBUG("fetch tag(size=%ld,L=%ld), %sstack, left=%ld, wn=%ld, tl=%ld",
			(long)size, (long)Left, sel?"":"!",
			(long)(sel?sel->left:0),
			(long)(sel?sel->want_nulls:0),
			(long)tl);
		switch(tl) {
		case -1: RETURN(RC_FAIL);
		case 0: RETURN(RC_WMORE);
		}

		tlv_constr = BER_TLV_CONSTRUCTED(buf_ptr);

		ll = ber_fetch_length(tlv_constr,
				(const char *)buf_ptr + tl,Left - tl,&tlv_len);
		ASN_DEBUG("Got tag=%s, tc=%d, left=%ld, tl=%ld, len=%ld, ll=%ld",
			ber_tlv_tag_string(tlv_tag), tlv_constr,
				(long)Left, (long)tl, (long)tlv_len, (long)ll);
		switch(ll) {
		case -1: RETURN(RC_FAIL);
		case 0: RETURN(RC_WMORE);
		}

		if(sel && sel->want_nulls
			&& ((const uint8_t *)buf_ptr)[0] == 0
			&& ((const uint8_t *)buf_ptr)[1] == 0)
		{

			ASN_DEBUG("Eat EOC; wn=%d--", sel->want_nulls);

			if(type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_ANY
			&& (tag_mode != 1 || sel->cont_level))
				APPEND("\0\0", 2);

			ADVANCE(2);
			sel->got += 2;
			if(sel->left != -1) {
				sel->left -= 2;	/* assert(sel->left >= 2) */
			}

			sel->want_nulls--;
			if(sel->want_nulls == 0) {
				/* Move to the next expectation */
				sel->left = 0;
				tlv_constr = 1;
			}

			continue;
		}

		/*
		 * Set up expected tags,
		 * depending on ASN.1 type being decoded.
		 */
		switch(type_variant) {
		case asn_OCTET_STRING_specifics_t::ASN_OSUBV_BIT:
			/* X.690: 8.6.4.1, NOTE 2 */
			/* Fall through */
		case asn_OCTET_STRING_specifics_t::ASN_OSUBV_STR:
		default:
			if(sel) {
				int level = sel->cont_level;
				if(level < td->all_tags_count) {
					expected_tag = td->all_tags[level];
					break;
				} else if(td->all_tags_count) {
					expected_tag = td->all_tags
						[td->all_tags_count - 1];
					break;
				}
				/* else, Fall through */
			}
			/* Fall through */
		case asn_OCTET_STRING_specifics_t::ASN_OSUBV_ANY:
			expected_tag = tlv_tag;
			break;
		}


		if(tlv_tag != expected_tag) {
			char buf[2][32];
			ber_tlv_tag_snprint(tlv_tag,
				buf[0], sizeof(buf[0]));
			ber_tlv_tag_snprint(td->tags[td->tags_count-1],
				buf[1], sizeof(buf[1]));
			ASN_DEBUG("Tag does not match expectation: %s != %s",
				buf[0], buf[1]);
			RETURN(RC_FAIL);
		}

		tlvl = tl + ll;	/* Combined length of T and L encoding */
		if((tlv_len + tlvl) < 0) {
			/* tlv_len value is too big */
			ASN_DEBUG("TLV encoding + length (%ld) is too big",
				(long)tlv_len);
			RETURN(RC_FAIL);
		}

		/*
		 * Append a new expectation.
		 */
		sel = OS__add_stack_el(stck);
		if(!sel) RETURN(RC_FAIL);

		sel->tag = tlv_tag;

		sel->want_nulls = (tlv_len==-1);
		if(sel->prev && sel->prev->left != -1) {
			/* Check that the parent frame is big enough */
			if(sel->prev->left < tlvl + (tlv_len==-1?0:tlv_len))
				RETURN(RC_FAIL);
			if(tlv_len == -1)
				sel->left = sel->prev->left - tlvl;
			else
				sel->left = tlv_len;
		} else {
			sel->left = tlv_len;
		}
		if(type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_ANY
		&& (tag_mode != 1 || sel->cont_level))
			APPEND(buf_ptr, tlvl);
		sel->got += tlvl;
		ADVANCE(tlvl);

		ASN_DEBUG("+EXPECT2 got=%ld left=%ld, wn=%d, clvl=%d",
			(long)sel->got, (long)sel->left,
			sel->want_nulls, sel->cont_level);

	  } while(tlv_constr);
		if(sel == NULL) {
			/* Finished operation, "phase out" */
			ASN_DEBUG("Phase out");
			_CH_PHASE(ctx, +3);
			break;
		}

		NEXT_PHASE(ctx);
		/* Fall through */
	case 2:
		stck = (struct _stack *)ctx->ptr;
		sel = stck->cur_ptr;
		ASN_DEBUG("Phase 2: Need %ld bytes, size=%ld, alrg=%ld, wn=%d",
			(long)sel->left, (long)size, (long)sel->got,
				sel->want_nulls);
	    {
		ber_tlv_len_t len;

		assert(sel->left >= 0);

		len = ((ber_tlv_len_t)size < sel->left)
				? (ber_tlv_len_t)size : sel->left;
		if(len > 0) {
			if(type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_BIT
			&& sel->bits_chopped == 0) {
        CAST_TO_BIT_STRING(bit_st, structPtr)
				/* Put the unused-bits-octet away */
        bit_st->SetBitsUnused(*(const uint8_t *)buf_ptr);
				APPEND(((const char *)buf_ptr+1), (len - 1));
				sel->bits_chopped = 1;
			} else {
				APPEND(buf_ptr, len);
			}
			ADVANCE(len);
			sel->left -= len;
			sel->got += len;
		}

		if(sel->left) {
			ASN_DEBUG("OS left %ld, size = %ld, wn=%d\n",
				(long)sel->left, (long)size, sel->want_nulls);
			RETURN(RC_WMORE);
		}

		PREV_PHASE(ctx);
		goto phase1;
	    }
		break;
	case 3:
	phase3:
		/*
		 * Primitive form, no stack required.
		 */
		assert(ctx->left >= 0);

		if(size < (size_t)ctx->left) {
			if(!size) RETURN(RC_WMORE);
			if(type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_BIT && !ctx->context) {
        CAST_TO_BIT_STRING(bit_st, structPtr)
				bit_st->SetBitsUnused(*(const uint8_t *)buf_ptr);
				ctx->left--;
				ADVANCE(1);
			}
			APPEND(buf_ptr, size);
			assert(ctx->context > 0);
			ctx->left -= size;
			ADVANCE(size);
			RETURN(RC_WMORE);
		} else {
			if(type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_BIT
			&& !ctx->context && ctx->left) {
        CAST_TO_BIT_STRING(bit_st, structPtr)
				bit_st->SetBitsUnused(*(const uint8_t *)buf_ptr);
				ctx->left--;
				ADVANCE(1);
			}
			APPEND(buf_ptr, ctx->left);
			ADVANCE(ctx->left);
			ctx->left = 0;

			NEXT_PHASE(ctx);
		}
		break;
	}

	if(sel) {
		ASN_DEBUG("3sel p=%p, wn=%d, l=%ld, g=%ld, size=%ld",
			sel->prev, sel->want_nulls,
			(long)sel->left, (long)sel->got, (long)size);
		if(sel->prev || sel->want_nulls > 1 || sel->left > 0) {
			RETURN(RC_WMORE);
		}
	}

	/*
	 * BIT STRING-specific processing.
	 */
	if(type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_BIT && st->size()) {
		/* Finalize BIT STRING: zero out unused bits. */
    CAST_TO_BIT_STRING(bit_st, structPtr)
		(*st)[st->size()-1] &= 0xff << bit_st->GetBitsUnused();
	}

	ASN_DEBUG("Took %ld bytes to encode %s: [%s]:%ld",
		(long)consumed_myself, td->name,
		(type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_STR) ? 
                          (char *)st->data() : "<data>",
		(long)st->size());

	RETURN(RC_OK);
}

template
asn_dec_rval_t
OCTET_STRING_decode_ber_impl<std::vector<uint8_t>>(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td, AsnAbstractType* structPtr,
	std::vector<uint8_t> *st, asn_struct_ctx_t *ctx, const void *buf_ptr, size_t size, int tag_mode);

template
asn_dec_rval_t
OCTET_STRING_decode_ber_impl<std::string>(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td, AsnAbstractType* structPtr,
	std::string *st, asn_struct_ctx_t *ctx, const void *buf_ptr, size_t size, int tag_mode);

/*
 * Encode OCTET STRING type using DER.
 */
template <class Type>
asn_enc_rval_t
OCTET_STRING_encode_der_impl(asn_TYPE_descriptor_t *td,
  void* sptr,
  AsnAbstractType* structPtr,
	Type *st,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
	asn_enc_rval_t er;
	asn_OCTET_STRING_specifics_t *specs = td->specifics
				? (asn_OCTET_STRING_specifics_t *)td->specifics
				: &asn_DEF_OCTET_STRING_specs;
	asn_OCTET_STRING_specifics_t::asn_OS_Subvariant type_variant = specs->subvariant;
	int fix_last_byte = 0;

	ASN_DEBUG("%s %s as OCTET STRING",
		cb?"Estimating":"Encoding", td->name);
  
	/*
	 * Write tags.
	 */
	if(type_variant != asn_OCTET_STRING_specifics_t::ASN_OSUBV_ANY || tag_mode == 1) {
		er.encoded = der_write_tags(td,
				(type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_BIT) + st->size(),
			tag_mode, type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_ANY, tag,
			cb, app_key);
		if(er.encoded == -1) {
			er.failed_type = td;
			er.structure_ptr = sptr;
			return er;
		}
	} else {
		/* Disallow: [<tag>] IMPLICIT ANY */
		assert(type_variant != asn_OCTET_STRING_specifics_t::ASN_OSUBV_ANY || tag_mode != -1);
		er.encoded = 0;
	}

	if(!cb) {
		er.encoded += (type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_BIT) + st->size();
		_ASN_ENCODED_OK(er);
	}

	/*
	 * Prepare to deal with the last octet of BIT STRING.
	 */
	if(type_variant == asn_OCTET_STRING_specifics_t::ASN_OSUBV_BIT) {
    CAST_TO_BIT_STRING(bit_st, structPtr)
		uint8_t b = bit_st->GetBitsUnused() & 0x07;
		if(b && st->size()) fix_last_byte = 1;
		_ASN_CALLBACK(&b, 1);
		er.encoded++;
	}

	/* Invoke callback for the main part of the buffer */
	_ASN_CALLBACK(st->data(), st->size() - fix_last_byte);

	/* The last octet should be stripped off the unused bits */
	if(fix_last_byte) {
    CAST_TO_BIT_STRING(bit_st, structPtr)
		uint8_t b = (*st)[st->size()-1] & (0xff << bit_st->GetBitsUnused());
		_ASN_CALLBACK(&b, 1);
	}

	er.encoded += st->size();
	_ASN_ENCODED_OK(er);
cb_failed:
	_ASN_ENCODE_FAILED;
}

template
asn_enc_rval_t
OCTET_STRING_encode_der_impl<std::vector<uint8_t>>(asn_TYPE_descriptor_t *td,
  void* sptr,
  AsnAbstractType* structPtr,
	std::vector<uint8_t> *st,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key);

template
asn_enc_rval_t
OCTET_STRING_encode_der_impl<std::string>(asn_TYPE_descriptor_t *td,
  void* sptr,
  AsnAbstractType* structPtr,
	std::string *st,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key);

void
OCTET_STRING_free_decode_time_stack(void*& ptr) {
  struct _stack *stck;
	/*
	 * Remove decode-time stack.
	 */
	stck = (struct _stack *)ptr;
	if(stck) {
		while(stck->tail) {
			struct _stack_el *sel = stck->tail;
			stck->tail = sel->prev;
			FREEMEM(sel);
		}
		FREEMEM(stck);
    ptr = 0;
	} 
}

void* OCTET_STRING_copy_decode_time_stack(void* ptr) {
  if (!ptr)
    return 0;
  struct _stack *stck;
  stck = (struct _stack *)ptr;
  struct _stack *newStack = 0;
  newStack = _new_stack();
  if (!newStack) 
    throw std::runtime_error("Unable to allocate memory for new stack in OCTET_STRING_copy_decode_time_stack");
  
  if (stck->tail) {  
    struct _stack_el *curEl = stck->tail;
    //moving to the beginning of stack
    while (curEl->prev)
      curEl = curEl->prev;
    //copying elements to the new stack
    while (curEl) {
      struct _stack_el *elem;
      elem = OS__add_stack_el(newStack);
      if (!elem) {
        void* stackPtr = newStack;
        OCTET_STRING_free_decode_time_stack(stackPtr);
        throw std::runtime_error("Unable to allocate memory for stack element in OCTET_STRING_copy_decode_time_stack");
      }
      elem->left = curEl->left;
      elem->got = curEl->got;
      elem->cont_level = curEl->cont_level;
      elem->want_nulls = curEl->want_nulls;
      elem->bits_chopped = curEl->bits_chopped;
      elem->tag = curEl->tag;
      
      curEl = curEl->next;
    }
    //now we have to fill newStack->cur_ptr correctly
    curEl = stck->tail;
    struct _stack_el *curNew = newStack->tail;
    while (curEl && curNew) {
      if (curEl == stck->cur_ptr) {
        newStack->cur_ptr = curNew;
        break;
      }
      curEl = curEl->prev;
      curNew = curNew->prev;
    }
  }
  return newStack;
}

