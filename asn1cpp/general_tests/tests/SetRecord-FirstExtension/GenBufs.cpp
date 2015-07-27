#include "GenBufs.hpp"
#include "SetRecord-FirstExtension.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_FirstExtension_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.a = 123;
  rec.d = 567.123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_FirstExtension, &rec, (void*)buf.data(), buf.size());
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
  SetRecord_FirstExtension_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.a = 123;
  rec.d = 567.123;
  rec.b = (BOOLEAN_t*)malloc(sizeof(*rec.b));
  rec.c = (long*)malloc(sizeof(*rec.c));
  *rec.b = 1;
  *rec.c = 9374;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_FirstExtension, &rec, (void*)buf.data(), buf.size());
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
  bufs.push_back(std::move(Buf2()));
  return std::move(bufs);
}
