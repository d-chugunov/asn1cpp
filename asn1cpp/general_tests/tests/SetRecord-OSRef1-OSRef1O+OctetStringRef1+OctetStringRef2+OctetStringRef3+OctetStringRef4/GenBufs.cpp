#include "GenBufs.hpp"
#include "SetRecord-OSRef1-OSRef1O.h"

const size_t DEFAULT_BUF_SIZE = 1024;

void Set(OCTET_STRING_t& dest, std::vector<uint8_t>& source) {
  dest.size = source.size();
  dest.buf = source.data();
}

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> octetString1 = {0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_OSRef1_OSRef1O_t rec;
  memset(&rec, 0, sizeof(rec));
  Set(rec.ref1, octetString1);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_OSRef1_OSRef1O, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf1");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf2() {
  std::vector<uint8_t> octetString1 = {0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> octetString2 = {0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_OSRef1_OSRef1O_t rec;
  memset(&rec, 0, sizeof(rec));
  Set(rec.ref1, octetString1);
  rec.ref2 = (OctetStringRef1_t*)malloc(sizeof(OctetStringRef1_t));
  Set(*rec.ref2, octetString2);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_OSRef1_OSRef1O, &rec, (void*)buf.data(), buf.size());
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