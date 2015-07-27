#include "GenBufs.hpp"
#include "SequenceT2seqof.h"
#include "SequenceOfT2seqof.h"
#include "SetOfT2seqof.h"
#include "SetT2seqof.h"
#include "SeqOfT1seqofRef.h"
#include "ChoiceT2seqof.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  long oneT1;
  oneT1 = 123;
  long twoT1;
  twoT1 = 456;
  long threeT1;
  threeT1 = 789;
  SequenceT2seqof rec;
  memset(&rec, 0, sizeof(rec));
  ASN_SEQUENCE_ADD(&rec.one, &oneT1);
  ASN_SEQUENCE_ADD(&rec.one, &twoT1);
  rec.two = (struct SeqOfT1*)malloc(sizeof(*rec.two));
  memset(rec.two, 0, sizeof(*rec.two));
  ASN_SEQUENCE_ADD(rec.two, &threeT1);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceT2seqof, &rec, (void*)buf.data(), buf.size());
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
  long oneT1;
  oneT1 = 123;
  long twoT1;
  twoT1 = 456;
  long threeT1;
  threeT1 = 789;
  SetT2seqof rec;
  memset(&rec, 0, sizeof(rec));
  ASN_SEQUENCE_ADD(&rec.one, &oneT1);
  ASN_SEQUENCE_ADD(&rec.one, &twoT1);
  rec.two = (struct SeqOfT1*)malloc(sizeof(*rec.two));
  memset(rec.two, 0, sizeof(*rec.two));
  ASN_SEQUENCE_ADD(rec.two, &threeT1);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetT2seqof, &rec, (void*)buf.data(), buf.size());
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
  long oneT1;
  oneT1 = 123;
  long twoT1;
  twoT1 = 456;
  long threeT1;
  threeT1 = 789;
  SequenceOfT2seqof rec;
  memset(&rec, 0, sizeof(rec));
  
  SeqOfT1_t one;
  memset(&one, 0, sizeof(one));
  ASN_SEQUENCE_ADD(&one, &oneT1);
  ASN_SEQUENCE_ADD(&one, &twoT1);
  SeqOfT1_t two;
  memset(&two, 0, sizeof(two));
  ASN_SEQUENCE_ADD(&two, &threeT1);
  
  ASN_SEQUENCE_ADD(&rec, &one);
  ASN_SEQUENCE_ADD(&rec, &two);
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceOfT2seqof, &rec, (void*)buf.data(), buf.size());
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
  long oneT1;
  oneT1 = 123;
  long twoT1;
  twoT1 = 456;
  long threeT1;
  threeT1 = 789;
  SetOfT2seqof rec;
  memset(&rec, 0, sizeof(rec));
  
  SeqOfT1_t one;
  memset(&one, 0, sizeof(one));
  ASN_SEQUENCE_ADD(&one, &oneT1);
  ASN_SEQUENCE_ADD(&one, &twoT1);
  SeqOfT1_t two;
  memset(&two, 0, sizeof(two));
  ASN_SEQUENCE_ADD(&two, &threeT1);
  
  ASN_SET_ADD(&rec, &one);
  ASN_SET_ADD(&rec, &two);
  
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetOfT2seqof, &rec, (void*)buf.data(), buf.size());
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
  long oneT1;
  oneT1 = 123;
  long twoT1;
  twoT1 = 456;
  long threeT1;
  threeT1 = 789;
  ChoiceT2seqof rec;
  memset(&rec, 0, sizeof(rec));
  rec.present = ChoiceT2seqof_PR::ChoiceT2seqof_PR_one;
  ASN_SEQUENCE_ADD(&rec.choice.one, &oneT1);
  ASN_SEQUENCE_ADD(&rec.choice.one, &twoT1);
  ASN_SEQUENCE_ADD(&rec.choice.one, &threeT1);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_ChoiceT2seqof, &rec, (void*)buf.data(), buf.size());
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
  long oneT1;
  oneT1 = 123;
  long twoT1;
  twoT1 = 456;
  long threeT1;
  threeT1 = 789;
  SeqOfT1seqofRef_t rec;
  memset(&rec, 0, sizeof(rec));
  ASN_SEQUENCE_ADD(&rec, &oneT1);
  ASN_SEQUENCE_ADD(&rec, &twoT1);
  ASN_SEQUENCE_ADD(&rec, &threeT1);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SeqOfT1seqofRef, &rec, (void*)buf.data(), buf.size());
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
