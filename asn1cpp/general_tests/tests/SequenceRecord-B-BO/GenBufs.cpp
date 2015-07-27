#include "GenBufs.hpp"
#include "SequenceRecord-B-BO.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_B_BO_t rec;
  rec.bool1 = 1;
  rec.bool2 = 0;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_B_BO, &rec, (void*)buf.data(), buf.size());
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
  SequenceRecord_B_BO_t rec;
  rec.bool1 = 0;
  rec.bool2 = (BOOLEAN_t*)malloc(sizeof(BOOLEAN_t));
  *rec.bool2 = 1;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_B_BO, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf2");
    exit(0);
  }
  return std::move(buf);
}

std::vector<std::vector<uint8_t>> GenBufs()
{
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(Buf1());
  bufs.push_back(Buf2());
  return std::move(bufs);
}




