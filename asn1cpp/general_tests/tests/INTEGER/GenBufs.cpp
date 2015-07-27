#include "GenBufs.hpp"
#include "INTEGER.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  INTEGER_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_long2INTEGER(&rec, 837823874);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_INTEGER, &rec, (void*)buf.data(), buf.size());
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
  INTEGER_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_long2INTEGER(&rec, -73629473);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_INTEGER, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf2");
    exit(0);
  }
  unsigned long ul;
  asn_INTEGER2ulong(&rec, &ul);
  printf("unsigned long: %u\n", ul);
  asn_ulong2INTEGER(&rec, ul);
  printf("asn_ulong2INTEGER for %u: {", ul);
  for (int i = 0; i < rec.size; ++i) {
    printf("0x%x", rec.buf[i]);
    if (i != rec.size - 1)
      printf(", ");
  }
  printf("}\n");
  return std::move(buf);
}

std::vector<uint8_t> Buf3() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  std::vector<uint8_t> value = {0x31, 0xf0, 0x2d, 0x82, 0x37, 0x31, 0xf0, 0x2d, 
                                0x82, 0x37, 0x31, 0xf0, 0x2d, 0x82, 0x37};
  INTEGER_t rec;
  rec.buf = value.data();
  rec.size = value.size();
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_INTEGER, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf3");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf4() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  INTEGER_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_long2INTEGER(&rec, 4221337823);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_INTEGER, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf4");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf5() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  INTEGER_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_long2INTEGER(&rec, -73629473);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_INTEGER, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf5");
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
  bufs.push_back(Buf4());
  bufs.push_back(Buf5());
  return std::move(bufs);
}
