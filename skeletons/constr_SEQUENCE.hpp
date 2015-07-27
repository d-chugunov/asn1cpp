/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_CONSTR_SEQUENCE_HPP_
#define	_CONSTR_SEQUENCE_HPP_

#include <asn_application.hpp>
#include <AsnAbstractType.hpp>

typedef const struct asn_SEQUENCE_specifics_s {
	/*
	 * Tags to members mapping table (sorted).
	 */
	const asn_TYPE_tag2member_t *tag2el;
	int tag2el_count;

	/*
	 * Description of an extensions group.
	 */
	int ext_after;		/* Extensions start after this member */
	int ext_before;		/* Extensions stop before this member */
} asn_SEQUENCE_specifics_t;

/*
 * Don't use this class. It's for internal purposes
 */ 
class constr_SEQUENCE : public asnStructCtx {
private:
  virtual AsnAbstractType* _getPtrOnMember(int itemIndex, bool createNew) = 0;
  virtual const AsnAbstractType* _getPtrOnMember(int itemIndex) const = 0;
protected:
  constr_SEQUENCE() = default;
  constr_SEQUENCE(const constr_SEQUENCE&) = delete;
  constr_SEQUENCE(constr_SEQUENCE&&) noexcept = delete;
  constr_SEQUENCE& operator =(const constr_SEQUENCE&) = default;
  constr_SEQUENCE& operator =(constr_SEQUENCE&&) noexcept = default;
public:
  virtual ~constr_SEQUENCE() noexcept { }
  friend asn_struct_print_f SEQUENCE_print;
  friend asn_constr_check_f SEQUENCE_constraint;
  friend ber_type_decoder_f SEQUENCE_decode_ber;
  friend der_type_encoder_f SEQUENCE_encode_der;
};


/*
 * A set specialized functions dealing with the SEQUENCE type.
 */
asn_struct_print_f SEQUENCE_print;
asn_constr_check_f SEQUENCE_constraint;
ber_type_decoder_f SEQUENCE_decode_ber;
der_type_encoder_f SEQUENCE_encode_der;

#endif	/* _CONSTR_SEQUENCE_HPP_ */
