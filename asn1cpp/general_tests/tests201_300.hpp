#ifndef TESTS201_300_HPP
#define	TESTS201_300_HPP

#include "headers.hpp"

void Test201() {
  
  TEST_NUMBER;
  SequenceRecord_ED_E_ED_ED rec;
  rec.SetVal1Default();
  rec.SetVal3Default();
  rec.SetVal4Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == 123 && 
             rec.val2 == 0 &&
          rec.val3 == 0 &&
          rec.val4 && *rec.val4 == 567
  );
}

void Test202() {
  uint8_t test[] = {0x30, 0x05, 0x81, 0x03, 0x38, 0x38, 0x38};
  std::string val1 = "111";
  std::string val2 = "888";
  std::string val3 = "666";
  std::string val4 = "222";
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_VSD_VS_VSD_VSD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.val1 && 
                rec.val2 == val2 && 
                !rec.val3 &&
          !rec.val4
  );
}

void Test203() {
  uint8_t test[] = {0x30, 0x14, 0x80, 0x03, 0x31, 0x31, 0x31, 0x81, 0x03, 0x38, 
                    0x38, 0x38, 0x82, 0x03, 0x36, 0x36, 0x36, 0x83, 0x03, 
                    0x32, 0x32, 0x32};
  std::string val1 = "111";
  std::string val2 = "888";
  std::string val3 = "666";
  std::string val4 = "222";
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_VSD_VS_VSD_VSD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test204() {
  uint8_t test[] = {0x30, 0x14, 0x80, 0x03, 0x31, 0x31, 0x31, 0x81, 0x03, 0x38, 
                    0x38, 0x38, 0x82, 0x03, 0x36, 0x36, 0x36, 0x83, 0x03, 
                    0x32, 0x32, 0x32};
  std::string val1 = "12\"3";
  std::string val2 = "888";
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_VSD_VS_VSD_VSD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  
  rec.SetVal1Default();
  rec.SetVal3Default();
  rec.SetVal4Default();
  
  CHECK_RESULT(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test205() {
  std::string val1 = "12\"3";
  std::string val2;
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  SequenceRecord_VSD_VS_VSD_VSD rec;
  rec.SetVal1Default();
  rec.SetVal3Default();
  rec.SetVal4Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test206() {
  uint8_t test[] = {0x31, 0x07, 0x81, 0x02, 0x03, 0x78, 0x82, 0x01, 0x00};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ID_I_ID_ID rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.val1 && 
                rec.val2 == 888 && 
                rec.val3 == 0 &&
                !rec.val4
  );
}

void Test207() {
  uint8_t test[] = {0x31, 0x0f, 0x80, 0x01, 0x6f, 0x81, 0x02, 0x03, 0x78, 0x82, 
                    0x02, 0x02, 0x9a, 0x83, 0x02, 0x00, 0xde};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ID_I_ID_ID rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.val1 && *rec.val1 == 111 &&
                rec.val2 == 888 && 
                rec.val3 == 666 &&
          rec.val4 && *rec.val4 == 222 
  );
}

void Test208() {
  
  TEST_NUMBER;
  SetRecord_ID_I_ID_ID rec;
#ifdef INSECURE_POINTERS
  rec.val1 = new NativeInteger();
#else
  rec.val1 = std::unique_ptr<NativeInteger>(new NativeInteger());
#endif
  *rec.val1 = 1;
  rec.val2 = 2;
  rec.val3 = 3;
#ifdef INSECURE_POINTERS
  rec.val4 = new NativeInteger();
#else
  rec.val4 = std::unique_ptr<NativeInteger>(new NativeInteger());
#endif
  *rec.val4 = 4;
  
  INTERMEDIATE_COND(
          rec.val1 && *rec.val1 == 1 && 
             rec.val2 == 2 &&
          rec.val3 == 3 &&
          rec.val4 && *rec.val4 == 4
  );
  
  rec.SetVal1Default();
  rec.SetVal3Default();
  rec.SetVal4Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == 123 && 
             rec.val2 == 2 &&
          rec.val3 == 0 &&
          rec.val4 && *rec.val4 == 567
  );
}

void Test209() {
  
  TEST_NUMBER;
  SetRecord_ID_I_ID_ID rec;
  rec.SetVal1Default();
  rec.SetVal3Default();
  rec.SetVal4Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == 123 && 
             rec.val2 == 0 &&
          rec.val3 == 0 &&
          rec.val4 && *rec.val4 == 567
  );
}

void Test210() {
  TEST_NUMBER;
  SequenceRecord_ID_I_ID_ID rec;
  rec.SetEmptyToDefault();
  
  CHECK_COND(rec.val1 && *rec.val1 == 123 && 
             rec.val2 == 0 &&
          rec.val3 == 0 &&
          rec.val4 && *rec.val4 == 567
  );
}

void Test211() {
  
  TEST_NUMBER;
  SetRecord_ID_I_ID_ID rec;
  rec.SetEmptyToDefault();
  
  CHECK_COND(rec.val1 && *rec.val1 == 123 && 
             rec.val2 == 0 &&
          rec.val3 == 0 &&
          rec.val4 && *rec.val4 == 567
  );
}

void Test212() {
  uint8_t test[] = {0x30, 0x07, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x02, 0x37};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ExtensionRootType rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 
  );
}

void Test213() {
  uint8_t test[] = {0x30, 0x0e, 0x02, 0x01, 0x7b, 0x09, 0x09, 0x80, 0xd7, 0x04, 
                    0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_FirstExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 && 
               !rec.b &&
               !rec.c 
  );
}

void Test214() {
  uint8_t test[] = {0x30, 0x15, 0x02, 0x01, 0x7b, 0x01, 0x01, 0xff, 0x02, 0x02, 
                    0x24, 0x9e, 0x09, 0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 
                    0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_FirstExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 && 
               rec.b && *rec.b == 0xFF && 
               rec.c && *rec.c == 9374
  );
}

void Test215() {
  uint8_t test[] = {0x30, 0x0e, 0x02, 0x01, 0x7b, 0x09, 0x09, 0x80, 0xd7, 0x04, 
                    0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_SecondExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          !rec.c &&
          !rec.d
  );
}

void Test216() {
  uint8_t test[] = {0x30, 0x12, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x02, 0x22, 0x09, 
                    0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_SecondExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          !rec.d
  );
}

void Test217() {
  std::string strBuf = "test string";
  uint8_t test[] = {0x30, 0x30, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x02, 0x22, 0x30, 
                    0x1c, 0x02, 0x02, 0x03, 0xd8, 0x16, 0x0b, 0x74, 0x65, 0x73, 
                    0x74, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x09, 0x09, 
                    0x80, 0xd7, 0x05, 0xd4, 0x3e, 0xf9, 0xdb, 0x22, 0xd1, 0x09, 
                    0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_SecondExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          rec.d &&
          rec.d->e == 984 &&
          rec.d->f == strBuf
  );
}

void Test218() {
  uint8_t test[] = {0x30, 0x0e, 0x02, 0x01, 0x7b, 0x09, 0x09, 0x80, 0xd7, 0x04, 
                    0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ThirdExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          !rec.c &&
          !rec.d
  );
}

void Test219() {
  uint8_t test[] = {0x30, 0x12, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x02, 0x22, 0x09, 
                    0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ThirdExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          !rec.d
  );
}

void Test220() {
  std::string strBuf = "test string";
  uint8_t test[] = {0x30, 0x30, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x02, 0x22, 0x30, 
                    0x1c, 0x02, 0x02, 0x03, 0xd8, 0x16, 0x0b, 0x74, 0x65, 0x73, 
                    0x74, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x09, 0x09, 
                    0x80, 0xd7, 0x05, 0xd4, 0x3e, 0xf9, 0xdb, 0x22, 0xd1, 0x09, 
                    0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ThirdExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          rec.d &&
          rec.d->e == 984 &&
          rec.d->f == strBuf &&
          !rec.d->g &&
          !rec.d->h
  );
}

void Test221() {
  std::string strBuf = "test string";
  uint8_t test[] = {0x30, 0x33, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x02, 0x22, 0x30, 
                    0x1f, 0x02, 0x02, 0x03, 0xd8, 0x16, 0x0b, 0x74, 0x65, 0x73, 
                    0x74, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x01, 0x01, 
                    0xff, 0x09, 0x09, 0x80, 0xd7, 0x05, 0xd4, 0x3e, 0xf9, 0xdb, 
                    0x22, 0xd1, 0x09, 0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 
                    0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ThirdExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          rec.d &&
          rec.d->e == 984 &&
          rec.d->f == strBuf &&
          rec.d->g && *rec.d->g == 0xFF &&
          !rec.d->h
  );
}

void Test222() {
  const char* str2 = "the string for h component";
  std::string strBuf = "test string";
  std::vector<uint8_t> str2Buf(str2, str2 + strlen(str2));
  uint8_t test[] = {0x30, 0x4c, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x02, 0x22, 0x30, 
                    0x38, 0x02, 0x02, 0x03, 0xd8, 0x16, 0x0b, 0x74, 0x65, 0x73, 
                    0x74, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x1e, 0x1a, 
                    0x74, 0x68, 0x65, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 
                    0x20, 0x66, 0x6f, 0x72, 0x20, 0x68, 0x20, 0x63, 0x6f, 0x6d, 
                    0x70, 0x6f, 0x6e, 0x65, 0x6e, 0x74, 0x09, 0x09, 0x80, 0xd7, 
                    0x05, 0xd4, 0x3e, 0xf9, 0xdb, 0x22, 0xd1, 0x09, 0x09, 0x80, 
                    0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ThirdExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          rec.d &&
          rec.d->e == 984 &&
          rec.d->f == strBuf &&
          !rec.d->g && 
          rec.d->h && *rec.d->h == str2Buf
  );
}

void Test223() {
  const char* str2 = "the string for h component";
  std::string strBuf = "test string";
  std::vector<uint8_t> str2Buf(str2, str2 + strlen(str2));
  uint8_t test[] = {0x30, 0x4f, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x02, 0x22, 0x30, 
                    0x3b, 0x02, 0x02, 0x03, 0xd8, 0x16, 0x0b, 0x74, 0x65, 0x73, 
                    0x74, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x01, 0x01, 
                    0xff, 0x1e, 0x1a, 0x74, 0x68, 0x65, 0x20, 0x73, 0x74, 0x72, 
                    0x69, 0x6e, 0x67, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x68, 0x20, 
                    0x63, 0x6f, 0x6d, 0x70, 0x6f, 0x6e, 0x65, 0x6e, 0x74, 0x09, 
                    0x09, 0x80, 0xd7, 0x05, 0xd4, 0x3e, 0xf9, 0xdb, 0x22, 0xd1, 
                    0x09, 0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 
                    0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ThirdExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          rec.d &&
          rec.d->e == 984 &&
          rec.d->f == strBuf &&
          rec.d->g && *rec.d->g == 0xFF &&
          rec.d->h && *rec.d->h == str2Buf
  );
}

void Test224() {
  uint8_t test[] = {0x31, 0x07, 0x80, 0x01, 0x7b, 0x81, 0x02, 0x02, 0x37};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ExtensionRootType rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 
  );
}

void Test225() {
  uint8_t test[] = {0x31, 0x0e, 0x80, 0x01, 0x7b, 0x83, 0x09, 0x80, 0xd7, 0x04, 
                    0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_FirstExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 && 
               !rec.b &&
               !rec.c 
  );
}

void Test226() {
  uint8_t test[] = {0x31, 0x15, 0x80, 0x01, 0x7b, 0x81, 0x01, 0xff, 0x82, 0x02, 
                    0x24, 0x9e, 0x83, 0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 
                    0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_FirstExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 && 
               rec.b && *rec.b == 0xFF && 
               rec.c && *rec.c == 9374
  );
}

void Test227() {
  uint8_t test[] = {0x31, 0x0e, 0x80, 0x01, 0x7b, 0x8f, 0x09, 0x80, 0xd7, 0x04, 
                    0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_SecondExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          !rec.c &&
          !rec.d 
  );
}

void Test228() {
  uint8_t test[] = {0x31, 0x12, 0x80, 0x01, 0x7b, 0x82, 0x02, 0x02, 0x22, 0x8f, 
                    0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_SecondExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          !rec.d
  );
}

void Test229() {
  std::string strBuf = "test string";
  uint8_t test[] = {0x31, 0x30, 0x80, 0x01, 0x7b, 0x82, 0x02, 0x02, 0x22, 0xa3, 
                    0x1c, 0x80, 0x02, 0x03, 0xd8, 0x81, 0x0b, 0x74, 0x65, 0x73, 
                    0x74, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x8a, 0x09, 
                    0x80, 0xd7, 0x05, 0xd4, 0x3e, 0xf9, 0xdb, 0x22, 0xd1, 0x8f, 
                    0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_SecondExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          rec.d &&
          rec.d->e == 984 &&
          rec.d->f == strBuf 
  );
}

void Test230() {
  uint8_t test[] = {0x31, 0x0e, 0x80, 0x01, 0x7b, 0x8f, 0x09, 0x80, 0xd7, 0x04, 
                    0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ThirdExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          !rec.c &&
          !rec.d 
  );
}

void Test231() {
  uint8_t test[] = {0x31, 0x12, 0x80, 0x01, 0x7b, 0x82, 0x02, 0x02, 0x22, 0x8f, 
                    0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ThirdExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          !rec.d 
  );
}

void Test232() {
  std::string strBuf = "test string";
  uint8_t test[] = {0x31, 0x30, 0x80, 0x01, 0x7b, 0x82, 0x02, 0x02, 0x22, 0xa3, 
                    0x1c, 0x80, 0x02, 0x03, 0xd8, 0x81, 0x0b, 0x74, 0x65, 0x73, 
                    0x74, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x8a, 0x09, 
                    0x80, 0xd7, 0x05, 0xd4, 0x3e, 0xf9, 0xdb, 0x22, 0xd1, 0x8f, 
                    0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ThirdExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          rec.d &&
          rec.d->e == 984 &&
          rec.d->f == strBuf &&
          !rec.d->g &&
          !rec.d->h 
  );
}

void Test233() {
  std::string strBuf = "test string";
  uint8_t test[] = {0x31, 0x33, 0x80, 0x01, 0x7b, 0x82, 0x02, 0x02, 0x22, 0xa3, 
                    0x1f, 0x80, 0x02, 0x03, 0xd8, 0x81, 0x0b, 0x74, 0x65, 0x73, 
                    0x74, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x82, 0x01, 
                    0xff, 0x8a, 0x09, 0x80, 0xd7, 0x05, 0xd4, 0x3e, 0xf9, 0xdb, 
                    0x22, 0xd1, 0x8f, 0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 
                    0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ThirdExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          rec.d &&
          rec.d->e == 984 &&
          rec.d->f == strBuf &&
          rec.d->g && *rec.d->g == 0xFF &&
          !rec.d->h 
  );
}

void Test234() {
  const char* str2 = "the string for h component";
  std::string strBuf = "test string";
  std::vector<uint8_t> str2Buf(str2, str2 + strlen(str2));
  uint8_t test[] = {0x31, 0x4c, 0x80, 0x01, 0x7b, 0x82, 0x02, 0x02, 0x22, 0xa3, 
                    0x38, 0x80, 0x02, 0x03, 0xd8, 0x81, 0x0b, 0x74, 0x65, 0x73, 
                    0x74, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x83, 0x1a, 
                    0x74, 0x68, 0x65, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 
                    0x20, 0x66, 0x6f, 0x72, 0x20, 0x68, 0x20, 0x63, 0x6f, 0x6d, 
                    0x70, 0x6f, 0x6e, 0x65, 0x6e, 0x74, 0x8a, 0x09, 0x80, 0xd7, 
                    0x05, 0xd4, 0x3e, 0xf9, 0xdb, 0x22, 0xd1, 0x8f, 0x09, 0x80, 
                    0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ThirdExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          rec.d &&
          rec.d->e == 984 &&
          rec.d->f == strBuf &&
          !rec.d->g && 
          rec.d->h && *rec.d->h == str2Buf 
  );
}

void Test235() {
  const char* str2 = "the string for h component";
  std::string strBuf = "test string";
  std::vector<uint8_t> str2Buf(str2, str2 + strlen(str2));
  uint8_t test[] = {0x31, 0x4f, 0x80, 0x01, 0x7b, 0x82, 0x02, 0x02, 0x22, 0xa3, 
                    0x3b, 0x80, 0x02, 0x03, 0xd8, 0x81, 0x0b, 0x74, 0x65, 0x73, 
                    0x74, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x82, 0x01, 
                    0xff, 0x83, 0x1a, 0x74, 0x68, 0x65, 0x20, 0x73, 0x74, 0x72, 
                    0x69, 0x6e, 0x67, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x68, 0x20, 
                    0x63, 0x6f, 0x6d, 0x70, 0x6f, 0x6e, 0x65, 0x6e, 0x74, 0x8a, 
                    0x09, 0x80, 0xd7, 0x05, 0xd4, 0x3e, 0xf9, 0xdb, 0x22, 0xd1, 
                    0x8f, 0x09, 0x80, 0xd7, 0x04, 0x6e, 0x3e, 0xf9, 0xdb, 0x22, 
                    0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ThirdExtension rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.a == 123 &&
          !rec.b &&
          rec.c && *rec.c == 546 &&
          rec.d &&
          rec.d->e == 984 &&
          rec.d->f == strBuf &&
          rec.d->g && *rec.d->g == 0xFF &&
          rec.d->h && *rec.d->h == str2Buf 
  );
}

void Test236() {
  uint8_t test[] = {0x09, 0x09, 0x80, 0xd2, 0x1e, 0xdb, 0xa5, 0xe3, 0x53, 0xf7, 0xcf};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ChoiceWithExtensible rec;
  ret = rec.DecodeBer(test, sizeof(test));
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec.FetchPresent() == ChoiceWithExtensible::PR_b &&
          rec.b() &&
          *rec.b() == 123.432
  );
#else
  CHECK_RESULT(rec.FetchPresent() == ChoiceWithExtensible::PR_b &&
          rec.b() == 123.432
  );
#endif
}

void Test237() {
  uint8_t test[] = {0x01, 0x01, 0xff};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ChoiceWithExtensible rec;
  ret = rec.DecodeBer(test, sizeof(test));
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec.FetchPresent() == ChoiceWithExtensible::PR_d &&
          rec.d() &&
          *rec.d() == 0xFF
  );
#else
  CHECK_RESULT(rec.FetchPresent() == ChoiceWithExtensible::PR_d &&
          rec.d() == 0xFF
  );
#endif
}

void Test238() {
  uint8_t test[] = {0x8a, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ChoiceWithExtensible rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.FetchPresent() == ChoiceWithExtensible::PR_NOTHING
  );
}

void Test239() {
  uint8_t test[] = {0x30, 0x12, 0x30, 0x10, 0x30, 0x06, 0x8a, 0x01, 0x01, 0x8c, 
                    0x01, 0x0a, 0x30, 0x06, 0x8a, 0x01, 0x02, 0x8c, 0x01, 0x14};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  const class SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I::sequenceRecord_I_IO_I& seqOf(rec.sequenceRecord_I_IO_I);
  INTERMEDIATE_CHECK(seqOf.size() == 2);
  const SequenceRecord_I_IO_I& rec1(seqOf[0]);
  const SequenceRecord_I_IO_I& rec2(seqOf[1]);
  CHECK_RESULT(rec1.type == 1 && 
              !rec1.type2 && 
              rec1.type3 == 10 &&
              rec2.type == 2 && 
              !rec2.type2 && 
              rec2.type3 == 20
  );
}

void Test240() {
  uint8_t test[] = {0x30, 0x03, 0x81, 0x01, 0xff};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_BD_B_BD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.val1 && 
                rec.val2 == 0xFF && 
                !rec.val3
  );
}

void Test241() {
  uint8_t test[] = {0x30, 0x09, 0x80, 0x01, 0x00, 0x81, 0x01, 0x00, 0x82, 0x01, 0xff};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_BD_B_BD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.val1 && *rec.val1 == 0 &&
                rec.val2 == 0 && 
              rec.val3 && *rec.val3 == 0xFF
  );
}

void Test242() {
  
  TEST_NUMBER;
  SequenceRecord_BD_B_BD rec;
#ifdef INSECURE_POINTERS
  rec.val1 = new BOOLEAN();
#else
  rec.val1.reset(new BOOLEAN());
#endif
  *rec.val1 = 0;
  rec.val2 = 1;
#ifdef INSECURE_POINTERS
  rec.val3 = new BOOLEAN();
#else
  rec.val3.reset(new BOOLEAN());
#endif
  *rec.val3 = 0xFF;
  
  INTERMEDIATE_COND(
          rec.val1 && *rec.val1 == 0 && 
             rec.val2 == 1 &&
          rec.val3 && *rec.val3 == 0xFF
  );
  
  rec.SetVal1Default();
  rec.SetVal3Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == 0xFF && 
             rec.val2 == 1 &&
          rec.val3 && *rec.val3 == 0
  );
}

void Test243() {
  TEST_NUMBER;
  SequenceRecord_BD_B_BD rec;
  rec.SetVal1Default();
  rec.SetVal3Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == 0xFF && 
             rec.val2 == 0 &&
          rec.val3 && *rec.val3 == 0
  );
}

void Test244() {
  TEST_NUMBER;
  SequenceRecord_BD_B_BD rec;
  rec.SetEmptyToDefault();
  
  CHECK_COND(rec.val1 && *rec.val1 == 0xFF && 
             rec.val2 == 0 &&
          rec.val3 && *rec.val3 == 0
  );
}

void Test245() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x1a, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_I646S_I646SO_I646SRefWithTag_I646SRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test246() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x1a, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_I646S_I646SO_I646SRefWithTag_I646SRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test247() {
  uint8_t test[] = {0x02, 0x02, 0x6f, 0x2f};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ANY rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.size() == 4);
  NativeInteger number;
  ret = number.DecodeBer(rec.data(), rec.size());
  CHECK_RESULT(number == (long)28463);
}

void Test248() {
  uint8_t test[] = {0x02, 0x02, 0x6f, 0x2f};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ANY rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  ANY rec2(rec1);
  INTERMEDIATE_CHECK(rec1.size() == 4 && rec2.size() == 4);
  NativeInteger number1;
  ret = number1.DecodeBer(rec1.data(), rec1.size());
  INTERMEDIATE_CHECK(number1 == (long)28463);
  NativeInteger number2;
  ret = number2.DecodeBer(rec2.data(), rec2.size());
  CHECK_RESULT(number2 == (long)28463);
}

void Test249() {
  uint8_t test[] = {0x02, 0x02, 0x6f, 0x2f};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ANY rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  ANY rec2(std::move(rec1));
  INTERMEDIATE_CHECK(rec1.size() == 0 && rec2.size() == 4);
  NativeInteger number2;
  ret = number2.DecodeBer(rec2.data(), rec2.size());
  CHECK_RESULT(number2 == (long)28463);
}

void Test250() {
  uint8_t test[] = {0x02, 0x02, 0x6f, 0x2f};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ANY rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  ANY rec2;
  rec2 = rec1;
  INTERMEDIATE_CHECK(rec1.size() == 4 && rec2.size() == 4);
  NativeInteger number1;
  ret = number1.DecodeBer(rec1.data(), rec1.size());
  INTERMEDIATE_CHECK(number1 == (long)28463);
  NativeInteger number2;
  ret = number2.DecodeBer(rec2.data(), rec2.size());
  CHECK_RESULT(number2 == (long)28463);
}

void Test251() {
  uint8_t test[] = {0x02, 0x02, 0x6f, 0x2f};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ANY rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  ANY rec2;
  rec2 = std::move(rec1);
  INTERMEDIATE_CHECK(rec1.size() == 0 && rec2.size() == 4);
  NativeInteger number2;
  ret = number2.DecodeBer(rec2.data(), rec2.size());
  CHECK_RESULT(number2 == (long)28463);
}

void Test252() {
  uint8_t test[] = {0x02, 0x04, 0x31, 0xf0, 0x2d, 0x82};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  INTEGER rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTEGER mustBe;
  mustBe.FromLong(837823874);
  CHECK_RESULT(rec == mustBe
  );
}

void Test253() {
  uint8_t test[] = {0x02, 0x04, 0x31, 0xf0, 0x2d, 0x82};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  INTEGER rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTEGER mustNotBe;
  mustNotBe.FromLong(837823875);
  CHECK_RESULT(! (rec == mustNotBe)
  );
}

void Test254() {
  uint8_t test[] = {0x02, 0x04, 0x31, 0xf0, 0x2d, 0x82};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  INTEGER rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTEGER mustBe;
  mustBe.FromLong(837823874);
  CHECK_RESULT(! (rec != mustBe)
  );
}

void Test255() {
  uint8_t test[] = {0x02, 0x04, 0x31, 0xf0, 0x2d, 0x82};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  INTEGER rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTEGER mustNotBe;
  mustNotBe.FromLong(837823875);
  CHECK_RESULT(rec != mustNotBe
  );
}

void Test256() {
  TEST_NUMBER;
  SetOfSeqOfSeq_I rec;
  std::vector<_SetOfSeqOfSeq_I>& list = rec;
  list.emplace_back();
  std::vector<__SetOfSeqOfSeq_I>& list2 = list[0];
  list2.emplace_back();
  list2[0].int1 = 123;
  
  CHECK_COND(rec.size() == 1 && 
             rec[0].size() == 1 && 
             123 == rec[0][0].int1);
}

void Test257() {
  TEST_NUMBER;
  
#define CHECK_OP(Type)                                      \
  {                                                         \
    std::vector<uint8_t> mustBe = {0x12, 0x45};             \
    std::vector<uint8_t> vec = mustBe;                      \
    {                                                       \
      Type rec;                                             \
      rec = vec;                                            \
      INTERMEDIATE_COND(rec == mustBe && vec.size() == 2);  \
    }                                                       \
    {                                                       \
      Type rec;                                             \
      rec = std::move(vec);                                 \
      INTERMEDIATE_COND(rec == mustBe && vec.size() == 0);  \
    }                                                       \
  }
#define CHECK_OP_STRING(Type)                               \
  {                                                         \
    std::string mustBe = "test string";                     \
    std::string vec = mustBe;                               \
    {                                                       \
      Type rec;                                             \
      rec = vec;                                            \
      INTERMEDIATE_COND(rec == mustBe && vec.size() == 11); \
    }                                                       \
    {                                                       \
      Type rec;                                             \
      rec = std::move(vec);                                 \
      INTERMEDIATE_COND(rec == mustBe && vec.size() == 0);  \
    }                                                       \
  }
#define CHECK_OP_SIMPLE_VALUE(Type, value)                  \
  {                                                         \
    Type rec;                                               \
    rec = value;                                            \
    INTERMEDIATE_COND(rec == value);                        \
  }

  CHECK_OP(ANY);
  CHECK_OP(BIT_STRING);
  CHECK_OP(BMPString);
  CHECK_OP(ENUMERATED);
  CHECK_OP_STRING(GeneralString);
  CHECK_OP(GeneralizedTime);
  CHECK_OP_STRING(GraphicString);
  CHECK_OP_STRING(IA5String);
  CHECK_OP(INTEGER);
  CHECK_OP_STRING(ISO646String);
  CHECK_OP_STRING(NumericString);
  CHECK_OP(OBJECT_IDENTIFIER);
  CHECK_OP(OCTET_STRING);
  CHECK_OP_STRING(ObjectDescriptor);
  CHECK_OP_STRING(PrintableString);
  CHECK_OP(REAL);
  CHECK_OP(RELATIVE_OID);
  CHECK_OP_STRING(T61String);
  CHECK_OP_STRING(TeletexString);
  CHECK_OP(UTCTime);
  CHECK_OP_STRING(UTF8String);
  CHECK_OP(UniversalString);
  CHECK_OP_STRING(VideotexString);
  CHECK_OP_STRING(VisibleString);
  
  CHECK_OP(AnyRef);
  CHECK_OP(BitStringRef);
  CHECK_OP(BMPStringRefWithTag);
  CHECK_OP_SIMPLE_VALUE(BooleanRef, 1);
  CHECK_OP_SIMPLE_VALUE(EnumeratedRef, 1);
  CHECK_OP_SIMPLE_VALUE(EnumeratedRefRef, 1);
  CHECK_OP_STRING(GenStringRefWithTag);
  CHECK_OP(GeneralizedTimeRefWithTag);
  CHECK_OP_STRING(GraStringRefWithTag);
  CHECK_OP_STRING(IA5StringRefWithTag);
  CHECK_OP_SIMPLE_VALUE(IntegerRefWithTag, 381663);
  CHECK_OP_STRING(ISO646StringRefWithTag);
  CHECK_OP_SIMPLE_VALUE(RealRef, 123.234);
  CHECK_OP_SIMPLE_VALUE(NullRef, 2348);
  CHECK_OP_STRING(NumericStringRefWithTag);
  CHECK_OP_STRING(ObjDescRefWithTag);
  CHECK_OP(ObjectIdentifierRef);
  CHECK_OP(OctetStringRef);
  CHECK_OP_STRING(PrintableStringRefWithTag);
  CHECK_OP(RelativeOidRefWithTag);
  CHECK_OP_STRING(T61StringRefWithTag);
  CHECK_OP_STRING(TeletexStringRefWithTag);
  CHECK_OP(UniversalStringRefWithTag);
  CHECK_OP(UtcTimeRefWithTag);
  CHECK_OP_STRING(UTF8StringRefWithTag);
  CHECK_OP_STRING(VideotexStringRefWithTag);
  CHECK_OP_STRING(VisibleStringRefWithTag);
 
  CHECK_COND(true);
#undef CHECK_OP
#undef CHECK_OP_SIMPLE_VALUE
#undef CHECK_OP_STRING
}

void Test258() {
  TEST_NUMBER;
  
#define CHECK_OP(Type)                                      \
  {                                                         \
    std::vector<NativeInteger> mustBe;                      \
    mustBe.emplace_back();                                  \
    mustBe.emplace_back();                                  \
    mustBe.emplace_back();                                  \
    mustBe[0] = 123;                                        \
    mustBe[1] = -274;                                       \
    mustBe[2] = 9278483;                                    \
    std::vector<NativeInteger> vec = mustBe;                \
    {                                                       \
      Type rec;                                             \
      rec = vec;                                            \
      INTERMEDIATE_COND(rec == mustBe &&                    \
                        rec.size() == 3 &&                  \
                        rec[0] == 123 &&                    \
                        rec[1] == -274 &&                   \
                        rec[2] == 9278483 &&                \
                        vec.size() == 3);                   \
    }                                                       \
    {                                                       \
      Type rec;                                             \
      rec = std::move(vec);                                 \
      INTERMEDIATE_COND(rec == mustBe &&                    \
                        rec.size() == 3 &&                  \
                        rec[0] == 123 &&                    \
                        rec[1] == -274 &&                   \
                        rec[2] == 9278483 &&                \
                        vec.size() == 0);                   \
    }                                                       \
  }

  CHECK_OP(SetOfInteger);
  CHECK_OP(SetOfIntegerRef);
  
  CHECK_COND(true);
#undef CHECK_OP
}

void Test259() {
  std::vector<uint8_t> mustBe = {0x31, 0xf0, 0x2d, 0x82};
  std::vector<uint8_t> test = {0x02, 0x04, 0x31, 0xf0, 0x2d, 0x82};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  long l;
  unsigned long ul;
  INTEGER rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe && 
          rec.ToLong(l) && l == 837823874 &&
          rec.ToULong(ul) && ul == 837823874
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test260() {
  std::vector<uint8_t> mustBe = {0xfb, 0x9c, 0x80, 0xdf};
  std::vector<uint8_t> test = {0x02, 0x04, 0xfb, 0x9c, 0x80, 0xdf};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  long l;
  unsigned long ul;
  INTEGER rec;
  ret = rec.DecodeBer(test);
  rec.ToULong(ul);
  INTERMEDIATE_CHECK(rec == mustBe && 
          rec.ToLong(l) && l == -73629473 && 
          rec.ToULong(ul) && ul == 4221337823
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test261() {
  std::vector<uint8_t> mustBe = {0x00, 0xfb, 0x9c, 0x80, 0xdf};
  std::vector<uint8_t> test = {0x02, 0x05, 0x00, 0xfb, 0x9c, 0x80, 0xdf};
  
  TEST_NUMBER;
  INTEGER rec;
  INTERMEDIATE_COND(rec.FromULong(4221337823) && 
                     rec == mustBe
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test262() {
  std::vector<uint8_t> mustBe = {0xfb, 0x9c, 0x80, 0xdf};
  std::vector<uint8_t> test = {0x02, 0x04, 0xfb, 0x9c, 0x80, 0xdf};
  
  TEST_NUMBER;
  INTEGER rec;
  INTERMEDIATE_COND(rec.FromLong(-73629473) && 
                     rec == mustBe
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test263() {
  std::vector<uint8_t> mustBe = {0x31, 0xf0, 0x2d, 0x82};
  //differs from INTEGER test only in tag (10)
  std::vector<uint8_t> test = {0x0a, 0x04, 0x31, 0xf0, 0x2d, 0x82};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  long l;
  unsigned long ul;
  ENUMERATED rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe && 
          rec.ToLong(l) && l == 837823874 &&
          rec.ToULong(ul) && ul == 837823874
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test264() {
  std::vector<uint8_t> mustBe = {0xfb, 0x9c, 0x80, 0xdf};
  //differs from INTEGER test only in tag (10)
  std::vector<uint8_t> test = {0x0a, 0x04, 0xfb, 0x9c, 0x80, 0xdf};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  long l;
  unsigned long ul;
  ENUMERATED rec;
  ret = rec.DecodeBer(test);
  rec.ToULong(ul);
  INTERMEDIATE_CHECK(rec == mustBe && 
          rec.ToLong(l) && l == -73629473 && 
          rec.ToULong(ul) && ul == 4221337823
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test265() {
  std::vector<uint8_t> mustBe = {0x00, 0xfb, 0x9c, 0x80, 0xdf};
  //differs from INTEGER test only in tag (10)
  std::vector<uint8_t> test = {0x0a, 0x05, 0x00, 0xfb, 0x9c, 0x80, 0xdf};
  
  TEST_NUMBER;
  ENUMERATED rec;
  INTERMEDIATE_COND(rec.FromULong(4221337823) && 
                     rec == mustBe
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test266() {
  std::vector<uint8_t> mustBe = {0xfb, 0x9c, 0x80, 0xdf};
  //differs from INTEGER test only in tag (10)
  std::vector<uint8_t> test = {0x0a, 0x04, 0xfb, 0x9c, 0x80, 0xdf};
  
  TEST_NUMBER;
  ENUMERATED rec;
  INTERMEDIATE_COND(rec.FromLong(-73629473) && 
                     rec == mustBe
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test267() {
  std::vector<uint8_t> mustBe = {0x80, 0xea, 0x0c, 0x7c, 0x0b, 0x60, 0xb6, 0xd5, 0x3d};
  std::vector<uint8_t> test = {0x09, 0x09, 0x80, 0xea, 0x0c, 0x7c, 0x0b, 0x60, 0xb6, 0xd5, 0x3d};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  double d;
  REAL rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe && rec.ToDouble(d) && d == 837823874.856765
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test268() {
  std::vector<uint8_t> mustBe = {0xc0, 0xe6, 0x11, 0x8d, 0xfc, 0x84, 0x7f, 0xc3, 0x2f};
  std::vector<uint8_t> test = {0x09, 0x09, 0xc0, 0xe6, 0x11, 0x8d, 0xfc, 0x84, 0x7f, 0xc3, 0x2f};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  double d;
  REAL rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe && rec.ToDouble(d) && d == -73629473.124768
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test269() {
  std::vector<uint8_t> test = {0x01, 0x01, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BOOLEAN rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == 0);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test270() {
  std::vector<uint8_t> test = {0x01, 0x01, 0xff};
  TEST_NUMBER;
  BOOLEAN rec;
  rec = 1;
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test271() {
  std::vector<uint8_t> test = {0x05, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  NULL_t rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(true);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test272() {
  std::vector<uint8_t> test = {0x02, 0x04, 0x31, 0xF0, 0x2D, 0x82};
  TEST_NUMBER
  NativeInteger rec;
  asn_dec_rval_t ret;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == 837823874)
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test273() {
  TEST_NUMBER
  {
    std::vector<uint8_t> test = {0x02, 0x04, 0xfb, 0x9c, 0x80, 0xdf};
    NativeInteger rec;
    asn_dec_rval_t ret;
    ret = rec.DecodeBer(test);
    INTERMEDIATE_CHECK(rec == -73629473)
    std::vector<uint8_t> bufferEnc;
    asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
    INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  }
  {
    std::vector<uint8_t> test = {0x02, 0x04, 0x88, 0xca, 0x6c, 0x00};
    NativeInteger rec;
    asn_dec_rval_t ret;
    ret = rec.DecodeBer(test);
    INTERMEDIATE_CHECK(rec == -2000000000)
    std::vector<uint8_t> bufferEnc;
    asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
    CHECK_RESULT_ENCODING(bufferEnc == test);
  }
}

void Test274() {
  std::vector<uint8_t> test = {0x0a, 0x04, 0x31, 0xF0, 0x2D, 0x82};
  TEST_NUMBER
  NativeEnumerated rec;
  asn_dec_rval_t ret;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == 837823874)
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test275() {
  std::vector<uint8_t> test = {0x0a, 0x04, 0xfb, 0x9c, 0x80, 0xdf};
  TEST_NUMBER
  NativeEnumerated rec;
  asn_dec_rval_t ret;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == -73629473)
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test276() {
  std::vector<uint8_t> test = {0x09, 0x09, 0x80, 0xe4, 0x0c, 0x60, 0x2a, 0xc1, 0xf7, 0xce, 
                    0xd9};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  NativeReal rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == 12976812.123);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test277() {
  std::vector<uint8_t> test = {0x09, 0x09, 0xc0, 0xed, 0x11, 0x45, 0xa6, 0x95, 0x7e, 0xfb, 
                    0xe7};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  NativeReal rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == -9272873647.873);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test278() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  std::vector<uint8_t> test = {0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 
                    0xfe, 0xcd};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test279() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  std::vector<uint8_t> test = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe && rec.GetBitsUnused() == 5);
  rec[rec.size() - 1] = 0xc5;
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test280() {
  std::vector<uint8_t> test = {0x02, 0x02, 0x6f, 0x2f};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ANY rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 4);
  NativeInteger number;
  ret = number.DecodeBer(rec.data(), rec.size());
  INTERMEDIATE_CHECK(number == (long)28463);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test281() {
  std::vector<uint8_t> test = {0x30, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 
                    0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.type == 123 && 
               !rec.type2 && 
               rec.type3 == 92367624
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test282() {
  std::vector<uint8_t> test = {0x30, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 0xb1, 0x92, 
                    0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.type == 123 && 
               rec.type2 && *rec.type2 == 635282 &&
               rec.type3 == 92367624
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test283() {
  std::vector<uint8_t> test = {0x30, 0x09, 0x81, 0x01, 0x7b, 0x82, 0x04, 0x05, 0x81, 0x6b, 
                    0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IO_I_I_Automatic rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(!rec.type && 
               rec.type2 == 123 && 
               rec.type3 == 92367624
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test284() {
  std::vector<uint8_t> test = {0x30, 0x0e, 0x80, 0x03, 0x09, 0xb1, 0x92, 0x81, 0x01, 
                    0x7b, 0x82, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IO_I_I_Automatic rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.type && *rec.type == 635282 &&
               rec.type2 == 123 && 
               rec.type3 == 92367624
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test285() {
  std::vector<uint8_t> test = {0x30, 0x0f, 0x8a, 0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 
                    0x08, 0xae, 0x04, 0x81, 0x02, 0x34, 0xaf};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.type == 123 && 
                !rec.type2 &&
                rec.type3 == 92367624 &&
                !rec.type4 && 
                !rec.type5.value1 &&
                rec.type5.value2 == 13487
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test286() {
  std::vector<uint8_t> test = {0x30, 0x20, 0x8a, 0x01, 0x7b, 0x8b, 0x02, 0x24, 0x39, 0x8c, 
                    0x04, 0x05, 0x81, 0x6b, 0x08, 0xad, 0x05, 0x80, 0x03, 0x0d, 
                    0x4c, 0xd2, 0xae, 0x0a, 0x80, 0x04, 0x00, 0xbc, 0x69, 0xb8, 
                    0x81, 0x02, 0x34, 0xaf};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.type == 123 && 
                rec.type2 &&
                *rec.type2 == 9273 &&
                rec.type3 == 92367624 &&
                rec.type4 && 
                rec.type4->value1 == 871634 &&
                rec.type5.value1 &&
                *rec.type5.value1 == 12347832 &&
                rec.type5.value2 == 13487
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test287() {
  std::vector<uint8_t> mustBe1 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  std::vector<uint8_t> mustBe2 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x32};
  std::vector<uint8_t> mustBe3 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x33};
  std::vector<uint8_t> mustBe4 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x34};

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x1e, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_BmpS_BmpSO_BmpSRefWithTag_BmpSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test288() {
  std::vector<uint8_t> mustBe1 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  std::vector<uint8_t> mustBe2 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x32};
  std::vector<uint8_t> mustBe3 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x33};
  std::vector<uint8_t> mustBe4 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x34};
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x1e, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_BmpS_BmpSO_BmpSRefWithTag_BmpSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test289() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x1b, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_GenS_GenSO_GenSRefWithTag_GenSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test290() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x1b, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_GenS_GenSO_GenSRefWithTag_GenSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test291() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x19, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_GraS_GraSO_GraSRefWithTag_GraSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test292() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x19, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_GraS_GraSO_GraSRefWithTag_GraSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test293() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x16, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_IA5S_IA5SO_IA5SRefWithTag_IA5SRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test294() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x16, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_IA5S_IA5SO_IA5SRefWithTag_IA5SRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test295() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x1a, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_I646S_I646SO_I646SRefWithTag_I646SRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test296() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x1a, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_I646S_I646SO_I646SRefWithTag_I646SRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test297() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x12, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test298() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x12, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test299() {
  std::vector<uint8_t> mustBe1 = {0x2b, 0x06, 0x01, 0x04, 0x01, 0xc9, 0x13, 0x84, 0xe4, 0x7a};
  std::vector<uint8_t> mustBe3 = {0x2b, 0x06, 0x01, 0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01};
  
  std::vector<uint8_t> test = {0x30, 0x1b, 0x30, 0x19, 0x06, 0x0a, 0x2b, 0x06, 0x01, 0x04, 
                    0x01, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x06, 0x0b, 0x2b, 0x06, 
                    0x01, 0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_OI_OIO_OIRef_OIRefO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.objectIdentifier1 == mustBe1 &&
            !rec.seq.objectIdentifier2 &&
          rec.seq.objectIdentifier3 == mustBe3 &&
          !rec.seq.objectIdentifier4
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test300() {
  std::vector<uint8_t> mustBe1 = {0x2b, 0x06, 0x01, 0x04, 0x01, 0xc9, 0x13, 0x84, 0xe4, 0x7a};
  std::vector<uint8_t> mustBe2 = {0x2b, 0x06, 0x01, 0x04, 0x02, 0xc9, 0x13};
  std::vector<uint8_t> mustBe3 = {0x2b, 0x06, 0x01, 0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01};
  std::vector<uint8_t> mustBe4 = {0x2b, 0x06, 0x01, 0x04, 0x04, 0xc9, 0x13};
  
  std::vector<uint8_t> test = {0x30, 0x2d, 0x30, 0x2b, 0x06, 0x0a, 0x2b, 0x06, 0x01, 0x04, 
                    0x01, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x81, 0x07, 0x2b, 0x06, 
                    0x01, 0x04, 0x02, 0xc9, 0x13, 0x06, 0x0b, 0x2b, 0x06, 0x01, 
                    0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x06, 0x07, 
                    0x2b, 0x06, 0x01, 0x04, 0x04, 0xc9, 0x13};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_OI_OIO_OIRef_OIRefO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.objectIdentifier1 == mustBe1 &&
            rec.seq.objectIdentifier2 && 
            *rec.seq.objectIdentifier2 == mustBe2 &&
          rec.seq.objectIdentifier3 == mustBe3 &&
          rec.seq.objectIdentifier4 &&
          *rec.seq.objectIdentifier4 == mustBe4
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Tests201_300() {
  Test201(); //SequenceRecord-ED-E-ED-ED
  Test202(); //SequenceRecord-VSD-VS-VSD-VSD
  Test203(); //SequenceRecord-VSD-VS-VSD-VSD
  Test204(); //SequenceRecord-VSD-VS-VSD-VSD
  Test205(); //SequenceRecord-VSD-VS-VSD-VSD
  Test206(); //SetRecord-ID-I-ID-ID
  Test207(); //SetRecord-ID-I-ID-ID
  Test208(); //SetRecord-ID-I-ID-ID
  Test209(); //SetRecord-ID-I-ID-ID
  Test210(); //SequenceRecord-ID-I-ID-ID::SetEmptyToDefault()
  Test211(); //SetRecord-ID-I-ID-ID::SetEmptyToDefault()
  Test212(); //SequenceRecord-ExtensionRootType
  Test213(); //SequenceRecord-FirstExtension
  Test214(); //SequenceRecord-FirstExtension
  Test215(); //SequenceRecord-SecondExtension
  Test216(); //SequenceRecord-SecondExtension
  Test217(); //SequenceRecord-SecondExtension
  Test218(); //SequenceRecord-ThirdExtension
  Test219(); //SequenceRecord-ThirdExtension
  Test220(); //SequenceRecord-ThirdExtension
  Test221(); //SequenceRecord-ThirdExtension
  Test222(); //SequenceRecord-ThirdExtension
  Test223(); //SequenceRecord-ThirdExtension
  Test224(); //SetRecord-ExtensionRootType
  Test225(); //SetRecord-FirstExtension
  Test226(); //SetRecord-FirstExtension
  Test227(); //SetRecord-SecondExtension
  Test228(); //SetRecord-SecondExtension
  Test229(); //SetRecord-SecondExtension
  Test230(); //SetRecord-ThirdExtension
  Test231(); //SetRecord-ThirdExtension
  Test232(); //SetRecord-ThirdExtension
  Test233(); //SetRecord-ThirdExtension
  Test234(); //SetRecord-ThirdExtension
  Test235(); //SetRecord-ThirdExtension
  Test236(); //ChoiceWithExtensible
  Test237(); //ChoiceWithExtensible
  Test238(); //ChoiceWithExtensible
  Test239(); //SequenceRecord-SeqOfSeqRec-SeqRec-I-IO-I + SequenceRecord-I-IO-I
  Test240(); //SequenceRecord-BD-B-BD
  Test241(); //SequenceRecord-BD-B-BD
  Test242(); //SequenceRecord-BD-B-BD
  Test243(); //SequenceRecord-BD-B-BD
  Test244(); //SequenceRecord-BD-B-BD::SetEmptyToDefault()
  Test245(); //SequenceRecord-IS-I646S-I646SO-I646SRefWithTag-I646SRefWithTagO+ISO646StringRefWithTag (the same as SequenceRecord-IS-VisS-VisSO-VisSRefWithTag-VisSRefWithTagO)
  Test246(); //SequenceRecord-IS-I646S-I646SO-I646SRefWithTag-I646SRefWithTagO+ISO646StringRefWithTag (the same as SequenceRecord-IS-VisS-VisSO-VisSRefWithTag-VisSRefWithTagO)
  Test247(); //ANY
  Test248(); //ANY copy constructor
  Test249(); //ANY move constructor
  Test250(); //ANY copy =
  Test251(); //ANY move =
  Test252(); //INTEGER ==
  Test253(); //INTEGER ==
  Test254(); //INTEGER !=
  Test255(); //INTEGER !=
  Test256(); //SetOfSeqOfSeq-I without BER decoding since asn1c cannot generate code compatible with C++ for making tests
  Test257(); //operator = (std::vector<uint8_t>) of various classes
  Test258(); //operator = (std::vector) for SetOfInteger and SetOfIntegerRef
  Test259(); //INTEGER::EncodeDer
  Test260(); //INTEGER::EncodeDer
  Test261(); //INTEGER::EncodeDer
  Test262(); //INTEGER::EncodeDer
  Test263(); //ENUMERATED::EncodeDer
  Test264(); //ENUMERATED::EncodeDer
  Test265(); //ENUMERATED::EncodeDer
  Test266(); //ENUMERATED::EncodeDer
  Test267(); //REAL::EncodeDer
  Test268(); //REAL::EncodeDer
  Test269(); //BOOLEAN::EncodeDer
  Test270(); //BOOLEAN::EncodeDer
  Test271(); //NULL::EncodeDer
  Test272(); //NativeInteger::EncodeDer
  Test273(); //NativeInteger::EncodeDer
  Test274(); //NativeEnumerated::EncodeDer
  Test275(); //NativeEnumerated::EncodeDer
  Test276(); //NativeReal::EncodeDer
  Test277(); //NativeReal::EncodeDer
  Test278(); //OCTET_STRING::EncodeDer
  Test279(); //BIT_STRING::EncodeDer
  Test280(); //ANY::EncodeDer
  Test281(); //SequenceRecord-I-IO-I::EncodeDer
  Test282(); //SequenceRecord-I-IO-I::EncodeDer
  Test283(); //SequenceRecord-IO-I-I-Automatic::EncodeDer
  Test284(); //SequenceRecord-IO-I-I-Automatic::EncodeDer
  Test285(); //SequenceRecord_I_IO_I_S_1I_S_1IO_1I::EncodeDer
  Test286(); //SequenceRecord_I_IO_I_S_1I_S_1IO_1I::EncodeDer
  Test287(); //SequenceRecord-IS-BmpS-BmpSO-BmpSRefWithTag-BmpSRefWithTagO::EncodeDer
  Test288(); //SequenceRecord-IS-BmpS-BmpSO-BmpSRefWithTag-BmpSRefWithTagO::EncodeDer
  Test289(); //SequenceRecord-IS-GenS-GenSO-GenSRefWithTag-GenSRefWithTagO::EncodeDer
  Test290(); //SequenceRecord-IS-GenS-GenSO-GenSRefWithTag-GenSRefWithTagO::EncodeDer
  Test291(); //SequenceRecord-IS-GraS-GraSO-GraSRefWithTag-GraSRefWithTagO::EncodeDer
  Test292(); //SequenceRecord-IS-GraS-GraSO-GraSRefWithTag-GraSRefWithTagO::EncodeDer
  Test293(); //SequenceRecord-IS-IA5S-IA5SO-IA5SRefWithTag-IA5SRefWithTagO::EncodeDer
  Test294(); //SequenceRecord-IS-IA5S-IA5SO-IA5SRefWithTag-IA5SRefWithTagO::EncodeDer
  Test295(); //SequenceRecord-IS-I646S-I646SO-I646SRefWithTag-I646SRefWithTagO::EncodeDer
  Test296(); //SequenceRecord-IS-I646S-I646SO-I646SRefWithTag-I646SRefWithTagO::EncodeDer
  Test297(); //SequenceRecord-IS-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO::EncodeDer
  Test298(); //SequenceRecord-IS-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO::EncodeDer
  Test299(); //SequenceRecord-IS-OI-OIO-OIRef-OIRefO::EncodeDer
  Test300(); //SequenceRecord-IS-OI-OIO-OIRef-OIRefO::EncodeDer
}

#endif	/* TESTS201_300_HPP */

