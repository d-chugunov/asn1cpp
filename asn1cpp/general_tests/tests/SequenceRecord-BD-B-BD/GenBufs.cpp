#include "GenBufs.hpp"
#include "SequenceRecord-BD-B-BD.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_BD_B_BD_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.val2 = 1;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_BD_B_BD, &rec, (void*)buf.data(), buf.size());
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
  SequenceRecord_BD_B_BD_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.val1 = (BOOLEAN_t*)malloc(sizeof(*rec.val1));
  *rec.val1 = 0;
  rec.val2 = 0;
  rec.val3 = (BOOLEAN_t*)malloc(sizeof(*rec.val3));
  *rec.val3 = 1;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_BD_B_BD, &rec, (void*)buf.data(), buf.size());
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
