#include "GenBufs.hpp"
#include "SomeRecord-IO-I-I-Automatic.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SomeRecord_IO_I_I_Automatic_t rec;
  rec.type = NULL;
  rec.type2 = 123;
  rec.type3 = 92367624;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SomeRecord_IO_I_I_Automatic, &rec, (void*)buf.data(), buf.size());
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
  SomeRecord_IO_I_I_Automatic_t rec;
  rec.type = (long*)malloc(sizeof(*rec.type));
  *rec.type = 635282;
  rec.type2 = 123;
  rec.type3 = 92367624;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SomeRecord_IO_I_I_Automatic, &rec, (void*)buf.data(), buf.size());
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
