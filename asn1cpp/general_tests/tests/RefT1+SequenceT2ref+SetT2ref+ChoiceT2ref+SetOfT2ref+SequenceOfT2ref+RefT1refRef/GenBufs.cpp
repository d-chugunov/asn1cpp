#include "GenBufs.hpp"
#include "SequenceT2ref.h"
#include "SequenceOfT2ref.h"
#include "SetOfT2ref.h"
#include "SetT2ref.h"
#include "RefT1refRef.h"
#include "ChoiceT2ref.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceT2ref rec;
  memset(&rec, 0, sizeof(rec));
  rec.one = 123;
  rec.two = (RefT1_t*)malloc(sizeof(*rec.two));
  memset(rec.two, 0, sizeof(*rec.two));
  *rec.two = 456;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceT2ref, &rec, (void*)buf.data(), buf.size());
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
  SetT2ref rec;
  memset(&rec, 0, sizeof(rec));
  rec.one = 123;
  rec.two = (RefT1_t*)malloc(sizeof(*rec.two));
  memset(rec.two, 0, sizeof(*rec.two));
  *rec.two = 456;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetT2ref, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf2");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf3() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceOfT2ref rec;
  memset(&rec, 0, sizeof(rec));
  
  RefT1_t one;
  memset(&one, 0, sizeof(one));
  one = 123;
  RefT1_t two;
  memset(&two, 0, sizeof(two));
  two = 456;
  
  ASN_SEQUENCE_ADD(&rec, &one);
  ASN_SEQUENCE_ADD(&rec, &two);
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceOfT2ref, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf3");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf4() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetOfT2ref rec;
  memset(&rec, 0, sizeof(rec));
  
  RefT1_t one;
  memset(&one, 0, sizeof(one));
  one = 123;
  RefT1_t two;
  memset(&two, 0, sizeof(two));
  two = 456;
  
  ASN_SET_ADD(&rec, &one);
  ASN_SET_ADD(&rec, &two);
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetOfT2ref, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf3");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf5() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  ChoiceT2ref rec;
  memset(&rec, 0, sizeof(rec));
  rec.present = ChoiceT2ref_PR::ChoiceT2ref_PR_one;
  rec.choice.one = 123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_ChoiceT2ref, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf5");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf6() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  RefT1refRef_t rec;
  memset(&rec, 0, sizeof(rec));
  rec = 123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_RefT1refRef, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf6");
    exit(0);
  }
  return std::move(buf);
}


std::vector<std::vector<uint8_t>> GenBufs()
{
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(Buf1());
  bufs.push_back(Buf2());
  bufs.push_back(Buf3());
  bufs.push_back(Buf4());
  bufs.push_back(Buf5());
  bufs.push_back(Buf6());
  return std::move(bufs);
}
