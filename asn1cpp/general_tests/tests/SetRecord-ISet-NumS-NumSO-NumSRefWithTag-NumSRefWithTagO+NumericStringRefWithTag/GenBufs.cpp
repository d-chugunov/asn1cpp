#include <stdexcept>

#include "GenBufs.hpp"
#include "SetRecord-ISet-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO.h"
#include "time.h"
#include "OCTET_STRING.h"

const size_t DEFAULT_BUF_SIZE = 1024;

void PrintOctetString(const OCTET_STRING_t& octetString) {
  printf("{");
  for (int i = 0; i < octetString.size; ++i) {
    printf("0x%.2x", octetString.buf[i]);
    if (i + 1 != octetString.size)
      printf(", ");
  }
  printf("};\n");
}

void SetString(OCTET_STRING_t& octetString, std::string& str) {
  octetString.buf = (uint8_t*)str.data();
  octetString.size = str.size();
}

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  std::string string1 = "string1";
  std::string string3 = "string3";
  SetRecord_ISet_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO_t rec;
  memset(&rec, 0, sizeof(rec));
  SetString(rec.set.str1, string1);
  SetString(rec.set.str3, string3);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ISet_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO, &rec, (void*)buf.data(), buf.size());
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
  std::string string1 = "string1";
  std::string string2 = "string2";
  std::string string3 = "string3";
  std::string string4 = "string4";
  SetRecord_ISet_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO_t rec;
  memset(&rec, 0, sizeof(rec));
  SetString(rec.set.str1, string1);
  rec.set.str2 = (NumericString_t*)malloc(sizeof(NumericString_t));
  SetString(*rec.set.str2, string2);
  SetString(rec.set.str3, string3);
  rec.set.str4 = (NumericStringRefWithTag_t*)malloc(sizeof(NumericStringRefWithTag_t));
  SetString(*rec.set.str4, string4);
  printf("std::vector<uint8_t> mustBe1 = "); PrintOctetString(rec.set.str1);
  printf("std::vector<uint8_t> mustBe2 = "); PrintOctetString(*rec.set.str2);
  printf("std::vector<uint8_t> mustBe3 = "); PrintOctetString(rec.set.str3);
  printf("std::vector<uint8_t> mustBe4 = "); PrintOctetString(*rec.set.str4);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ISet_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO, &rec, (void*)buf.data(), buf.size());
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



