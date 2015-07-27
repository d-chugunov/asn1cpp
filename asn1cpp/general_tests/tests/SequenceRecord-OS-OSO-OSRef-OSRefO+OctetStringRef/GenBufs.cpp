#include "GenBufs.hpp"
#include "SequenceRecord-OS-OSO-OSRef-OSRefO.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  uint8_t octetString1[] = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                           0x90, 0xe3, 0x98, 0xfe, 0xcd};
  uint8_t octetString3[] = {0x14, 0x82, 0xa7, 0x8b, 0x97};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_OS_OSO_OSRef_OSRefO rec;
  rec.octetString1.size = sizeof(octetString1);
  rec.octetString1.buf = (uint8_t*)malloc(rec.octetString1.size);
  for (size_t i = 0; i < rec.octetString1.size; ++i)
    rec.octetString1.buf[i] = octetString1[i];
  
  rec.octetString2 = 0;
  
  rec.octetString3.size = sizeof(octetString3);
  rec.octetString3.buf = (uint8_t*)malloc(rec.octetString3.size);
  for (size_t i = 0; i < rec.octetString3.size; ++i)
    rec.octetString3.buf[i] = octetString3[i];
  
  rec.octetString4 = 0;
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_OS_OSO_OSRef_OSRefO, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf1");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf2() {
  uint8_t octetString1[] = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                           0x90, 0xe3, 0x98, 0xfe, 0xcd};
  uint8_t octetString2[] = {0x13, 0x82, 0xa7, 0x8b, 0x97, 
                           0x90, 0xe3, 0x98};
  uint8_t octetString3[] = {0x14, 0x82, 0xa7, 0x8b, 0x97};
  uint8_t octetString4[] = {0x15, 0x82, 0xa7, 0x8b, 0x97, 0x90};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_OS_OSO_OSRef_OSRefO rec;
  rec.octetString1.size = sizeof(octetString1);
  rec.octetString1.buf = (uint8_t*)malloc(rec.octetString1.size);
  for (size_t i = 0; i < rec.octetString1.size; ++i)
    rec.octetString1.buf[i] = octetString1[i];
  
  rec.octetString2 = (OctetStringRef_t*)malloc(sizeof(rec.octetString2));
  rec.octetString2->size = sizeof(octetString2);
  rec.octetString2->buf = (uint8_t*)malloc(rec.octetString2->size);
  for (size_t i = 0; i < rec.octetString2->size; ++i)
    rec.octetString2->buf[i] = octetString2[i];
  
  rec.octetString3.size = sizeof(octetString3);
  rec.octetString3.buf = (uint8_t*)malloc(rec.octetString3.size);
  for (size_t i = 0; i < rec.octetString3.size; ++i)
    rec.octetString3.buf[i] = octetString3[i];
  
  rec.octetString4 = (OctetStringRef_t*)malloc(sizeof(rec.octetString4));
  rec.octetString4->size = sizeof(octetString4);
  rec.octetString4->buf = (uint8_t*)malloc(rec.octetString4->size);
  for (size_t i = 0; i < rec.octetString4->size; ++i)
    rec.octetString4->buf[i] = octetString4[i];
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_OS_OSO_OSRef_OSRefO, &rec, (void*)buf.data(), buf.size());
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



