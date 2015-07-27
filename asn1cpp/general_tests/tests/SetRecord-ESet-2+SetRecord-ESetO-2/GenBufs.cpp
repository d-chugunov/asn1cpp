#include "GenBufs.hpp"
#include "SetRecord-ESet-2.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_ESet_2_t rec;
  rec.ptr1 = (SetRecord_ESetO_2_t*)malloc(sizeof(SetRecord_ESetO_2_t));
  rec.ptr1->ptr2 = 0;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ESet_2, &rec, (void*)buf.data(), buf.size());
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
  SetRecord_ESet_2_t rec;
  rec.ptr1 = (SetRecord_ESetO_2*)malloc(sizeof(SetRecord_ESetO_2));
  rec.ptr1->ptr2 = (SetRecord_ESet_2_t*)malloc(sizeof(SetRecord_ESet_2_t));
  rec.ptr1->ptr2->ptr1 = (SetRecord_ESetO_2_t*)malloc(sizeof(SetRecord_ESetO_2_t));;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ESet_2, &rec, (void*)buf.data(), buf.size());
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



