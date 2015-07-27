#include "headers.hpp"
#include "string.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

size_t testCounter = 0;
uint32_t countOK = 0, countFAILED = 0, skippedCount = 0;
size_t testMinNumber = 1;
std::vector<size_t> failedNumbers;


#define TEST_NUMBER PrintTestNumber();
#define OK if (testCounter >= testMinNumber) printf("OK\n"); ++countOK;
#define OK_SKIPPED if (testCounter >= testMinNumber) printf("OK (skipped)\n"); ++countOK; ++skippedCount;

#define TEST_FAILED_MSG(message) {            \
    if (testCounter >= testMinNumber) message \
    failedNumbers.push_back(testCounter);     \
    ++countFAILED;                            \
    return; }
#define TEST_FAILED TEST_FAILED_MSG(printf("FAILED (code: %d, consumed: %u)\n", (int)ret.code, (uint32_t)ret.consumed);)
#define TEST_FAILED_COND TEST_FAILED_MSG(printf("FAILED\n");)
#define TEST_FAILED_ENCODING TEST_FAILED_MSG(printf("FAILED (encoding)\n");)

#define CHECK(condition, FAILED_ACTIONS)  \
  if (condition) {                        \
    OK                                    \
  } else {                                \
    FAILED_ACTIONS                        \
  }
#define CHECK_RESULT(condition) CHECK(ret.code == RC_OK && (condition), TEST_FAILED)
#define CHECK_RESULT_ENCODING(condition) CHECK(enc.encoded >= 0 && (condition), TEST_FAILED_ENCODING) 
#define CHECK_COND(condition) CHECK(condition, TEST_FAILED_COND)

#define INTERMEDIATE(condition, FAILED_ACTIONS) \
  if (!(condition)) {                           \
    FAILED_ACTIONS                              \
  } 
#define INTERMEDIATE_CHECK(condition) INTERMEDIATE(ret.code == RC_OK && (condition), TEST_FAILED)
#define INTERMEDIATE_CHECK_ENCODING(condition) INTERMEDIATE(enc.encoded >= 0 && (condition), TEST_FAILED_ENCODING)
#define INTERMEDIATE_COND(condition) INTERMEDIATE(condition, TEST_FAILED_COND)

#define CHECK_OUT_printResult(mustOut, printResult, intermediate)             \
  {                                                                           \
    std::stringstream out(std::ios_base::out);                                \
    INTERMEDIATE_COND(rec.Print(out));                                        \
    if (printResult)                                                          \
      printf("<%s>\n", out.str().c_str());                                    \
    INTERMEDIATE_COND(out.str() == mustOut);                                  \
  }                                                                           \
  {                                                                           \
    std::stringstream out(std::ios_base::out);                                \
    out << rec;                                                               \
    INTERMEDIATE_COND(out);                                                   \
    if (printResult)                                                          \
      printf("<%s>\n", out.str().c_str());                                    \
    if (intermediate) {                                                       \
      INTERMEDIATE_COND(out.str() == mustOut);                                \
    } else {                                                                  \
      CHECK_COND(out.str() == mustOut);                                       \
    }                                                                         \
  }

#define CHECK_OUTt(mustOut) CHECK_OUT_printResult(mustOut, true, false)
#define CHECK_OUT(mustOut) CHECK_OUT_printResult(mustOut, false, false)
#define INTERMEDIATE_OUTt(mustOut) CHECK_OUT_printResult(mustOut, true, true)
#define INTERMEDIATE_OUT(mustOut) CHECK_OUT_printResult(mustOut, false, true)


void PrintLn(const asn_dec_rval_t& rval) {
  printf("code: %d   consumed: %u\n", rval.code, (uint32_t)rval.consumed);
}

std::vector<uint8_t> ReadFile(const char* fileName) {
  std::fstream f(fileName, std::ios_base::in);
  f.seekg (0, f.end);
  int length = f.tellg();
  f.seekg (0, f.beg);
  
  std::vector<uint8_t> buf(length);
  f.read((char*)buf.data(), buf.size());
  f.close();
  return std::move(buf);
}

void PrintLn(const std::vector<uint8_t>& vec) {
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    printf("%.2x ", *it);
  }
  printf("\n");
}

void PrintLn(const std::vector<unsigned int>& vec) {
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    printf("%u ", *it);
  }
  printf("\n");
}

void PrintTestNumber() {
  ++testCounter;
  if (testCounter >= testMinNumber)
    printf("Test %u: ", (uint32_t)testCounter);
}

#include "tests1_100.hpp"
#include "tests101_200.hpp"
#include "tests201_300.hpp"
#include "tests301_400.hpp"
#include "tests401_500.hpp"
#include "NativeInteger.hpp"


void Test501() {
  uint8_t test[] = {0x31, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfInteger rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2 + 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  SetOfInteger rec2;
  rec2 = rec;
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.size() == 3 && 
              rec2[0] == 1 && 
             rec2[1] == 2 && 
             rec2[2] == 3
  );
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_RESULT(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 2 && 
             rec[2] == 3
  );
}

void Test502() {
  uint8_t test[] = {0x31, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfInteger rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2 + 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  SetOfInteger rec2;
  rec2 = std::move(rec);
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.size() == 3 && 
              rec2[0] == 1 && 
             rec2[1] == 2 && 
             rec2[2] == 3
  );
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_COND(ret.code == RC_FAIL);
}

void Test503() {
  uint8_t test1[] = {0x31, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  uint8_t test2[] = {0x31, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x0a, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfInteger rec;
  ret = rec.DecodeBer(test1, sizeof(test1));
  INTERMEDIATE_CHECK(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 2 && 
             rec[2] == 3
  );
  ret = rec.DecodeBer(test2, sizeof(test2));
  CHECK_RESULT(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 10 && 
             rec[2] == 3
  );
}

void Test504() {
  uint8_t test[] = {0x30, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceOfInteger rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2 + 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  SequenceOfInteger rec2(rec);
  size_t consumed = ret.consumed;
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.size() == 3 && 
              rec2[0] == 1 && 
             rec2[1] == 2 && 
             rec2[2] == 3
  );
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_RESULT(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 2 && 
             rec[2] == 3
  );
}

void Test505() {
  uint8_t test[] = {0x30, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceOfInteger rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2 + 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  SequenceOfInteger rec2(std::move(rec));
  size_t consumed = ret.consumed;
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.size() == 3 && 
              rec2[0] == 1 && 
             rec2[1] == 2 && 
             rec2[2] == 3
  );
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_COND(ret.code == RC_FAIL);
}

void Test506() {
  uint8_t test[] = {0x30, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceOfInteger rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2 + 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  SequenceOfInteger rec2;
  rec2 = rec;
  size_t consumed = ret.consumed;
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.size() == 3 && 
              rec2[0] == 1 && 
             rec2[1] == 2 && 
             rec2[2] == 3
  );
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_RESULT(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 2 && 
             rec[2] == 3
  );
}

void Test507() {
  uint8_t test[] = {0x30, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceOfInteger rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2 + 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  SequenceOfInteger rec2;
  rec2 = std::move(rec);
  size_t consumed = ret.consumed;
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.size() == 3 && 
              rec2[0] == 1 && 
             rec2[1] == 2 && 
             rec2[2] == 3
  );
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_COND(ret.code == RC_FAIL);
}

void Test508() {
  uint8_t test1[] = {0x30, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  uint8_t test2[] = {0x30, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x0a, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceOfInteger rec;
  ret = rec.DecodeBer(test1, sizeof(test1));
  INTERMEDIATE_CHECK(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 2 && 
             rec[2] == 3
  );
  ret = rec.DecodeBer(test2, sizeof(test2));
  CHECK_RESULT(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 10 && 
             rec[2] == 3
  );
}

void Test509() {
  TEST_NUMBER;
  
#define UNWRAP(...) __VA_ARGS__
  
#define CHECK_EQ(Type, DecodeBuffer)                                          \
  {                                                                           \
    Type rec;                                                                 \
    std::vector<uint8_t> test = UNWRAP DecodeBuffer;                          \
    asn_dec_rval_t ret = rec.DecodeBer(test);                                 \
    INTERMEDIATE_CHECK(true);                                                 \
    Type rec2(rec);                                                           \
    INTERMEDIATE_COND(rec == rec2);                                           \
    INTERMEDIATE_COND(! (rec != rec2));                                       \
  }
  
  CHECK_EQ(ANY, ({0x02, 0x02, 0x6f, 0x2f}));
  CHECK_EQ(AnyRef, ({0x02, 0x02, 0x6f, 0x2f}));
  CHECK_EQ(BIT_STRING, ({0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 0xfe, 0xc0}));
  CHECK_EQ(BOOLEAN, ({0x01, 0x01, 0x00}));
  {
    BOOLEAN rec1;
    BOOLEAN rec2;
    rec1 = 1;
    rec2 = 2;
    INTERMEDIATE_COND(rec1 == rec2);
    INTERMEDIATE_COND(! (rec1 != rec2));
  }
  CHECK_EQ(ENUMERATED, ({0x0a, 0x04, 0x31, 0xf0, 0x2d, 0x82}));
  CHECK_EQ(INTEGER, ({0x02, 0x04, 0x31, 0xf0, 0x2d, 0x82}));
  CHECK_EQ(NULL_t, ({0x05, 0x00}));
  {
    NULL_t rec1;
    NULL_t rec2;
    rec1 = 1;
    rec2 = 2;
    INTERMEDIATE_COND(rec1 == rec2);
    INTERMEDIATE_COND(! (rec1 != rec2) );
  }
  CHECK_EQ(NativeEnumerated, ({0x0a, 0x01, 0x02}));
  CHECK_EQ(NativeInteger, ({0x02, 0x04, 0x31, 0xF0, 0x2D, 0x82}));
  CHECK_EQ(NativeReal, ({0x09, 0x09, 0x80, 0xe4, 0x0c, 0x60, 0x2a, 0xc1, 0xf7, 0xce, 0xd9}));
  CHECK_EQ(OCTET_STRING, ({0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 0xfe, 0xcd}));
  CHECK_EQ(REAL, ({0x09, 0x09, 0x80, 0xea, 0x0c, 0x7c, 0x0b, 0x60, 0xb6, 0xd5, 0x3d}));
  CHECK_EQ(SequenceRecord_IS_OI_OIO_OIRef_OIRefO, 
                   ({0x30, 0x2d, 0x30, 0x2b, 0x06, 0x0a, 0x2b, 0x06, 0x01, 0x04, 
                    0x01, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x81, 0x07, 0x2b, 0x06, 
                    0x01, 0x04, 0x02, 0xc9, 0x13, 0x06, 0x0b, 0x2b, 0x06, 0x01, 
                    0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x06, 0x07, 
                    0x2b, 0x06, 0x01, 0x04, 0x04, 0xc9, 0x13}));
  CHECK_EQ(SequenceRecord_IS_ROI_ROIO_ROIRefWithTag_ROIRefWithTagO, 
                    ({0x30, 0x33, 0x30, 0x31, 0x0d, 0x0b, 0xc9, 0x13, 0x84, 0xe4, 
                    0x7a, 0x01, 0x03, 0x06, 0x01, 0x04, 0x01, 0x81, 0x08, 0xc9, 
                    0x13, 0x01, 0x03, 0x06, 0x01, 0x04, 0x02, 0x9f, 0x32, 0x0c, 
                    0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 
                    0x04, 0x03, 0x9f, 0x32, 0x08, 0xc9, 0x13, 0x01, 0x03, 0x06, 
                    0x01, 0x04, 0x04}));
  CHECK_EQ(SequenceRecord_IS_UT_UTO_UTRefWithTag_UTRefWithTagO, 
                    ({0x30, 0x50, 0x30, 0x4e, 0x17, 0x11, 0x31, 0x30, 0x30, 0x33, 
                    0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 
                    0x30, 0x30, 0x30, 0x81, 0x11, 0x32, 0x30, 0x30, 0x33, 0x31, 
                    0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 
                    0x30, 0x30, 0x9f, 0x32, 0x11, 0x33, 0x30, 0x30, 0x33, 0x31, 
                    0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 
                    0x30, 0x30, 0x9f, 0x32, 0x11, 0x34, 0x30, 0x30, 0x33, 0x31, 
                    0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 
                    0x30, 0x30}));
  CHECK_EQ(SequenceRecord_IS_GT_GTO_GTRefWithTag_GTRefWithTagO, 
                    ({0x30, 0x48, 0x30, 0x46, 0x18, 0x0f, 0x32, 0x30, 0x31, 0x30, 
                    0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 
                    0x5a, 0x81, 0x0f, 0x32, 0x30, 0x32, 0x30, 0x30, 0x33, 0x31, 
                    0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a, 0x9f, 0x3c, 
                    0x0f, 0x32, 0x30, 0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 
                    0x36, 0x34, 0x30, 0x31, 0x32, 0x5a, 0x9f, 0x3c, 0x0f, 0x32, 
                    0x30, 0x34, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 
                    0x30, 0x31, 0x32, 0x5a}));
  CHECK_EQ(SequenceRecord_IS_BmpS_BmpSO_BmpSRefWithTag_BmpSRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x1e, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_UTF8S_UTF8SO_UTF8SRefWithTag_UTF8SRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x0c, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_GenS_GenSO_GenSRefWithTag_GenSRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x1b, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_GraS_GraSO_GraSRefWithTag_GraSRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x19, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_IA5S_IA5SO_IA5SRefWithTag_IA5SRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x16, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_VisS_VisSO_VisSRefWithTag_VisSRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x1a, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x12, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_PriS_PriSO_PriSRefWithTag_PriSRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_TeleS_TeleSO_TeleSRefWithTag_TeleSRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x14, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_T61S_T61SO_T61SRefWithTag_T61SRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x14, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_UniS_UniSO_UniSRefWithTag_UniSRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x1c, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_VidS_VidSO_VidSRefWithTag_VidSRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x15, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_ObjD_ObjDO_ObjDRefWithTag_ObjDRefWithTagO, 
                    ({0x30, 0x28, 0x30, 0x26, 0x07, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34}));
  CHECK_EQ(SequenceRecord_IS_I646S_I646SO_I646SRefWithTag_I646SRefWithTagO, 
                    ({0x30, 0x15, 0x30, 0x13, 0x1a, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33}));
  CHECK_EQ(SequenceRecord_I_IO_I, ({0x30, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 0xb1, 0x92, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08}));
  {
    std::vector<uint8_t> test = {0x30, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 0xb1, 0x92, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
    SequenceRecord_I_IO_I rec;
    asn_dec_rval_t ret = rec.DecodeBer(test);
    INTERMEDIATE_CHECK(true);
    SequenceRecord_I_IO_I rec2(rec);
#ifdef INSECURE_POINTERS
    delete rec2.type2;
    rec2.type2 = 0;
#else
    rec2.type2.reset();
#endif
    INTERMEDIATE_COND(rec != rec2);
    INTERMEDIATE_COND(! (rec == rec2));
  }
  CHECK_EQ(SetRecord_I_IO_I, ({0x31, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 0xb1, 0x92, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08}));
  {
    std::vector<uint8_t> test = {0x31, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 0xb1, 0x92, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
    SetRecord_I_IO_I rec;
    asn_dec_rval_t ret = rec.DecodeBer(test);
    INTERMEDIATE_CHECK(true);
    SetRecord_I_IO_I rec2(rec);
#ifdef INSECURE_POINTERS
    delete rec.type2;
    rec.type2 = 0;
#else
    rec2.type2.reset();
#endif
    INTERMEDIATE_COND(rec != rec2);
    INTERMEDIATE_COND(! (rec == rec2));
  }
  CHECK_EQ(SetOfInteger, ({0x31, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03}));
  {
    std::vector<uint8_t> test = {0x31, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
    SetOfInteger rec;
    asn_dec_rval_t ret = rec.DecodeBer(test);
    INTERMEDIATE_CHECK(true);
    SetOfInteger rec2(rec);
    ++rec.back();
    INTERMEDIATE_COND(rec != rec2);
    INTERMEDIATE_COND(! (rec == rec2));
  }
  CHECK_EQ(SequenceOfInteger, ({0x30, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03}));
  {
    std::vector<uint8_t> test = {0x30, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
    SequenceOfInteger rec;
    asn_dec_rval_t ret = rec.DecodeBer(test);
    INTERMEDIATE_CHECK(true);
    SequenceOfInteger rec2(rec);
    ++rec.back();
    INTERMEDIATE_COND(rec != rec2);
    INTERMEDIATE_COND(! (rec == rec2));
  }
  CHECK_EQ(ChoiceRealInteger, ({0x02, 0x01, 0x7b}));
  {
    std::vector<uint8_t> test = {0x02, 0x01, 0x7b};
    ChoiceRealInteger rec;
    asn_dec_rval_t ret = rec.DecodeBer(test);
    INTERMEDIATE_CHECK(true && rec.FetchPresent() == ChoiceRealInteger::PR_integer);
    ChoiceRealInteger rec2(rec);
    INTERMEDIATE_COND(rec == rec2);
    INTERMEDIATE_COND(! (rec != rec2) );
    INTERMEDIATE_COND(rec.integer());
#ifdef PTR_CHOICE_GETTERS
    ++(*rec.integer());
#else
    ++rec.integer();
#endif
    INTERMEDIATE_COND(rec != rec2);
    INTERMEDIATE_COND(! (rec == rec2));
#ifdef PTR_CHOICE_GETTERS
    --(*rec.integer());
#else
    --rec.integer();
#endif
    INTERMEDIATE_COND(rec == rec2);
    INTERMEDIATE_COND(! (rec != rec2) );
    rec.real(new NativeReal(123.345));
    INTERMEDIATE_COND(rec != rec2);
    INTERMEDIATE_COND(! (rec == rec2));
  }
  CHECK_EQ(ChoiceRealInteger_direct, ({0x02, 0x01, 0x7b}));
  {
    std::vector<uint8_t> test = {0x02, 0x01, 0x7b};
    ChoiceRealInteger_direct rec;
    asn_dec_rval_t ret = rec.DecodeBer(test);
    INTERMEDIATE_CHECK(true && rec.FetchPresent() == ChoiceRealInteger_direct::PR_integer);
    ChoiceRealInteger_direct rec2(rec);
    INTERMEDIATE_COND(rec == rec2);
    INTERMEDIATE_COND(! (rec != rec2) );
    rec2.real = 123.345;
    INTERMEDIATE_COND(rec == rec2);
    INTERMEDIATE_COND(! (rec != rec2) );
    rec2.real = 0;
    ++rec.integer;
    INTERMEDIATE_COND(rec != rec2);
    INTERMEDIATE_COND(! (rec == rec2));
    --rec.integer;
    INTERMEDIATE_COND(rec == rec2);
    INTERMEDIATE_COND(! (rec != rec2) );
    rec.SetPresent(ChoiceRealInteger_direct::PR_real);
    INTERMEDIATE_COND(rec != rec2);
    INTERMEDIATE_COND(! (rec == rec2));
  }
  
  
  CHECK_COND(true);
#undef CHECK_EQ
#undef UNWRAP
}

void Test510() {
  TEST_NUMBER;
  std::vector<uint8_t> mustBe = {0x02, 0x02, 0x6f, 0x2f};
  ANY rec;
  bool isOk = false;
  NativeInteger someNumber(28463);
  CHECK_COND(rec.FromType(someNumber) && rec == mustBe &&
          ANY::CreateFromType(someNumber, &isOk) == mustBe && 
          isOk
  );
}

void Test511() {
  TEST_NUMBER;
  std::vector<uint8_t> anyBuf = {0x02, 0x02, 0x6f, 0x2f};
  ANY rec;
  rec = anyBuf;
  NativeInteger someNumber;
  CHECK_COND(rec.ToType(someNumber) && 28463 == someNumber);
}

void Test512() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x0f, 0xa0, 0x05, 0xa0, 0x03, 0x02, 0x01, 
                                 0x7b, 0xa1, 0x06, 0xa1, 0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SequenceT2choice rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.one.FetchPresent() == ModuleTest1::ChoiceT1::PR_first &&
          rec.one.first() &&
          *rec.one.first() == 123 &&
          rec.two &&
          rec.two->FetchPresent() == ModuleTest1::ChoiceT1::PR_second &&
          rec.two->second() &&
          *rec.two->second() == 456);
#else
  INTERMEDIATE_CHECK(rec.one.FetchPresent() == ModuleTest1::ChoiceT1::PR_first &&
          rec.one.first() == 123 &&
          rec.two &&
          rec.two->FetchPresent() == ModuleTest1::ChoiceT1::PR_second &&
          rec.two->second() == 456);
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceT2choice ::= {\n    one: first: 123\n    two: second: 456\n}");
}

void Test513() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x0f, 0xa0, 0x05, 0xa0, 0x03, 0x02, 0x01, 
                               0x7b, 0xa1, 0x06, 0xa1, 0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SetT2choice rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.one.FetchPresent() == ModuleTest1::ChoiceT1::PR_first &&
          rec.one.first() &&
          *rec.one.first() == 123 &&
          rec.two &&
          rec.two->FetchPresent() == ModuleTest1::ChoiceT1::PR_second &&
          rec.two->second() &&
          *rec.two->second() == 456);
#else
  INTERMEDIATE_CHECK(rec.one.FetchPresent() == ModuleTest1::ChoiceT1::PR_first &&
          rec.one.first() == 123 &&
          rec.two &&
          rec.two->FetchPresent() == ModuleTest1::ChoiceT1::PR_second &&
          rec.two->second() == 456);
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetT2choice ::= {\n    one: first: 123\n    two: second: 456\n}");
}

void Test514() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x0b, 0xa0, 0x03, 0x02, 0x01, 0x7b, 0xa1, 
                               0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SequenceOfT2choice rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.size() == 2 &&
          rec[0].FetchPresent() == ModuleTest1::ChoiceT1::PR_first &&
          rec[0].first() &&
          *rec[0].first() == 123 &&
          rec[1].FetchPresent() == ModuleTest1::ChoiceT1::PR_second &&
          rec[1].second() &&
          *rec[1].second() == 456);
#else
  INTERMEDIATE_CHECK(rec.size() == 2 &&
          rec[0].FetchPresent() == ModuleTest1::ChoiceT1::PR_first &&
          rec[0].first() == 123 &&
          rec[1].FetchPresent() == ModuleTest1::ChoiceT1::PR_second &&
          rec[1].second() == 456);
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceOfT2choice ::= {\n    first: 123\n    second: 456\n}");
}

void Test515() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x0b, 0xa0, 0x03, 0x02, 0x01, 0x7b, 0xa1, 
                               0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SetOfT2choice rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.size() == 2 &&
          rec[0].FetchPresent() == ModuleTest1::ChoiceT1::PR_first &&
          rec[0].first() &&
          *rec[0].first() == 123 &&
          rec[1].FetchPresent() == ModuleTest1::ChoiceT1::PR_second &&
          rec[1].second() &&
          *rec[1].second() == 456);
#else
  INTERMEDIATE_CHECK(rec.size() == 2 &&
          rec[0].FetchPresent() == ModuleTest1::ChoiceT1::PR_first &&
          rec[0].first() == 123 &&
          rec[1].FetchPresent() == ModuleTest1::ChoiceT1::PR_second &&
          rec[1].second() == 456);
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetOfT2choice ::= {\n    first: 123\n    second: 456\n}");
}

void Test516() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0xa0, 0x05, 0xa0, 0x03, 0x02, 0x01, 0x7b};
  asn_dec_rval_t ret;
  ModuleTest2::ChoiceT2choice rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT2choice::PR_one &&
          rec.one() &&
          rec.one()->FetchPresent() == ModuleTest1::ChoiceT1::PR_first &&
          rec.one()->first() &&
          *rec.one()->first() == 123);
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT2choice::PR_one &&
          rec.one().FetchPresent() == ModuleTest1::ChoiceT1::PR_first &&
          rec.one().first() == 123);
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("one: first: 123");
}

void Test517() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0xa0, 0x03, 0x02, 0x01, 0x7b};
  asn_dec_rval_t ret;
  ModuleTest2::ChoiceT1choiceRef rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT1choiceRef::PR_first &&
          rec.first() && 
          *rec.first() == 123);
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT1choiceRef::PR_first &&
          rec.first() == 123);
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("first: 123");
}

void Test518() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x1b, 0xa0, 0x0b, 0xa0, 0x03, 0x02, 0x01, 
                               0x7b, 0xa1, 0x04, 0x02, 0x02, 0x01, 0x41, 0xa1, 
                               0x0c, 0xa0, 0x04, 0x02, 0x02, 0x02, 0x8e, 0xa1, 
                               0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SequenceT2seq rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.one.first == 123 &&
          rec.one.second == 321 &&
          rec.two &&
          rec.two->first == 654 &&
          rec.two->second == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceT2seq ::= {\n    one: SeqT1 ::= {\n        first: 123\n"
            "        second: 321\n    }\n    two: SeqT1 ::= {\n        "
            "first: 654\n        second: 456\n    }\n}");
}

void Test519() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x1b, 0xa0, 0x0b, 0xa0, 0x03, 0x02, 0x01, 
                               0x7b, 0xa1, 0x04, 0x02, 0x02, 0x01, 0x41, 0xa1, 
                               0x0c, 0xa0, 0x04, 0x02, 0x02, 0x02, 0x8e, 0xa1, 
                                0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SetT2seq rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.one.first == 123 &&
          rec.one.second == 321 &&
          rec.two &&
          rec.two->first == 654 &&
          rec.two->second == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetT2seq ::= {\n    one: SeqT1 ::= {\n        first: 123\n"
            "        second: 321\n    }\n    two: SeqT1 ::= {\n        "
            "first: 654\n        second: 456\n    }\n}");
}

void Test520() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x1b, 0x30, 0x0b, 0xa0, 0x03, 0x02, 0x01, 
                               0x7b, 0xa1, 0x04, 0x02, 0x02, 0x01, 0x41, 0x30, 
                               0x0c, 0xa0, 0x04, 0x02, 0x02, 0x02, 0x8e, 0xa1, 
                               0x04, 0x02, 0x02, 0x01, 0xc8};
;
  asn_dec_rval_t ret;
  ModuleTest2::SequenceOfT2seq rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 2 &&
          rec[0].first == 123 &&
          rec[0].second == 321 &&
          rec[1].first == 654 &&
          rec[1].second == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceOfT2seq ::= {\n    SeqT1 ::= {\n        first: 123\n"
            "        second: 321\n    }\n    SeqT1 ::= {\n        "
            "first: 654\n        second: 456\n    }\n}");
}

void Test521() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x1b, 0x30, 0x0b, 0xa0, 0x03, 0x02, 0x01, 
                               0x7b, 0xa1, 0x04, 0x02, 0x02, 0x01, 0x41, 0x30, 
                               0x0c, 0xa0, 0x04, 0x02, 0x02, 0x02, 0x8e, 0xa1, 
                               0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SetOfT2seq rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 2 &&
          rec[0].first == 123 &&
          rec[0].second == 321 &&
          rec[1].first == 654 &&
          rec[1].second == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetOfT2seq ::= {\n    SeqT1 ::= {\n        first: 123\n"
            "        second: 321\n    }\n    SeqT1 ::= {\n        "
            "first: 654\n        second: 456\n    }\n}");
}

void Test522() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0xa0, 0x0b, 0xa0, 0x03, 0x02, 0x01, 0x7b, 0xa1, 
                               0x04, 0x02, 0x02, 0x01, 0xc8};
                    
  asn_dec_rval_t ret;
  ModuleTest2::ChoiceT2seq rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT2seq::PR_one &&
          rec.one() &&
          rec.one()->first == 123 &&
          rec.one()->second == 456);
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT2seq::PR_one &&
          rec.one().first == 123 &&
          rec.one().second == 456);
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("one: SeqT1 ::= {\n    first: 123\n    second: 456\n}");
}

void Test523() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x0b, 0xa0, 0x03, 0x02, 0x01, 0x7b, 0xa1, 
                               0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SeqT1seqRef rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.first == 123 && rec.second == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SeqT1seqRef ::= {\n    first: 123\n    second: 456\n}");
}

void Test524() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x1b, 0xa0, 0x0b, 0xa0, 0x03, 0x02, 0x01, 
                               0x7b, 0xa1, 0x04, 0x02, 0x02, 0x01, 0x41, 0xa1, 
                               0x0c, 0xa0, 0x04, 0x02, 0x02, 0x02, 0x8e, 0xa1, 
                               0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SequenceT2set rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.one.first == 123 &&
          rec.one.second == 321 &&
          rec.two &&
          rec.two->first == 654 &&
          rec.two->second == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceT2set ::= {\n    one: SetT1 ::= {\n        first: 123\n"
            "        second: 321\n    }\n    two: SetT1 ::= {\n        "
            "first: 654\n        second: 456\n    }\n}");
}

void Test525() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x1b, 0xa0, 0x0b, 0xa0, 0x03, 0x02, 0x01, 
                              0x7b, 0xa1, 0x04, 0x02, 0x02, 0x01, 0x41, 0xa1, 
                              0x0c, 0xa0, 0x04, 0x02, 0x02, 0x02, 0x8e, 0xa1, 
                              0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SetT2set rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.one.first == 123 &&
          rec.one.second == 321 &&
          rec.two &&
          rec.two->first == 654 &&
          rec.two->second == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetT2set ::= {\n    one: SetT1 ::= {\n        first: 123\n"
            "        second: 321\n    }\n    two: SetT1 ::= {\n        "
            "first: 654\n        second: 456\n    }\n}");
}

void Test526() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x1b, 0x31, 0x0b, 0xa0, 0x03, 0x02, 0x01, 
                              0x7b, 0xa1, 0x04, 0x02, 0x02, 0x01, 0x41, 0x31, 
                              0x0c, 0xa0, 0x04, 0x02, 0x02, 0x02, 0x8e, 0xa1, 
                              0x04, 0x02, 0x02, 0x01, 0xc8};
;
  asn_dec_rval_t ret;
  ModuleTest2::SequenceOfT2set rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 2 &&
          rec[0].first == 123 &&
          rec[0].second == 321 &&
          rec[1].first == 654 &&
          rec[1].second == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceOfT2set ::= {\n    SetT1 ::= {\n        first: 123\n"
            "        second: 321\n    }\n    SetT1 ::= {\n        "
            "first: 654\n        second: 456\n    }\n}");
}

void Test527() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x1b, 0x31, 0x0b, 0xa0, 0x03, 0x02, 0x01, 
                               0x7b, 0xa1, 0x04, 0x02, 0x02, 0x01, 0x41, 0x31, 
                               0x0c, 0xa0, 0x04, 0x02, 0x02, 0x02, 0x8e, 0xa1, 
                               0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SetOfT2set rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 2 &&
          rec[0].first == 123 &&
          rec[0].second == 321 &&
          rec[1].first == 654 &&
          rec[1].second == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetOfT2set ::= {\n    SetT1 ::= {\n        first: 123\n"
            "        second: 321\n    }\n    SetT1 ::= {\n        "
            "first: 654\n        second: 456\n    }\n}");
}

void Test528() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0xa0, 0x0b, 0xa0, 0x03, 0x02, 0x01, 0x7b, 0xa1, 
                                0x04, 0x02, 0x02, 0x01, 0xc8};
                    
  asn_dec_rval_t ret;
  ModuleTest2::ChoiceT2set rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT2set::PR_one &&
          rec.one() &&
          rec.one()->first == 123 &&
          rec.one()->second == 456);
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT2set::PR_one &&
          rec.one().first == 123 &&
          rec.one().second == 456);
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("one: SetT1 ::= {\n    first: 123\n    second: 456\n}");
}

void Test529() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x0b, 0xa0, 0x03, 0x02, 0x01, 0x7b, 0xa1, 
                               0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SetT1setRef rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.first == 123 && rec.second == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetT1setRef ::= {\n    first: 123\n    second: 456\n}");
}

void Test530() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x0f, 0xa0, 0x07, 0x02, 0x01, 0x7b, 0x02, 
                               0x02, 0x01, 0xc8, 0xa1, 0x04, 0x02, 0x02, 0x03, 0x15};
  asn_dec_rval_t ret;
  ModuleTest2::SequenceT2seqof rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.one.size() == 2 &&
                      rec.one[0] == 123 &&
                      rec.one[1] == 456 &&
                    rec.two && rec.two->size() == 1 && 
                    (*rec.two)[0] == 789);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceT2seqof ::= {\n    one: SeqOfT1 ::= {\n        123\n"
            "        456\n    }\n    two: SeqOfT1 ::= {\n        789\n    }\n}");
}

void Test531() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x0f, 0xa0, 0x07, 0x02, 0x01, 0x7b, 0x02, 
                                0x02, 0x01, 0xc8, 0xa1, 0x04, 0x02, 0x02, 0x03, 0x15};
  asn_dec_rval_t ret;
  ModuleTest2::SetT2seqof rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.one.size() == 2 &&
                      rec.one[0] == 123 &&
                      rec.one[1] == 456 &&
                    rec.two && rec.two->size() == 1 && 
                    (*rec.two)[0] == 789);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetT2seqof ::= {\n    one: SeqOfT1 ::= {\n        123\n        "
            "456\n    }\n    two: SeqOfT1 ::= {\n        789\n    }\n}");
}

void Test532() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x0f, 0x30, 0x07, 0x02, 0x01, 0x7b, 0x02, 
                                0x02, 0x01, 0xc8, 0x30, 0x04, 0x02, 0x02, 0x03, 0x15};
  asn_dec_rval_t ret;
  ModuleTest2::SequenceOfT2seqof rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 2 &&
                     rec[0].size() == 2 && 
                      rec[0][0] == 123 &&
                      rec[0][1] == 456 &&
                    rec[1].size() == 1 &&
                    rec[1][0] == 789);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceOfT2seqof ::= {\n    SeqOfT1 ::= {\n        123\n        "
            "456\n    }\n    SeqOfT1 ::= {\n        789\n    }\n}");
}

void Test533() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x0f, 0x30, 0x04, 0x02, 0x02, 0x03, 0x15, 
                              0x30, 0x07, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SetOfT2seqof rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 2 &&
                     rec[1].size() == 2 && 
                      rec[1][0] == 123 &&
                      rec[1][1] == 456 &&
                    rec[0].size() == 1 &&
                    rec[0][0] == 789);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetOfT2seqof ::= {\n    SeqOfT1 ::= {\n        789\n    }\n    "
            "SeqOfT1 ::= {\n        123\n        456\n    }\n}");
}

void Test534() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0xa0, 0x0b, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x01, 
                                0xc8, 0x02, 0x02, 0x03, 0x15};
                    
  asn_dec_rval_t ret;
  ModuleTest2::ChoiceT2seqof rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT2seqof::PR_one &&
          rec.one() &&
          rec.one()->size() == 3 &&
          (*rec.one())[0] == 123 &&
          (*rec.one())[1] == 456 && 
          (*rec.one())[2] == 789);
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT2seqof::PR_one &&
          rec.one().size() == 3 &&
          rec.one()[0] == 123 &&
          rec.one()[1] == 456 && 
          rec.one()[2] == 789);
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("one: SeqOfT1 ::= {\n    123\n    456\n    789\n}");
}

void Test535() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x0b, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x01, 
                                0xc8, 0x02, 0x02, 0x03, 0x15};
  asn_dec_rval_t ret;
  ModuleTest2::SeqOfT1seqofRef rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 3 &&
                    rec[0] == 123 && 
                    rec[1] == 456 &&
                    rec[2] == 789);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SeqOfT1seqofRef ::= {\n    123\n    456\n    789\n}");
}

void Test536() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x0f, 0xa0, 0x07, 0x02, 0x01, 0x7b, 0x02, 
                               0x02, 0x01, 0xc8, 0xa1, 0x04, 0x02, 0x02, 0x03, 0x15};
  asn_dec_rval_t ret;
  ModuleTest2::SequenceT2setof rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.one.size() == 2 &&
                      rec.one[0] == 123 &&
                      rec.one[1] == 456 &&
                    rec.two && rec.two->size() == 1 && 
                    (*rec.two)[0] == 789);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceT2setof ::= {\n    one: SetOfT1 ::= {\n        123\n"
            "        456\n    }\n    two: SetOfT1 ::= {\n        789\n    }\n}");
}

void Test537() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x0f, 0xa0, 0x07, 0x02, 0x01, 0x7b, 0x02, 
                               0x02, 0x01, 0xc8, 0xa1, 0x04, 0x02, 0x02, 0x03, 0x15};
  asn_dec_rval_t ret;
  ModuleTest2::SetT2setof rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.one.size() == 2 &&
                      rec.one[0] == 123 &&
                      rec.one[1] == 456 &&
                    rec.two && rec.two->size() == 1 && 
                    (*rec.two)[0] == 789);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetT2setof ::= {\n    one: SetOfT1 ::= {\n        123\n        "
            "456\n    }\n    two: SetOfT1 ::= {\n        789\n    }\n}");
}

void Test538() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x0f, 0x31, 0x07, 0x02, 0x01, 0x7b, 0x02, 
                               0x02, 0x01, 0xc8, 0x31, 0x04, 0x02, 0x02, 0x03, 0x15};
  asn_dec_rval_t ret;
  ModuleTest2::SequenceOfT2setof rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 2 &&
                     rec[0].size() == 2 && 
                      rec[0][0] == 123 &&
                      rec[0][1] == 456 &&
                    rec[1].size() == 1 &&
                    rec[1][0] == 789);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceOfT2setof ::= {\n    SetOfT1 ::= {\n        123\n        "
            "456\n    }\n    SetOfT1 ::= {\n        789\n    }\n}");
}

void Test539() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x0f, 0x31, 0x04, 0x02, 0x02, 0x03, 0x15, 
                                0x31, 0x07, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SetOfT2setof rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 2 &&
                     rec[1].size() == 2 && 
                      rec[1][0] == 123 &&
                      rec[1][1] == 456 &&
                    rec[0].size() == 1 &&
                    rec[0][0] == 789);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetOfT2setof ::= {\n    SetOfT1 ::= {\n        789\n    }\n    "
            "SetOfT1 ::= {\n        123\n        456\n    }\n}");
}

void Test540() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0xa0, 0x0b, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x01, 
                                0xc8, 0x02, 0x02, 0x03, 0x15};
                    
  asn_dec_rval_t ret;
  ModuleTest2::ChoiceT2setof rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT2setof::PR_one &&
          rec.one() &&
          rec.one()->size() == 3 &&
          (*rec.one())[0] == 123 &&
          (*rec.one())[1] == 456 && 
          (*rec.one())[2] == 789);
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT2setof::PR_one &&
          rec.one().size() == 3 &&
          rec.one()[0] == 123 &&
          rec.one()[1] == 456 && 
          rec.one()[2] == 789);
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("one: SetOfT1 ::= {\n    123\n    456\n    789\n}");
}

void Test541() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x0b, 0x02, 0x01, 0x7b, 0x02, 0x02, 0x01, 
                                0xc8, 0x02, 0x02, 0x03, 0x15};
  asn_dec_rval_t ret;
  ModuleTest2::SetOfT1setofRef rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 3 &&
                    rec[0] == 123 && 
                    rec[1] == 456 &&
                    rec[2] == 789);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetOfT1setofRef ::= {\n    123\n    456\n    789\n}");
}

void Test542() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x0b, 0xa0, 0x03, 0x02, 0x01, 0x7b, 0xa1, 
                              0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SequenceT2ref rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.one == 123 &&
                    rec.two &&
                    *rec.two == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceT2ref ::= {\n    one: 123\n    two: 456\n}");
}

void Test543() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x0b, 0xa0, 0x03, 0x02, 0x01, 0x7b, 0xa1, 
                                0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SetT2ref rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.one == 123 &&
                    rec.two &&
                    *rec.two == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetT2ref ::= {\n    one: 123\n    two: 456\n}");
}

void Test544() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x30, 0x0d, 0xbf, 0x32, 0x03, 0x02, 0x01, 0x7b, 
                                  0xbf, 0x32, 0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SequenceOfT2ref rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 2 &&
                      rec[0] == 123 &&
                      rec[1] == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceOfT2ref ::= {\n    123\n    456\n}");
}

void Test545() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x31, 0x0d, 0xbf, 0x32, 0x03, 0x02, 0x01, 0x7b, 
                                0xbf, 0x32, 0x04, 0x02, 0x02, 0x01, 0xc8};
  asn_dec_rval_t ret;
  ModuleTest2::SetOfT2ref rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 2 &&
                      rec[0] == 123 &&
                      rec[1] == 456);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SetOfT2ref ::= {\n    123\n    456\n}");
}

void Test546() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0xa0, 0x03, 0x02, 0x01, 0x7b};
                    
  asn_dec_rval_t ret;
  ModuleTest2::ChoiceT2ref rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT2ref::PR_one &&
          rec.one() &&
          *rec.one() == 123);
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == ModuleTest2::ChoiceT2ref::PR_one &&
          rec.one() == 123);
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("one: 123");
}

void Test547() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0xbf, 0x32, 0x03, 0x02, 0x01, 0x7b};
  asn_dec_rval_t ret;
  ModuleTest2::RefT1refRef rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == 123);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("123");
}

void Test548() {
  std::vector<uint8_t> test = {0x30, 0x0a, 0x30, 0x08, 0x02, 0x03, 0x0c, 0xc3, 
                               0x34, 0x01, 0x01, 0xff};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_C_R_I_B_compound rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0xFF &&
          rec.set.choice.FetchPresent() == SequenceRecord_IS_C_R_I_B_compound::SequenceRecord_IS_C_R_I_B_compound__set::SequenceRecord_IS_C_R_I_B_compound__set__choice::PR_integer &&
          rec.set.choice.integer() &&
          *rec.set.choice.integer() == 836404
  );
#else
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0xFF &&
          rec.set.choice.FetchPresent() == SequenceRecord_IS_C_R_I_B_compound::SequenceRecord_IS_C_R_I_B_compound__set::SequenceRecord_IS_C_R_I_B_compound__set__choice::PR_integer &&
          rec.set.choice.integer() == 836404
  );
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceRecord-IS-C-R-I-B-compound ::= {\n    set: set ::= {\n        "
            "choice: integer: 836404\n        boolean: TRUE\n    }\n}");
}

void Test549() {
  std::vector<uint8_t> test = {0x30, 0x10, 0x30, 0x0e, 0x09, 0x09, 0x80, 0xd9, 
                               0x18, 0x2b, 0x0f, 0xd9, 0x1a, 0xb8, 0xe9, 0x01, 
                               0x01, 0x00};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_C_R_I_B_compound rec;
  SequenceRecord_IS_C_R_I_B_compound::SequenceRecord_IS_C_R_I_B_compound__set& set(rec.set);
  SequenceRecord_IS_C_R_I_B_compound::SequenceRecord_IS_C_R_I_B_compound__set::SequenceRecord_IS_C_R_I_B_compound__set__choice choice(rec.set.choice);
  (void)set;
  (void)choice;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0 &&
          rec.set.choice.FetchPresent() == SequenceRecord_IS_C_R_I_B_compound::SequenceRecord_IS_C_R_I_B_compound__set::SequenceRecord_IS_C_R_I_B_compound__set__choice::PR_real &&
          rec.set.choice.real() &&
          *rec.set.choice.real() == 12374.123813
  );
#else
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0 &&
          rec.set.choice.FetchPresent() == SequenceRecord_IS_C_R_I_B_compound::SequenceRecord_IS_C_R_I_B_compound__set::SequenceRecord_IS_C_R_I_B_compound__set__choice::PR_real &&
          rec.set.choice.real() == 12374.123813
  );
#endif
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("SequenceRecord-IS-C-R-I-B-compound ::= {\n    set: set ::= {\n        "
            "choice: real: 12374.123813000000155\n        boolean: FALSE\n    }\n}");
}

void Test550() {
  TEST_NUMBER;
  SetOfSeqOfSeq_I_compound rec;
  std::vector<_SetOfSeqOfSeq_I_compound>& list = rec;
  list.emplace_back();
  std::vector<__SetOfSeqOfSeq_I_compound>& list2 = list[0];
  list2.emplace_back();
  list2[0].int1 = 123;
  
  CHECK_COND(rec.size() == 1 && 
             rec[0].size() == 1 && 
             123 == rec[0][0].int1);
}

void Test551() {
  uint8_t test[] = {0x31, 0x16, 0x31, 0x14, 0xa1, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0x01, 0x8c, 0x01, 0x03, 0xa3, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0xff, 0x8c, 0x01, 0xfd};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Seqs_of_seq_compound rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.set.field1.size() == 1 && 
                  !rec.set.field2 &&
                  rec.set.field3.size() == 1 &&
                !rec.set.field4);
  SequenceRecord_I_IO_IRef_compound rec1(rec.set.field1[0]);
  SetRecord_ISet_Seqs_of_seq_compound::SetRecord_ISet_Seqs_of_seq_compound__set::_SetRecord_ISet_Seqs_of_seq_compound__set__field3 rec3(rec.set.field3[0]);
  CHECK_RESULT(rec1.type == 1 && 
              !rec1.type2 && 
              rec1.type3 == 3 &&
          
          rec3.type == -1 &&
          !rec3.type2 &&
          rec3.type3 == -3
  );
}

void Test552() {
  uint8_t test[] = {0x31, 0x2a, 0x31, 0x28, 0xa1, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0x01, 0x8c, 0x01, 0x03, 0xa2, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0x0a, 0x8c, 0x01, 0x1e, 0xa3, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0xff, 0x8c, 0x01, 0xfd, 0xa4, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0xf6, 0x8c, 0x01, 0xe2};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Seqs_of_seq_compound rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.set.field1.size() == 1 && 
                  rec.set.field2 &&
                  rec.set.field2->size() == 1 &&
                  rec.set.field3.size() == 1 &&
                rec.set.field4 && 
                rec.set.field4->size() == 1);
  SequenceRecord_I_IO_IRef_compound rec1(rec.set.field1[0]);
  SequenceRecord_I_IO_IRef_compound rec2((*rec.set.field2)[0]);
  SetRecord_ISet_Seqs_of_seq_compound::SetRecord_ISet_Seqs_of_seq_compound__set::SetRecord_ISet_Seqs_of_seq_compound__set__field3 temp1;
  (void)temp1;
  SetRecord_ISet_Seqs_of_seq_compound::SetRecord_ISet_Seqs_of_seq_compound__set::SetRecord_ISet_Seqs_of_seq_compound__set__field4 temp2;
  (void)temp2;
  SetRecord_ISet_Seqs_of_seq_compound::SetRecord_ISet_Seqs_of_seq_compound__set::_SetRecord_ISet_Seqs_of_seq_compound__set__field3 rec3(rec.set.field3[0]);
  SetRecord_ISet_Seqs_of_seq_compound::SetRecord_ISet_Seqs_of_seq_compound__set::_SetRecord_ISet_Seqs_of_seq_compound__set__field4 rec4((*rec.set.field4)[0]);
  CHECK_RESULT(rec1.type == 1 && 
              !rec1.type2 && 
              rec1.type3 == 3 &&
          
          rec2.type == 10 && 
              !rec2.type2 && 
              rec2.type3 == 30 &&
          
          rec3.type == -1 &&
          !rec3.type2 &&
          rec3.type3 == -3 &&
          
          rec4.type == -10 && 
              !rec4.type2 && 
              rec4.type3 == -30
  );
}

void Test553() {
  uint8_t test[] = {0x31, 0x16, 0x31, 0x14, 0xa1, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0x01, 0x8c, 0x01, 0x03, 0xa3, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0xff, 0x8c, 0x01, 0xfd};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_seq_compound rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.set.field1.size() == 1 && 
                  !rec.set.field2 &&
                  rec.set.field3.size() == 1 &&
                !rec.set.field4);
  SequenceRecord_I_IO_IRef_compound rec1(rec.set.field1[0]);
  SetRecord_ISet_Sets_of_seq_compound::SetRecord_ISet_Sets_of_seq_compound__set::_SetRecord_ISet_Sets_of_seq_compound__set__field3 rec3(rec.set.field3[0]);
  CHECK_RESULT(rec1.type == 1 && 
              !rec1.type2 && 
              rec1.type3 == 3 &&
          
          rec3.type == -1 &&
          !rec3.type2 &&
          rec3.type3 == -3
  );
}

void Test554() {
  uint8_t test[] = {0x31, 0x2a, 0x31, 0x28, 0xa1, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0x01, 0x8c, 0x01, 0x03, 0xa2, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0x0a, 0x8c, 0x01, 0x1e, 0xa3, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0xff, 0x8c, 0x01, 0xfd, 0xa4, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0xf6, 0x8c, 0x01, 0xe2};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_seq_compound rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.set.field1.size() == 1 && 
                  rec.set.field2 &&
                  rec.set.field2->size() == 1 &&
                  rec.set.field3.size() == 1 &&
                rec.set.field4 && 
                rec.set.field4->size() == 1);
  SequenceRecord_I_IO_IRef_compound rec1(rec.set.field1[0]);
  SequenceRecord_I_IO_IRef_compound rec2((*rec.set.field2)[0]);
  SetRecord_ISet_Sets_of_seq_compound::SetRecord_ISet_Sets_of_seq_compound__set::SetRecord_ISet_Sets_of_seq_compound__set__field3 temp1;
  (void)temp1;
  SetRecord_ISet_Sets_of_seq_compound::SetRecord_ISet_Sets_of_seq_compound__set::SetRecord_ISet_Sets_of_seq_compound__set__field4 temp2;
  (void)temp2;
  SetRecord_ISet_Sets_of_seq_compound::SetRecord_ISet_Sets_of_seq_compound__set::_SetRecord_ISet_Sets_of_seq_compound__set__field3 rec3(rec.set.field3[0]);
  SetRecord_ISet_Sets_of_seq_compound::SetRecord_ISet_Sets_of_seq_compound__set::_SetRecord_ISet_Sets_of_seq_compound__set__field4 rec4((*rec.set.field4)[0]);
  CHECK_RESULT(rec1.type == 1 && 
              !rec1.type2 && 
              rec1.type3 == 3 &&
          
          rec2.type == 10 && 
              !rec2.type2 && 
              rec2.type3 == 30 &&
          
          rec3.type == -1 &&
          !rec3.type2 &&
          rec3.type3 == -3 &&
          
          rec4.type == -10 && 
              !rec4.type2 && 
              rec4.type3 == -30
  );
}

void Test555() {
  uint8_t test[] = {0x30, 0x05, 0x30, 0x03, 0x02, 0x01, 0x01};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_IE_compound rec;
  SequenceRecord_IS_IE_compound::SequenceRecord_IS_IE_compound__field temp1;
  (void)temp1;
  SequenceRecord_IS_IE_compound::SequenceRecord_IS_IE_compound__field::SequenceRecord_IS_IE_compound__field__value_enum temp2;
  temp2 = SequenceRecord_IS_IE_compound::SequenceRecord_IS_IE_compound__field::SequenceRecord_IS_IE_compound__field__value_enum::value_value1;
  temp2 = SequenceRecord_IS_IE_compound::SequenceRecord_IS_IE_compound__field::value_value2;
  (void)temp2;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.field.value == SequenceRecord_IS_IE_compound::SequenceRecord_IS_IE_compound__field::SequenceRecord_IS_IE_compound__field__value_enum::value_value2
  );
}

void Test556() {
  TEST_NUMBER;
  Choice_IChoiceRealInteger rec;
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_COND(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_NOTHING && 
                    !rec.choice());
#else
  INTERMEDIATE_COND(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_NOTHING);
#endif
  rec.choice(new class Choice_IChoiceRealInteger::choice());
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_COND(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice && 
                  rec.choice());
#else
  INTERMEDIATE_COND(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice);
#endif
  rec.choice(nullptr);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_COND(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_NOTHING && 
                    !rec.choice());
#else
  INTERMEDIATE_COND(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_NOTHING);
#endif
  rec.choice(new class Choice_IChoiceRealInteger::choice());
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_COND(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice && 
                  rec.choice());
  INTERMEDIATE_COND(rec.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_NOTHING && 
          !rec.choice()->integer() && !rec.choice()->real());
  rec.choice()->integer(new NativeInteger(10));
  INTERMEDIATE_COND(rec.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          !rec.choice()->real() &&
          rec.choice()->integer() &&
          *rec.choice()->integer() == 10);
  rec.choice()->real(new NativeReal(123.1345));
  CHECK_COND(rec.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_real &&
          !rec.choice()->integer() &&
          rec.choice()->real() &&
          *rec.choice()->real() == 123.1345);
#else
  INTERMEDIATE_COND(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice);
  INTERMEDIATE_COND(rec.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_NOTHING);
  rec.choice().integer(new NativeInteger(10));
  INTERMEDIATE_COND(rec.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec.choice().integer() == 10);
  rec.choice().real(new NativeReal(123.1345));
  CHECK_COND(rec.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_real &&
          rec.choice().real() == 123.1345);
#endif
}

void Test557() {
  std::vector<uint8_t> test = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger_direct rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoiceRealInteger_direct::PR_choice &&
          rec.choice.FetchPresent() == Choice_IChoiceRealInteger_direct::choice::PR_integer &&
          rec.choice.integer == 123
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("choice: integer: 123");
}

void Test558() {
  std::vector<uint8_t> test = {0x09, 0x09, 0x80, 0xd2, 0x1e, 0xc7, 0xdf, 0x3b, 0x64, 0x5a, 0x1d};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger_direct rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoiceRealInteger_direct::PR_choice &&
          rec.choice.FetchPresent() == Choice_IChoiceRealInteger_direct::choice::PR_real &&
          rec.choice.real == 123.123
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  INTERMEDIATE_CHECK_ENCODING(bufferEnc == test);
  CHECK_OUT("choice: real: 123.123000000000005");
}

void Test559() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger_direct rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  Choice_IChoiceRealInteger_direct rec2(rec1);
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger_direct::PR_choice &&
          rec1.choice.FetchPresent() == Choice_IChoiceRealInteger_direct::choice::PR_integer &&
          rec1.choice.integer == 123 &&
          
          rec2.FetchPresent() == Choice_IChoiceRealInteger_direct::PR_choice &&
          rec2.choice.FetchPresent() == Choice_IChoiceRealInteger_direct::choice::PR_integer &&
          rec2.choice.integer == 123
  );
}

void Test560() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger_direct rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  Choice_IChoiceRealInteger_direct rec2(std::move(rec1));
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger_direct::PR_NOTHING &&
          rec1.choice.FetchPresent() == Choice_IChoiceRealInteger_direct::choice::PR_NOTHING &&
          rec1.choice.integer == 0 &&
          
          rec2.FetchPresent() == Choice_IChoiceRealInteger_direct::PR_choice &&
          rec2.choice.FetchPresent() == Choice_IChoiceRealInteger_direct::choice::PR_integer &&
          rec2.choice.integer == 123
  );
}

void Test561() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger_direct rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  Choice_IChoiceRealInteger_direct rec2;
  rec2 = rec1;
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger_direct::PR_choice &&
          rec1.choice.FetchPresent() == Choice_IChoiceRealInteger_direct::choice::PR_integer &&
          rec1.choice.integer == 123 &&
          
          rec2.FetchPresent() == Choice_IChoiceRealInteger_direct::PR_choice &&
          rec2.choice.FetchPresent() == Choice_IChoiceRealInteger_direct::choice::PR_integer &&
          rec2.choice.integer == 123
  );
}

void Test562() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger_direct rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  Choice_IChoiceRealInteger_direct rec2;
  rec2 = std::move(rec1);
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger_direct::PR_NOTHING &&
          rec1.choice.FetchPresent() == Choice_IChoiceRealInteger_direct::choice::PR_NOTHING &&
          rec1.choice.integer == 0 &&
          
          rec2.FetchPresent() == Choice_IChoiceRealInteger_direct::PR_choice &&
          rec2.choice.FetchPresent() == Choice_IChoiceRealInteger_direct::choice::PR_integer &&
          rec2.choice.integer == 123
  );
}

void Test563() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger_direct rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  rec1.Clear();
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger_direct::PR_NOTHING &&
          rec1.choice.FetchPresent() == Choice_IChoiceRealInteger_direct::choice::PR_NOTHING &&
          rec1.choice.integer == 0 
  );
}

void Test564() {
  uint8_t test1[] = {0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  uint8_t test2[] = {0x13, 0x06, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x32};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoicePS_IA5_direct rec;
  ret = rec.DecodeBer(test1, sizeof(test1));
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoicePS_IA5_direct::PR_choice &&
          rec.choice.FetchPresent() == Choice_IChoicePS_IA5_direct::choice::PR_str1 &&
          rec.choice.str1 == "string1");
  ret = rec.DecodeBer(test2, sizeof(test2));
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoicePS_IA5_direct::PR_choice &&
          rec.choice.FetchPresent() == Choice_IChoicePS_IA5_direct::choice::PR_str1 &&
          rec.choice.str1 == "strin2");
}

void Test565() {
  uint8_t test[] = {0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoicePS_IA5_direct rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  Choice_IChoicePS_IA5_direct rec2(rec);
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.FetchPresent() == Choice_IChoicePS_IA5_direct::PR_choice &&
          rec2.choice.FetchPresent() == Choice_IChoicePS_IA5_direct::choice::PR_str1 &&
          rec2.choice.str1 == "string1");
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoicePS_IA5_direct::PR_choice &&
          rec.choice.FetchPresent() == Choice_IChoicePS_IA5_direct::choice::PR_str1 &&
          rec.choice.str1 == "string1");
}

void Test566() {
  uint8_t test[] = {0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoicePS_IA5_direct rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  Choice_IChoicePS_IA5_direct rec2(std::move(rec));
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.FetchPresent() == Choice_IChoicePS_IA5_direct::PR_choice &&
          rec2.choice.FetchPresent() == Choice_IChoicePS_IA5_direct::choice::PR_str1 &&
          rec2.choice.str1 == "string1");
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_COND(ret.code == RC_FAIL);
}

void Test567() {
  uint8_t test[] = {0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoicePS_IA5_direct rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  Choice_IChoicePS_IA5_direct rec2;
  rec2 = rec;
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.FetchPresent() == Choice_IChoicePS_IA5_direct::PR_choice &&
          rec2.choice.FetchPresent() == Choice_IChoicePS_IA5_direct::choice::PR_str1 &&
          rec2.choice.str1 == "string1");
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoicePS_IA5_direct::PR_choice &&
          rec.choice.FetchPresent() == Choice_IChoicePS_IA5_direct::choice::PR_str1 &&
          rec.choice.str1 == "string1");
}

void Test568() {
  uint8_t test[] = {0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoicePS_IA5_direct rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  Choice_IChoicePS_IA5_direct rec2;
  rec2 = std::move(rec);
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.FetchPresent() == Choice_IChoicePS_IA5_direct::PR_choice &&
          rec2.choice.FetchPresent() == Choice_IChoicePS_IA5_direct::choice::PR_str1 &&
          rec2.choice.str1 == "string1");
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_COND(ret.code == RC_FAIL);
}

void Test569() {
  TEST_NUMBER;
#ifdef SKIP_ANOTHER_PRINT_FUNC_TESTS
  OK_SKIPPED;
#else
  const char* str = "some string";
  {
    OCTET_STRING rec;
    rec.assign(str, str + strlen(str));
    INTERMEDIATE_OUT("73 6F 6D 65 20 73 74 72 69 6E 67");
    rec.ChangePrintFunc(OCTET_STRING_print_utf8<OCTET_STRING, std::vector<uint8_t>>);
    INTERMEDIATE_OUT(str);
    rec.Clear();
    rec.assign(str, str + strlen(str));
    INTERMEDIATE_OUT(str);
    {
      OCTET_STRING rec1;
      rec1.assign(str, str + strlen(str));
      rec = rec1;
      INTERMEDIATE_OUT(str);
      OCTET_STRING rec2;
      rec2.assign(str, str + strlen(str));
      rec = std::move(rec2);
      INTERMEDIATE_OUT(str);
    }
    rec.ChangePrintFunc();
    INTERMEDIATE_OUT("73 6F 6D 65 20 73 74 72 69 6E 67");
  }
  {
    OCTET_STRING rec2;
    rec2.assign(str, str + strlen(str));
    rec2.ChangePrintFunc(OCTET_STRING_print_utf8<OCTET_STRING, std::vector<uint8_t>>);
    INTERMEDIATE_COND(rec2.GetAnotherPrintFunc());
    OCTET_STRING rec(rec2);
    INTERMEDIATE_OUT("73 6F 6D 65 20 73 74 72 69 6E 67");
  }
  {
    OCTET_STRING rec2;
    rec2.assign(str, str + strlen(str));
    rec2.ChangePrintFunc(OCTET_STRING_print_utf8<OCTET_STRING, std::vector<uint8_t>>);
    INTERMEDIATE_COND(rec2.GetAnotherPrintFunc());
    OCTET_STRING rec(std::move(rec2));
    INTERMEDIATE_OUT("73 6F 6D 65 20 73 74 72 69 6E 67");
  }
  CHECK_COND(true);
#endif
}

void Test570() {
  TEST_NUMBER;
  std::vector<uint8_t> data = {0x34, 0x53, 0x84};
  BIT_STRING rec1;
  rec1 = data;
  BIT_STRING rec2;
  rec2 = data;
  INTERMEDIATE_COND(rec1 == rec2);
  rec1.back() |= 1;
  INTERMEDIATE_COND(!(rec1 == rec2));
  rec1.SetBitsUnused(3);
  INTERMEDIATE_COND(!(rec1 == rec2));
  rec2.SetBitsUnused(3);
  INTERMEDIATE_COND(rec1 == rec2);
  rec2.back() = 0x80;
  INTERMEDIATE_COND(rec1 == rec2);
  rec1.resize(rec1.size() - 1);
  INTERMEDIATE_COND(!(rec1 == rec2));
  rec1 = data;
  rec2 = data;
  INTERMEDIATE_COND(rec1 == rec2);
  rec1[1] |= 0b100;
  INTERMEDIATE_COND(!(rec1 == rec2));
  rec1.SetBitsUnused(10);
  rec2.SetBitsUnused(10);
  INTERMEDIATE_COND(!(rec1 == rec2));
  rec1.SetBitsUnused(11);
  rec2.SetBitsUnused(11);
  INTERMEDIATE_COND(rec1 == rec2);
  rec1.SetBitsUnused(24);
  rec2.SetBitsUnused(24);
  INTERMEDIATE_COND(rec1 == rec2);
  rec1.SetBitsUnused(50);
  rec2.SetBitsUnused(50);
  CHECK_COND(rec1 == rec2);
}

void Test571() {
  TEST_NUMBER;
  std::vector<uint8_t> data = {0x34, 0x53, 0x84};
  BIT_STRING rec1;
  rec1 = data;
  BIT_STRING rec2;
  rec2 = data;
  INTERMEDIATE_COND(!(rec1 != rec2));
  rec1.back() |= 1;
  INTERMEDIATE_COND(rec1 != rec2);
  rec1.SetBitsUnused(3);
  INTERMEDIATE_COND(rec1 != rec2);
  rec2.SetBitsUnused(3);
  INTERMEDIATE_COND(!(rec1 != rec2));
  rec2.back() = 0x80;
  INTERMEDIATE_COND(!(rec1 != rec2));
  rec1.resize(rec1.size() - 1);
  CHECK_COND(rec1 != rec2);
}

void Test572() {
  TEST_NUMBER;
  NativeInteger rec;
  rec = 10;
  INTERMEDIATE_COND(rec == 10);
  NativeInteger rec2 = rec++;
  INTERMEDIATE_COND(rec2 == 10 && rec == 11);
  rec2 = rec--;
  CHECK_COND(rec2 == 11 && rec == 10);
}

void Test573() {
  TEST_NUMBER;
  std::vector<uint8_t> data = {0x9f, 0x32, 0x02, 0x02, 0x9a};
  EnumeratedRefRef rec;
  auto ret = rec.DecodeBer(data);
  CHECK_RESULT(rec == 666);
}

void Test574() {
  std::string val1 = "12\"3";
  std::string val2;
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  SequenceRecord_VSD_VS_VSD_VSD rec;
  rec.SetEmptyToDefault();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test575() {
  uint8_t test[] = {0x30, 0x05, 0x81, 0x03, 0x38, 0x38, 0x38};
  std::string val1 = "111";
  std::string val2 = "888";
  std::string val3 = "666";
  std::string val4 = "222";
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IA5D_IA5_IA5D_IA5D rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.val1 && 
                rec.val2 == val2 && 
                !rec.val3 &&
          !rec.val4
  );
}

void Test576() {
  uint8_t test[] = {0x30, 0x14, 0x80, 0x03, 0x31, 0x31, 0x31, 0x81, 0x03, 0x38, 
                    0x38, 0x38, 0x82, 0x03, 0x36, 0x36, 0x36, 0x83, 0x03, 0x32, 
                    0x32, 0x32};
  std::string val1 = "111";
  std::string val2 = "888";
  std::string val3 = "666";
  std::string val4 = "222";
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IA5D_IA5_IA5D_IA5D rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test577() {
  uint8_t test[] = {0x30, 0x14, 0x80, 0x03, 0x31, 0x31, 0x31, 0x81, 0x03, 0x38, 
                    0x38, 0x38, 0x82, 0x03, 0x36, 0x36, 0x36, 0x83, 0x03, 0x32, 
                    0x32, 0x32};
  std::string val1 = "12\"3";
  std::string val2 = "888";
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IA5D_IA5_IA5D_IA5D rec;
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

void Test578() {
  std::string val1 = "12\"3";
  std::string val2;
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  SequenceRecord_IA5D_IA5_IA5D_IA5D rec;
  rec.SetVal1Default();
  rec.SetVal3Default();
  rec.SetVal4Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test579() {
  std::string val1 = "12\"3";
  std::string val2;
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  SequenceRecord_IA5D_IA5_IA5D_IA5D rec;
  rec.SetEmptyToDefault();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test580() {
  uint8_t test[] = {0x30, 0x05, 0x81, 0x03, 0x38, 0x38, 0x38};
  std::string val1 = "111";
  std::string val2 = "888";
  std::string val3 = "666";
  std::string val4 = "222";
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_PSD_PS_PSD_PSD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.val1 && 
                rec.val2 == val2 && 
                !rec.val3 &&
          !rec.val4
  );
}

void Test581() {
  uint8_t test[] = {0x30, 0x14, 0x80, 0x03, 0x31, 0x31, 0x31, 0x81, 0x03, 0x38,
                    0x38, 0x38, 0x82, 0x03, 0x36, 0x36, 0x36, 0x83, 0x03, 0x32, 
                    0x32, 0x32};
  std::string val1 = "111";
  std::string val2 = "888";
  std::string val3 = "666";
  std::string val4 = "222";
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_PSD_PS_PSD_PSD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test582() {
  uint8_t test[] = {0x30, 0x14, 0x80, 0x03, 0x31, 0x31, 0x31, 0x81, 0x03, 0x38,
                    0x38, 0x38, 0x82, 0x03, 0x36, 0x36, 0x36, 0x83, 0x03, 0x32, 
                    0x32, 0x32};
  std::string val1 = "12\"3";
  std::string val2 = "888";
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_PSD_PS_PSD_PSD rec;
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

void Test583() {
  std::string val1 = "12\"3";
  std::string val2;
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  SequenceRecord_PSD_PS_PSD_PSD rec;
  rec.SetVal1Default();
  rec.SetVal3Default();
  rec.SetVal4Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test584() {
  std::string val1 = "12\"3";
  std::string val2;
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  SequenceRecord_PSD_PS_PSD_PSD rec;
  rec.SetEmptyToDefault();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test585() {
  uint8_t test[] = {0x30, 0x05, 0x81, 0x03, 0x38, 0x38, 0x38};
  std::string val1 = "111";
  std::string val2 = "888";
  std::string val3 = "666";
  std::string val4 = "222";
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I646D_I646_I646D_I646D rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.val1 && 
                rec.val2 == val2 && 
                !rec.val3 &&
          !rec.val4
  );
}

void Test586() {
  uint8_t test[] = {0x30, 0x14, 0x80, 0x03, 0x31, 0x31, 0x31, 0x81, 0x03, 0x38, 
                    0x38, 0x38, 0x82, 0x03, 0x36, 0x36, 0x36, 0x83, 0x03, 
                    0x32, 0x32, 0x32};
  std::string val1 = "111";
  std::string val2 = "888";
  std::string val3 = "666";
  std::string val4 = "222";
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I646D_I646_I646D_I646D rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test587() {
  uint8_t test[] = {0x30, 0x14, 0x80, 0x03, 0x31, 0x31, 0x31, 0x81, 0x03, 0x38, 
                    0x38, 0x38, 0x82, 0x03, 0x36, 0x36, 0x36, 0x83, 0x03, 
                    0x32, 0x32, 0x32};
  std::string val1 = "12\"3";
  std::string val2 = "888";
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I646D_I646_I646D_I646D rec;
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

void Test588() {
  std::string val1 = "12\"3";
  std::string val2;
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  SequenceRecord_I646D_I646_I646D_I646D rec;
  rec.SetVal1Default();
  rec.SetVal3Default();
  rec.SetVal4Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test589() {
  std::string val1 = "12\"3";
  std::string val2;
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  SequenceRecord_I646D_I646_I646D_I646D rec;
  rec.SetEmptyToDefault();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test590() {
  uint8_t test[] = {0x30, 0x05, 0x81, 0x03, 0x38, 0x38, 0x38};
  std::string val1 = "111";
  std::string val2 = "888";
  std::string val3 = "666";
  std::string val4 = "222";
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_NSD_NS_NSD_NSD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.val1 && 
                rec.val2 == val2 && 
                !rec.val3 &&
          !rec.val4
  );
}

void Test591() {
  uint8_t test[] = {0x30, 0x14, 0x80, 0x03, 0x31, 0x31, 0x31, 0x81, 0x03, 0x38,
                    0x38, 0x38, 0x82, 0x03, 0x36, 0x36, 0x36, 0x83, 0x03, 0x32,
                    0x32, 0x32};
  std::string val1 = "111";
  std::string val2 = "888";
  std::string val3 = "666";
  std::string val4 = "222";
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_NSD_NS_NSD_NSD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test592() {
  uint8_t test[] = {0x30, 0x14, 0x80, 0x03, 0x31, 0x31, 0x31, 0x81, 0x03, 0x38,
                    0x38, 0x38, 0x82, 0x03, 0x36, 0x36, 0x36, 0x83, 0x03, 0x32,
                    0x32, 0x32};
  std::string val1 = "12\"3";
  std::string val2 = "888";
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_NSD_NS_NSD_NSD rec;
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

void Test593() {
  std::string val1 = "12\"3";
  std::string val2;
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  SequenceRecord_NSD_NS_NSD_NSD rec;
  rec.SetVal1Default();
  rec.SetVal3Default();
  rec.SetVal4Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test594() {
  std::string val1 = "12\"3";
  std::string val2;
  std::string val3 = "567";
  std::string val4 = "78*/9";
  TEST_NUMBER;
  SequenceRecord_NSD_NS_NSD_NSD rec;
  rec.SetEmptyToDefault();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test595() {
  uint8_t test[] = {0x30, 0x0e, 0x81, 0x0c, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 
                    0x00, 0x38, 0x00, 0x00, 0x00, 0x38};
  std::string _val1 = {0, 0, 0, '1', 0, 0, 0, '1', 0, 0, 0, '1'};
  std::string _val2 = {0, 0, 0, '8', 0, 0, 0, '8', 0, 0, 0, '8'};
  std::string _val3 = {0, 0, 0, '6', 0, 0, 0, '6', 0, 0, 0, '6'};
  std::string _val4 = {0, 0, 0, '2', 0, 0, 0, '2', 0, 0, 0, '2'};
  std::vector<uint8_t> val1(_val1.begin(), _val1.end());
  std::vector<uint8_t> val2(_val2.begin(), _val2.end());
  std::vector<uint8_t> val3(_val3.begin(), _val3.end());
  std::vector<uint8_t> val4(_val4.begin(), _val4.end());
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_USD_US_USD_USD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.val1 && 
                rec.val2 == val2 && 
                !rec.val3 &&
          !rec.val4
  );
}

void Test596() {
  uint8_t test[] = {0x30, 0x38, 0x80, 0x0c, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 
                    0x00, 0x31, 0x00, 0x00, 0x00, 0x31, 0x81, 0x0c, 0x00, 0x00, 
                    0x00, 0x38, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x38, 
                    0x82, 0x0c, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x36, 
                    0x00, 0x00, 0x00, 0x36, 0x83, 0x0c, 0x00, 0x00, 0x00, 0x32, 
                    0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x32};
  std::string _val1 = {0, 0, 0, '1', 0, 0, 0, '1', 0, 0, 0, '1'};
  std::string _val2 = {0, 0, 0, '8', 0, 0, 0, '8', 0, 0, 0, '8'};
  std::string _val3 = {0, 0, 0, '6', 0, 0, 0, '6', 0, 0, 0, '6'};
  std::string _val4 = {0, 0, 0, '2', 0, 0, 0, '2', 0, 0, 0, '2'};
  std::vector<uint8_t> val1(_val1.begin(), _val1.end());
  std::vector<uint8_t> val2(_val2.begin(), _val2.end());
  std::vector<uint8_t> val3(_val3.begin(), _val3.end());
  std::vector<uint8_t> val4(_val4.begin(), _val4.end());
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_USD_US_USD_USD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test597() {
  uint8_t test[] = {0x30, 0x38, 0x80, 0x0c, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 
                    0x00, 0x31, 0x00, 0x00, 0x00, 0x31, 0x81, 0x0c, 0x00, 0x00, 
                    0x00, 0x38, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x38, 
                    0x82, 0x0c, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x36, 
                    0x00, 0x00, 0x00, 0x36, 0x83, 0x0c, 0x00, 0x00, 0x00, 0x32, 
                    0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x32};
  std::string _val1 = {0, 0, 0, '1', 0, 0, 0, '2', 0, 0, 0, '\"', 0, 0, 0, '3'};
  std::string _val2 = {0, 0, 0, '8', 0, 0, 0, '8', 0, 0, 0, '8'};
  std::string _val3 = {0, 0, 0, '5', 0, 0, 0, '6', 0, 0, 0, '7'};
  std::string _val4 = {0, 0, 0, '7', 0, 0, 0, '8', 0, 0, 0, '*', 0, 0, 0, '/', 0, 0, 0, '9'};
  std::vector<uint8_t> val1(_val1.begin(), _val1.end());
  std::vector<uint8_t> val2(_val2.begin(), _val2.end());
  std::vector<uint8_t> val3(_val3.begin(), _val3.end());
  std::vector<uint8_t> val4(_val4.begin(), _val4.end());
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_USD_US_USD_USD rec;
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

void Test598() {
  std::string _val1 = {0, 0, 0, '1', 0, 0, 0, '2', 0, 0, 0, '\"', 0, 0, 0, '3'};
  std::string _val2;
  std::string _val3 = {0, 0, 0, '5', 0, 0, 0, '6', 0, 0, 0, '7'};
  std::string _val4 = {0, 0, 0, '7', 0, 0, 0, '8', 0, 0, 0, '*', 0, 0, 0, '/', 0, 0, 0, '9'};
  std::vector<uint8_t> val1(_val1.begin(), _val1.end());
  std::vector<uint8_t> val2(_val2.begin(), _val2.end());
  std::vector<uint8_t> val3(_val3.begin(), _val3.end());
  std::vector<uint8_t> val4(_val4.begin(), _val4.end());
  TEST_NUMBER;
  SequenceRecord_USD_US_USD_USD rec;
  rec.SetVal1Default();
  rec.SetVal3Default();
  rec.SetVal4Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test599() {
  std::string _val1 = {0, 0, 0, '1', 0, 0, 0, '2', 0, 0, 0, '\"', 0, 0, 0, '3'};
  std::string _val2;
  std::string _val3 = {0, 0, 0, '5', 0, 0, 0, '6', 0, 0, 0, '7'};
  std::string _val4 = {0, 0, 0, '7', 0, 0, 0, '8', 0, 0, 0, '*', 0, 0, 0, '/', 0, 0, 0, '9'};
  std::vector<uint8_t> val1(_val1.begin(), _val1.end());
  std::vector<uint8_t> val2(_val2.begin(), _val2.end());
  std::vector<uint8_t> val3(_val3.begin(), _val3.end());
  std::vector<uint8_t> val4(_val4.begin(), _val4.end());
  TEST_NUMBER;
  SequenceRecord_USD_US_USD_USD rec;
  rec.SetEmptyToDefault();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test600() {
  uint8_t test[] = {0x30, 0x08, 0x81, 0x06, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38};
  std::string _val1 = {0, '1', 0, '1', 0, '1'};
  std::string _val2 = {0, '8', 0, '8', 0, '8'};
  std::string _val3 = {0, '6', 0, '6', 0, '6'};
  std::string _val4 = {0, '2', 0, '2', 0, '2'};
  std::vector<uint8_t> val1(_val1.begin(), _val1.end());
  std::vector<uint8_t> val2(_val2.begin(), _val2.end());
  std::vector<uint8_t> val3(_val3.begin(), _val3.end());
  std::vector<uint8_t> val4(_val4.begin(), _val4.end());
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_BSD_BS_BSD_BSD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.val1 && 
                rec.val2 == val2 && 
                !rec.val3 &&
          !rec.val4
  );
}

void Test601() {
  uint8_t test[] = {0x30, 0x20, 0x80, 0x06, 0x00, 0x31, 0x00, 0x31, 0x00, 0x31, 
                    0x81, 0x06, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x82, 0x06, 
                    0x00, 0x36, 0x00, 0x36, 0x00, 0x36, 0x83, 0x06, 0x00, 0x32, 
                    0x00, 0x32, 0x00, 0x32};
  std::string _val1 = {0, '1', 0, '1', 0, '1'};
  std::string _val2 = {0, '8', 0, '8', 0, '8'};
  std::string _val3 = {0, '6', 0, '6', 0, '6'};
  std::string _val4 = {0, '2', 0, '2', 0, '2'};
  std::vector<uint8_t> val1(_val1.begin(), _val1.end());
  std::vector<uint8_t> val2(_val2.begin(), _val2.end());
  std::vector<uint8_t> val3(_val3.begin(), _val3.end());
  std::vector<uint8_t> val4(_val4.begin(), _val4.end());
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_BSD_BS_BSD_BSD rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test602() {
  uint8_t test[] = {0x30, 0x20, 0x80, 0x06, 0x00, 0x31, 0x00, 0x31, 0x00, 0x31, 
                    0x81, 0x06, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x82, 0x06, 
                    0x00, 0x36, 0x00, 0x36, 0x00, 0x36, 0x83, 0x06, 0x00, 0x32, 
                    0x00, 0x32, 0x00, 0x32};
  std::string _val1 = {0, '1', 0, '2', 0, '\"', 0, '3'};
  std::string _val2 = {0, '8', 0, '8', 0, '8'};
  std::string _val3 = {0, '5', 0, '6', 0, '7'};
  std::string _val4 = {0, '7', 0, '8', 0, '*', 0, '/', 0, '9'};
  std::vector<uint8_t> val1(_val1.begin(), _val1.end());
  std::vector<uint8_t> val2(_val2.begin(), _val2.end());
  std::vector<uint8_t> val3(_val3.begin(), _val3.end());
  std::vector<uint8_t> val4(_val4.begin(), _val4.end());
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_BSD_BS_BSD_BSD rec;
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

void Test603() {
  std::string _val1 = {0, '1', 0, '2', 0, '\"', 0, '3'};
  std::string _val2;
  std::string _val3 = {0, '5', 0, '6', 0, '7'};
  std::string _val4 = {0, '7', 0, '8', 0, '*', 0, '/', 0, '9'};
  std::vector<uint8_t> val1(_val1.begin(), _val1.end());
  std::vector<uint8_t> val2(_val2.begin(), _val2.end());
  std::vector<uint8_t> val3(_val3.begin(), _val3.end());
  std::vector<uint8_t> val4(_val4.begin(), _val4.end());
  TEST_NUMBER;
  SequenceRecord_BSD_BS_BSD_BSD rec;
  rec.SetVal1Default();
  rec.SetVal3Default();
  rec.SetVal4Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test604() {
  std::string _val1 = {0, '1', 0, '2', 0, '\"', 0, '3'};
  std::string _val2;
  std::string _val3 = {0, '5', 0, '6', 0, '7'};
  std::string _val4 = {0, '7', 0, '8', 0, '*', 0, '/', 0, '9'};
  std::vector<uint8_t> val1(_val1.begin(), _val1.end());
  std::vector<uint8_t> val2(_val2.begin(), _val2.end());
  std::vector<uint8_t> val3(_val3.begin(), _val3.end());
  std::vector<uint8_t> val4(_val4.begin(), _val4.end());
  TEST_NUMBER;
  SequenceRecord_BSD_BS_BSD_BSD rec;
  rec.SetEmptyToDefault();
  
  CHECK_COND(rec.val1 && *rec.val1 == val1 &&
                rec.val2 == val2 && 
                rec.val3 && *rec.val3 == val3 &&
          rec.val4 && *rec.val4 == val4
  );
}

void Test605() {
  uint8_t test[] = {0x31, 0x0c, 0x31, 0x0a, 0xa3, 0x03, 0x0a, 0x01, 0x02, 0xa4, 
                    0x03, 0x0a, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_enumerated rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  rec1 = SetRecord_ISet_Sets_of_enumerated();
  CHECK_RESULT(!rec1.set.field3.size() &&
                !rec1.set.field4
  );
}

void Test606() {
  uint8_t test[] = {0x31, 0x0c, 0x31, 0x0a, 0xa3, 0x03, 0x0a, 0x01, 0x02, 0xa4, 
                    0x03, 0x0a, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_enumerated rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(true);
  SetRecord_ISet_Sets_of_enumerated rec2;
  ret = rec2.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec2.set.field4 && 
                rec2.set.field4->size() == 1);
  (*rec2.set.field4)[0] = SetRecord_ISet_Sets_of_enumerated::set::field4_enum::field4_value1;
  rec1 = std::move(rec2);
  INTERMEDIATE_CHECK(rec1.set.field3.size() == 1 &&
                rec1.set.field4 && 
                rec1.set.field4->size() == 1);
  NativeEnumerated rec3(rec1.set.field3[0]);
  NativeEnumerated rec4((*rec1.set.field4)[0]);
  CHECK_RESULT(rec3 == SetRecord_ISet_Sets_of_enumerated::set::field3_enum::field3_value2 &&
          rec4 == SetRecord_ISet_Sets_of_enumerated::set::field4_enum::field4_value1
  );
}

void Test607() {
  uint8_t test[] = {0x30, 0x0e, 0x02, 0x01, 0x7b, 0x09, 0x09, 0x80, 0xd7, 0x04, 
                    0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_empty rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(true);
}

void Test608() {
  uint8_t test[] = {0x31, 0x0e, 0x02, 0x01, 0x7b, 0x09, 0x09, 0x80, 0xd7, 0x04, 
                    0x6e, 0x3e, 0xf9, 0xdb, 0x22, 0xd1};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_empty rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(true);
}

void Test609() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ChoiceRecord_empty rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(true);
}

void Test610() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ChoiceRecord_empty_direct rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(true);
}

void Test611() {
  TEST_NUMBER;
  NativeInteger rec1;
  NativeInteger rec2;
  rec1 = 5;
  rec2 = 6;
  
  CHECK_COND(rec1 < 10 && 1 < rec1 && rec1 < rec2 &&
          rec1 <= 10 && 1 <= rec1 && rec1 <= rec2 &&
          rec1 >= 1 && 10 >= rec1 && rec2 >= rec1 &&
          rec1 > 1 && 10 > rec1 && rec2 > rec1);
}

void Test612() {
  TEST_NUMBER;
  UnsignedNativeInteger rec1;
  UnsignedNativeInteger rec2;
  rec1 = 5;
  rec2 = 6;
  
  CHECK_COND(rec1 < 10 && 1 < rec1 && rec1 < rec2 &&
          rec1 <= 10 && 1 <= rec1 && rec1 <= rec2 &&
          rec1 >= 1 && 10 >= rec1 && rec2 >= rec1 &&
          rec1 > 1 && 10 > rec1 && rec2 > rec1);
}

void Test613() {
  TEST_NUMBER;
  NativeReal rec1;
  NativeReal rec2;
  rec1 = 5;
  rec2 = 6;
  
  CHECK_COND(rec1 < 10 && 1 < rec1 && rec1 < rec2 &&
          rec1 <= 10 && 1 <= rec1 && rec1 <= rec2 &&
          rec1 >= 1 && 10 >= rec1 && rec2 >= rec1 &&
          rec1 > 1 && 10 > rec1 && rec2 > rec1);
}

void Test614() {
  TEST_NUMBER;
  std::vector<NativeInteger> mustBe;
  for (size_t i = 1; i < 11; ++i) {
    mustBe.emplace_back();
    mustBe.back() = i;
  }
  
  std::vector<NativeInteger> arr;
  arr.push_back(NativeInteger() = 2);
  arr.push_back(NativeInteger() = 5);
  arr.push_back(NativeInteger() = 4);
  arr.push_back(NativeInteger() = 8);
  arr.push_back(NativeInteger() = 9);
  arr.push_back(NativeInteger() = 1);
  arr.push_back(NativeInteger() = 10);
  arr.push_back(NativeInteger() = 7);
  arr.push_back(NativeInteger() = 3);
  arr.push_back(NativeInteger() = 6);
  std::sort(arr.begin(), arr.end());
  
  CHECK_COND(arr == mustBe);
}

void Test615() {
  TEST_NUMBER;
  std::vector<UnsignedNativeInteger> mustBe;
  for (size_t i = 1; i < 11; ++i) {
    mustBe.emplace_back();
    mustBe.back() = i;
  }
  
  std::vector<UnsignedNativeInteger> arr;
  arr.push_back(UnsignedNativeInteger() = 2);
  arr.push_back(UnsignedNativeInteger() = 5);
  arr.push_back(UnsignedNativeInteger() = 4);
  arr.push_back(UnsignedNativeInteger() = 8);
  arr.push_back(UnsignedNativeInteger() = 9);
  arr.push_back(UnsignedNativeInteger() = 1);
  arr.push_back(UnsignedNativeInteger() = 10);
  arr.push_back(UnsignedNativeInteger() = 7);
  arr.push_back(UnsignedNativeInteger() = 3);
  arr.push_back(UnsignedNativeInteger() = 6);
  std::sort(arr.begin(), arr.end());
  
  CHECK_COND(arr == mustBe);
}

void Test616() {
  TEST_NUMBER;
  std::vector<NativeReal> mustBe;
  for (size_t i = 1; i < 11; ++i) {
    mustBe.emplace_back();
    mustBe.back() = i;
  }
  
  std::vector<NativeReal> arr;
  arr.push_back(NativeReal() = 2);
  arr.push_back(NativeReal() = 5);
  arr.push_back(NativeReal() = 4);
  arr.push_back(NativeReal() = 8);
  arr.push_back(NativeReal() = 9);
  arr.push_back(NativeReal() = 1);
  arr.push_back(NativeReal() = 10);
  arr.push_back(NativeReal() = 7);
  arr.push_back(NativeReal() = 3);
  arr.push_back(NativeReal() = 6);
  std::sort(arr.begin(), arr.end());
  
  CHECK_COND(arr == mustBe);
}

void Test617() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x28, 0x3f, 0x06, 0x04, 0x2a, 0x03, 0x04, 0x05, 
      0x02, 0x01, 0x7b, 0x07, 0x11, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x20, 
      0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x6f, 0x72, 0xa0, 0x21, 
      0x19, 0x1f, 0x74, 0x68, 0x65, 0x20, 0x63, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 
      0x74, 0x20, 0x6f, 0x66, 0x20, 0x73, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x20, 
      0x41, 0x53, 0x4e, 0x31, 0x20, 0x74, 0x79, 0x70, 0x65};
  
  OBJECT_IDENTIFIER directReference;
  directReference.SetArcs(std::vector<int>({1, 2, 3, 4, 5}));
  
  GraphicString message;
  message = "the content of single ASN1 type";
  
  ANY singleAsn1Type;
  INTERMEDIATE_COND(singleAsn1Type.FromType(message));
  
  
  asn_dec_rval_t ret;
  SOME_MODULE1::External rec1;
  ret = rec1.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec1.direct_reference &&
          *rec1.direct_reference == directReference &&
          rec1.indirect_reference &&
          *rec1.indirect_reference == 123 &&
          rec1.data_value_descriptor &&
          *rec1.data_value_descriptor == "object descriptor" &&
          rec1.encoding.FetchPresent() == SOME_MODULE1::External::encoding::encoding_PR::PR_single_ASN1_type &&
          *rec1.encoding.single_ASN1_type() == singleAsn1Type);
#else
  INTERMEDIATE_CHECK(rec1.direct_reference &&
          *rec1.direct_reference == directReference &&
          rec1.indirect_reference &&
          *rec1.indirect_reference == 123 &&
          rec1.data_value_descriptor &&
          *rec1.data_value_descriptor == "object descriptor" &&
          rec1.encoding.FetchPresent() == SOME_MODULE1::External::encoding::encoding_PR::PR_single_ASN1_type &&
          rec1.encoding.single_ASN1_type() == singleAsn1Type);
#endif
  
  SOME_MODULE2::ExternalASN rec2;
  ret = rec2.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec2.direct_reference &&
          *rec2.direct_reference == directReference &&
          rec2.indirect_reference &&
          *rec2.indirect_reference == 123 &&
          rec2.data_value_descriptor &&
          *rec2.data_value_descriptor == "object descriptor" &&
          rec2.encoding.FetchPresent() == SOME_MODULE2::ExternalASN::encoding::encoding_PR::PR_single_ASN1_type &&
          *rec2.encoding.single_ASN1_type() == singleAsn1Type);
#else
  CHECK_RESULT(rec2.direct_reference &&
          *rec2.direct_reference == directReference &&
          rec2.indirect_reference &&
          *rec2.indirect_reference == 123 &&
          rec2.data_value_descriptor &&
          *rec2.data_value_descriptor == "object descriptor" &&
          rec2.encoding.FetchPresent() == SOME_MODULE2::ExternalASN::encoding::encoding_PR::PR_single_ASN1_type &&
          rec2.encoding.single_ASN1_type() == singleAsn1Type);
#endif
}

void Test618() {
  TEST_NUMBER;
  std::vector<uint8_t> test = {0x28, 0x3f, 0x06, 0x04, 0x2a, 0x03, 0x04, 0x05, 
      0x02, 0x01, 0x7b, 0x07, 0x11, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x20, 
      0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x6f, 0x72, 0xa0, 0x21, 
      0x19, 0x1f, 0x74, 0x68, 0x65, 0x20, 0x63, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 
      0x74, 0x20, 0x6f, 0x66, 0x20, 0x73, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x20, 
      0x41, 0x53, 0x4e, 0x31, 0x20, 0x74, 0x79, 0x70, 0x65};
  
  OBJECT_IDENTIFIER directReference;
  directReference.SetArcs(std::vector<int>({1, 2, 3, 4, 5}));
  
  GraphicString message;
  message = "the content of single ASN1 type";
  
  ANY singleAsn1Type;
  INTERMEDIATE_COND(singleAsn1Type.FromType(message));
  
  
  asn_dec_rval_t ret;
  SOME_MODULE1::External_direct rec1;
  ret = rec1.DecodeBer(test);
  INTERMEDIATE_CHECK(rec1.direct_reference &&
          *rec1.direct_reference == directReference &&
          rec1.indirect_reference &&
          *rec1.indirect_reference == 123 &&
          rec1.data_value_descriptor &&
          *rec1.data_value_descriptor == "object descriptor" &&
          rec1.encoding.FetchPresent() == SOME_MODULE1::External_direct::encoding::encoding_PR::PR_single_ASN1_type &&
          rec1.encoding.single_ASN1_type == singleAsn1Type);
  
  SOME_MODULE2::ExternalASN_direct rec2;
  ret = rec2.DecodeBer(test);
  CHECK_RESULT(rec2.direct_reference &&
          *rec2.direct_reference == directReference &&
          rec2.indirect_reference &&
          *rec2.indirect_reference == 123 &&
          rec2.data_value_descriptor &&
          *rec2.data_value_descriptor == "object descriptor" &&
          rec2.encoding.FetchPresent() == SOME_MODULE2::ExternalASN_direct::encoding::encoding_PR::PR_single_ASN1_type &&
          rec2.encoding.single_ASN1_type == singleAsn1Type);
}

int main(int argc, char** argv) {
  if (argc >= 2 && strncmp(argv[1], "-test_min_number=", 17) == 0) {
    testMinNumber = atoi(argv[1] + 17);
  }
  Tests1_100();
  Tests101_200();
  Tests201_300();
  Tests301_400();
  Tests401_500();
  Test501(); //SetOfInteger partial decoding copy operator =
  Test502(); //SetOfInteger partial decoding move operator =
  Test503(); //SetOfInteger and the same SetOfInteger again
  Test504(); //SequenceOfInteger partial decoding copy constructor
  Test505(); //SequenceOfInteger partial decoding move constructor
  Test506(); //SequenceOfInteger partial decoding copy operator =
  Test507(); //SequenceOfInteger partial decoding move operator =
  Test508(); //SequenceOfInteger and the same SequenceOfInteger again
  Test509(); //operator == and operator !=
  Test510(); //ANY::FromType && ANY::CreateFromType
  Test511(); //ANY::ToType
  Test512(); //SequenceT2choice + ChoiceT1 DecodeBer + EncodeDer + Print
  Test513(); //SetT2choice + ChoiceT1 DecodeBer + EncodeDer + Print
  Test514(); //SequenceOfT2choice + ChoiceT1 DecodeBer + EncodeDer + Print
  Test515(); //SetOfT2choice + ChoiceT1 DecodeBer + EncodeDer + Print
  Test516(); //ChoiceT2choice + ChoiceT1 DecodeBer + EncodeDer + Print
  Test517(); //ChoiceT1choiceRef + ChoiceT1 DecodeBer + EncodeDer + Print
  Test518(); //SequenceT2seq + SeqT1 DecodeBer + EncodeDer + Print
  Test519(); //SetT2seq + SeqT1 DecodeBer + EncodeDer + Print
  Test520(); //SequenceOfT2seq + SeqT1 DecodeBer + EncodeDer + Print
  Test521(); //SetOfT2seq + SeqT1 DecodeBer + EncodeDer + Print
  Test522(); //ChoiceT2seq + SeqT1 DecodeBer + EncodeDer + Print
  Test523(); //SeqT1seqRef + SeqT1 DecodeBer + EncodeDer + Print
  Test524(); //SequenceT2set + SetT1 DecodeBer + EncodeDer + Print
  Test525(); //SetT2set + SetT1 DecodeBer + EncodeDer + Print
  Test526(); //SequenceOfT2set + SetT1 DecodeBer + EncodeDer + Print
  Test527(); //SetOfT2set + SetT1 DecodeBer + EncodeDer + Print
  Test528(); //ChoiceT2set + SetT1 DecodeBer + EncodeDer + Print
  Test529(); //SetT1setRef + SetT1 DecodeBer + EncodeDer + Print
  Test530(); //SequenceT2seqof + SeqOfT1 DecodeBer + EncodeDer + Print
  Test531(); //SetT2seqof + SeqOfT1 DecodeBer + EncodeDer + Print
  Test532(); //SequenceOfT2seqof + SeqOfT1 DecodeBer + EncodeDer + Print
  Test533(); //SetOfT2seqof + SeqOfT1 DecodeBer + EncodeDer + Print
  Test534(); //ChoiceT2seqof + SeqOfT1 DecodeBer + EncodeDer + Print
  Test535(); //SeqOfT1seqofRef + SeqOfT1 DecodeBer + EncodeDer + Print
  Test536(); //SequenceT2setof + SetOfT1 DecodeBer + EncodeDer + Print
  Test537(); //SetT2setof + SetOfT1 DecodeBer + EncodeDer + Print
  Test538(); //SequenceOfT2setof + SetOfT1 DecodeBer + EncodeDer + Print
  Test539(); //SetOfT2setof + SetOfT1 DecodeBer + EncodeDer + Print
  Test540(); //ChoiceT2setof + SetOfT1 DecodeBer + EncodeDer + Print
  Test541(); //SetOfT1setofRef + SetOfT1 DecodeBer + EncodeDer + Print
  Test542(); //SequenceT2ref + RefT1 DecodeBer + EncodeDer + Print
  Test543(); //SetT2ref + RefT1 DecodeBer + EncodeDer + Print
  Test544(); //SequenceOfT2ref + RefT1 DecodeBer + EncodeDer + Print
  Test545(); //SetOfT2ref + RefT1 DecodeBer + EncodeDer + Print
  Test546(); //ChoiceT2ref + RefT1 DecodeBer + EncodeDer + Print
  Test547(); //RefT1refRef + RefT1 DecodeBer + EncodeDer + Print
  Test548(); //SequenceRecord-IS-C-R-I-B-compound DecodeBer + EncodeDer + print
  Test549(); //SequenceRecord-IS-C-R-I-B-compound DecodeBer + EncodeDer + print
  Test550(); //SetOfSeqOfSeq-I-compound without BER decoding since asn1c cannot generate code compatible with C++ for making tests
  Test551(); //SetRecord-ISet-Seqs-of-seq-compound + SeqOfSequenceRecord-I-IO-I-compound + SequenceRecord-I-IO-IRef-compound + SequenceRecord-I-IO-I-compound
  Test552(); //SetRecord-ISet-Seqs-of-seq-compound + SeqOfSequenceRecord-I-IO-I-compound + SequenceRecord-I-IO-IRef-compound + SequenceRecord-I-IO-I-compound
  Test553(); //SetRecord-ISet-Sets-of-seq-compound + SetOfSequenceRecord-I-IO-I-compound + SequenceRecord-I-IO-IRef-compound + SequenceRecord-I-IO-I-compound
  Test554(); //SetRecord-ISet-Sets-of-seq-compound + SetOfSequenceRecord-I-IO-I-compound + SequenceRecord-I-IO-IRef-compound + SequenceRecord-I-IO-I-compound
  Test555(); //SequenceRecord-IS-IE-compound
  Test556(); //Choice-IChoiceRealInteger setters and getters
  Test557(); //Choice-IChoiceRealInteger-direct DecodeBer + EncodeDer + Print
  Test558(); //Choice-IChoiceRealInteger-direct DecodeBer + EncodeDer + Print
  Test559(); //Choice-IChoiceRealInteger-direct copy constructor
  Test560(); //Choice-IChoiceRealInteger-direct move constructor
  Test561(); //Choice-IChoiceRealInteger-direct copy =
  Test562(); //Choice-IChoiceRealInteger-direct move =
  Test563(); //Choice-IChoiceRealInteger-direct Clear
  Test564(); //Choice-IChoicePS-IA5-direct and the same Choice-IChoicePS-IA5-direct again
  Test565(); //Choice-IChoicePS-IA5-direct partial decoding copy constructor
  Test566(); //Choice-IChoicePS-IA5-direct partial decoding move constructor
  Test567(); //Choice-IChoicePS-IA5-direct partial decoding copy operator =
  Test568(); //Choice-IChoicePS-IA5-direct partial decoding move operator =
  Test569(); //AsnAbstractType::ChangePrintFunc()
  Test570(); //BIT_STRING::operator ==
  Test571(); //BIT_STRING::operator !=
  Test572(); //NativeInteger::operator ++ и NativeInteger::operator --
  Test573(); //EnumeratedRefRef
  Test574(); //SequenceRecord-VSD-VS-VSD-VSD::SetEmptyToDefault()
  Test575(); //SequenceRecord-IA5D-IA5-IA5D-IA5D
  Test576(); //SequenceRecord-IA5D-IA5-IA5D-IA5D
  Test577(); //SequenceRecord-IA5D-IA5-IA5D-IA5D
  Test578(); //SequenceRecord-IA5D-IA5-IA5D-IA5D
  Test579(); //SequenceRecord-IA5D-IA5-IA5D-IA5D::SetEmptyToDefault()
  Test580(); //SequenceRecord-PSD-PS-PSD-PSD
  Test581(); //SequenceRecord-PSD-PS-PSD-PSD
  Test582(); //SequenceRecord-PSD-PS-PSD-PSD
  Test583(); //SequenceRecord-PSD-PS-PSD-PSD
  Test584(); //SequenceRecord-PSD-PS-PSD-PSD::SetEmptyToDefault()
  Test585(); //SequenceRecord-I646D-I646-I646D-I646D
  Test586(); //SequenceRecord-I646D-I646-I646D-I646D
  Test587(); //SequenceRecord-I646D-I646-I646D-I646D
  Test588(); //SequenceRecord-I646D-I646-I646D-I646D
  Test589(); //SequenceRecord-I646D-I646-I646D-I646D::SetEmptyToDefault()
  Test590(); //SequenceRecord-NSD-NS-NSD-NSD
  Test591(); //SequenceRecord-NSD-NS-NSD-NSD
  Test592(); //SequenceRecord-NSD-NS-NSD-NSD
  Test593(); //SequenceRecord-NSD-NS-NSD-NSD
  Test594(); //SequenceRecord-NSD-NS-NSD-NSD::SetEmptyToDefault()
  Test595(); //SequenceRecord-USD-US-USD-USD
  Test596(); //SequenceRecord-USD-US-USD-USD
  Test597(); //SequenceRecord-USD-US-USD-USD
  Test598(); //SequenceRecord-USD-US-USD-USD
  Test599(); //SequenceRecord-USD-US-USD-USD::SetEmptyToDefault()
  Test600(); //SequenceRecord-BSD-BS-BSD-BSD
  Test601(); //SequenceRecord-BSD-BS-BSD-BSD
  Test602(); //SequenceRecord-BSD-BS-BSD-BSD
  Test603(); //SequenceRecord-BSD-BS-BSD-BSD
  Test604(); //SequenceRecord-BSD-BS-BSD-BSD::SetEmptyToDefault()
  Test605(); //SetRecord-ISet-Sets-of-enumerated::operator = move (tests memory leak in move operator =)
  Test606(); //SetRecord-ISet-Sets-of-enumerated::operator = move (tests memory leak in move operator =)
  Test607(); //SequenceRecord-empty
  Test608(); //SetRecord-empty
  Test609(); //ChoiceRecord-empty
  Test610(); //ChoiceRecord-empty-direct
  Test611(); //NativeInteger::operators <, <=, >, >=
  Test612(); //UnsignedNativeInteger::operators <, <=, >, >=
  Test613(); //NativeReal::operators <, <=, >, >=
  Test614(); //Sorting of std::vector<NativeInteger>
  Test615(); //Sorting of std::vector<UnsignedNativeInteger>
  Test616(); //Sorting of std::vector<NativeReal>
  Test617(); //SOME_MODULE1::External + SOME_MODULE2::External (including check that field single-ASN1-type will be appropriate pointer)
  Test618(); //SOME_MODULE1::External-direct + SOME_MODULE2::External-direct
  printf("\nOK count: %u\nFAILED count: %u\nSkipped count: %u\n",
          countOK, countFAILED, skippedCount);
  if (failedNumbers.size()) {
    printf("\nFailed test numbers: ");
    for (auto it = failedNumbers.begin(); it != failedNumbers.end(); ++it) {
      printf("%u ", (uint32_t)*it);
    }
    printf("\n");
  }
  if (!countFAILED)
    return 0;
  else
    return 1;
}

