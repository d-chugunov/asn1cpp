/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_CONSTR_SET_HPP_
#define	_CONSTR_SET_HPP_

#include <asn_application.hpp>
#include <AsnAbstractType.hpp>


typedef const struct asn_SET_specifics_s {
	/*
	 * Tags to members mapping table (sorted).
	 * Sometimes suitable for DER encoding (untagged CHOICE is present);
	 * if so, tag2el_count will be greater than td->elements_count.
	 */
	const asn_TYPE_tag2member_t *tag2el;
	int tag2el_count;

	/*
	 * Extensions-related stuff.
	 */
	int extensible;				/* Whether SET is extensible */
	const unsigned int *_mandatory_elements;	/* Bitmask of mandatory ones */
} asn_SET_specifics_t;

/*
 * Don't use this class. It's for internal purposes
 */ 
class constr_SET : public asnStructCtx {
protected:
  /* Presence bitmask */
  std::vector<unsigned int> _presenceMap;
protected:
  constr_SET(size_t presenceMapSize) : _presenceMap(presenceMapSize, 0) { }
  constr_SET(const constr_SET& other) = delete;
  constr_SET(constr_SET&& other) = delete;
  constr_SET& operator =(const constr_SET& other) {
    _presenceMap = other._presenceMap;
    asnStructCtx::operator =(other);
    return *this;
  }
  constr_SET& operator =(constr_SET&& other) noexcept {
    _presenceMap.swap(other._presenceMap);
    other._presenceMap.assign(other._presenceMap.size(), 0);
    asnStructCtx::operator=(std::move(other));
    return *this;
  }
private:
  /*
   * Figure out whether the SET member indicated by PR_x has already been decoded.
   * It is very simple bitfield test, despite its visual complexity.
   * These functions are only used for decoding purposes, don't use them.
   */
  bool _isPresent(int PR_x) const {
    return _presenceMap[(PR_x)	/ (8 * sizeof(unsigned int))]
          & (1 << ((8 * sizeof(unsigned int)) - 1 
            - ((PR_x) % (8 * sizeof(unsigned int)))));
  }
  void _makePresent(int PR_x) {
    _presenceMap[(PR_x)	/ (8 * sizeof(unsigned int))]
          |= (1 << ((8 * sizeof(unsigned int)) - 1
          - ((PR_x) % (8 * sizeof(unsigned int)))));
  }
  const std::vector<unsigned int>& _getPresenceMap() const {
    return _presenceMap;
  }
  virtual AsnAbstractType* _getPtrOnMember(int itemIndex, bool createNew) = 0;
  virtual const AsnAbstractType* _getPtrOnMember(int itemIndex) const = 0;
public:
  virtual ~constr_SET() noexcept { }
  friend asn_struct_print_f SET_print;
  friend asn_constr_check_f SET_constraint;
  friend ber_type_decoder_f SET_decode_ber;
  friend der_type_encoder_f SET_encode_der;
  friend int _SET_is_populated(asn_TYPE_descriptor_t *td, void *st);

};

/*
 * A set specialized functions dealing with the SET type.
 */
asn_struct_print_f SET_print;
asn_constr_check_f SET_constraint;
ber_type_decoder_f SET_decode_ber;
der_type_encoder_f SET_encode_der;

#endif	/* _CONSTR_SET_HPP_ */
