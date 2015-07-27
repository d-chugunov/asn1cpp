#include "GenBufs.hpp"
#include "SetRecord-ISet-CO-R-I-B.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_ISet_CO_R_I_B_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.set.boolean = 1;
  rec.set.choice = (struct SetRecord_ISet_CO_R_I_B_t::set::choice*)malloc(sizeof(*rec.set.choice));
  memset(rec.set.choice, 0, sizeof(*rec.set.choice));
  rec.set.choice->present = choice_PR_integer;
  rec.set.choice->choice.integer = 836404;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ISet_CO_R_I_B, &rec, (void*)buf.data(), buf.size());
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
  SetRecord_ISet_CO_R_I_B_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.set.boolean = 0;
  rec.set.choice = (struct SetRecord_ISet_CO_R_I_B_t::set::choice*)malloc(sizeof(*rec.set.choice));
  memset(rec.set.choice, 0, sizeof(*rec.set.choice));
  rec.set.choice->present = choice_PR_real;
  rec.set.choice->choice.real = 12374.123813;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ISet_CO_R_I_B, &rec, (void*)buf.data(), buf.size());
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
  SetRecord_ISet_CO_R_I_B_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.set.boolean = 1;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ISet_CO_R_I_B, &rec, (void*)buf.data(), buf.size());
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