#include "GenBufs.hpp"
#include "SequenceRecord-ED-E-ED-ED.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_ED_E_ED_ED_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.val2 = 888;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_ED_E_ED_ED, &rec, (void*)buf.data(), buf.size());
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
  SequenceRecord_ED_E_ED_ED_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.val1 = (long*)malloc(sizeof(*rec.val1));
  *rec.val1 = 111;
  rec.val2 = 888;
  rec.val3 = 666;
  rec.val4 = (long*)malloc(sizeof(*rec.val4));
  *rec.val4 = 222;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_ED_E_ED_ED, &rec, (void*)buf.data(), buf.size());
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
