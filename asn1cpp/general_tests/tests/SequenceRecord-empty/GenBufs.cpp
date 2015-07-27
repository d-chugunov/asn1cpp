#include "GenBufs.hpp"
#include "SequenceRecord-empty.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_empty rec;
  memset(&rec, 0, sizeof(rec));
  rec.Int = 123;
  rec.real = 567.123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_empty, &rec, (void*)buf.data(), buf.size());
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
