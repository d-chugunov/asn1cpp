#include <vector>
#include <string>
#include <string.h>

#include "BIT_STRING.hpp"
#include "GeneralizedTime.hpp"
#include "IA5String.hpp"
#include "VisibleString.hpp"
#include "ISO646String.hpp"
#include "NumericString.hpp"
#include "OBJECT_IDENTIFIER.hpp"
#include "PrintableString.hpp"
#include "UTCTime.hpp"
#include "UTF8String.hpp"
#include "module/Choice-NumS-UT.hpp"
#include "module/SequenceRecord-NumS-NumSO-UT-UTO.hpp"
#include "module/SeqOf-NumS.hpp"
#include "module/SetRecord-NumS-NumSO-UT-UTO.hpp"
#include "module/SetOf-NumS.hpp"
#include "module/SequenceRecord-I-IRef-IRefC.hpp"
#include "module/SequenceRecord-I-IRefEq-IRefCEq.hpp"
#include "module/SequenceRecord-B-BRefEq-BRefCEq.hpp"
#include "module/SequenceRecord-E-ERef-ERefC.hpp"
#include "module/SequenceRecord-E-ERefEq-ERefCEq.hpp"
#include "module/SequenceRecord-UI-UIRef-UIRefC.hpp"
#include "module/SequenceRecord-UI-UIRefEq-UIRefCEq.hpp"
#include "module/SequenceRecord-IA5-IA5Ref-IA5RefC.hpp"
#include "module/SequenceRecord-PS-PSRef-PSRefC.hpp"
#include "module/SequenceRecord-VS-VSRef-VSRefC.hpp"
#include "module/SequenceRecord-I646S-I646SRef-I646SRefC.hpp"
#include "module/SequenceRecord-NS-NSRef-NSRefC.hpp"
#include "module/SequenceRecord-US-USRef-USRefC.hpp"
#include "module/SequenceRecord-BS-BSRef-BSRefC.hpp"
#include "module/SequenceRecord-U8S-U8SRef-U8SRefC.hpp"
#include "module/SequenceRecord-GenS-GenSRef-GenSRefC.hpp"
#include "module/SequenceRecord-GraS-GraSRef-GraSRefC.hpp"
#include "module/SequenceRecord-TS-TSRef-TSRefC.hpp"
#include "module/SequenceRecord-T61S-T61SRef-T61SRefC.hpp"
#include "module/SequenceRecord-VidS-VidSRef-VidSRefC.hpp"
#include "module/SequenceRecord-OD-ODRef-ODRefC.hpp"
#include "module/SequenceRecord-BitSSize-BitSRefSize-BitSRefCSize.hpp"
#include "module/SequenceRecord-OSSize-OSRefSize-OSRefCSize.hpp"
#include "module/SequenceRecord-SeqOfSeqOfISize-SeqOfSeqOfISizeRef-SeqOfISize-SeqOfISizeRef.hpp"
#include "module/SequenceRecord-SetOfSetOfISize-SetOfSetOfISizeRef-SetOfISize-SetOfISizeRef.hpp"
#include "module/SequenceRecord-IA5SSize-IA5SRefSize-IA5SRefCSize.hpp"
#include "module/SequenceRecord-PSSize-PSRefSize-PSRefCSize.hpp"
#include "module/SequenceRecord-VSSize-VSRefSize-VSRefCSize.hpp"
#include "module/SequenceRecord-I646SSize-I646SRefSize-I646SRefCSize.hpp"
#include "module/SequenceRecord-NSSize-NSRefSize-NSRefCSize.hpp"
#include "module/SequenceRecord-USSize-USRefSize-USRefCSize.hpp"
#include "module/SequenceRecord-BSSize-BSRefSize-BSRefCSize.hpp"
#include "module/SequenceRecord-U8SSize-U8SRefSize-U8SRefCSize.hpp"
#include "module/SequenceRecord-GenSSize-GenSRefSize-GenSRefCSize.hpp"
#include "module/SequenceRecord-GraSSize-GraSRefSize-GraSRefCSize.hpp"
#include "module/SequenceRecord-TSSize-TSRefSize-TSRefCSize.hpp"
#include "module/SequenceRecord-T61SSize-T61SRefSize-T61SRefCSize.hpp"
#include "module/SequenceRecord-VidSSize-VidSRefSize-VidSRefCSize.hpp"
#include "module/SequenceRecord-ODSize-ODRefSize-ODRefCSize.hpp"
#include "module/SequenceRecord-SeqOfSeqOfICSize-SeqOfSeqOfICSizeRef-SeqOfICSize-SeqOfICSizeRef.hpp"
#include "module/SequenceRecord-SetOfSetOfICSize-SetOfSetOfICSizeRef-SetOfICSize-SetOfICSizeRef.hpp"
#include "module/SequenceRecord-IW-IWRef-IWRefC.hpp"
#include "module/SequenceRecord-EW-EWRef-EWRefC.hpp"
#include "module/IntRefRef.hpp"
#include "module/IntRefRef2.hpp"
#include "module/SetOfIntSizeRef.hpp"
#include "module/SetOfIntSizeRefSize.hpp"
#include "module/SeqOfIntSizeRef.hpp"
#include "module/SeqOfIntSizeRefSize.hpp"
#include "module/VisStrRefCRef.hpp"
#include "module/Choice-NumS-UT-direct.hpp"
#include "module/IntBig.hpp"

using namespace SOME_MODULE;

size_t testCounter = 0;
uint32_t countOK = 0, countFAILED = 0;
size_t testMinNumber = 1;


#define TEST_NUMBER PrintTestNumber();
#define OK if (testCounter >= testMinNumber) printf("OK\n"); ++countOK;

#define TEST_FAILED_MSG(message) {            \
    if (testCounter >= testMinNumber) message \
    ++countFAILED;                            \
    return; }
#define TEST_FAILED_COND TEST_FAILED_MSG(printf("FAILED\n");)

#define CHECK(condition, FAILED_ACTIONS)  \
  if (condition) {                        \
    OK                                    \
  } else {                                \
    FAILED_ACTIONS                        \
  }
#define CHECK_COND(condition) CHECK(condition, TEST_FAILED_COND)
#define CHECK_CONSTR CHECK_COND(rec.CheckConstraints())
#define CHECK_CONSTR_NOT CHECK_COND(!rec.CheckConstraints())

#define INTERMEDIATE(condition, FAILED_ACTIONS) \
  if (!(condition)) {                           \
    FAILED_ACTIONS                              \
  } 
#define INTERMEDIATE_COND(condition) INTERMEDIATE(condition, TEST_FAILED_COND)
#define INTERMEDIATE_CONSTR INTERMEDIATE_COND(rec.CheckConstraints())
#define INTERMEDIATE_CONSTR_NOT INTERMEDIATE_COND(!rec.CheckConstraints())


void PrintLn(const std::vector<uint8_t>& vec) {
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    printf("%.2x ", *it);
  }
  printf("\n");
}

void PrintTestNumber() {
  ++testCounter;
  if (testCounter >= testMinNumber)
    printf("Test %u: ", (uint32_t)testCounter);
}

void Test1() {
  TEST_NUMBER;
  BIT_STRING rec;
  rec.SetBitsUnused(5);
  INTERMEDIATE_CONSTR_NOT;
  rec.push_back(0xff);
  INTERMEDIATE_CONSTR;
  rec.SetBitsUnused(8);
  INTERMEDIATE_CONSTR_NOT;
  rec.SetBitsUnused(-1);
  CHECK_CONSTR_NOT;
}

void Test2() {
  TEST_NUMBER;
  std::vector<uint8_t> time = {0x32, 0x30, 0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  GeneralizedTime rec;
  rec = time;
  INTERMEDIATE_CONSTR;
  rec.resize(rec.size() / 2);
  CHECK_CONSTR_NOT;
}

void Test3() {
  TEST_NUMBER;
  IA5String rec;
  rec = "Test string";
  INTERMEDIATE_CONSTR;
  rec.back() = 0xff;
  CHECK_CONSTR_NOT;
}

void Test4() {
  TEST_NUMBER;
  VisibleString rec;
  rec = "Test string";
  INTERMEDIATE_CONSTR;
  rec.back() = 0xff;
  CHECK_CONSTR_NOT;
}

void Test5() {
  TEST_NUMBER;
  ISO646String rec;
  rec = "Test string";
  INTERMEDIATE_CONSTR;
  rec.back() = 0xff;
  CHECK_CONSTR_NOT;
}

void Test6() {
  TEST_NUMBER;
  NumericString rec;
  rec = "123 456 7890";
  INTERMEDIATE_CONSTR;
  rec.back() = 'a';
  CHECK_CONSTR_NOT;
}

void Test7() {
  TEST_NUMBER;
  OBJECT_IDENTIFIER rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.push_back(1);
  CHECK_CONSTR;
}

void Test8() {
  TEST_NUMBER;
  PrintableString rec;
  rec = "Test string";
  INTERMEDIATE_CONSTR;
  rec.back() = 0xff;
  CHECK_CONSTR_NOT;
}

void Test9() {
  TEST_NUMBER;
  UTCTime rec;
  std::vector<uint8_t> time = {0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  rec = time;
  INTERMEDIATE_CONSTR;
  rec.resize(rec.size() / 2);
  CHECK_CONSTR_NOT;
}

void Test10() {
  TEST_NUMBER;
  UTF8String rec;
  rec = "Test string";
  INTERMEDIATE_CONSTR;
  rec.back() = 0xff;
  CHECK_CONSTR_NOT;
}

void Test11() {
  TEST_NUMBER;
  Choice_NumS_UT rec;
  INTERMEDIATE_CONSTR_NOT;
  //rec.SetPresent(Choice_NumS_UT::PR_string);
  rec.string(new NumericString());
  INTERMEDIATE_CONSTR;
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_COND(rec.string());
  *rec.string() = "123 456 7890";
#else
  rec.string() = "123 456 7890";
#endif
  
  INTERMEDIATE_CONSTR;
#ifdef PTR_CHOICE_GETTERS
  rec.string()->back() = 'a';
#else
  rec.string().back() = 'a';
#endif
  INTERMEDIATE_CONSTR_NOT;
  //rec.SetPresent(Choice_NumS_UT::PR_time);
  rec.time(new UTCTime());
  std::vector<uint8_t> time = {0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_COND(rec.time());
  *rec.time() = time;
#else
  rec.time() = time;
#endif
  INTERMEDIATE_CONSTR;
#ifdef PTR_CHOICE_GETTERS
  rec.time()->resize(rec.time()->size() / 2);
#else
  rec.time().resize(rec.time().size() / 2);
#endif
  CHECK_CONSTR_NOT;
}

void Test12() {
  TEST_NUMBER;
  SequenceRecord_NumS_NumSO_UT_UTO rec;
  INTERMEDIATE_CONSTR_NOT;
  std::vector<uint8_t> time = {0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  rec.time1 = time;
  INTERMEDIATE_CONSTR;
  rec.time1.resize(rec.time1.size() / 2);
  INTERMEDIATE_CONSTR_NOT;
  rec.time1 = time;
  INTERMEDIATE_CONSTR;
  
  rec.string1 = "123 456 7890";
  INTERMEDIATE_CONSTR;
  rec.string1.back() = 'a';
  INTERMEDIATE_CONSTR_NOT;
  rec.string1.pop_back();
  INTERMEDIATE_CONSTR;

#ifdef INSECURE_POINTERS  
  rec.time2 = new UTCTime();
#else
  rec.time2.reset(new UTCTime());
#endif
  INTERMEDIATE_CONSTR_NOT;
  *rec.time2 = time;
  INTERMEDIATE_CONSTR;
#ifdef INSECURE_POINTERS
  rec.string2 = new NumericString();
#else
  rec.string2.reset(new NumericString());
#endif
  INTERMEDIATE_CONSTR;
  *rec.string2 = "123 456 7890";
  INTERMEDIATE_CONSTR;
  rec.string2->back() = 'a';
  CHECK_CONSTR_NOT;
}

void Test13() {
  TEST_NUMBER;
  SeqOf_NumS rec;
  rec.emplace_back();
  rec.emplace_back();
  INTERMEDIATE_CONSTR;
  rec[0] = rec[1] = "123 456 7890";
  INTERMEDIATE_CONSTR;
  rec[1].back() = 'a';
  INTERMEDIATE_CONSTR_NOT;
  rec[1].pop_back();
  INTERMEDIATE_CONSTR;
  rec[0].back() = 'a';
  INTERMEDIATE_CONSTR_NOT;
  rec[0].pop_back();
  CHECK_CONSTR;
}

void Test14() {
  TEST_NUMBER;
  SetRecord_NumS_NumSO_UT_UTO rec;
  INTERMEDIATE_CONSTR_NOT;
  std::vector<uint8_t> time = {0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  rec.time1 = time;
  INTERMEDIATE_CONSTR;
  rec.time1.resize(rec.time1.size() / 2);
  INTERMEDIATE_CONSTR_NOT;
  rec.time1 = time;
  INTERMEDIATE_CONSTR;
  
  rec.string1 = "123 456 7890";
  INTERMEDIATE_CONSTR;
  rec.string1.back() = 'a';
  INTERMEDIATE_CONSTR_NOT;
  rec.string1.pop_back();
  INTERMEDIATE_CONSTR;

#ifdef INSECURE_POINTERS
  rec.time2 = new UTCTime();
#else  
  rec.time2.reset(new UTCTime());
#endif
  INTERMEDIATE_CONSTR_NOT;
  *rec.time2 = time;
  INTERMEDIATE_CONSTR;
  
#ifdef INSECURE_POINTERS
  rec.string2 = new NumericString();
#else
  rec.string2.reset(new NumericString());
#endif
  INTERMEDIATE_CONSTR;
  *rec.string2 = "123 456 7890";
  INTERMEDIATE_CONSTR;
  rec.string2->back() = 'a';
  CHECK_CONSTR_NOT;
}

void Test15() {
  TEST_NUMBER;
  SetOf_NumS rec;
  rec.emplace_back();
  rec.emplace_back();
  INTERMEDIATE_CONSTR;
  rec[0] = rec[1] = "123 456 7890";
  INTERMEDIATE_CONSTR;
  rec[1].back() = 'a';
  INTERMEDIATE_CONSTR_NOT;
  rec[1].pop_back();
  INTERMEDIATE_CONSTR;
  rec[0].back() = 'a';
  INTERMEDIATE_CONSTR_NOT;
  rec[0].pop_back();
  CHECK_CONSTR;
}

void Test16() {
  TEST_NUMBER;
  SequenceRecord_I_IRef_IRefC rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.int1 = 50;
  rec.int2 = 150;
  rec.int3 = 250;
  INTERMEDIATE_CONSTR;
  rec.int1 = 101;
  INTERMEDIATE_CONSTR_NOT;
  rec.int1 = 100;
  INTERMEDIATE_CONSTR;
  rec.int2 = 50;
  INTERMEDIATE_CONSTR_NOT;
  rec.int2 = 200;
  INTERMEDIATE_CONSTR;
  rec.int3 = 301;
  CHECK_CONSTR_NOT;
}

void Test17() {
  TEST_NUMBER;
  SequenceRecord_I_IRefEq_IRefCEq rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.int1 = 100;
  rec.int2 = 200;
  rec.int3 = 300;
  INTERMEDIATE_CONSTR;
  rec.int1 = 101;
  INTERMEDIATE_CONSTR_NOT;
  rec.int1 = 100;
  rec.int2 = 50;
  INTERMEDIATE_CONSTR_NOT;
  rec.int2 = 200;
  rec.int3 = 301;
  CHECK_CONSTR_NOT;
}

void Test18() {
  TEST_NUMBER;
  SequenceRecord_B_BRefEq_BRefCEq rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.bool1 = 0;
  rec.bool2 = 1;
  rec.bool3 = 0;
  INTERMEDIATE_CONSTR;
  rec.bool1 = 1;
  INTERMEDIATE_CONSTR_NOT;
  rec.bool1 = 0;
  rec.bool2 = 0;
  INTERMEDIATE_CONSTR_NOT;
  rec.bool2 = 1;
  rec.bool3 = 1;
  CHECK_CONSTR_NOT;
}

void Test19() {
  TEST_NUMBER;
  SequenceRecord_E_ERef_ERefC rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.en1 = 50;
  rec.en2 = 150;
  rec.en3 = 250;
  INTERMEDIATE_CONSTR;
  rec.en1 = 101;
  INTERMEDIATE_CONSTR_NOT;
  rec.en1 = 100;
  INTERMEDIATE_CONSTR;
  rec.en2 = 50;
  INTERMEDIATE_CONSTR_NOT;
  rec.en2 = 200;
  INTERMEDIATE_CONSTR;
  rec.en3 = 301;
  CHECK_CONSTR_NOT;
}

void Test20() {
  TEST_NUMBER;
  SequenceRecord_E_ERefEq_ERefCEq rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.en1 = 100;
  rec.en2 = 200;
  rec.en3 = 300;
  INTERMEDIATE_CONSTR;
  rec.en1 = 101;
  INTERMEDIATE_CONSTR_NOT;
  rec.en1 = 100;
  rec.en2 = 50;
  INTERMEDIATE_CONSTR_NOT;
  rec.en2 = 200;
  rec.en3 = 301;
  CHECK_CONSTR_NOT;
}

void Test21() {
  TEST_NUMBER;
  SequenceRecord_UI_UIRef_UIRefC rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.int1 = 2147483650;
  rec.int2 = 2147483750;
  rec.int3 = 2147483850;
  INTERMEDIATE_CONSTR;
  rec.int1 = 2147483647;
  INTERMEDIATE_CONSTR_NOT;
  rec.int1 = 2147483650;
  INTERMEDIATE_CONSTR;
  rec.int2 = 2147483849;
  INTERMEDIATE_CONSTR_NOT;
  rec.int2 = 2147483750;
  INTERMEDIATE_CONSTR;
  rec.int3 = 2147483950;
  CHECK_CONSTR_NOT;
}

void Test22() {
  TEST_NUMBER;
  SequenceRecord_UI_UIRefEq_UIRefCEq rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.int1 = 2147483649;
  rec.int2 = 2147483749;
  rec.int3 = 2147483849;
  INTERMEDIATE_CONSTR;
  ++rec.int1;
  INTERMEDIATE_CONSTR_NOT;
  --rec.int1;
  ++rec.int2;
  INTERMEDIATE_CONSTR_NOT;
  --rec.int2;
  ++rec.int3;
  CHECK_CONSTR_NOT;
}

void Test23() {
  TEST_NUMBER;
  SequenceRecord_IA5_IA5Ref_IA5RefC rec;
  INTERMEDIATE_CONSTR;
  rec.str1 = "abcdfghijklmn";
  rec.str2 = "opqr";
  rec.str3 = "stuvwxyz";
  INTERMEDIATE_CONSTR;
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test24() {
  TEST_NUMBER;
  SequenceRecord_PS_PSRef_PSRefC rec;
  INTERMEDIATE_CONSTR;
  rec.str1 = "abcdfghijklmn";
  rec.str2 = "opqr";
  rec.str3 = "stuvwxyz";
  INTERMEDIATE_CONSTR;
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test25() {
  TEST_NUMBER;
  SequenceRecord_VS_VSRef_VSRefC rec;
  INTERMEDIATE_CONSTR;
  rec.str1 = "abcdfghijklmn";
  rec.str2 = "opqr";
  rec.str3 = "stuvwxyz";
  INTERMEDIATE_CONSTR;
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test26() {
  TEST_NUMBER;
  SequenceRecord_I646S_I646SRef_I646SRefC rec;
  INTERMEDIATE_CONSTR;
  rec.str1 = "abcdfghijklmn";
  rec.str2 = "opqr";
  rec.str3 = "stuvwxyz";
  INTERMEDIATE_CONSTR;
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test27() {
  TEST_NUMBER;
  SequenceRecord_NS_NSRef_NSRefC rec;
  INTERMEDIATE_CONSTR;
  rec.str1 = "0134";
  rec.str2 = "567";
  rec.str3 = "89";
  INTERMEDIATE_CONSTR;
  rec.str1.push_back('2');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = '5';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str2.push_back('8');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = '4';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str3.push_back('0');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test28() {
  TEST_NUMBER;
  SequenceRecord_US_USRef_USRefC rec;
  INTERMEDIATE_CONSTR;
  const uint8_t str1[] = "\0\0\0a\0\0\0b\0\0\0c\0\0\0d\0\0\0f\0\0\0g\0\0\0h\0\0\0i\0\0\0j\0\0\0k\0\0\0l\0\0\0m\0\0\0n";
  const uint8_t str2[] = "\0\0\0o\0\0\0p\0\0\0q\0\0\0r";
  const uint8_t str3[] = "\0\0\0s\0\0\0t\0\0\0u\0\0\0v\0\0\0w\0\0\0x\0\0\0y\0\0\0z";
  rec.str1.assign(str1, str1 + sizeof(str1) - 1);
  rec.str2.assign(str2, str2 + sizeof(str2) - 1);
  rec.str3.assign(str3, str3 + sizeof(str3) - 1);
  INTERMEDIATE_CONSTR;
  rec.str1.push_back(0);
  rec.str1.push_back(0);
  rec.str1.push_back(0);
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str1.pop_back();
  rec.str1.pop_back();
  rec.str1.pop_back();
  rec.str2.push_back(0);
  rec.str2.push_back(0);
  rec.str2.push_back(0);
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str2.pop_back();
  rec.str2.pop_back();
  rec.str2.pop_back();
  rec.str3.push_back(0);
  rec.str3.push_back(0);
  rec.str3.push_back(0);
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  rec.str3.pop_back();
  rec.str3.pop_back();
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test29() {
  TEST_NUMBER;
  SequenceRecord_BS_BSRef_BSRefC rec;
  INTERMEDIATE_CONSTR;
  const uint8_t str1[] = "\0a\0b\0c\0d\0f\0g\0h\0i\0j\0k\0l\0m\0n";
  const uint8_t str2[] = "\0o\0p\0q\0r";
  const uint8_t str3[] = "\0s\0t\0u\0v\0w\0x\0y\0z";
  rec.str1.assign(str1, str1 + sizeof(str1) - 1);
  rec.str2.assign(str2, str2 + sizeof(str2) - 1);
  rec.str3.assign(str3, str3 + sizeof(str3) - 1);
  INTERMEDIATE_CONSTR;
  rec.str1.push_back(0);
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str1.pop_back();
  rec.str2.push_back(0);
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str2.pop_back();
  rec.str3.push_back(0);
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test30() {
  TEST_NUMBER;
  SequenceRecord_U8S_U8SRef_U8SRefC rec;
  INTERMEDIATE_CONSTR;
  rec.str1 = "abcdfghijklmn";
  rec.str2 = "opqr";
  rec.str3 = "stuvwxyz";
  INTERMEDIATE_CONSTR;
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test31() {
  TEST_NUMBER;
  SequenceRecord_GenS_GenSRef_GenSRefC rec;
  INTERMEDIATE_CONSTR;
  const uint8_t str1[] = "abcdfghijklmn";
  const uint8_t str2[] = "opqr";
  const uint8_t str3[] = "stuvwxyz";
  rec.str1.assign(str1, str1 + sizeof(str1) - 1);
  rec.str2.assign(str2, str2 + sizeof(str2) - 1);
  rec.str3.assign(str3, str3 + sizeof(str3) - 1);
  INTERMEDIATE_CONSTR;
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test32() {
  TEST_NUMBER;
  SequenceRecord_GraS_GraSRef_GraSRefC rec;
  INTERMEDIATE_CONSTR;
  const uint8_t str1[] = "abcdfghijklmn";
  const uint8_t str2[] = "opqr";
  const uint8_t str3[] = "stuvwxyz";
  rec.str1.assign(str1, str1 + sizeof(str1) - 1);
  rec.str2.assign(str2, str2 + sizeof(str2) - 1);
  rec.str3.assign(str3, str3 + sizeof(str3) - 1);
  INTERMEDIATE_CONSTR;
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test33() {
  TEST_NUMBER;
  SequenceRecord_TS_TSRef_TSRefC rec;
  INTERMEDIATE_CONSTR;
  const uint8_t str1[] = "abcdfghijklmn";
  const uint8_t str2[] = "opqr";
  const uint8_t str3[] = "stuvwxyz";
  rec.str1.assign(str1, str1 + sizeof(str1) - 1);
  rec.str2.assign(str2, str2 + sizeof(str2) - 1);
  rec.str3.assign(str3, str3 + sizeof(str3) - 1);
  INTERMEDIATE_CONSTR;
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test34() {
  TEST_NUMBER;
  SequenceRecord_T61S_T61SRef_T61SRefC rec;
  INTERMEDIATE_CONSTR;
  const uint8_t str1[] = "abcdfghijklmn";
  const uint8_t str2[] = "opqr";
  const uint8_t str3[] = "stuvwxyz";
  rec.str1.assign(str1, str1 + sizeof(str1) - 1);
  rec.str2.assign(str2, str2 + sizeof(str2) - 1);
  rec.str3.assign(str3, str3 + sizeof(str3) - 1);
  INTERMEDIATE_CONSTR;
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test35() {
  TEST_NUMBER;
  SequenceRecord_VidS_VidSRef_VidSRefC rec;
  INTERMEDIATE_CONSTR;
  const uint8_t str1[] = "abcdfghijklmn";
  const uint8_t str2[] = "opqr";
  const uint8_t str3[] = "stuvwxyz";
  rec.str1.assign(str1, str1 + sizeof(str1) - 1);
  rec.str2.assign(str2, str2 + sizeof(str2) - 1);
  rec.str3.assign(str3, str3 + sizeof(str3) - 1);
  INTERMEDIATE_CONSTR;
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test36() {
  TEST_NUMBER;
  SequenceRecord_OD_ODRef_ODRefC rec;
  INTERMEDIATE_CONSTR;
  const uint8_t str1[] = "abcdfghijklmn";
  const uint8_t str2[] = "opqr";
  const uint8_t str3[] = "stuvwxyz";
  rec.str1.assign(str1, str1 + sizeof(str1) - 1);
  rec.str2.assign(str2, str2 + sizeof(str2) - 1);
  rec.str3.assign(str3, str3 + sizeof(str3) - 1);
  INTERMEDIATE_CONSTR;
  rec.str1.push_back('e');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.back() = 'o';
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.pop_back();
  rec.str2.push_back('n');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.back() = 's';
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.pop_back();
  rec.str3.push_back('r');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.pop_back();
  CHECK_CONSTR;
}

void Test37() {
  TEST_NUMBER;
  SequenceRecord_BitSSize_BitSRefSize_BitSRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(2);
  rec.str1.SetBitsUnused(1);
  rec.str2.resize(1);
  rec.str2.SetBitsUnused(4);
  rec.str3.resize(2);
  rec.str3.SetBitsUnused(4);
  INTERMEDIATE_CONSTR;
  rec.str1.SetBitsUnused(0);
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.SetBitsUnused(5);
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.SetBitsUnused(6);
  INTERMEDIATE_CONSTR;
  rec.str2.SetBitsUnused(3);
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.SetBitsUnused(7);
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.SetBitsUnused(5);
  INTERMEDIATE_CONSTR;
  rec.str3.SetBitsUnused(3);
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.SetBitsUnused(7);
  CHECK_CONSTR_NOT;
}

void Test38() {
  TEST_NUMBER;
  SequenceRecord_OSSize_OSRefSize_OSRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15);
  rec.str2.resize(4);
  rec.str3.resize(12);
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16);
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11);
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10);
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5);
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1);
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3);
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13);
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9);
  CHECK_CONSTR_NOT;
}

void Test39() {
  TEST_NUMBER;
  SequenceRecord_SeqOfSeqOfISize_SeqOfSeqOfISizeRef_SeqOfISize_SeqOfISizeRef rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.seq1.resize(1);
  rec.seq1[0].resize(15);
  rec.seq2.resize(1);
  rec.seq2[0].resize(3);
  rec.seq3.resize(30);
  rec.seq4.resize(40);
  INTERMEDIATE_CONSTR;
  rec.seq1.resize(2);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq1.pop_back();
  rec.seq1[0].resize(11);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq1[0].resize(12);
  INTERMEDIATE_CONSTR;
  rec.seq1[0].resize(16);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq1[0].resize(10);
  INTERMEDIATE_CONSTR;
  rec.seq1[0].resize(4);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq1[0].resize(5);
  INTERMEDIATE_CONSTR;
  rec.seq2.resize(2);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq2.pop_back();
  rec.seq2[0].resize(4);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq2[0].resize(1);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq2[0].resize(2);
  INTERMEDIATE_CONSTR;
  rec.seq3.resize(31);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq3.resize(19);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq3.resize(20);
  INTERMEDIATE_CONSTR;
  rec.seq4.resize(41);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq4.resize(30);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq4.resize(31);
  CHECK_CONSTR;
}

void Test40() {
  TEST_NUMBER;
  SequenceRecord_SetOfSetOfISize_SetOfSetOfISizeRef_SetOfISize_SetOfISizeRef rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.set1.resize(1);
  rec.set1[0].resize(15);
  rec.set2.resize(1);
  rec.set2[0].resize(3);
  rec.set3.resize(30);
  rec.set4.resize(40);
  INTERMEDIATE_CONSTR;
  rec.set1.resize(2);
  INTERMEDIATE_CONSTR_NOT;
  rec.set1.pop_back();
  rec.set1[0].resize(11);
  INTERMEDIATE_CONSTR_NOT;
  rec.set1[0].resize(12);
  INTERMEDIATE_CONSTR;
  rec.set1[0].resize(16);
  INTERMEDIATE_CONSTR_NOT;
  rec.set1[0].resize(10);
  INTERMEDIATE_CONSTR;
  rec.set1[0].resize(4);
  INTERMEDIATE_CONSTR_NOT;
  rec.set1[0].resize(5);
  INTERMEDIATE_CONSTR;
  rec.set2.resize(2);
  INTERMEDIATE_CONSTR_NOT;
  rec.set2.pop_back();
  rec.set2[0].resize(4);
  INTERMEDIATE_CONSTR_NOT;
  rec.set2[0].resize(1);
  INTERMEDIATE_CONSTR_NOT;
  rec.set2[0].resize(2);
  INTERMEDIATE_CONSTR;
  rec.set3.resize(31);
  INTERMEDIATE_CONSTR_NOT;
  rec.set3.resize(19);
  INTERMEDIATE_CONSTR_NOT;
  rec.set3.resize(20);
  INTERMEDIATE_CONSTR;
  rec.set4.resize(41);
  INTERMEDIATE_CONSTR_NOT;
  rec.set4.resize(30);
  INTERMEDIATE_CONSTR_NOT;
  rec.set4.resize(31);
  CHECK_CONSTR;
}

void Test41() {
  TEST_NUMBER;
  SequenceRecord_IA5SSize_IA5SRefSize_IA5SRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15);
  rec.str2.resize(4);
  rec.str3.resize(12);
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16);
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11);
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10);
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5);
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1);
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3);
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13);
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9);
  CHECK_CONSTR_NOT;
}

void Test42() {
  TEST_NUMBER;
  SequenceRecord_PSSize_PSRefSize_PSRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15, 'a');
  rec.str2.resize(4, 'a');
  rec.str3.resize(12, 'a');
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10, 'a');
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3, 'a');
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9, 'a');
  CHECK_CONSTR_NOT;
}

void Test43() {
  TEST_NUMBER;
  SequenceRecord_VSSize_VSRefSize_VSRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15, 'a');
  rec.str2.resize(4, 'a');
  rec.str3.resize(12, 'a');
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10, 'a');
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3, 'a');
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9, 'a');
  CHECK_CONSTR_NOT;
}

void Test44() {
  TEST_NUMBER;
  SequenceRecord_I646SSize_I646SRefSize_I646SRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15, 'a');
  rec.str2.resize(4, 'a');
  rec.str3.resize(12, 'a');
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10, 'a');
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3, 'a');
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13, 'a');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9, 'a');
  CHECK_CONSTR_NOT;
}

void Test45() {
  TEST_NUMBER;
  SequenceRecord_NSSize_NSRefSize_NSRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15, '1');
  rec.str2.resize(4, '1');
  rec.str3.resize(12, '1');
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10, '1');
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3, '1');
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9, '1');
  CHECK_CONSTR_NOT;
}

void Test46() {
  TEST_NUMBER;
  SequenceRecord_USSize_USRefSize_USRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15 * 4);
  rec.str2.resize(4 * 4);
  rec.str3.resize(12 * 4);
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16 * 4);
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11 * 4);
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10 * 4);
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5 * 4);
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1 * 4);
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3 * 4);
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13 * 4);
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9 * 4);
  CHECK_CONSTR_NOT;
}

void Test47() {
  TEST_NUMBER;
  SequenceRecord_BSSize_BSRefSize_BSRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15 * 2);
  rec.str2.resize(4 * 2);
  rec.str3.resize(12 * 2);
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16 * 2);
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11 * 2);
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10 * 2);
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5 * 2);
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1 * 2);
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3 * 2);
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13 * 2);
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9 * 2);
  CHECK_CONSTR_NOT;
}

void Test48() {
  TEST_NUMBER;
  SequenceRecord_U8SSize_U8SRefSize_U8SRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15, '1');
  rec.str2.resize(4, '1');
  rec.str3.resize(12, '1');
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10, '1');
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3, '1');
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9, '1');
  CHECK_CONSTR_NOT;
}

void Test49() {
  TEST_NUMBER;
  SequenceRecord_GenSSize_GenSRefSize_GenSRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15, '1');
  rec.str2.resize(4, '1');
  rec.str3.resize(12, '1');
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10, '1');
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3, '1');
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9, '1');
  CHECK_CONSTR_NOT;
}

void Test50() {
  TEST_NUMBER;
  SequenceRecord_GraSSize_GraSRefSize_GraSRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15, '1');
  rec.str2.resize(4, '1');
  rec.str3.resize(12, '1');
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10, '1');
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3, '1');
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9, '1');
  CHECK_CONSTR_NOT;
}

void Test51() {
  TEST_NUMBER;
  SequenceRecord_TSSize_TSRefSize_TSRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15, '1');
  rec.str2.resize(4, '1');
  rec.str3.resize(12, '1');
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10, '1');
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3, '1');
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9, '1');
  CHECK_CONSTR_NOT;
}

void Test52() {
  TEST_NUMBER;
  SequenceRecord_T61SSize_T61SRefSize_T61SRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15, '1');
  rec.str2.resize(4, '1');
  rec.str3.resize(12, '1');
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10, '1');
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3, '1');
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9, '1');
  CHECK_CONSTR_NOT;
}

void Test53() {
  TEST_NUMBER;
  SequenceRecord_VidSSize_VidSRefSize_VidSRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15, '1');
  rec.str2.resize(4, '1');
  rec.str3.resize(12, '1');
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10, '1');
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3, '1');
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9, '1');
  CHECK_CONSTR_NOT;
}

void Test54() {
  TEST_NUMBER;
  SequenceRecord_ODSize_ODRefSize_ODRefCSize rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(15, '1');
  rec.str2.resize(4, '1');
  rec.str3.resize(12, '1');
  INTERMEDIATE_CONSTR;
  rec.str1.resize(16, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(11, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str1.resize(10, '1');
  INTERMEDIATE_CONSTR;
  rec.str2.resize(5, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(1, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str2.resize(3, '1');
  INTERMEDIATE_CONSTR;
  rec.str3.resize(13, '1');
  INTERMEDIATE_CONSTR_NOT;
  rec.str3.resize(9, '1');
  CHECK_CONSTR_NOT;
}

void Test55() {
  TEST_NUMBER;
  SequenceRecord_SeqOfSeqOfICSize_SeqOfSeqOfICSizeRef_SeqOfICSize_SeqOfICSizeRef rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.seq1.resize(1);
  NativeInteger int10;
  NativeInteger int20;
  NativeInteger int30;
  NativeInteger int40;
  int10 = 10;
  int20 = 20;
  int30 = 30;
  int40 = 40;
  rec.seq1[0].resize(15, int10);
  rec.seq2.resize(1);
  rec.seq2[0].resize(3, int20);
  rec.seq3.resize(30, int30);
  rec.seq4.resize(40, int40);
  INTERMEDIATE_CONSTR;
  rec.seq1.resize(2);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq1.pop_back();
  rec.seq1[0].resize(11, int10);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq1[0].resize(12, int10);
  INTERMEDIATE_CONSTR;
  rec.seq1[0].resize(16, int10);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq1[0].resize(10, int10);
  INTERMEDIATE_CONSTR;
  rec.seq1[0].resize(4, int10);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq1[0].resize(5, int10);
  INTERMEDIATE_CONSTR;
  rec.seq2.resize(2);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq2.pop_back();
  rec.seq2[0].resize(4, int20);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq2[0].resize(1, int20);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq2[0].resize(2, int20);
  INTERMEDIATE_CONSTR;
  rec.seq3.resize(31, int30);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq3.resize(19, int30);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq3.resize(20, int30);
  INTERMEDIATE_CONSTR;
  rec.seq4.resize(41, int40);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq4.resize(30, int40);
  INTERMEDIATE_CONSTR_NOT;
  rec.seq4.resize(31, int40);
  INTERMEDIATE_CONSTR;
  rec.seq1[0][0] = 9;
  INTERMEDIATE_CONSTR_NOT;
  rec.seq1[0][0] = 21;
  INTERMEDIATE_CONSTR_NOT;
  rec.seq1[0][0] = 20;
  rec.seq2[0][0] = 19;
  INTERMEDIATE_CONSTR_NOT;
  rec.seq2[0][0] = 31;
  INTERMEDIATE_CONSTR_NOT;
  rec.seq2[0][0] = 30;
  rec.seq3[0] = 29;
  INTERMEDIATE_CONSTR_NOT;
  rec.seq3[0] = 41;
  INTERMEDIATE_CONSTR_NOT;
  rec.seq3[0] = 40;
  rec.seq4[0] = 39;
  INTERMEDIATE_CONSTR_NOT;
  rec.seq4[0] = 51;
  INTERMEDIATE_CONSTR_NOT;
  rec.seq4[0] = 50;
  CHECK_CONSTR;
}

void Test56() {
  TEST_NUMBER;
  SequenceRecord_SetOfSetOfICSize_SetOfSetOfICSizeRef_SetOfICSize_SetOfICSizeRef rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.set1.resize(1);
  NativeInteger int10;
  NativeInteger int20;
  NativeInteger int30;
  NativeInteger int40;
  int10 = 10;
  int20 = 20;
  int30 = 30;
  int40 = 40;
  rec.set1[0].resize(15, int10);
  rec.set2.resize(1);
  rec.set2[0].resize(3, int20);
  rec.set3.resize(30, int30);
  rec.set4.resize(40, int40);
  INTERMEDIATE_CONSTR;
  rec.set1.resize(2);
  INTERMEDIATE_CONSTR_NOT;
  rec.set1.pop_back();
  rec.set1[0].resize(11, int10);
  INTERMEDIATE_CONSTR_NOT;
  rec.set1[0].resize(12, int10);
  INTERMEDIATE_CONSTR;
  rec.set1[0].resize(16, int10);
  INTERMEDIATE_CONSTR_NOT;
  rec.set1[0].resize(10, int10);
  INTERMEDIATE_CONSTR;
  rec.set1[0].resize(4, int10);
  INTERMEDIATE_CONSTR_NOT;
  rec.set1[0].resize(5, int10);
  INTERMEDIATE_CONSTR;
  rec.set2.resize(2);
  INTERMEDIATE_CONSTR_NOT;
  rec.set2.pop_back();
  rec.set2[0].resize(4, int20);
  INTERMEDIATE_CONSTR_NOT;
  rec.set2[0].resize(1, int20);
  INTERMEDIATE_CONSTR_NOT;
  rec.set2[0].resize(2, int20);
  INTERMEDIATE_CONSTR;
  rec.set3.resize(31, int30);
  INTERMEDIATE_CONSTR_NOT;
  rec.set3.resize(19, int30);
  INTERMEDIATE_CONSTR_NOT;
  rec.set3.resize(20, int30);
  INTERMEDIATE_CONSTR;
  rec.set4.resize(41, int40);
  INTERMEDIATE_CONSTR_NOT;
  rec.set4.resize(30, int40);
  INTERMEDIATE_CONSTR_NOT;
  rec.set4.resize(31, int40);
  INTERMEDIATE_CONSTR;
  rec.set1[0][0] = 9;
  INTERMEDIATE_CONSTR_NOT;
  rec.set1[0][0] = 21;
  INTERMEDIATE_CONSTR_NOT;
  rec.set1[0][0] = 20;
  rec.set2[0][0] = 19;
  INTERMEDIATE_CONSTR_NOT;
  rec.set2[0][0] = 31;
  INTERMEDIATE_CONSTR_NOT;
  rec.set2[0][0] = 30;
  rec.set3[0] = 29;
  INTERMEDIATE_CONSTR_NOT;
  rec.set3[0] = 41;
  INTERMEDIATE_CONSTR_NOT;
  rec.set3[0] = 40;
  rec.set4[0] = 39;
  INTERMEDIATE_CONSTR_NOT;
  rec.set4[0] = 51;
  INTERMEDIATE_CONSTR_NOT;
  rec.set4[0] = 50;
  CHECK_CONSTR;
}

void Test57() {
  TEST_NUMBER;
  IntegerRefC rec;
  INTERMEDIATE_CONSTR_NOT;
  rec = 201;
  INTERMEDIATE_CONSTR;
  rec = 301;
  INTERMEDIATE_CONSTR_NOT;
  rec = 300;
  INTERMEDIATE_CONSTR;
  rec = 200;
  CHECK_CONSTR_NOT;
}

void Test58() {
  TEST_NUMBER;
  SequenceRecord_IW_IWRef_IWRefC rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.int1 = 50;
  rec.int2.FromLong(150);
  rec.int3 = 250;
  INTERMEDIATE_CONSTR;
  rec.int1 = 101;
  INTERMEDIATE_CONSTR_NOT;
  rec.int1 = 100;
  INTERMEDIATE_CONSTR;
  rec.int2.FromLong(50);
  INTERMEDIATE_CONSTR_NOT;
  rec.int2.FromLong(200);
  INTERMEDIATE_CONSTR;
  rec.int3 = 301;
  CHECK_CONSTR_NOT;
}

void Test59() {
  TEST_NUMBER;
  SequenceRecord_EW_EWRef_EWRefC rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.en1 = 50;
  rec.en2.FromLong(150);
  rec.en3 = 250;
  INTERMEDIATE_CONSTR;
  rec.en1 = 101;
  INTERMEDIATE_CONSTR_NOT;
  rec.en1 = 100;
  INTERMEDIATE_CONSTR;
  rec.en2.FromLong(50);
  INTERMEDIATE_CONSTR_NOT;
  rec.en2.FromLong(200);
  INTERMEDIATE_CONSTR;
  rec.en3 = 301;
  CHECK_CONSTR_NOT;
}

void Test60() {
  TEST_NUMBER;
  SeqOfICSizeRef rec;
  INTERMEDIATE_CONSTR_NOT;
  NativeInteger int40;
  int40 = 40;
  rec.resize(31, int40);
  INTERMEDIATE_CONSTR;
  rec.back() = 39;
  INTERMEDIATE_CONSTR_NOT;
  rec.back() = 51;
  INTERMEDIATE_CONSTR_NOT;
  rec.back() = 50;
  INTERMEDIATE_CONSTR;
  rec.resize(30, int40);
  INTERMEDIATE_CONSTR_NOT;
  rec.resize(40, int40);
  INTERMEDIATE_CONSTR;
  rec.resize(41, int40);
  CHECK_CONSTR_NOT;
}

void Test61() {
  TEST_NUMBER;
  SetOfICSizeRef rec;
  INTERMEDIATE_CONSTR_NOT;
  NativeInteger int40;
  int40 = 40;
  rec.resize(31, int40);
  INTERMEDIATE_CONSTR;
  rec.back() = 39;
  INTERMEDIATE_CONSTR_NOT;
  rec.back() = 51;
  INTERMEDIATE_CONSTR_NOT;
  rec.back() = 50;
  INTERMEDIATE_CONSTR;
  rec.resize(30, int40);
  INTERMEDIATE_CONSTR_NOT;
  rec.resize(40, int40);
  INTERMEDIATE_CONSTR;
  rec.resize(41, int40);
  CHECK_CONSTR_NOT;
}

void Test62() {
  TEST_NUMBER;
  IntRefRef rec;
  INTERMEDIATE_CONSTR_NOT;
  rec = 1;
  INTERMEDIATE_CONSTR;
  rec = 51;
  INTERMEDIATE_CONSTR_NOT;
  rec = 50;
  CHECK_CONSTR;
}

void Test63() {
  TEST_NUMBER;
  IntRefRef2 rec;
  INTERMEDIATE_CONSTR_NOT;
  rec = 30;
  INTERMEDIATE_CONSTR;
  rec = 1;
  INTERMEDIATE_CONSTR_NOT;
  rec = 35;
  INTERMEDIATE_CONSTR;
  std::vector<uint8_t> buffer;
  INTERMEDIATE_COND(rec.EncodeDer(buffer).encoded >= 0);
  rec = 50;
  CHECK_CONSTR_NOT;
}

void Test64() {
  TEST_NUMBER;
  SetOfIntSizeRef rec;
  INTERMEDIATE_CONSTR_NOT;
  NativeInteger int10(10);
  rec.resize(5, int10);
  INTERMEDIATE_CONSTR;
  rec.back() = 11;
  INTERMEDIATE_CONSTR_NOT;
  rec.back() = 1;
  INTERMEDIATE_CONSTR;
  rec.back() = 0;
  INTERMEDIATE_CONSTR_NOT;
  rec.back() = 5;
  INTERMEDIATE_CONSTR;
  rec.resize(6, int10);
  INTERMEDIATE_CONSTR_NOT;
  rec.resize(5, int10);
  INTERMEDIATE_CONSTR;
  rec.resize(4, int10);
  CHECK_CONSTR_NOT;
}

void Test65() {
  TEST_NUMBER;
  SetOfIntSizeRefSize rec;
  INTERMEDIATE_CONSTR_NOT;
  NativeInteger int10(10);
  rec.resize(7, int10);
  INTERMEDIATE_CONSTR;
  rec.back() = 11;
  INTERMEDIATE_CONSTR_NOT;
  rec.back() = 1;
  INTERMEDIATE_CONSTR;
  rec.back() = 0;
  INTERMEDIATE_CONSTR_NOT;
  rec.back() = 5;
  INTERMEDIATE_CONSTR;
  rec.resize(8, int10);
  INTERMEDIATE_CONSTR_NOT;
  rec.resize(7, int10);
  INTERMEDIATE_CONSTR;
  rec.resize(6, int10);
  CHECK_CONSTR_NOT;
}

void Test66() {
  TEST_NUMBER;
  SeqOfIntSizeRef rec;
  INTERMEDIATE_CONSTR_NOT;
  NativeInteger int10(10);
  rec.resize(5, int10);
  INTERMEDIATE_CONSTR;
  rec.back() = 11;
  INTERMEDIATE_CONSTR_NOT;
  rec.back() = 1;
  INTERMEDIATE_CONSTR;
  rec.back() = 0;
  INTERMEDIATE_CONSTR_NOT;
  rec.back() = 5;
  INTERMEDIATE_CONSTR;
  rec.resize(6, int10);
  INTERMEDIATE_CONSTR_NOT;
  rec.resize(5, int10);
  INTERMEDIATE_CONSTR;
  rec.resize(4, int10);
  CHECK_CONSTR_NOT;
}

void Test67() {
  TEST_NUMBER;
  SeqOfIntSizeRefSize rec;
  INTERMEDIATE_CONSTR_NOT;
  NativeInteger int10(10);
  rec.resize(7, int10);
  INTERMEDIATE_CONSTR;
  rec.back() = 11;
  INTERMEDIATE_CONSTR_NOT;
  rec.back() = 1;
  INTERMEDIATE_CONSTR;
  rec.back() = 0;
  INTERMEDIATE_CONSTR_NOT;
  rec.back() = 5;
  INTERMEDIATE_CONSTR;
  rec.resize(8, int10);
  INTERMEDIATE_CONSTR_NOT;
  rec.resize(7, int10);
  INTERMEDIATE_CONSTR;
  rec.resize(6, int10);
  CHECK_CONSTR_NOT;
}

void Test68() {
  TEST_NUMBER;
  {
    ModuleTest2::VisStrRefC rec;
    INTERMEDIATE_CONSTR_NOT;
    rec.resize(1, 'a');
    INTERMEDIATE_CONSTR;
    rec.resize(33, 'a');
    INTERMEDIATE_CONSTR_NOT;
    rec.pop_back();
    INTERMEDIATE_CONSTR;
    rec.back() = '\n';
    INTERMEDIATE_CONSTR_NOT;
  }
  {
    ModuleTest1::VisStrRefCRef rec;
    INTERMEDIATE_CONSTR_NOT;
    rec.resize(1, 'a');
    INTERMEDIATE_CONSTR;
    rec.resize(33, 'a');
    INTERMEDIATE_CONSTR_NOT;
    rec.pop_back();
    INTERMEDIATE_CONSTR;
    rec.back() = '\n';
    INTERMEDIATE_CONSTR_NOT;
  }
  CHECK_COND(true);
}

void Test69() {
  TEST_NUMBER;
  Choice_NumS_UT_direct rec;
  INTERMEDIATE_CONSTR_NOT;
  rec.SetPresent(Choice_NumS_UT_direct::PR_string);
  INTERMEDIATE_CONSTR;
  rec.string = "123 456 7890";
  INTERMEDIATE_CONSTR;
  rec.string.back() = 'a';
  INTERMEDIATE_CONSTR_NOT;
  rec.SetPresent(Choice_NumS_UT_direct::PR_time);
  std::vector<uint8_t> time = {0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  rec.time = time;
  INTERMEDIATE_CONSTR;
  rec.time.resize(rec.time.size() / 2);
  CHECK_CONSTR_NOT;
}

void Test70() {
  TEST_NUMBER;
  IntBig rec;
  INTERMEDIATE_CONSTR;
  rec.FromLong(LONG_MAX);
  INTERMEDIATE_CONSTR;
  rec.FromLong(LONG_MIN);
  CHECK_CONSTR;
}

int main(int argc, char** argv) {
  if (argc >= 2 && strncmp(argv[1], "-test_min_number=", 17) == 0) {
    testMinNumber = atoi(argv[1] + 17);
  }
  Test1(); //BIT_STRING constraints
  Test2(); //GeneralizedTime constraints
  Test3(); //IA5String constraints
  Test4(); //VisibleString constraints
  Test5(); //ISO646String constraints
  Test6(); //NumericString constraints
  Test7(); //OBJECT IDENTIFIER constraints
  Test8(); //PrintableString constraints
  Test9(); //UTCTime constraints
  Test10(); //UTF8String constraints
  Test11(); //Choice-NumS-UT constraints
  Test12(); //SequenceRecord-NumS-NumSO-UT-UTO constraints
  Test13(); //SeqOf-NumS constraints
  Test14(); //SetRecord-NumS-NumSO-UT-UTO constraints
  Test15(); //SetOf-NumS constraints
  Test16(); //SequenceRecord-I-IRef-IRefC + IntegerRef + IntegerRefC constraints
  Test17(); //SequenceRecord_I_IRefEq_IRefCEq + IntegerRefEq + IntegerRefCEq constraints
  Test18(); //SequenceRecord_B_BRefEq_BRefCEq + BooleanRefEq + BooleanRefCEq constraints
  Test19(); //SequenceRecord-E-ERef-ERefC + EnumeratedRef + EnumeratedRefC constraints
  Test20(); //SequenceRecord-E-ERefEq-ERefCEq + EnumeratedRefEq + EnumeratedRefCEq constraints
  Test21(); //SequenceRecord-UI-UIRef-UIRefC + UIntegerRef + UIntegerRefC constraints
  Test22(); //SequenceRecord-UI-UIRefEq-UIRefCEq + UIntegerRefEq + UIntegerRefCEq constraints
  Test23(); //SequenceRecord-IA5-IA5Ref-IA5RefC + IA5Ref + + IA5RefC constraints
  Test24(); //SequenceRecord-PS-PSRef-PSRefC + PSRef + PSRefC constraints
  Test25(); //SequenceRecord-VS-VSRef-VSRefC + VSRef + VSRefC constraints
  Test26(); //SequenceRecord-I646S-I646SRef-I646SRefC + I646SRef + I646SRefC constraints
  Test27(); //SequenceRecord-NS-NSRef-NSRefC + NSRef + NSRefC constraints
  Test28(); //SequenceRecord-US-USRef-USRefC + USRef + USRefC constraints
  Test29(); //SequenceRecord-BS-BSRef-BSRefC + BSRef + BSRefC constraints
  Test30(); //SequenceRecord-U8S-U8SRef-U8SRefC + U8SRef + U8SRefC constraints
  Test31(); //SequenceRecord-GenS-GenSRef-GenSRefC + GenSRef + GenSRefC constraints
  Test32(); //SequenceRecord-GraS-GraSRef-GraSRefC + GraSRef + GraSRefC constraints
  Test33(); //SequenceRecord-TS-TSRef-TSRefC + TSRef + TSRefC constraints
  Test34(); //SequenceRecord-T61S-T61SRef-T61SRefC + T61SRef + T61SRefC constraints
  Test35(); //SequenceRecord-VidS-VidSRef-VidSRefC + VidSRef + VidSRefC constraints
  Test36(); //SequenceRecord-OD-ODRef-ODRefC + ODRef + ODRefC constraints
  Test37(); //SequenceRecord-BitSSize-BitSRefSize-BitSRefCSize + BitSRefSize + BitSRefCSize constraints
  Test38(); //SequenceRecord-OSSize-OSRefSize-OSRefCSize + OSRefSize + OSRefCSize constraints
  Test39(); //SequenceRecord-SeqOfSeqOfISize-SeqOfSeqOfISizeRef-SeqOfISize-SeqOfISizeRef + SeqOfSeqOfISizeRef + SeqOfISizeRef constraints
  Test40(); //SequenceRecord-SetOfSetOfISize-SetOfSetOfISizeRef-SetOfISize-SetOfISizeRef + SetOfSetOfISizeRef + SetOfISizeRef constraints
  Test41(); //SequenceRecord-IA5SSize-IA5SRefSize-IA5SRefCSize + IA5SRefSize + IA5SRefCSize constraints
  Test42(); //SequenceRecord-PSSize-PSRefSize-PSRefCSize + PSRefSize + PSRefCSize constraints
  Test43(); //SequenceRecord-VSSize-VSRefSize-VSRefCSize + VSRefSize + VSRefCSize constraints
  Test44(); //SequenceRecord-I646SSize-I646SRefSize-I646SRefCSize + I646SRefSize + I646SRefCSize constraints
  Test45(); //SequenceRecord-NSSize-NSRefSize-NSRefCSize + NSRefSize + NSRefCSize constraints
  Test46(); //SequenceRecord-USSize-USRefSize-USRefCSize + USRefSize + USRefCSize constraints
  Test47(); //SequenceRecord-BSSize-BSRefSize-BSRefCSize + BSRefSize + BSRefCSize constraints
  Test48(); //SequenceRecord-U8SSize-U8SRefSize-U8SRefCSize + U8SRefSize + U8SRefCSize constraints
  Test49(); //SequenceRecord-GenSSize-GenSRefSize-GenSRefCSize + GenSRefSize + GenSRefCSize constraints
  Test50(); //SequenceRecord-GraSSize-GraSRefSize-GraSRefCSize + GraSRefSize + GraSRefCSize constraints
  Test51(); //SequenceRecord-TSSize-TSRefSize-TSRefCSize + TSRefSize + TSRefCSize constraints
  Test52(); //SequenceRecord-T61SSize-T61SRefSize-T61SRefCSize + T61SRefSize + T61SRefCSize constraints
  Test53(); //SequenceRecord-VidSSize-VidSRefSize-VidSRefCSize + VidSRefSize + VidSRefCSize constraints
  Test54(); //SequenceRecord-ODSize-ODRefSize-ODRefCSize + ODRefSize + ODRefCSize constraints
  Test55(); //SequenceRecord-SeqOfSeqOfICSize-SeqOfSeqOfICSizeRef-SeqOfICSize-SeqOfICSizeRef + SeqOfSeqOfICSizeRef + SeqOfICSizeRef constraints
  Test56(); //SequenceRecord-SetOfSetOfICSize-SetOfSetOfICSizeRef-SetOfICSize-SetOfICSizeRef + SetOfSetOfICSizeRef + SetOfICSizeRef constraints
  Test57(); //IntegerRefC constraints
  Test58(); //SequenceRecord-IW-IWRef-IWRefC + IntegerWRef + IntegerWRefC constraints
  Test59(); //SequenceRecord-EW-EWRef-EWRefC + EnumeratedWRef + EnumeratedWRefC constraints
  Test60(); //SeqOfICSizeRef constraints
  Test61(); //SetOfICSizeRef constraints
  Test62(); //IntRefRef + IntRef constraints
  Test63(); //IntRefRef2 + IntRef2 constraints
  Test64(); //SetOfIntSizeRef + SetOfIntSize constraints
  Test65(); //SetOfIntSizeRefSize + SetOfIntSize2 constraints
  Test66(); //SeqOfIntSizeRef + SeqOfIntSize constraints
  Test67(); //SeqOfIntSizeRefSize + SeqOfIntSize2 constraints
  Test68(); //ModuleTest2::VisStrRefC + ModuleTest1::VisStrRefCRef constraints
  Test69(); //Choice-NumS-UT-direct constraints
  Test70(); //IntBig
  printf("\nOK count: %u\nFAILED count: %u\n", countOK, countFAILED);
  if (!countFAILED)
    return 0;
  else
    return 1;
  return 0;
}

