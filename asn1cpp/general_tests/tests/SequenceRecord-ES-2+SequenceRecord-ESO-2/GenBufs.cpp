#include "GenBufs.hpp"
#include "SequenceRecord-ES-2.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_ES_2 rec;
  rec.ptr1 = (SequenceRecord_ESO_2*)malloc(sizeof(SequenceRecord_ESO_2));
  rec.ptr1->ptr2 = 0;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_ES_2, &rec, (void*)buf.data(), buf.size());
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
  SequenceRecord_ES_2 rec;
  rec.ptr1 = (SequenceRecord_ESO_2*)malloc(sizeof(SequenceRecord_ESO_2));
  rec.ptr1->ptr2 = (SequenceRecord_ES_2*)malloc(sizeof(SequenceRecord_ES_2));
  rec.ptr1->ptr2->ptr1 = (SequenceRecord_ESO_2*)malloc(sizeof(SequenceRecord_ESO_2));;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_ES_2, &rec, (void*)buf.data(), buf.size());
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



