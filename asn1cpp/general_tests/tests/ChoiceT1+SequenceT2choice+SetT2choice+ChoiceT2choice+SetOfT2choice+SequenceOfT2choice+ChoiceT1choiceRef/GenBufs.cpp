#include "GenBufs.hpp"
#include "SequenceT2choice.h"
#include "SequenceOfT2choice.h"
#include "SetOfT2choice.h"
#include "SetT2choice.h"
#include "ChoiceT1choiceRef.h"
#include "ChoiceT2choice.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceT2choice rec;
  memset(&rec, 0, sizeof(rec));
  rec.one.present = ChoiceT1_PR::ChoiceT1_PR_first;
  rec.one.choice.first = 123;
  rec.two = (struct ChoiceT1*)malloc(sizeof(*rec.two));
  memset(rec.two, 0, sizeof(*rec.two));
  rec.two->present = ChoiceT1_PR::ChoiceT1_PR_second;
  rec.two->choice.second = 456;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceT2choice, &rec, (void*)buf.data(), buf.size());
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
  SetT2choice rec;
  memset(&rec, 0, sizeof(rec));
  rec.one.present = ChoiceT1_PR::ChoiceT1_PR_first;
  rec.one.choice.first = 123;
  rec.two = (struct ChoiceT1*)malloc(sizeof(*rec.two));
  memset(rec.two, 0, sizeof(*rec.two));
  rec.two->present = ChoiceT1_PR::ChoiceT1_PR_second;
  rec.two->choice.second = 456;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetT2choice, &rec, (void*)buf.data(), buf.size());
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
  SequenceOfT2choice rec;
  memset(&rec, 0, sizeof(rec));
  
  ChoiceT1_t one;
  memset(&one, 0, sizeof(one));
  one.present = ChoiceT1_PR::ChoiceT1_PR_first;
  one.choice.first = 123;
  ChoiceT1_t two;
  memset(&two, 0, sizeof(two));
  two.present = ChoiceT1_PR::ChoiceT1_PR_second;
  two.choice.second = 456;
  
  ASN_SEQUENCE_ADD(&rec, &one);
  ASN_SEQUENCE_ADD(&rec, &two);
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceOfT2choice, &rec, (void*)buf.data(), buf.size());
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
  SetOfT2choice rec;
  memset(&rec, 0, sizeof(rec));
  
  ChoiceT1_t one;
  memset(&one, 0, sizeof(one));
  one.present = ChoiceT1_PR::ChoiceT1_PR_first;
  one.choice.first = 123;
  ChoiceT1_t two;
  memset(&two, 0, sizeof(two));
  two.present = ChoiceT1_PR::ChoiceT1_PR_second;
  two.choice.second = 456;
  
  ASN_SET_ADD(&rec, &one);
  ASN_SET_ADD(&rec, &two);
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetOfT2choice, &rec, (void*)buf.data(), buf.size());
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
  ChoiceT2choice rec;
  memset(&rec, 0, sizeof(rec));
  rec.present = ChoiceT2choice_PR::ChoiceT2choice_PR_one;
  rec.choice.one.present = ChoiceT1_PR::ChoiceT1_PR_first;
  rec.choice.one.choice.first = 123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_ChoiceT2choice, &rec, (void*)buf.data(), buf.size());
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
  ChoiceT1choiceRef_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.present = ChoiceT1_PR::ChoiceT1_PR_first;
  rec.choice.first = 123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_ChoiceT1choiceRef, &rec, (void*)buf.data(), buf.size());
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
