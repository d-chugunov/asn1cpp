#include "GenBufs.hpp"
#include "SequenceRecord-ISO-BSE-BSEO.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  uint8_t octetString[] = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                           0x90, 0xe3, 0x98, 0xfe, 0xcd};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_ISO_BSE_BSEO_t rec;
  rec.seq = (struct SequenceRecord_ISO_BSE_BSEO_t::seq*)malloc(sizeof(*rec.seq));
  rec.seq->bitString2 = 0;
  rec.seq->bitString1.size = sizeof(octetString);
  rec.seq->bitString1.buf = (uint8_t*)malloc(rec.seq->bitString1.size);
  rec.seq->bitString1.bits_unused = 5;
  for (size_t i = 0; i < rec.seq->bitString1.size; ++i)
    rec.seq->bitString1.buf[i] = octetString[i];
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_ISO_BSE_BSEO, &rec, (void*)buf.data(), buf.size());
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



