#include "GenBufs.hpp"
#include "SequenceOfSequenceRecord-I-IO-I.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_I_IO_IRef_t val1;
  memset(&val1, 0, sizeof(val1));
  val1.type = 1;
  val1.type3 = 3;
  SequenceRecord_I_IO_IRef_t val2;
  memset(&val2, 0, sizeof(val2));
  val2.type = -1;
  val2.type3 = -3;
  SequenceOfSequenceRecord_I_IO_I_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_sequence_add(&rec.list, &val1);
  asn_sequence_add(&rec.list, &val2);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceOfSequenceRecord_I_IO_I, &rec, (void*)buf.data(), buf.size());
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