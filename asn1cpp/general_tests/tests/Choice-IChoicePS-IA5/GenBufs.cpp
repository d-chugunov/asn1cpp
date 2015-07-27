#include "GenBufs.hpp"
#include "Choice-IChoicePS-IA5.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  Choice_IChoicePS_IA5_t rec;
  rec.present = Choice_IChoicePS_IA5_PR::Choice_IChoicePS_IA5_PR_choice;
  rec.choice.choice.present = choice_PR::choice_PR_str1;
  rec.choice.choice.choice.str1.buf = (uint8_t*)"string1";
  rec.choice.choice.choice.str1.size = strlen((char*)rec.choice.choice.choice.str1.buf);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_Choice_IChoicePS_IA5, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf1");
    exit(0);
  }
  return std::move(buf);
}

std::vector<std::vector<uint8_t>> GenBufs()
{
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(Buf1());
  return std::move(bufs);
}
