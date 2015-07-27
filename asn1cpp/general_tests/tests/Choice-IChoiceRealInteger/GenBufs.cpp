#include "GenBufs.hpp"
#include "Choice-IChoiceRealInteger.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  Choice_IChoiceRealInteger_t rec;
  rec.present = Choice_IChoiceRealInteger_PR::Choice_IChoiceRealInteger_PR_choice;
  rec.choice.choice.present = choice_PR::choice_PR_integer;
  rec.choice.choice.choice.integer = 123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_Choice_IChoiceRealInteger, &rec, (void*)buf.data(), buf.size());
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
  Choice_IChoiceRealInteger_t rec;
  rec.present = Choice_IChoiceRealInteger_PR::Choice_IChoiceRealInteger_PR_choice;
  rec.choice.choice.present = choice_PR::choice_PR_real;
  rec.choice.choice.choice.real = 123.123;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_Choice_IChoiceRealInteger, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf2");
    exit(0);
  }
  return std::move(buf);
}


std::vector<std::vector<uint8_t>> GenBufs()
{
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(Buf1());
  bufs.push_back(Buf2());
  return std::move(bufs);
}
