#include "GenBufs.hpp"
#include "SequenceT2set.h"
#include "SequenceOfT2set.h"
#include "SetOfT2set.h"
#include "SetT2set.h"
#include "SetT1setRef.h"
#include "ChoiceT2set.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceT2set rec;
  memset(&rec, 0, sizeof(rec));
  rec.one.first = 123;
  rec.one.second = 321;
  rec.two = (struct SetT1*)malloc(sizeof(*rec.two));
  memset(rec.two, 0, sizeof(*rec.two));
  rec.two->first = 654;
  rec.two->second = 456;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceT2set, &rec, (void*)buf.data(), buf.size());
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
  SetT2set rec;
  memset(&rec, 0, sizeof(rec));
  rec.one.first = 123;
  rec.one.second = 321;
  rec.two = (struct SetT1*)malloc(sizeof(*rec.two));
  memset(rec.two, 0, sizeof(*rec.two));
  rec.two->first = 654;
  rec.two->second = 456;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetT2set, &rec, (void*)buf.data(), buf.size());
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
  SequenceOfT2set rec;
  memset(&rec, 0, sizeof(rec));
  
  SetT1_t one;
  memset(&one, 0, sizeof(one));
  one.first = 123;
  one.second = 321;
  SetT1_t two;
  memset(&two, 0, sizeof(two));
  two.first = 654;
  two.second = 456;
  
  ASN_SEQUENCE_ADD(&rec, &one);
  ASN_SEQUENCE_ADD(&rec, &two);
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceOfT2set, &rec, (void*)buf.data(), buf.size());
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
  SetOfT2set rec;
  memset(&rec, 0, sizeof(rec));
  
  SetT1_t one;
  memset(&one, 0, sizeof(one));
  one.first = 123;
  one.second = 321;
  SetT1_t two;
  memset(&two, 0, sizeof(two));
  two.first = 654;
  two.second = 456;
  
  ASN_SET_ADD(&rec, &one);
  ASN_SET_ADD(&rec, &two);
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetOfT2set, &rec, (void*)buf.data(), buf.size());
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
  ChoiceT2set rec;
  memset(&rec, 0, sizeof(rec));
  rec.present = ChoiceT2set_PR::ChoiceT2set_PR_one;
  rec.choice.one.first = 123;
  rec.choice.one.second = 456;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_ChoiceT2set, &rec, (void*)buf.data(), buf.size());
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
  SetT1setRef_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.first = 123;
  rec.second = 456;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetT1setRef, &rec, (void*)buf.data(), buf.size());
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
