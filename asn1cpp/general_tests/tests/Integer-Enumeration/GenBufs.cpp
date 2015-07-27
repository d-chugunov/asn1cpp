#include "GenBufs.hpp"
#include "Integer-Enumeration.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  Integer_Enumeration_t rec;
  rec = Integer_Enumeration::Integer_Enumeration_value2;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_Integer_Enumeration, &rec, (void*)buf.data(), buf.size());
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
  Integer_Enumeration_t rec;
  rec = 512;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_Integer_Enumeration, &rec, (void*)buf.data(), buf.size());
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
