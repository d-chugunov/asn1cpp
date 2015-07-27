#include "GenBufs.hpp"
#include "ChoiceWithExtensible.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  ChoiceWithExtensible_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.present = ChoiceWithExtensible_PR::ChoiceWithExtensible_PR_b;
  rec.choice.b = 123.432;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_ChoiceWithExtensible, &rec, (void*)buf.data(), buf.size());
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
  ChoiceWithExtensible_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.present = ChoiceWithExtensible_PR::ChoiceWithExtensible_PR_d;
  rec.choice.d = 1;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_ChoiceWithExtensible, &rec, (void*)buf.data(), buf.size());
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
  ChoiceWithExtensible_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.present = ChoiceWithExtensible_PR::ChoiceWithExtensible_PR_e;
  rec.choice.e = 123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_ChoiceWithExtensible, &rec, (void*)buf.data(), buf.size());
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
