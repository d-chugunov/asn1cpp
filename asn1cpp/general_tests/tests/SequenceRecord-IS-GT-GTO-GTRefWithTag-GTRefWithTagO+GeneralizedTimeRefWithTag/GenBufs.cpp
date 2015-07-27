#include <stdexcept>

#include "GenBufs.hpp"
#include "SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO.h"
#include "time.h"
#include "ber_decoder.h"

const size_t DEFAULT_BUF_SIZE = 1024;

void PrintLn(const OCTET_STRING_t& octetString) {
  printf("{");
  for (int i = 0; i < octetString.size; ++i) {
    printf("0x%.2x", octetString.buf[i]);
    if (i + 1 != octetString.size)
      printf(", ");
  }
  printf("};\n");
}

std::vector<uint8_t> Buf1() {
  struct tm time1;
  memset(&time1, 0, sizeof(time1));
  time1.tm_year = 110;
  time1.tm_mon = 2;
  time1.tm_mday = 10;
  time1.tm_hour = 16;
  time1.tm_min = 40;
  time1.tm_sec = 12;
  struct tm time3;
  memset(&time3, 0, sizeof(time3));
  time3.tm_year = 130;
  time3.tm_mon = 2;
  time3.tm_mday = 10;
  time3.tm_hour = 16;
  time3.tm_min = 40;
  time3.tm_sec = 12;
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_IS_GT_GTO_GTRefWithTag_GTRefWithTagO_t rec;
  memset(&rec, 0, sizeof(rec));
  if (!asn_time2GT(&rec.seq.time1, &time1, 0))
    throw std::runtime_error("error");
  rec.seq.time2 = 0;
  if (!asn_time2GT(&rec.seq.time3, &time3, 0))
    throw std::runtime_error("error");
  rec.seq.time4 = 0;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_IS_GT_GTO_GTRefWithTag_GTRefWithTagO, &rec, (void*)buf.data(), buf.size());
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
  SequenceRecord_IS_GT_GTO_GTRefWithTag_GTRefWithTagO_t rec;
  memset(&rec, 0, sizeof(rec));
  struct tm time1;
  memset(&time1, 0, sizeof(time1));
  time1.tm_year = 110;
  time1.tm_mon = 2;
  time1.tm_mday = 10;
  time1.tm_hour = 16;
  time1.tm_min = 40;
  time1.tm_sec = 12;
  struct tm time2;
  memset(&time2, 0, sizeof(time2));
  time2.tm_year = 120;
  time2.tm_mon = 2;
  time2.tm_mday = 10;
  time2.tm_hour = 16;
  time2.tm_min = 40;
  time2.tm_sec = 12;
  struct tm time3;
  memset(&time3, 0, sizeof(time3));
  time3.tm_year = 130;
  time3.tm_mon = 2;
  time3.tm_mday = 10;
  time3.tm_hour = 16;
  time3.tm_min = 40;
  time3.tm_sec = 12;
  struct tm time4;
  memset(&time4, 0, sizeof(time4));
  time4.tm_year = 137;
  time4.tm_mon = 2;
  time4.tm_mday = 10;
  time4.tm_hour = 16;
  time4.tm_min = 40;
  time4.tm_sec = 12;
  if (!asn_time2GT(&rec.seq.time1, &time1, 0))
    throw std::runtime_error("error");
  rec.seq.time2 = (GeneralizedTime_t*)malloc(sizeof(GeneralizedTime_t));
  memset(rec.seq.time2, 0, sizeof(*rec.seq.time2));
  if (!asn_time2GT(rec.seq.time2, &time2, 0))
    throw std::runtime_error("error");
  if (!asn_time2GT(&rec.seq.time3, &time3, 0))
    throw std::runtime_error("error");
  rec.seq.time4 = (GeneralizedTime_t*)malloc(sizeof(GeneralizedTime_t));
  memset(rec.seq.time4, 0, sizeof(*rec.seq.time4));
  if (!asn_time2GT(rec.seq.time4, &time4, 0))
    throw std::runtime_error("error");
  printf("std::vector<uint8_t> mustBe1 = "); PrintLn(rec.seq.time1);
  printf("std::vector<uint8_t> mustBe2 = "); PrintLn(*rec.seq.time2);
  printf("std::vector<uint8_t> mustBe3 = "); PrintLn(rec.seq.time3);
  printf("std::vector<uint8_t> mustBe4 = "); PrintLn(*rec.seq.time4);
  printf("time1: %u\n", asn_GT2time(&rec.seq.time1, 0, 0));
  printf("time2: %u\n", asn_GT2time(rec.seq.time2, 0, 0));
  printf("time3: %u\n", asn_GT2time(&rec.seq.time3, 0, 0));
  printf("time4: %u\n", asn_GT2time(rec.seq.time4, 0, 0));
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_IS_GT_GTO_GTRefWithTag_GTRefWithTagO, &rec, (void*)buf.data(), buf.size());
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
  printf("-------------------------------------------------------------------\n");
  printf("You should replace 0x2b, 0x30, 0x30, 0x30, 0x30 in mustBe with 0x5a\n");
  printf("-------------------------------------------------------------------\n");
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(Buf1());
  bufs.push_back(Buf2());
  return std::move(bufs);
}



