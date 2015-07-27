/*
 * Copyright (c) 2014-2015 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_CONSTR_SET_OF_HPP_
#define	_CONSTR_SET_OF_HPP_

#include <asn_application.hpp>
#include <AsnAbstractType.hpp>

//Don't use this class. It's only for internal purposes
class constr_SET_OF : public asnStructCtx {
public:
  virtual size_t _size() const = 0;
private:
  virtual AsnAbstractType* _emplaceBack() = 0;
  virtual AsnAbstractType* _getPtrOnMember(int itemIndex) = 0;
  virtual const AsnAbstractType* _getPtrOnMember(int itemIndex) const = 0;
protected:
  constr_SET_OF() = default;
  constr_SET_OF(const constr_SET_OF&) = default;
  constr_SET_OF(constr_SET_OF&&) noexcept = default;
  constr_SET_OF& operator =(const constr_SET_OF&) = default;
  constr_SET_OF& operator =(constr_SET_OF&&) noexcept = default;
public:
  virtual ~constr_SET_OF() noexcept { }
  friend asn_struct_print_f SET_OF_print;
  friend asn_constr_check_f SET_OF_constraint;
  friend ber_type_decoder_f SET_OF_decode_ber;
  friend der_type_encoder_f SET_OF_encode_der;
  friend der_type_encoder_f SEQUENCE_OF_encode_der;
};

/*
 * A set specialized functions dealing with the SET OF type.
 */
asn_struct_print_f SET_OF_print;
asn_constr_check_f SET_OF_constraint;
ber_type_decoder_f SET_OF_decode_ber;
der_type_encoder_f SET_OF_encode_der;

#endif	/* _CONSTR_SET_OF_HPP_ */
