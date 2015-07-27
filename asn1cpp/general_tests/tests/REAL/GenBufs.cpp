#include "GenBufs.hpp"
#include "REAL.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  REAL_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_double2REAL(&rec, 837823874.856765);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_REAL, &rec, (void*)buf.data(), buf.size());
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
  REAL_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_double2REAL(&rec, -73629473.124768);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_REAL, &rec, (void*)buf.data(), buf.size());
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
  std::vector<uint8_t> value = {0x80, 0xea, 0x0c, 0x7c, 0x0b, 0x60, 0xb6, 0xd5, 
                                0x3d, 0xd5, 0x3d, 0xd5, 0x3d, 0xd5, 0x3d, 0xd5, 
                                0x3d, 0xd5, 0x3d, 0xd5, 0x3d, 0xd5, 0x3d, 0xd5};
  REAL_t rec;
  rec.buf = value.data();
  rec.size = value.size();
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_REAL, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf3");
    exit(0);
  }
  return std::move(buf);
}


std::vector<std::vector<uint8_t>> GenBufs()
{
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(Buf1());
  bufs.push_back(Buf2());
  bufs.push_back(Buf3());
  return std::move(bufs);
}
