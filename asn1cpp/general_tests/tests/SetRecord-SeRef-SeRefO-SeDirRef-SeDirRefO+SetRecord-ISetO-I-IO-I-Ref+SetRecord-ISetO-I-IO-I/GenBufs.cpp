#include "GenBufs.hpp"
#include "SetRecord-SeRef-SeRefO-SeDirRef-SeDirRefO.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.ref1.set = (struct SetRecord_ISetO_I_IO_I_t::set*)malloc(sizeof(struct SetRecord_ISetO_I_IO_I_t::set));
  memset(rec.ref1.set, 0, sizeof(*rec.ref1.set));
  rec.ref1.set->type = 123;
  rec.ref1.set->type2 = NULL;
  rec.ref1.set->type3 = 92367624;
  
  rec.ref3.set = (struct SetRecord_ISetO_I_IO_I_t::set*)malloc(sizeof(struct SetRecord_ISetO_I_IO_I_t::set));
  memset(rec.ref3.set, 0, sizeof(*rec.ref3.set));
  rec.ref3.set->type = 123;
  rec.ref3.set->type2 = NULL;
  rec.ref3.set->type3 = 92367624;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf1");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf2() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.ref1.set = (struct SetRecord_ISetO_I_IO_I_t::set*)malloc(sizeof(struct SetRecord_ISetO_I_IO_I_t::set));
  memset(rec.ref1.set, 0, sizeof(*rec.ref1.set));
  rec.ref1.set->type = 123;
  rec.ref1.set->type2 = (long*)malloc(sizeof(*rec.ref1.set->type2));
  *rec.ref1.set->type2 = 635282;
  rec.ref1.set->type3 = 92367624;
  
  rec.ref2 = (SetRecord_ISetO_I_IO_I_Ref_t*)malloc(sizeof(SetRecord_ISetO_I_IO_I_Ref_t));
  memset(rec.ref2, 0, sizeof(*rec.ref2));
  rec.ref2->set = (struct SetRecord_ISetO_I_IO_I_t::set*)malloc(sizeof(struct SetRecord_ISetO_I_IO_I_t::set));
  memset(rec.ref2->set, 0, sizeof(*rec.ref2->set));
  rec.ref2->set->type = 123;
  rec.ref2->set->type2 = (long*)malloc(sizeof(*rec.ref2->set->type2));
  *rec.ref2->set->type2 = 635282;
  rec.ref2->set->type3 = 92367624;
  
  rec.ref3.set = (struct SetRecord_ISetO_I_IO_I_t::set*)malloc(sizeof(struct SetRecord_ISetO_I_IO_I_t::set));
  memset(rec.ref3.set, 0, sizeof(*rec.ref3.set));
  rec.ref3.set->type = 123;
  rec.ref3.set->type2 = (long*)malloc(sizeof(*rec.ref1.set->type2));
  *rec.ref3.set->type2 = 635282;
  rec.ref3.set->type3 = 92367624;
  
  rec.ref4 = (SetRecord_ISetO_I_IO_I_t*)malloc(sizeof(SetRecord_ISetO_I_IO_I_t));
  memset(rec.ref4, 0, sizeof(*rec.ref4));
  rec.ref4->set = (struct SetRecord_ISetO_I_IO_I_t::set*)malloc(sizeof(struct SetRecord_ISetO_I_IO_I_t::set));
  memset(rec.ref4->set, 0, sizeof(*rec.ref4->set));
  rec.ref4->set->type = 123;
  rec.ref4->set->type2 = (long*)malloc(sizeof(*rec.ref4->set->type2));
  *rec.ref4->set->type2 = 635282;
  rec.ref4->set->type3 = 92367624;
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf2");
    exit(0);
  }
  return std::move(buf);
}

std::vector<std::vector<uint8_t>> GenBufs() {
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(std::move(Buf1()));
  bufs.push_back(std::move(Buf2()));
  return std::move(bufs);
}