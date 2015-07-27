#include "GenBufs.hpp"
#include "SequenceRecord-SeqOfSeqRec-SeqRec-I-IO-I.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_I_IO_I_t rec1;
  memset(&rec1, 0, sizeof(rec1));
  rec1.type = 1;
  rec1.type3 = 10;
  SequenceRecord_I_IO_I_t rec2;
  memset(&rec2, 0, sizeof(rec2));
  rec2.type = 2;
  rec2.type3 = 20;
  SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I_t rec;
  memset(&rec, 0, sizeof(rec));
  ASN_SEQUENCE_ADD(&rec.sequenceRecord_I_IO_I.list, &rec1);
  ASN_SEQUENCE_ADD(&rec.sequenceRecord_I_IO_I.list, &rec2);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf1");
    exit(0);
  }
  return std::move(buf);
}

std::vector<std::vector<uint8_t>> GenBufs() {
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(std::move(Buf1()));
  return std::move(bufs);
}