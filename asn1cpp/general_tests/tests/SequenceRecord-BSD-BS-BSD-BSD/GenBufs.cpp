#include "GenBufs.hpp"
#include "SequenceRecord-BSD-BS-BSD-BSD.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  uint8_t val1[] = {0, '1', 0, '1', 0, '1'};
  uint8_t val2[] = {0, '8', 0, '8', 0, '8'};
  uint8_t val3[] = {0, '6', 0, '6', 0, '6'};
  uint8_t val4[] = {0, '2', 0, '2', 0, '2'};
  SequenceRecord_BSD_BS_BSD_BSD_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.val2.buf = val2;
  rec.val2.size = sizeof(val2);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_BSD_BS_BSD_BSD, &rec, (void*)buf.data(), buf.size());
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
  uint8_t val1[] = {0, '1', 0, '1', 0, '1'};
  uint8_t val2[] = {0, '8', 0, '8', 0, '8'};
  uint8_t val3[] = {0, '6', 0, '6', 0, '6'};
  uint8_t val4[] = {0, '2', 0, '2', 0, '2'};
  SequenceRecord_BSD_BS_BSD_BSD_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.val1 = (BMPString_t*)malloc(sizeof(*rec.val1));
  rec.val1->buf = val1;
  rec.val1->size = sizeof(val1);
  rec.val2.buf = val2;
  rec.val2.size = sizeof(val2);
  rec.val3 = (BMPString_t*)malloc(sizeof(*rec.val3));
  rec.val3->buf = val3;
  rec.val3->size = sizeof(val3);
  rec.val4 = (BMPString_t*)malloc(sizeof(*rec.val4));
  rec.val4->buf = val4;
  rec.val4->size = sizeof(val4);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_BSD_BS_BSD_BSD, &rec, (void*)buf.data(), buf.size());
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