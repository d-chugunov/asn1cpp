#include "GenBufs.hpp"
#include "SeqRecWithThisChoice.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SeqRecWithThisChoice_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.ch = (struct Choice_SeqWithThisChoice*)malloc(sizeof(struct Choice_SeqWithThisChoice));
  rec.ch->present = Choice_SeqWithThisChoice_PR_seq;
  rec.ch->choice.seq = (SeqRecWithThisChoice_t*)malloc(sizeof(SeqRecWithThisChoice_t));
  memset(rec.ch->choice.seq, 0, sizeof(*rec.ch->choice.seq));
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SeqRecWithThisChoice, &rec, (void*)buf.data(), buf.size());
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
