#include "GenBufs.hpp"
#include "SequenceRecord-SecondExtension.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_SecondExtension_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.a = 123;
  rec.z = 567.123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_SecondExtension, &rec, (void*)buf.data(), buf.size());
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
  SequenceRecord_SecondExtension_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.a = 123;
  rec.c = (long*)malloc(sizeof(*rec.c));
  *rec.c = 546;
  rec.z = 567.123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_SecondExtension, &rec, (void*)buf.data(), buf.size());
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
  SequenceRecord_SecondExtension_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.a = 123;
  rec.c = (long*)malloc(sizeof(*rec.c));
  *rec.c = 546;
  rec.d = (struct SequenceRecord_SecondExtension_t::d*)malloc(sizeof(*rec.d));
  memset(rec.d, 0, sizeof(*rec.d));
  rec.d->e = 984;
  const char* str = "test string";
  rec.d->f.buf = (uint8_t*)str;
  rec.d->f.size = strlen(str);
  rec.d->y = (double*)malloc(sizeof(*rec.d->y));
  *rec.d->y = 746.123;
  rec.z = 567.123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_SecondExtension, &rec, (void*)buf.data(), buf.size());
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
//  uint8_t buf[] = {0x30, 0x30, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x02, 0x22, 0x30, 
//                    0x1c, 0x02, 0x02, 0x03, 0xd8, 0x09, 0x09, 0x80, 0xd7, 0x05, 
//                    0xd4, 0x3e, 0xf9, 0xdb, 0x22, 0xd1, 0x16, 0x0b, 0x74, 0x65, 
//                    0x73, 0x74, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x09, 
//                    0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
//  SequenceRecord_SecondExtension_t *rec = 0;
//  asn_dec_rval_t ret;
//  ret = ber_decode(0, &asn_DEF_SequenceRecord_SecondExtension, (void**)&rec, buf, sizeof(buf));
//  printf("%d\n", ret.code);
  return std::move(bufs);
}
