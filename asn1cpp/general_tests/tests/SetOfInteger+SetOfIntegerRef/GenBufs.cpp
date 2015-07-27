#include "GenBufs.hpp"
#include "SetOfInteger.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  long val1 = 1;
  long val2 = 2;
  long val3 = 3;
  SetOfInteger_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_set_add(&rec.list, &val1);
  asn_set_add(&rec.list, &val2);
  asn_set_add(&rec.list, &val3);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetOfInteger, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf1");
    exit(0);
  }
  return std::move(buf);
}

std::vector<std::vector<uint8_t>> GenBufs() {
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(std::move(Buf1()));
  return std::move(bufs);
}