#include "GenBufs.hpp"
#include "SequenceRecord-I-IO-I-S-1I-S-1IO-1I.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec;
  rec.type = 123;
  rec.type2 = 0;
  rec.type3 = 92367624;
  rec.type4 = NULL;
  rec.type5.value1 = 0;
  rec.type5.value2 = 13487;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_I_IO_I_S_1I_S_1IO_1I, &rec, (void*)buf.data(), buf.size());
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
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec;
  rec.type = 123;
  rec.type2 = (long*)malloc(sizeof(*rec.type2));
  *rec.type2 = 9273;
  rec.type3 = 92367624;
  rec.type4 = (struct SequenceRecord_I_IO_I_S_1I_S_1IO_1I::type4*)malloc(sizeof(SequenceRecord_I_IO_I_S_1I_S_1IO_1I::type4));
  rec.type4->value1 = 871634;
  rec.type5.value1 = (long*)malloc(sizeof(*rec.type5.value1));
  *rec.type5.value1 = 12347832;
  rec.type5.value2 = 13487;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_I_IO_I_S_1I_S_1IO_1I, &rec, (void*)buf.data(), buf.size());
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

