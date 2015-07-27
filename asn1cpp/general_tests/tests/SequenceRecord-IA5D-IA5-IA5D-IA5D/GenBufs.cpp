#include "GenBufs.hpp"
#include "SequenceRecord-IA5D-IA5-IA5D-IA5D.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  uint8_t val1[] = "111";
  uint8_t val2[] = "888";
  uint8_t val3[] = "666";
  uint8_t val4[] = "222";
  SequenceRecord_IA5D_IA5_IA5D_IA5D_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.val2.buf = val2;
  rec.val2.size = sizeof(val2) - 1;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_IA5D_IA5_IA5D_IA5D, &rec, (void*)buf.data(), buf.size());
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
  uint8_t val1[] = "111";
  uint8_t val2[] = "888";
  uint8_t val3[] = "666";
  uint8_t val4[] = "222";
  SequenceRecord_IA5D_IA5_IA5D_IA5D_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.val1 = (IA5String_t*)malloc(sizeof(*rec.val1));
  rec.val1->buf = val1;
  rec.val1->size = sizeof(val1) - 1;
  rec.val2.buf = val2;
  rec.val2.size = sizeof(val2) - 1;
  rec.val3 = (IA5String_t*)malloc(sizeof(*rec.val3));
  rec.val3->buf = val3;
  rec.val3->size = sizeof(val3) - 1;
  rec.val4 = (IA5String_t*)malloc(sizeof(*rec.val4));
  rec.val4->buf = val4;
  rec.val4->size = sizeof(val4) - 1;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_IA5D_IA5_IA5D_IA5D, &rec, (void*)buf.data(), buf.size());
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