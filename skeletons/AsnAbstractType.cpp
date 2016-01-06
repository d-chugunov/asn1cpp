/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */

#include <AsnAbstractType.hpp>

asn_dec_rval_t AsnAbstractType::_DecodeBer(const uint8_t* buf, size_t size, 
        asn_codec_ctx_t* opt_codec_ctx, asn_TYPE_descriptor_t* td, 
        int tag_mode)
{
  if (RC_OK == _lastBerDecodingResult) {
    //Since last decoding was successful, right now we are again decoding 
    //this structure. Therefore we have to start with a blank page
    Clear();
  }
#ifdef DEBUG
  if (td->ber_decoder) {
#endif
    asn_dec_rval_t rval;
    void* _pointerToMyself = static_cast<AsnAbstractType*>(this);
    rval = td->ber_decoder(opt_codec_ctx, td, &_pointerToMyself, buf, size, tag_mode);
    _lastBerDecodingResult = rval.code;
    return rval;
#ifdef DEBUG
  } else {
    //If the system doesn't contain mistakes it shouldn't be executed
    throw std::runtime_error("ber_decoder of type descriptor is null in DecodeBer.");
  }
#endif
}

asn_enc_rval_t AsnAbstractType::EncodeDer(std::vector<uint8_t>& buffer) const {
  buffer.resize(0);
  return _EncodeDer(this->_getDefaultTypeDescriptorPtr(), 0, 0, _EncodeDerBufferCb, &buffer);
}

asn_enc_rval_t AsnAbstractType::EncodeDer(std::ostream& out) const {
  return _EncodeDer(this->_getDefaultTypeDescriptorPtr(), 0, 0, _EncodeDerOstreamCb, &out);
}

asn_enc_rval_t AsnAbstractType::_EncodeDer(asn_TYPE_descriptor_t *td, 
                        int tag_mode, ber_tlv_tag_t tag, 
                        asn_app_consume_bytes_f *consume_bytes, void *app_key) const
{
#ifdef DEBUG
  if (td->der_encoder) {
#endif
    void* _pointerToMyself = const_cast<AsnAbstractType*>(static_cast<const AsnAbstractType*>(this));
    return td->der_encoder(td, _pointerToMyself, tag_mode, tag, consume_bytes, app_key);
#ifdef DEBUG
  } else {
    //If the system doesn't contain mistakes it shouldn't be executed
    throw std::runtime_error("der_encoder of type descriptor is null in _EncodeDer.");
  }
#endif 
}

bool AsnAbstractType::Print(std::ostream& out) const {
  return !_Print(this->_getDefaultTypeDescriptorPtr(), 1, _PrintOstreamCb, &out);
}

int AsnAbstractType::_Print(asn_TYPE_descriptor_t* td, int ilevel, 
                          asn_app_consume_bytes_f* cb, void* app_key) const
{
  void* _pointerToMyself = const_cast<AsnAbstractType*>(static_cast<const AsnAbstractType*>(this));
#ifdef ENABLE_ANOTHER_PRINT_FUNC
  if (this->_anotherPrintFunc)
    return this->_anotherPrintFunc(td, _pointerToMyself, ilevel, cb, app_key);
#endif
  
#ifdef DEBUG
  if (td->print_struct) {
#endif
    return td->print_struct(td, _pointerToMyself, ilevel, cb, app_key);
#ifdef DEBUG
  } else {
    //If the system doesn't contain mistakes it shouldn't be executed
    throw std::runtime_error("print_type of type descriptor is null in _Print.");
  }
#endif
}

bool AsnAbstractType::CheckConstraints(asn_app_constraint_failed_f* ctfailcb, void* app_key) const {
  return !_CheckConstraints(0, this->_getDefaultTypeDescriptorPtr(), ctfailcb, app_key);
}

int AsnAbstractType::_CheckConstraints(asn_constr_check_f *memb_constraints, asn_TYPE_descriptor_t* td, 
               asn_app_constraint_failed_f* ctfailcb, void* app_key) const 
{
  if (!memb_constraints)
    memb_constraints = td->check_constraints;
  
#ifdef DEBUG
  if (memb_constraints) {
#endif
    void* _pointerToMyself = const_cast<AsnAbstractType*>(static_cast<const AsnAbstractType*>(this));
    return memb_constraints(td, _pointerToMyself, ctfailcb, app_key);
#ifdef DEBUG
  } else {
    //If the system doesn't contain mistakes it shouldn't be executed
    throw std::runtime_error("check_constraints of type descriptor is null in CheckConstraints.");
  }
#endif
}

int AsnAbstractType::_EncodeDerBufferCb(const void* buffer, size_t size, void* key) {
  std::vector<uint8_t>* buf = static_cast<std::vector<uint8_t>*>(key);
  buf->insert(buf->end(), static_cast<const char*>(buffer), 
                          static_cast<const char*>(buffer) + size);
  return 0;
}

int AsnAbstractType::_EncodeDerOstreamCb(const void* buffer, size_t size, void* key) {
  std::ostream* pStream = (std::ostream*)key;
  pStream->write((const char*)buffer, size);
  if(!pStream->good())
    return -1;
  return 0;
}

int AsnAbstractType::_PrintOstreamCb(const void* buffer, size_t size, void* key) {
  std::ostream* pStream = (std::ostream*)key;
  pStream->write((const char*)buffer, size);
  if(!pStream->good())
    return -1;
  return 0;
}

std::ostream& operator <<(std::ostream& out, const AsnAbstractType& asnType) {
  if (!asnType.Print(out))
    out.setstate(std::ios::failbit);
  return out;
}

