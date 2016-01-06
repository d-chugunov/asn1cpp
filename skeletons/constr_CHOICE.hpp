/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_CONSTR_CHOICE_HPP_
#define	_CONSTR_CHOICE_HPP_

#include <asn_application.hpp>
#include <AsnAbstractType.hpp>

typedef const struct asn_CHOICE_specifics_s {
	/*
	 * Tags to members mapping table.
	 */
	const asn_TYPE_tag2member_t *tag2el;
	int tag2el_count;

	/*
	 * Extensions-related stuff.
	 */
	int ext_start;		/* First member of extensions, or -1 */
} asn_CHOICE_specifics_t;


/*
 * Don't use this class. It's for internal purposes
 */ 
class constr_CHOICE : public asnStructCtx {
private:
  virtual void _setPresent(int present) = 0;
  virtual int _fetchPresent() const = 0;
  virtual AsnAbstractType* _getPtrOnMember(int itemIndex, bool createNew) = 0;
  virtual const AsnAbstractType* _getPtrOnMember(int itemIndex) const = 0;
protected:
  constr_CHOICE() = default;
  constr_CHOICE(const constr_CHOICE&) = delete;
  constr_CHOICE(constr_CHOICE&&) noexcept = delete;
  constr_CHOICE& operator =(const constr_CHOICE&) = default;
  constr_CHOICE& operator =(constr_CHOICE&&) noexcept = default;
public:
  virtual ~constr_CHOICE() noexcept { }
  friend asn_struct_print_f CHOICE_print;
  friend asn_constr_check_f CHOICE_constraint;
  friend ber_type_decoder_f CHOICE_decode_ber;
  friend der_type_encoder_f CHOICE_encode_der;
  friend asn_outmost_tag_f CHOICE_outmost_tag;
};

/*
 * A set specialized functions dealing with the CHOICE type.
 */
asn_struct_print_f CHOICE_print;
asn_constr_check_f CHOICE_constraint;
ber_type_decoder_f CHOICE_decode_ber;
der_type_encoder_f CHOICE_encode_der;
asn_outmost_tag_f CHOICE_outmost_tag;

#endif	/* _CONSTR_CHOICE_HPP_ */
