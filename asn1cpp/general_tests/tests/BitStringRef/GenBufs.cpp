#include "GenBufs.hpp"
#include "BitStringRef.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  uint8_t octetString[] = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                           0x90, 0xe3, 0x98, 0xfe, 0xcd};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  BitStringRef_t rec;
  rec.size = sizeof(octetString);
  rec.buf = (uint8_t*)malloc(rec.size);
  rec.bits_unused = 5;
  for (size_t i = 0; i < rec.size; ++i)
    rec.buf[i] = octetString[i];
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_BitStringRef, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf1");
    exit(0);
  }
  return std::move(buf);
}

std::vector<std::vector<uint8_t>> GenBufs()
{
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(Buf1());
  return std::move(bufs);
}



