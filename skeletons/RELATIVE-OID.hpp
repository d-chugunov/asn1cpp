/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_RELATIVE_OID_HPP_
#define	_RELATIVE_OID_HPP_

#include <OBJECT_IDENTIFIER.hpp>


extern asn_TYPE_descriptor_t asn_DEF_RELATIVE_OID;

asn_struct_print_f RELATIVE_OID_print;

/* Implemented via OBJECT IDENTIFIER */

class RELATIVE_OID : public _OBJECT_IDENTIFIER_BASE<&asn_DEF_RELATIVE_OID> {
public:
  RELATIVE_OID() : _OBJECT_IDENTIFIER_BASE<&asn_DEF_RELATIVE_OID>() { }
  RELATIVE_OID(const RELATIVE_OID& other) : 
                    _OBJECT_IDENTIFIER_BASE<&asn_DEF_RELATIVE_OID>(other) {  }
  RELATIVE_OID(RELATIVE_OID&& other) noexcept : 
          _OBJECT_IDENTIFIER_BASE<&asn_DEF_RELATIVE_OID>(std::move(other)) { }
  RELATIVE_OID& operator =(const RELATIVE_OID& other) {
    _OBJECT_IDENTIFIER_BASE<&asn_DEF_RELATIVE_OID>::operator=(other);
    return *this;
  }
  RELATIVE_OID& operator =(RELATIVE_OID&& other) noexcept {
    _OBJECT_IDENTIFIER_BASE<&asn_DEF_RELATIVE_OID>::operator=(std::move(other));
    return *this;
  }
  using _OBJECT_IDENTIFIER_BASE::operator =;
  virtual ~RELATIVE_OID() noexcept { }
  /* See OBJECT_IDENTIFIER::GetArcs function */
  template <typename ArcType>
  int GetArcs(std::vector<ArcType>& arcs) const;
  /* See OBJECT_IDENTIFIER::SetArcs function */
  template <typename ArcType>
  int SetArcs(const std::vector<ArcType>& arcs);
private:
  bool SetLongArcs(const std::vector<long>& arcs) override {
    return SetArcs(arcs) == 0;
  }
};

template <typename ArcType>
int RELATIVE_OID::GetArcs(std::vector<ArcType>& arcs) const
{
  const std::vector<uint8_t>& roid(*this);
  unsigned int arc_type_size = sizeof(ArcType);
	int num_arcs = 0;
	int startn = 0;
	size_t i;
  
  arcs.clear();

	for(i = 0; i < roid.size(); i++) {
		uint8_t b = roid[i];
		if((b & 0x80))			/* Continuation expected */
			continue;

    ArcType newArc;
    if(OBJECT_IDENTIFIER_get_single_arc(&roid[startn], i + 1 - startn, 0,
                                        &newArc, arc_type_size)) {
      return -1;
    }
    arcs.push_back(newArc);
    num_arcs++;

		startn = i + 1;
	}

	return num_arcs;
}

template <typename ArcType>
int RELATIVE_OID::SetArcs(const std::vector<ArcType>& arcs)
{
  std::vector<uint8_t>& roid(*this);
  unsigned int arc_type_size = sizeof(ArcType);
  unsigned int arcs_slots = arcs.size();
	uint8_t *buf;
	uint8_t *bp;
	unsigned int size;
	unsigned int i;

	if(arc_type_size < 1) {
		errno = EINVAL;
		return -1;
	}
  
  roid.clear();

	/*
	 * Roughly estimate the maximum size necessary to encode these arcs.
	 */
	size = ((arc_type_size * CHAR_BIT + 6) / 7) * arcs_slots;
  roid.resize(size + 1);
  buf = bp = static_cast<uint8_t*>(roid.data());
  
  const char* arcs_ptr = reinterpret_cast<const char*>(arcs.data());

	/*
	 * Encode the arcs.
	 */
	for(i = 0; i < arcs_slots; i++, arcs_ptr = ((char *)arcs_ptr) + arc_type_size) 
  {
		bp += OBJECT_IDENTIFIER_set_single_arc(bp, arcs_ptr, arc_type_size, 0);
	}

	assert((unsigned)(bp - buf) <= size);

	/*
	 * Resize buffer.
	 */
  roid.resize(bp - buf);

	return 0;
}

#endif	/* _RELATIVE_OID_HPP_ */
