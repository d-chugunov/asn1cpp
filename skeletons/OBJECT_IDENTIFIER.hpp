/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_OBJECT_IDENTIFIER_HPP_
#define	_OBJECT_IDENTIFIER_HPP_

#include <asn_application.hpp>
#include <asn_codecs_prim.hpp>
#include <INTEGER.hpp>

template <asn_TYPE_descriptor_t* typeDescriptorPtr>
class _OBJECT_IDENTIFIER_BASE : public AsnPrimitiveType<typeDescriptorPtr> {
public:
  _OBJECT_IDENTIFIER_BASE() : AsnPrimitiveType<typeDescriptorPtr>() { }
  _OBJECT_IDENTIFIER_BASE(const _OBJECT_IDENTIFIER_BASE& other) : 
              AsnPrimitiveType<typeDescriptorPtr>(other) { }
  _OBJECT_IDENTIFIER_BASE(_OBJECT_IDENTIFIER_BASE&& other) noexcept : 
              AsnPrimitiveType<typeDescriptorPtr>(std::move(other)) { }
  _OBJECT_IDENTIFIER_BASE& operator =(const _OBJECT_IDENTIFIER_BASE& other) {
    AsnPrimitiveType<typeDescriptorPtr>::operator =(other);
    return *this;
  }
  _OBJECT_IDENTIFIER_BASE& operator =(_OBJECT_IDENTIFIER_BASE&& other) noexcept {
    AsnPrimitiveType<typeDescriptorPtr>::operator =(std::move(other));
    return *this;
  }
  using AsnPrimitiveType<typeDescriptorPtr>::operator =;
  virtual ~_OBJECT_IDENTIFIER_BASE() noexcept { }
  /*
   * Parse the OBJECT IDENTIFIER textual representation ("1.3.6.1.4.1.9363").
   * No arc can exceed the (0..signed_long_max) range (typically, 0..2G if L32).
   * This function is not specific to OBJECT IDENTIFIER, it may be used to parse
   * the RELATIVE-OID data, or any other data consisting of dot-separated
   * series of numeric values.
   *
   * If (oid_txt_length == -1), the strlen() will be invoked to determine the
   * size of the (oid_text) string.
   * 
   * After return, the optional (opt_oid_text_end) is set to the character after
   * the last parsed one. (opt_oid_text_end) is never less than (oid_text).
   * 
   * RETURN VALUES:
   *   -1:	Parse error.
   * >= 0:	Number of arcs contained in the OBJECT IDENTIFIER.
   */
  static int ParseArcs(const char *oid_text, std::vector<long>& arcs, 
                ssize_t oid_txt_length = -1,
                const char **opt_oid_text_end = 0);
  static int ParseArcs(const std::string& oid_text, std::vector<long>& arcs) {
    return ParseArcs(oid_text.c_str(), arcs, oid_text.size());
  }
  /*
   * Fills current object by parsing OBJECT IDENTIFIER textual representation.
   * RETURN VALUS:
   *    true: Parsed successfully
   *   false: Parse error
   */
  bool FromArcs(const char *oid_text, ssize_t oid_txt_length = -1, 
               const char **opt_oid_text_end = 0)
  {
    std::vector<long> arcs;
    int ret = ParseArcs(oid_text, arcs, oid_txt_length, opt_oid_text_end);
    if (ret > 0) {
      return SetLongArcs(arcs);
    } else
      return false;
  }
  bool FromArcs(const std::string& oid_text) {
    return FromArcs(oid_text.c_str(), oid_text.size());
  }
protected:
  virtual bool SetLongArcs(const std::vector<long>& arcs) = 0;
  
};

extern asn_TYPE_descriptor_t asn_DEF_OBJECT_IDENTIFIER;

asn_struct_print_f OBJECT_IDENTIFIER_print;
asn_constr_check_f OBJECT_IDENTIFIER_constraint;
der_type_encoder_f OBJECT_IDENTIFIER_encode_der;

/*
 * Internal functions.
 * Used by RELATIVE-OID implementation in particular.
 */
int OBJECT_IDENTIFIER_get_single_arc(const uint8_t *arcbuf, 
                             unsigned int arclen, signed int add, 
                             void *value, unsigned int value_size);
int OBJECT_IDENTIFIER_set_single_arc(uint8_t *arcbuf,
 const void *arcval, unsigned int arcval_size, int _prepared_order);
  
/*
 * Print the specified OBJECT IDENTIFIER arc. Returns the number of written digits
 */
ssize_t OBJECT_IDENTIFIER__dump_arc(const uint8_t *arcbuf, int arclen, int add,
	asn_app_consume_bytes_f *cb, void *app_key);


class OBJECT_IDENTIFIER : public _OBJECT_IDENTIFIER_BASE<&asn_DEF_OBJECT_IDENTIFIER> 
{
public:
  OBJECT_IDENTIFIER() : _OBJECT_IDENTIFIER_BASE<&asn_DEF_OBJECT_IDENTIFIER>() { }
  OBJECT_IDENTIFIER(const OBJECT_IDENTIFIER& other) : 
                 _OBJECT_IDENTIFIER_BASE<&asn_DEF_OBJECT_IDENTIFIER>(other) {  }
  OBJECT_IDENTIFIER(OBJECT_IDENTIFIER&& other) noexcept : 
      _OBJECT_IDENTIFIER_BASE<&asn_DEF_OBJECT_IDENTIFIER>(std::move(other)) { }
  OBJECT_IDENTIFIER& operator =(const OBJECT_IDENTIFIER& other) {
    _OBJECT_IDENTIFIER_BASE<&asn_DEF_OBJECT_IDENTIFIER>::operator=(other);
    return *this;
  }
  OBJECT_IDENTIFIER& operator =(OBJECT_IDENTIFIER&& other) noexcept {
    _OBJECT_IDENTIFIER_BASE<&asn_DEF_OBJECT_IDENTIFIER>::operator=(std::move(other));
    return *this;
  }
  using _OBJECT_IDENTIFIER_BASE::operator =;
  virtual ~OBJECT_IDENTIFIER() noexcept { }
  /*
   * This function fills an (arcs) array with OBJECT IDENTIFIER arcs
   * 
   * RETURN VALUES:
   * -1/EINVAL:	Invalid arguments (sizeof(ActType) <= 1). In that case 
   *            (arcs) will not be changed
   * -1/ERANGE:	One or more arcs have value out of array cell type range. In that 
   *            case (arcs) will contain first arcs
   * >=0:		Number of arcs contained in the OBJECT IDENTIFIER
   */
  template <typename ArcType>
  int GetArcs(std::vector<ArcType>& arcs) const;
  /*
   * This functions initializes the OBJECT IDENTIFIER object with
   * the given set of arcs.
   * The minimum of two arcs must be present; some restrictions apply.
   * RETURN VALUES:
   * -1/EINVAL:	Invalid arguments
   * -1/ERANGE:	The first two arcs do not conform to ASN.1 restrictions.
   * 0:		The object was initialized with new arcs.
   */
  template <typename ArcType>
  int SetArcs(const std::vector<ArcType>& arcs);
private:
  bool SetLongArcs(const std::vector<long>& arcs) override {
    return SetArcs(arcs) == 0;
  }
};

template <typename ArcType>
int OBJECT_IDENTIFIER::GetArcs(std::vector<ArcType>& arcs) const
{
  const std::vector<uint8_t>& oid = *this;
	//void *arcs_end = (char *)arcs + (arc_type_size * arc_slots);
	int num_arcs = 0;
	int startn = 0;
	int add = 0;
	size_t i;
  unsigned int arc_type_size = sizeof(ArcType);

	if(arc_type_size <= 1) {
		errno = EINVAL;
		return -1;
	}
  
  arcs.clear();
  

	for(i = 0; i < oid.size(); i++) {
		uint8_t b = oid[i];
		if((b & 0x80))			/* Continuation expected */
			continue;

		if(num_arcs == 0) {
			/*
			 * First two arcs are encoded through the backdoor.
			 */
			unsigned LE = 1;	/* Little endian */
			int first_arc;
			num_arcs++;

			if(i) first_arc = 2;
			else if(b <= 39) first_arc = 0;
			else if(b < 79)	first_arc = 1;
			else first_arc = 2;

			add = -40 * first_arc;
      arcs.push_back(0);
      ArcType& currentArc = arcs[arcs.size() - 1];
			*(unsigned char *)((char *)&currentArc
				+ ((*(char *)&LE)?0:(arc_type_size - 1)))
					= first_arc;
		}

    ArcType newArc;
    if(OBJECT_IDENTIFIER_get_single_arc(&oid[startn], i + 1 - startn, add, 
           &newArc, sizeof(ArcType))) {
      return -1;
    }
    arcs.push_back(newArc);
    startn = i + 1;
    add = 0;
      
		num_arcs++;
	}

	return num_arcs;
}

template <typename ArcType>
int OBJECT_IDENTIFIER::SetArcs(const std::vector<ArcType>& arcs) {
  std::vector<uint8_t>& oid = *this;
  oid.clear();
  unsigned int arc_type_size = sizeof(ArcType);
  unsigned int arc_slots = arcs.size();
	uint8_t *buf;
	uint8_t *bp;
	unsigned LE = 1;	/* Little endian (x86) */
	unsigned isLittleEndian = *((char *)&LE);
	unsigned int arc0;
	unsigned int arc1;
	unsigned size;
	unsigned i;

	if(arc_type_size < 1
	|| arc_type_size > 16
	|| arc_slots < 2) {
		errno = EINVAL;
		return -1;
	}
  
  arc0 = arcs[0];
  arc1 = arcs[1];

	/*
	 * The previous chapter left us with the first and the second arcs.
	 * The values are not precise (that is, they are valid only if
	 * they're less than 255), but OK for the purposes of making
	 * the sanity test below.
	 */
	if(arc0 <= 1) {
		if(arc1 >= 39) {
			/* 8.19.4: At most 39 subsequent values (including 0) */
			errno = ERANGE;
			return -1;
		}
	} else if(arc0 > 2) {
		/* 8.19.4: Only three values are allocated from the root node */
		errno = ERANGE;
		return -1;
	}
	/*
	 * After above tests it is known that the value of arc0 is completely
	 * trustworthy (0..2). However, the arc1's value is still meaningless.
	 */

	/*
	 * Roughly estimate the maximum size necessary to encode these arcs.
	 * This estimation implicitly takes in account the following facts,
	 * that cancel each other:
	 * 	* the first two arcs are encoded in a single value.
	 * 	* the first value may require more space (+1 byte)
	 * 	* the value of the first arc which is in range (0..2)
	 */
	size = ((arc_type_size * CHAR_BIT + 6) / 7) * arc_slots;
  oid.resize(size + 1);
  buf = bp = static_cast<uint8_t*>(oid.data());

  const char* arcs_ptr = reinterpret_cast<const char*>(arcs.data());
	/*
	 * Encode the first two arcs.
	 * These require special treatment.
	 */
	{
		uint8_t *tp;
		uint8_t first_value[1 + 16];	/* of two arcs */
		uint8_t *fv = first_value;

		/*
		 * Simulate first_value = arc0 * 40 + arc1;
		 */
		/* Copy the second (1'st) arcs[1] into the first_value */
		*fv++ = 0;
		arcs_ptr = ((const char *)arcs_ptr) + arc_type_size;
		if(isLittleEndian) {
			const uint8_t *aend = (const unsigned char *)arcs_ptr - 1;
			const uint8_t *a1 = (const unsigned char *)arcs_ptr + arc_type_size - 1;
			for(; a1 > aend; fv++, a1--) *fv = *a1;
		} else {
			const uint8_t *a1 = (const uint8_t *)arcs_ptr;
			const uint8_t *aend = a1 + arc_type_size;
			for(; a1 < aend; fv++, a1++) *fv = *a1;
		}
		/* Increase the first_value by arc0 */
		arc0 *= 40;	/* (0..80) */
		for(tp = first_value + arc_type_size; tp >= first_value; tp--) {
			unsigned int v = *tp;
			v += arc0;
			*tp = v;
			if(v >= (1 << CHAR_BIT)) arc0 = v >> CHAR_BIT;
			else break;
		}

		assert(tp >= first_value);

		bp += OBJECT_IDENTIFIER_set_single_arc(bp, first_value,
			fv - first_value, 1);
 	}

	/*
	 * Save the rest of arcs.
	 */
	for(arcs_ptr = ((const char *)arcs_ptr) + arc_type_size, i = 2;
		i < arc_slots;
			i++, arcs_ptr = ((const char *)arcs_ptr) + arc_type_size) {
		bp += OBJECT_IDENTIFIER_set_single_arc(bp,
			arcs_ptr, arc_type_size, 0);
	}

	assert((unsigned)(bp - buf) <= size);

	/*
	 * Resize buffer.
	 */
  oid.resize(bp - buf);

	return 0;
}

template <asn_TYPE_descriptor_t* typeDescriptorPtr>
int _OBJECT_IDENTIFIER_BASE<typeDescriptorPtr>::ParseArcs(const char* oid_text, 
                      std::vector<long>& arcs, ssize_t oid_txt_length, 
                      const char** opt_oid_text_end)
{
	unsigned int arcs_count = 0;
	const char *oid_end;
	enum {
		ST_LEADSPACE,
		ST_TAILSPACE,
		ST_AFTERVALUE,	/* Next character ought to be '.' or a space */
		ST_WAITDIGITS,	/* Next character is expected to be a digit */
	} state = ST_LEADSPACE;

	if(!oid_text || oid_txt_length < -1) {
		if(opt_oid_text_end) *opt_oid_text_end = oid_text;
		errno = EINVAL;
		return -1;
	}
  
	if(oid_txt_length == -1)
		oid_txt_length = strlen(oid_text);
  
  arcs.clear();

#define	_OID_CAPTURE_ARC(oid_text, oid_end)		do {	\
	const char *endp = oid_end;				\
	long value;						\
	switch(asn_strtol_lim(oid_text, &endp, &value)) {	\
	case ASN_STRTOL_EXTRA_DATA:				\
	case ASN_STRTOL_OK:					\
    arcs.push_back(value);    \
		arcs_count++;					\
		oid_text = endp - 1;				\
		break;						\
	case ASN_STRTOL_ERROR_RANGE:				\
		if(opt_oid_text_end)				\
			*opt_oid_text_end = oid_text;		\
		errno = ERANGE;					\
		return -1;					\
	case ASN_STRTOL_ERROR_INVAL:				\
	case ASN_STRTOL_EXPECT_MORE:				\
		if(opt_oid_text_end)				\
			*opt_oid_text_end = oid_text;		\
		errno = EINVAL;					\
		return -1;					\
	}							\
  } while(0)

	for(oid_end = oid_text + oid_txt_length; oid_text<oid_end; oid_text++) {
	    switch(*oid_text) {
	    case 0x09: case 0x0a: case 0x0d: case 0x20:	/* whitespace */
		switch(state) {
		case ST_LEADSPACE:
		case ST_TAILSPACE:
			continue;
		case ST_AFTERVALUE:
			state = ST_TAILSPACE;
			continue;
		case ST_WAITDIGITS:
			break;	/* Digits expected after ".", got whitespace */
		}
		break;
	    case 0x2e:	/* '.' */
		switch(state) {
		case ST_LEADSPACE:
		case ST_TAILSPACE:
		case ST_WAITDIGITS:
			if(opt_oid_text_end)
				*opt_oid_text_end = oid_text;
			errno = EINVAL;	/* Broken OID */
			return -1;
			break;
		case ST_AFTERVALUE:
			state = ST_WAITDIGITS;
			continue;
		}
		break;
	    case 0x30: case 0x31: case 0x32: case 0x33: case 0x34:
	    case 0x35: case 0x36: case 0x37: case 0x38: case 0x39:
		switch(state) {
		case ST_TAILSPACE:
		case ST_AFTERVALUE:
			if(opt_oid_text_end)
				*opt_oid_text_end = oid_text;
			errno = EINVAL;	/* "1. 1" => broken OID */
			return -1;
		case ST_LEADSPACE:
		case ST_WAITDIGITS:
			_OID_CAPTURE_ARC(oid_text, oid_end);
			state = ST_AFTERVALUE;
			continue;
		}
		break;
	    default:
		/* Unexpected symbols */
		state = ST_WAITDIGITS;
		break;
	    } /* switch() */
	    break;
	} /* for() */


	if(opt_oid_text_end) *opt_oid_text_end = oid_text;

	/* Finalize last arc */
	switch(state) {
	case ST_LEADSPACE:
		return 0; /* No OID found in input data */
	case ST_WAITDIGITS:
		errno = EINVAL;	/* Broken OID */
		return -1;
	case ST_AFTERVALUE:
	case ST_TAILSPACE:
		return arcs_count;
	}

	errno = EINVAL;	/* Broken OID */
	return -1;
}


#endif	/* _OBJECT_IDENTIFIER_HPP_ */
