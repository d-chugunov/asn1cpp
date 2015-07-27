#include "GenBufs.hpp"
#include "SetRecord-ISetO-I-IO-I.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_ISetO_I_IO_I_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.set = (struct SetRecord_ISetO_I_IO_I_t::set*)malloc(sizeof(struct SetRecord_ISetO_I_IO_I_t::set));
  memset(rec.set, 0, sizeof(*rec.set));
  rec.set->type = 123;
  rec.set->type2 = NULL;
  rec.set->type3 = 92367624;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ISetO_I_IO_I, &rec, (void*)buf.data(), buf.size());
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
  SetRecord_ISetO_I_IO_I_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.set = (struct SetRecord_ISetO_I_IO_I_t::set*)malloc(sizeof(struct SetRecord_ISetO_I_IO_I_t::set));
  memset(rec.set, 0, sizeof(*rec.set));
  rec.set->type = 123;
  rec.set->type2 = (long*)malloc(sizeof(*rec.set->type2));
  *rec.set->type2 = 635282;
  rec.set->type3 = 92367624;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ISetO_I_IO_I, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf2");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf3() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_ISetO_I_IO_I_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ISetO_I_IO_I, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf3");
    exit(0);
  }
  return std::move(buf);
}

std::vector<std::vector<uint8_t>> GenBufs() {
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(std::move(Buf1()));
  bufs.push_back(std::move(Buf2()));
  bufs.push_back(std::move(Buf3()));
  return std::move(bufs);
}