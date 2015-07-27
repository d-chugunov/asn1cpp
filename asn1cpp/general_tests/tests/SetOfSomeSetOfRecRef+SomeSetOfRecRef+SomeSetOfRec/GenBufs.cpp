#include "GenBufs.hpp"
#include "SetOfSomeSetOfRecRef.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetOfSomeSetOfRecRef_t val1_1;
  memset(&val1_1, 0, sizeof(val1_1));
  
  struct SomeSetOfRec val1;
  memset(&val1, 0, sizeof(val1));
  asn_set_add(&val1.list, &val1_1);
  
  struct SomeSetOfRec val2;
  memset(&val2, 0, sizeof(val2));
  
  SetOfSomeSetOfRecRef_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_set_add(&rec.list, &val1);
  asn_set_add(&rec.list, &val2);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetOfSomeSetOfRecRef, &rec, (void*)buf.data(), buf.size());
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