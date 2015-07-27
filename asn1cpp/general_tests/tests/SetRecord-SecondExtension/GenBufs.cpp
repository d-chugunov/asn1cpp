#include "GenBufs.hpp"
#include "SetRecord-SecondExtension.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_SecondExtension_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.a = 123;
  rec.z = 567.123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_SecondExtension, &rec, (void*)buf.data(), buf.size());
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
  SetRecord_SecondExtension_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.a = 123;
  rec.c = (long*)malloc(sizeof(*rec.c));
  *rec.c = 546;
  rec.z = 567.123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_SecondExtension, &rec, (void*)buf.data(), buf.size());
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
  SetRecord_SecondExtension_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.a = 123;
  rec.c = (long*)malloc(sizeof(*rec.c));
  *rec.c = 546;
  rec.d = (struct SetRecord_SecondExtension_t::d*)malloc(sizeof(*rec.d));
  memset(rec.d, 0, sizeof(*rec.d));
  rec.d->e = 984;
  const char* str = "test string";
  rec.d->f.buf = (uint8_t*)str;
  rec.d->f.size = strlen(str);
  rec.d->y = (double*)malloc(sizeof(*rec.d->y));
  *rec.d->y = 746.123;
  rec.z = 567.123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_SecondExtension, &rec, (void*)buf.data(), buf.size());
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
