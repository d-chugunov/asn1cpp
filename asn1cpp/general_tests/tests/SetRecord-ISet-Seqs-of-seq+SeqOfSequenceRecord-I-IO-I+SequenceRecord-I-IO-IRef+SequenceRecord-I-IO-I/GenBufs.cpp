#include "GenBufs.hpp"
#include "SetRecord-ISet-Seqs-of-seq.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  SequenceRecord_I_IO_I_t val1;
  memset(&val1, 0, sizeof(val1));
  val1.type = 1;
  val1.type3 = 3;
  SequenceRecord_I_IO_I_t val3;
  memset(&val3, 0, sizeof(val3));
  val3.type = -1;
  val3.type3 = -3;
  
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_ISet_Seqs_of_seq_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_set_add(&rec.set.field1, &val1);
  asn_set_add(&rec.set.field3, &val3);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ISet_Seqs_of_seq, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf1");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf2() {
  SequenceRecord_I_IO_I_t val1;
  memset(&val1, 0, sizeof(val1));
  val1.type = 1;
  val1.type3 = 3;
  
  SequenceRecord_I_IO_I_t val2;
  memset(&val2, 0, sizeof(val2));
  val2.type = 10;
  val2.type3 = 30;
  
  SequenceRecord_I_IO_I_t val3;
  memset(&val3, 0, sizeof(val3));
  val3.type = -1;
  val3.type3 = -3;
  
  SequenceRecord_I_IO_I_t val4;
  memset(&val4, 0, sizeof(val4));
  val4.type = -10;
  val4.type3 = -30;
  
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_ISet_Seqs_of_seq_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_set_add(&rec.set.field1, &val1);
  rec.set.field2 = (struct SeqOfSequenceRecord_I_IO_I*)malloc(sizeof(struct SeqOfSequenceRecord_I_IO_I));
  memset(rec.set.field2, 0, sizeof(*rec.set.field2));
  asn_set_add(rec.set.field2, &val2);
  asn_set_add(&rec.set.field3, &val3);
  rec.set.field4 = (struct SetRecord_ISet_Seqs_of_seq::set::field4*)malloc(sizeof(*rec.set.field4));
  memset(rec.set.field4, 0, sizeof(*rec.set.field4));
  asn_set_add(rec.set.field4, &val4);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ISet_Seqs_of_seq, &rec, (void*)buf.data(), buf.size());
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