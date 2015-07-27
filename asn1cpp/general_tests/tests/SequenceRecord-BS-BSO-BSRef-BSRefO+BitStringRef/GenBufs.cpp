#include "GenBufs.hpp"
#include "SequenceRecord-BS-BSO-BSRef-BSRefO.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  uint8_t bitString1[] = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                           0x90, 0xe3, 0x98, 0xfe, 0xcd};
  uint8_t bitString3[] = {0x14, 0x82, 0xa7, 0x8b, 0x97};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_BS_BSO_BSRef_BSRefO rec;
  rec.bitString1.size = sizeof(bitString1);
  rec.bitString1.buf = (uint8_t*)malloc(rec.bitString1.size);
  for (size_t i = 0; i < rec.bitString1.size; ++i)
    rec.bitString1.buf[i] = bitString1[i];
  rec.bitString1.bits_unused = 5;
  
  rec.bitString2 = 0;
  
  rec.bitString3.size = sizeof(bitString3);
  rec.bitString3.buf = (uint8_t*)malloc(rec.bitString3.size);
  for (size_t i = 0; i < rec.bitString3.size; ++i)
    rec.bitString3.buf[i] = bitString3[i];
  rec.bitString3.bits_unused = 3;
  
  rec.bitString4 = 0;
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_BS_BSO_BSRef_BSRefO, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf1");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf2() {
  uint8_t bitString1[] = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                           0x90, 0xe3, 0x98, 0xfe, 0xcd};
  uint8_t bitString2[] = {0x13, 0x82, 0xa7, 0x8b, 0x97, 
                           0x90, 0xe3, 0x98};
  uint8_t bitString3[] = {0x14, 0x82, 0xa7, 0x8b, 0x97};
  uint8_t bitString4[] = {0x15, 0x82, 0xa7, 0x8b, 0x97, 0x90};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_BS_BSO_BSRef_BSRefO rec;
  rec.bitString1.size = sizeof(bitString1);
  rec.bitString1.buf = (uint8_t*)malloc(rec.bitString1.size);
  for (size_t i = 0; i < rec.bitString1.size; ++i)
    rec.bitString1.buf[i] = bitString1[i];
  rec.bitString1.bits_unused = 5;
  
  rec.bitString2 = (BitStringRef_t*)malloc(sizeof(rec.bitString2));
  rec.bitString2->size = sizeof(bitString2);
  rec.bitString2->buf = (uint8_t*)malloc(rec.bitString2->size);
  for (size_t i = 0; i < rec.bitString2->size; ++i)
    rec.bitString2->buf[i] = bitString2[i];
  rec.bitString2->bits_unused = 2;
  
  rec.bitString3.size = sizeof(bitString3);
  rec.bitString3.buf = (uint8_t*)malloc(rec.bitString3.size);
  for (size_t i = 0; i < rec.bitString3.size; ++i)
    rec.bitString3.buf[i] = bitString3[i];
  rec.bitString3.bits_unused = 3;
  
  rec.bitString4 = (BitStringRef_t*)malloc(sizeof(rec.bitString4));
  rec.bitString4->size = sizeof(bitString4);
  rec.bitString4->buf = (uint8_t*)malloc(rec.bitString4->size);
  for (size_t i = 0; i < rec.bitString4->size; ++i)
    rec.bitString4->buf[i] = bitString4[i];
  rec.bitString4->bits_unused = 7;
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_BS_BSO_BSRef_BSRefO, &rec, (void*)buf.data(), buf.size());
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



