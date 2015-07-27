#ifndef TESTS401_500_HPP
#define	TESTS401_500_HPP

#include "headers.hpp"

void Test401() {
  std::vector<uint8_t> mustBe = {0xc0, 0xe6, 0x11, 0x8d, 0xfc, 0x84, 0x7f, 0xc3, 0x2f};
  std::vector<uint8_t> test = {0x09, 0x09, 0xc0, 0xe6, 0x11, 0x8d, 0xfc, 0x84, 0x7f, 0xc3, 0x2f};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  double d;
  REAL rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe && rec.ToDouble(d) && d == -73629473.124768
  );
  CHECK_OUT("-73629473.124768003821373");
}

void Test402() {
  std::vector<uint8_t> test = {0x01, 0x01, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BOOLEAN rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == 0);
  CHECK_OUT("FALSE");
}

void Test403() {
  TEST_NUMBER;
  BOOLEAN rec;
  rec = 1;
  CHECK_OUT("TRUE");
}

void Test404() {
  TEST_NUMBER;
  NULL_t rec;
  CHECK_OUT("<present>");
}

void Test405() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  std::vector<uint8_t> test = {0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 
                    0xfe, 0xcd};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe);
  CHECK_OUT("12 82 A7 8B 97 90 E3 98 FE CD");
}

void Test406() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  std::vector<uint8_t> test = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe && rec.GetBitsUnused() == 5);
  CHECK_OUT("12 82 A7 8B 97 90 E3 98 FE C0 (bits unused: 5)");
}

void Test407() {
  std::vector<uint8_t> test = {0x02, 0x02, 0x6f, 0x2f};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ANY rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 4);
  NativeInteger number;
  ret = number.DecodeBer(rec.data(), rec.size());
  INTERMEDIATE_CHECK(number == (long)28463);
  CHECK_OUT("02 02 6F 2F");
}

void Test408() {
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
  CHECK_OUT("SequenceRecord-I-IO-I ::= {\n    type: 123\n    type3: 92367624\n}");
}

void Test409() {
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
  CHECK_OUT("SequenceRecord-I-IO-I ::= {\n    type: 123\n    type2: 635282\n    type3: 92367624\n}");
}

void Test410() {
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
  CHECK_OUT("SequenceRecord-I-IO-I-S-1I-S-1IO-1I ::= {\n    type: 123\n    "
             "type3: 92367624\n    type5: type5 ::= {\n        value2: 13487\n"
             "    }\n}");
}

void Test411() {
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
  CHECK_OUT("SequenceRecord-I-IO-I-S-1I-S-1IO-1I ::= {\n    type: 123\n    "
            "type2: 9273\n    type3: 92367624\n    type4: type4 ::= {\n        "
            "value1: 871634\n    }\n    type5: type5 ::= {\n        value1: "
            "12347832\n        value2: 13487\n    }\n}");
}

void Test412() {
  TEST_NUMBER;
  SequenceRecord_ES_2 rec;
  CHECK_OUT("SequenceRecord-ES-2 ::= {\n    ptr1: <absent>\n}");
}

void Test413() {
  uint8_t test[] = {0x30, 0x06, 0xaa, 0x04, 0x30, 0x02, 0xaa, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ES_2 rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.ptr1 && 
                rec.ptr1->ptr2 &&
                rec.ptr1->ptr2->ptr1 && 
                !rec.ptr1->ptr2->ptr1->ptr2
  );
#ifdef INSECURE_POINTERS
  delete rec.ptr1->ptr2->ptr1;
  rec.ptr1->ptr2->ptr1 = 0;
#else
  rec.ptr1->ptr2->ptr1.reset();
#endif
  CHECK_OUT("SequenceRecord-ES-2 ::= {\n    ptr1: SequenceRecord-ESO-2 ::= "
            "{\n        ptr2: SequenceRecord-ES-2 ::= {\n            ptr1: "
            "<absent>\n        }\n    }\n}");
}

void Test414() {
  std::vector<uint8_t> mustBe1 = {0x0, 0x74, 0x0, 0x69, 0x0, 0x67, 0x0, 0x31};
  std::vector<uint8_t> mustBe2 = {0x0, 0x74, 0x0, 0x69, 0x0, 0x67, 0x0, 0x32};
  std::vector<uint8_t> mustBe3 = {0x0, 0x74, 0x0, 0x69, 0x0, 0x67, 0x0, 0x33};
  std::vector<uint8_t> mustBe4 = {0x0, 0x74, 0x0, 0x69, 0x0, 0x67, 0x0, 0x34};

  
  std::vector<uint8_t> test = {0x30, 0x17, 0x30, 0x15, 0x1e, 0x08, 0x0, 0x74, 
                    0x0, 0x69, 0x0, 0x67, 0x0, 0x31, 0x9f, 0x32, 0x08, 0x0, 
                    0x74, 0x0, 0x69, 0x0, 0x67, 0x0, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_BmpS_BmpSO_BmpSRefWithTag_BmpSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  CHECK_OUT("SequenceRecord-IS-BmpS-BmpSO-BmpSRefWithTag-BmpSRefWithTagO ::= "
  "{\n    seq: seq ::= {\n        str1: tig1\n        str3: "
  "tig3\n    }\n}");
}

void Test415() {
  std::vector<uint8_t> mustBe1 = {0x0, 0x74, 0x0, 0x69, 0x0, 0x67, 0x0, 0x31};
  std::vector<uint8_t> mustBe2 = {0x0, 0x74, 0x0, 0x69, 0x0, 0x67, 0x0, 0x32};
  std::vector<uint8_t> mustBe3 = {0x0, 0x74, 0x0, 0x69, 0x0, 0x67, 0x0, 0x33};
  std::vector<uint8_t> mustBe4 = {0x0, 0x74, 0x0, 0x69, 0x0, 0x67, 0x0, 0x34};
  
  std::vector<uint8_t> test = {0x30, 0x2c, 0x30, 0x2a, 0x1e, 0x08, 0x0, 0x74, 
                    0x0, 0x69, 0x0, 0x67, 0x0, 0x31, 0x81, 0x08, 0x0, 0x74, 0x0, 
                    0x69, 0x0, 0x67, 0x0, 0x32, 0x9f, 0x32, 0x08, 0x0, 0x74, 0x0, 
                    0x69, 0x0, 0x67, 0x0, 0x33, 0x9f, 0x32, 0x08, 0x0, 0x74, 0x0, 
                    0x69, 0x0, 0x67, 0x0, 0x34};
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
  CHECK_OUT("SequenceRecord-IS-BmpS-BmpSO-BmpSRefWithTag-BmpSRefWithTagO ::= "
  "{\n    seq: seq ::= {\n        str1: tig1\n        str2: tig2\n        str3: "
  "tig3\n        str4: tig4\n    }\n}");
}

void Test416() {
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
  CHECK_OUT("SequenceRecord-IS-GenS-GenSO-GenSRefWithTag-GenSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: 73 74 72 69 6E 67 31\n        "
            "str3: 73 74 72 69 6E 67 33\n    }\n}");
}

void Test417() {
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
  CHECK_OUT("SequenceRecord-IS-GenS-GenSO-GenSRefWithTag-GenSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: 73 74 72 69 6E 67 31\n        "
            "str2: 73 74 72 69 6E 67 32\n        str3: 73 74 72 69 6E 67 33\n"
            "        str4: 73 74 72 69 6E 67 34\n    }\n}");
}

void Test418() {
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
  CHECK_OUT("SequenceRecord-IS-GraS-GraSO-GraSRefWithTag-GraSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: 73 74 72 69 6E 67 31\n        "
            "str3: 73 74 72 69 6E 67 33\n    }\n}");
}

void Test419() {
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
  CHECK_OUT("SequenceRecord-IS-GraS-GraSO-GraSRefWithTag-GraSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: 73 74 72 69 6E 67 31\n        "
            "str2: 73 74 72 69 6E 67 32\n        str3: 73 74 72 69 6E 67 33\n"
            "        str4: 73 74 72 69 6E 67 34\n    }\n}");
}

void Test420() {
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
  CHECK_OUT("SequenceRecord-IS-IA5S-IA5SO-IA5SRefWithTag-IA5SRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: string1\n        "
            "str3: string3\n    }\n}");
}

void Test421() {
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
  CHECK_OUT("SequenceRecord-IS-IA5S-IA5SO-IA5SRefWithTag-IA5SRefWithTagO ::= "
             "{\n    seq: seq ::= {\n        str1: string1\n        "
             "str2: string2\n        str3: string3\n        str4: string4\n    }\n}");
}

void Test422() {
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
  CHECK_OUT("SequenceRecord-IS-I646S-I646SO-I646SRefWithTag-I646SRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: string1\n        "
            "str3: string3\n    }\n}");
}

void Test423() {
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
  CHECK_OUT("SequenceRecord-IS-I646S-I646SO-I646SRefWithTag-I646SRefWithTagO ::= "
             "{\n    seq: seq ::= {\n        str1: string1\n        "
             "str2: string2\n        str3: string3\n        str4: string4\n    }\n}");
}

void Test424() {
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
  CHECK_OUT("SequenceRecord-IS-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: string1\n        "
            "str3: string3\n    }\n}");
}

void Test425() {
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
  CHECK_OUT("SequenceRecord-IS-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO ::= "
             "{\n    seq: seq ::= {\n        str1: string1\n        "
             "str2: string2\n        str3: string3\n        str4: string4\n    }\n}");
}

void Test426() {
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
  CHECK_OUT("SequenceRecord-IS-OI-OIO-OIRef-OIRefO ::= {\n    seq: seq ::= "
            "{\n        objectIdentifier1: { 1.3.6.1.4.1.9363.78458 }\n        "
            "objectIdentifier3: { 1.3.6.1.4.3.9363.78458.1 }\n    }\n}");
}

void Test427() {
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
  CHECK_OUT("SequenceRecord-IS-OI-OIO-OIRef-OIRefO ::= {\n    seq: seq ::= {\n "
             "       objectIdentifier1: { 1.3.6.1.4.1.9363.78458 }\n        "
             "objectIdentifier2: { 1.3.6.1.4.2.9363 }\n        "
             "objectIdentifier3: { 1.3.6.1.4.3.9363.78458.1 }\n        "
             "objectIdentifier4: { 1.3.6.1.4.4.9363 }\n    }\n}");
}

void Test428() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x07, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_ObjD_ObjDO_ObjDRefWithTag_ObjDRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  CHECK_OUT("SequenceRecord-IS-ObjD-ObjDO-ObjDRefWithTag-ObjDRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: string1\n        "
            "str3: string3\n    }\n}");
}

void Test429() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x07, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_ObjD_ObjDO_ObjDRefWithTag_ObjDRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
  CHECK_OUT("SequenceRecord-IS-ObjD-ObjDO-ObjDRefWithTag-ObjDRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: string1\n        "
            "str2: string2\n        str3: string3\n        "
            "str4: string4\n    }\n}");
}

void Test430() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_PriS_PriSO_PriSRefWithTag_PriSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  CHECK_OUT("SequenceRecord-IS-PriS-PriSO-PriSRefWithTag-PriSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: string1\n        "
            "str3: string3\n    }\n}");
}

void Test431() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_PriS_PriSO_PriSRefWithTag_PriSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
  );
  CHECK_OUT("SequenceRecord-IS-PriS-PriSO-PriSRefWithTag-PriSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: string1\n        "
            "str2: string2\n        str3: string3\n        "
            "str4: string4\n    }\n}");
}

void Test432() {
  std::vector<uint8_t> mustBe1 = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x03, 0x06, 0x01, 0x04, 0x01};
  std::vector<uint8_t> mustBe3 = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 0x04, 0x03};
  
  std::vector<uint8_t> test = {0x30, 0x1e, 0x30, 0x1c, 0x0d, 0x0b, 0xc9, 0x13, 0x84, 0xe4, 
                    0x7a, 0x01, 0x03, 0x06, 0x01, 0x04, 0x01, 0x9f, 0x32, 0x0c, 
                    0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 
                    0x04, 0x03};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_ROI_ROIO_ROIRefWithTag_ROIRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.relativeOid1 == mustBe1 &&
            !rec.seq.relativeOid2 &&
          rec.seq.relativeOid3 == mustBe3 &&
          !rec.seq.relativeOid4
  );
  CHECK_OUT("SequenceRecord-IS-ROI-ROIO-ROIRefWithTag-ROIRefWithTagO ::= {\n"
          "    seq: seq ::= {\n        relativeOid1: { 9363.78458.1.3.6.1.4.1 "
          "}\n        relativeOid3: { 9363.78458.1.1.3.6.1.4.3 }\n    }\n}");
}

void Test433() {
  std::vector<uint8_t> mustBe1 = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x03, 0x06, 0x01, 0x04, 0x01};
  std::vector<uint8_t> mustBe2 = {0xc9, 0x13, 0x01, 0x03, 0x06, 0x01, 0x04, 0x02};
  std::vector<uint8_t> mustBe3 = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 0x04, 0x03};
  std::vector<uint8_t> mustBe4 = {0xc9, 0x13, 0x01, 0x03, 0x06, 0x01, 0x04, 0x04};
  
  std::vector<uint8_t> test = {0x30, 0x33, 0x30, 0x31, 0x0d, 0x0b, 0xc9, 0x13, 0x84, 0xe4, 
                    0x7a, 0x01, 0x03, 0x06, 0x01, 0x04, 0x01, 0x81, 0x08, 0xc9, 
                    0x13, 0x01, 0x03, 0x06, 0x01, 0x04, 0x02, 0x9f, 0x32, 0x0c, 
                    0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 
                    0x04, 0x03, 0x9f, 0x32, 0x08, 0xc9, 0x13, 0x01, 0x03, 0x06, 
                    0x01, 0x04, 0x04};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_ROI_ROIO_ROIRefWithTag_ROIRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.relativeOid1 == mustBe1 &&
            rec.seq.relativeOid2 && 
            *rec.seq.relativeOid2 == mustBe2 &&
          rec.seq.relativeOid3 == mustBe3 &&
          rec.seq.relativeOid4 &&
          *rec.seq.relativeOid4 == mustBe4
  );
  CHECK_OUT("SequenceRecord-IS-ROI-ROIO-ROIRefWithTag-ROIRefWithTagO ::= {\n"
            "    seq: seq ::= {\n        relativeOid1: { 9363.78458.1.3.6.1.4.1"
            " }\n        relativeOid2: { 9363.1.3.6.1.4.2 }\n        "
            "relativeOid3: { 9363.78458.1.1.3.6.1.4.3 }\n        "
            "relativeOid4: { 9363.1.3.6.1.4.4 }\n    }\n}");
}

void Test434() {
  std::string mustBe1 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  std::string mustBe2 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x32};
  std::string mustBe3 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x33};
  std::string mustBe4 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x34};

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x14, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_T61S_T61SO_T61SRefWithTag_T61SRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  CHECK_OUT("SequenceRecord-IS-T61S-T61SO-T61SRefWithTag-T61SRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: 73 74 72 69 6E 67 31\n"
            "        str3: 73 74 72 69 6E 67 33\n    }\n}");
}

void Test435() {
  std::string mustBe1 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  std::string mustBe2 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x32};
  std::string mustBe3 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x33};
  std::string mustBe4 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x34};
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x14, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_T61S_T61SO_T61SRefWithTag_T61SRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
  CHECK_OUT("SequenceRecord-IS-T61S-T61SO-T61SRefWithTag-T61SRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: 73 74 72 69 6E 67 31\n"
            "        str2: 73 74 72 69 6E 67 32\n        "
            "str3: 73 74 72 69 6E 67 33\n        "
            "str4: 73 74 72 69 6E 67 34\n    }\n}");
}

void Test436() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x14, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_TeleS_TeleSO_TeleSRefWithTag_TeleSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  CHECK_OUT("SequenceRecord-IS-TeleS-TeleSO-TeleSRefWithTag-TeleSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: 73 74 72 69 6E 67 31\n"
            "        str3: 73 74 72 69 6E 67 33\n    }\n}");
}

void Test437() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x14, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_TeleS_TeleSO_TeleSRefWithTag_TeleSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
  );
  CHECK_OUT("SequenceRecord-IS-TeleS-TeleSO-TeleSRefWithTag-TeleSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: 73 74 72 69 6E 67 31\n"
            "        str2: 73 74 72 69 6E 67 32\n        "
            "str3: 73 74 72 69 6E 67 33\n        "
            "str4: 73 74 72 69 6E 67 34\n    }\n}");
}

void Test438() {
  std::vector<uint8_t> mustBe1 = {0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe3 = {0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe4 = {0x34, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  
  std::vector<uint8_t> test = {0x30, 0x29, 0x30, 0x27, 0x17, 0x11, 0x31, 0x30, 0x30, 0x33, 
                    0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 
                    0x30, 0x30, 0x30, 0x9f, 0x32, 0x11, 0x33, 0x30, 0x30, 0x33, 
                    0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 
                    0x30, 0x30, 0x30};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_UT_UTO_UTRefWithTag_UTRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.time1 == mustBe1 &&
          rec.seq.time1.ToTime() == 1268239212 && 
            !rec.seq.time2 &&
          rec.seq.time3 == mustBe3 &&
          rec.seq.time3.ToTime() == 1899391212 &&
          !rec.seq.time4
  );
  CHECK_OUT("SequenceRecord-IS-UT-UTO-UTRefWithTag-UTRefWithTagO ::= {\n    "
            "seq: seq ::= {\n        time1: 2010-03-10 16:40:12 (GMT)\n        "
            "time3: 2030-03-10 16:40:12 (GMT)\n    }\n}");
}

void Test439() {
  std::vector<uint8_t> mustBe1 = {0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe3 = {0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe4 = {0x33, 0x37, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  
  std::vector<uint8_t> test = {0x30, 0x50, 0x30, 0x4e, 0x17, 0x11, 0x31, 0x30, 0x30, 0x33, 
                    0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 
                    0x30, 0x30, 0x30, 0x81, 0x11, 0x32, 0x30, 0x30, 0x33, 0x31, 
                    0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 
                    0x30, 0x30, 0x9f, 0x32, 0x11, 0x33, 0x30, 0x30, 0x33, 0x31, 
                    0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 
                    0x30, 0x30, 0x9f, 0x32, 0x11, 0x33, 0x37, 0x30, 0x33, 0x31, 
                    0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 
                    0x30, 0x30};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_UT_UTO_UTRefWithTag_UTRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.time1 == mustBe1 &&
          rec.seq.time1.ToTime() == 1268239212 && 
            rec.seq.time2 && 
          rec.seq.time2->ToTime() == 1583858412 &&
            *rec.seq.time2 == mustBe2 &&
          rec.seq.time3 == mustBe3 &&
          rec.seq.time3.ToTime() == 1899391212 &&
          rec.seq.time4 &&
          rec.seq.time4->ToTime() == 2120316012 &&
          *rec.seq.time4 == mustBe4
          
  );
  CHECK_OUT("SequenceRecord-IS-UT-UTO-UTRefWithTag-UTRefWithTagO ::= {\n    "
            "seq: seq ::= {\n        time1: 2010-03-10 16:40:12 (GMT)\n        "
            "time2: 2020-03-10 16:40:12 (GMT)\n        "
            "time3: 2030-03-10 16:40:12 (GMT)\n        "
            "time4: 2037-03-10 16:40:12 (GMT)\n    }\n}");
}

void Test440() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x0c, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_UTF8S_UTF8SO_UTF8SRefWithTag_UTF8SRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  CHECK_OUT("SequenceRecord-IS-UTF8S-UTF8SO-UTF8SRefWithTag-UTF8SRefWithTagO "
            "::= {\n    seq: seq ::= {\n        str1: string1\n        "
            "str3: string3\n    }\n}");
}

void Test441() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x0c, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_UTF8S_UTF8SO_UTF8SRefWithTag_UTF8SRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
  );
  CHECK_OUT("SequenceRecord-IS-UTF8S-UTF8SO-UTF8SRefWithTag-UTF8SRefWithTagO "
            "::= {\n    seq: seq ::= {\n        str1: string1\n        "
            "str2: string2\n        str3: string3\n        "
            "str4: string4\n    }\n}");
}

void Test442() {
  std::vector<uint8_t> mustBe1 = {0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x31};
  std::vector<uint8_t> mustBe2 = {0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x32};
  std::vector<uint8_t> mustBe3 = {0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x33};
  std::vector<uint8_t> mustBe4 = {0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x34};

  
  std::vector<uint8_t> test = {0x30, 0x17, 0x30, 0x15, 0x1c, 0x08, 0x0, 0x0, 
                               0x0, 0x69, 0x0, 0x0, 0x0, 0x31, 0x9f, 0x32, 0x08, 
                               0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_UniS_UniSO_UniSRefWithTag_UniSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  CHECK_OUT("SequenceRecord-IS-UniS-UniSO-UniSRefWithTag-UniSRefWithTagO "
            "::= {\n    seq: seq ::= {\n        str1: i1\n        "
            "str3: i3\n    }\n}");
}

void Test443() {
  std::vector<uint8_t> mustBe1 = {0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x31};
  std::vector<uint8_t> mustBe2 = {0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x32};
  std::vector<uint8_t> mustBe3 = {0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x33};
  std::vector<uint8_t> mustBe4 = {0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x34};
  
  std::vector<uint8_t> test = {0x30, 0x2c, 0x30, 0x2a, 
                               0x1c, 0x08, 0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x31, 
                               0x81, 0x08, 0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x32, 
                               0x9f, 0x32, 0x08, 0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x33, 
                               0x9f, 0x32, 0x08, 0x0, 0x0, 0x0, 0x69, 0x0, 0x0, 0x0, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_UniS_UniSO_UniSRefWithTag_UniSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
  CHECK_OUT("SequenceRecord-IS-UniS-UniSO-UniSRefWithTag-UniSRefWithTagO "
            "::= {\n    seq: seq ::= {\n        str1: i1\n        "
            "str2: i2\n        str3: i3\n        "
            "str4: i4\n    }\n}");
}

void Test444() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x15, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_VidS_VidSO_VidSRefWithTag_VidSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  CHECK_OUT("SequenceRecord-IS-VidS-VidSO-VidSRefWithTag-VidSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: 73 74 72 69 6E 67 31\n        "
            "str3: 73 74 72 69 6E 67 33\n    }\n}");
}

void Test445() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x15, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_VidS_VidSO_VidSRefWithTag_VidSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
  CHECK_OUT("SequenceRecord-IS-VidS-VidSO-VidSRefWithTag-VidSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: 73 74 72 69 6E 67 31\n        "
            "str2: 73 74 72 69 6E 67 32\n        str3: 73 74 72 69 6E 67 33\n"
            "        str4: 73 74 72 69 6E 67 34\n    }\n}");
}

void Test446() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x1a, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_VisS_VisSO_VisSRefWithTag_VisSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
  CHECK_OUT("SequenceRecord-IS-VisS-VisSO-VisSRefWithTag-VisSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: string1\n        "
            "str3: string3\n    }\n}");
}

void Test447() {
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
  SequenceRecord_IS_VisS_VisSO_VisSRefWithTag_VisSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
  CHECK_OUT("SequenceRecord-IS-VisS-VisSO-VisSRefWithTag-VisSRefWithTagO ::= "
            "{\n    seq: seq ::= {\n        str1: string1\n        "
            "str2: string2\n        str3: string3\n        "
            "str4: string4\n    }\n}");
}

void Test448() {
  std::vector<uint8_t> test = {0x80, 0x03, 0x13, 0xa5, 0xbc};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  IntegerRefWithTag rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == 1287612);
  CHECK_OUT("1287612");
}

void Test449() {
  std::vector<uint8_t> mustBe1 = {0x32, 0x30, 0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe3 = {0x32, 0x30, 0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe4 = {0x32, 0x30, 0x34, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  
  std::vector<uint8_t> test = {0x30, 0x25, 0x30, 0x23, 0x18, 0x0f, 0x32, 0x30, 0x31, 0x30, 
                    0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 
                    0x5a, 0x9f, 0x3c, 0x0f, 0x32, 0x30, 0x33, 0x30, 0x30, 0x33, 
                    0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_GT_GTO_GTRefWithTag_GTRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.time1 == mustBe1 &&
          rec.seq.time1.ToTime() == 1268239212 &&
            !rec.seq.time2 &&
          rec.seq.time3 == mustBe3 &&
          rec.seq.time3.ToTime() == 1899391212 &&
          !rec.seq.time4
  );
  CHECK_OUT("SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO ::= {\n    "
            "seq: seq ::= {\n        time1: 2010-03-10 16:40:12 (GMT)\n        "
            "time3: 2030-03-10 16:40:12 (GMT)\n    }\n}");
}

void Test450() {
  std::vector<uint8_t> mustBe1 = {0x32, 0x30, 0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe3 = {0x32, 0x30, 0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe4 = {0x32, 0x30, 0x33, 0x37, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  
  std::vector<uint8_t> test = {0x30, 0x48, 0x30, 0x46, 0x18, 0x0f, 0x32, 0x30, 0x31, 0x30, 
                    0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 
                    0x5a, 0x81, 0x0f, 0x32, 0x30, 0x32, 0x30, 0x30, 0x33, 0x31, 
                    0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a, 0x9f, 0x3c, 
                    0x0f, 0x32, 0x30, 0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 
                    0x36, 0x34, 0x30, 0x31, 0x32, 0x5a, 0x9f, 0x3c, 0x0f, 0x32, 
                    0x30, 0x33, 0x37, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 
                    0x30, 0x31, 0x32, 0x5a};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_GT_GTO_GTRefWithTag_GTRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.seq.time1 == mustBe1 &&
          rec.seq.time1.ToTime() == 1268239212 &&
            rec.seq.time2 && 
            rec.seq.time2->ToTime() == 1583858412 &&
            *rec.seq.time2 == mustBe2 &&
          rec.seq.time3 == mustBe3 &&
          rec.seq.time3.ToTime() == 1899391212 &&
          rec.seq.time4 &&
          rec.seq.time4->ToTime() == 2120316012 &&
          *rec.seq.time4 == mustBe4
  );
  CHECK_OUT("SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO ::= {\n    "
            "seq: seq ::= {\n        time1: 2010-03-10 16:40:12 (GMT)\n        "
            "time2: 2020-03-10 16:40:12 (GMT)\n        "
            "time3: 2030-03-10 16:40:12 (GMT)\n        "
            "time4: 2037-03-10 16:40:12 (GMT)\n    }\n}");
}

void Test451() {
  std::vector<uint8_t> test = {0x31, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 
                    0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_I_IO_I rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.type== 123 && 
               !rec.type2 && 
               rec.type3 == 92367624 
  );
  CHECK_OUT("SetRecord-I-IO-I ::= {\n    type: 123\n    type3: 92367624\n}");
}

void Test452() {
  std::vector<uint8_t> test = {0x31, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 0xb1, 0x92, 
                    0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_I_IO_I rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.type == 123 && 
               rec.type2 && *rec.type2 == 635282 &&
               rec.type3 == 92367624 
  );
  CHECK_OUT("SetRecord-I-IO-I ::= {\n    "
            "type: 123\n    type2: 635282\n    type3: 92367624\n}");
}

void Test453() {
  std::vector<uint8_t> test = {0x31, 0x0b, 0x31, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 0x04, 0x05, 
                    0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISetO_I_IO_I rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.set &&
              rec.set->type == 123 && 
               !rec.set->type2 && 
               rec.set->type3 == 92367624 
  );
  CHECK_OUT("SetRecord-ISetO-I-IO-I ::= {\n    set: set ::= "
            "{\n        type: 123\n        type3: 92367624\n    }\n}");
}

void Test454() {
  std::vector<uint8_t> test = {0x31, 0x10, 0x31, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 
                    0xb1, 0x92, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISetO_I_IO_I rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.set &&
                rec.set->type == 123 && 
               rec.set->type2 && *rec.set->type2 == 635282 &&
               rec.set->type3 == 92367624 
  );
  CHECK_OUT("SetRecord-ISetO-I-IO-I ::= {\n    set: set ::= {\n        "
             "type: 123\n        type2: 635282\n        "
             "type3: 92367624\n    }\n}");
}

void Test455() {
  std::vector<uint8_t> test = {0x31, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISetO_I_IO_I rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(!rec.set 
  );
  CHECK_OUT("SetRecord-ISetO-I-IO-I ::= {\n}");
}

void Test456() {
  std::vector<uint8_t> test = {0x31, 0x1a, 0x31, 0x0b, 0x31, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 
                    0x04, 0x05, 0x81, 0x6b, 0x08, 0xab, 0x0b, 0x31, 0x09, 0x8a, 
                    0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.ref1.set &&
              rec.ref1.set->type == 123 && 
               !rec.ref1.set->type2 && 
          !rec.ref2 &&
          
              rec.ref3.set &&
              rec.ref3.set->type == 123 && 
               !rec.ref3.set->type2 && 
               rec.ref3.set->type3 == 92367624 &&
          !rec.ref4 
  );
  CHECK_OUT("SetRecord-SeRef-SeRefO-SeDirRef-SeDirRefO ::= {\n    "
             "ref1: SetRecord-ISetO-I-IO-I-Ref ::= {\n        set: set ::= {\n"
             "            type: 123\n            type3: 92367624\n        }\n"
             "    }\n    ref3: SetRecord-ISetO-I-IO-I ::= {\n        "
             "set: set ::= {\n            type: 123\n            "
             "type3: 92367624\n        }\n    }\n}");
}

void Test457() {
  std::vector<uint8_t> test = {0x31, 0x48, 0x31, 0x10, 0x31, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 
                    0x03, 0x09, 0xb1, 0x92, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08, 
                    0xaa, 0x10, 0x31, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 
                    0xb1, 0x92, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08, 0xab, 0x10, 
                    0x31, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 0xb1, 0x92, 
                    0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08, 0xac, 0x10, 0x31, 0x0e, 
                    0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 0xb1, 0x92, 0x8c, 0x04, 
                    0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.ref1.set &&
              rec.ref1.set->type == 123 && 
               rec.ref1.set->type2 && 
                *rec.ref1.set->type2 == 635282 &&
               rec.ref1.set->type3 == 92367624 &&
          rec.ref2 &&
          rec.ref2->set &&
              rec.ref2->set->type == 123 && 
               rec.ref2->set->type2 && 
              *rec.ref2->set->type2 == 635282 &&
               rec.ref2->set->type3 == 92367624 &&
              rec.ref3.set &&
              rec.ref3.set->type == 123 && 
               rec.ref3.set->type2 && 
              *rec.ref3.set->type2 == 635282 &&
               rec.ref3.set->type3 == 92367624 &&
          rec.ref4 &&
          rec.ref4->set &&
              rec.ref4->set->type == 123 && 
               rec.ref4->set->type2 && 
               *rec.ref4->set->type2== 635282 &&
               rec.ref4->set->type3 == 92367624 
  );
  CHECK_OUT("SetRecord-SeRef-SeRefO-SeDirRef-SeDirRefO ::= {\n    "
            "ref1: SetRecord-ISetO-I-IO-I-Ref ::= {\n        set: set ::= {\n"
            "            type: 123\n            type2: 635282\n            "
            "type3: 92367624\n        }\n    }\n    "
            "ref2: SetRecord-ISetO-I-IO-I-Ref ::= {\n        set: set ::= {\n"
            "            type: 123\n            type2: 635282\n"
            "            type3: 92367624\n        }\n    }\n    "
            "ref3: SetRecord-ISetO-I-IO-I ::= {\n        set: set ::= {\n"
            "            type: 123\n            type2: 635282\n            "
            "type3: 92367624\n        }\n    }\n    "
            "ref4: SetRecord-ISetO-I-IO-I ::= {\n        set: set ::= {\n"
            "            type: 123\n            type2: 635282\n            "
            "type3: 92367624\n        }\n    }\n}");
}

void Test458() {
  std::vector<uint8_t> mustBe1 = {0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> test = {0x31, 0x08, 0x9f, 0x32, 0x05, 0x37, 0x84, 0x73, 0x91, 0x23};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_OSRef1_OSRef1O rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.ref1 == mustBe1 &&
          !rec.ref2
  );
  CHECK_OUT("SetRecord-OSRef1-OSRef1O ::= {\n    ref1: 37 84 73 91 23\n}");
}

void Test459() {
  std::vector<uint8_t> mustBe1 = {0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> mustBe2 = {0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> test = {0x31, 0x14, 0x8a, 0x0a, 0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 
                    0x84, 0x73, 0x91, 0x23, 0x9f, 0x32, 0x05, 0x37, 0x84, 0x73, 
                    0x91, 0x23};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_OSRef1_OSRef1O rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.ref1 == mustBe1 &&
          rec.ref2 &&
          *rec.ref2 == mustBe2
  );
  CHECK_OUT("SetRecord-OSRef1-OSRef1O ::= {\n    ref1: 37 84 73 91 23\n    "
            "ref2: 37 84 73 91 23 37 84 73 91 23\n}");
}

void Test460() {
  uint8_t test[] = {0x02, 0x05, 0x00, 0x80, 0x00, 0x00, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  UnsignedNativeIntegerTest rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec == 2147483648);
  CHECK_OUT("2147483648");
}

void Test461() {
  TEST_NUMBER;
  SetRecord_ESet_2 rec;
  CHECK_OUT("SetRecord-ESet-2 ::= {\n    ptr1: <absent>\n}");
}

void Test462() {
  uint8_t test[] = {0x31, 0x06, 0xaa, 0x04, 0x31, 0x02, 0xaa, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ESet_2 rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.ptr1 && 
                rec.ptr1->ptr2 &&
                rec.ptr1->ptr2->ptr1 && 
                !rec.ptr1->ptr2->ptr1->ptr2
  );
#ifdef INSECURE_POINTERS
  delete rec.ptr1->ptr2->ptr1;
  rec.ptr1->ptr2->ptr1 = 0;
#else
  rec.ptr1->ptr2->ptr1.reset();
#endif
  CHECK_OUT("SetRecord-ESet-2 ::= {\n    ptr1: SetRecord-ESetO-2 ::= "
            "{\n        ptr2: SetRecord-ESet-2 ::= {\n            ptr1: "
            "<absent>\n        }\n    }\n}");
}

void Test463() {
  std::vector<uint8_t> test = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ChoiceRealInteger rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == ChoiceRealInteger::PR_integer &&
          rec.integer() &&
          *rec.integer() == 123
  );
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == ChoiceRealInteger::PR_integer &&
          rec.integer() == 123
  );
#endif
  CHECK_OUT("integer: 123");
}

void Test464() {
  std::vector<uint8_t> test = {0x09, 0x09, 0x80, 0xd2, 0x1e, 0xc7, 0xdf, 0x3b, 0x64, 0x5a, 0x1d};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ChoiceRealInteger rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == ChoiceRealInteger::PR_real &&
          rec.real() &&
          *rec.real() == 123.123
  );
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == ChoiceRealInteger::PR_real &&
          rec.real() == 123.123
  );
#endif
  CHECK_OUT("real: 123.123000000000005");
}

void Test465() {
  std::vector<uint8_t> test = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec.choice() &&
          rec.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec.choice()->integer() &&
          *rec.choice()->integer() == 123
  );
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec.choice().integer() == 123
  );
#endif
  CHECK_OUT("choice: integer: 123");
}

void Test466() {
  std::vector<uint8_t> test = {0x09, 0x09, 0x80, 0xd2, 0x1e, 0xc7, 0xdf, 0x3b, 0x64, 0x5a, 0x1d};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec.choice() &&
          rec.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_real &&
          rec.choice()->real() &&
          *rec.choice()->real() == 123.123
  );
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_real &&
          rec.choice().real() == 123.123
  );
#endif
  CHECK_OUT("choice: real: 123.123000000000005");
}

void Test467() {
  std::vector<uint8_t> test = {0x30, 0x02, 0x30, 0x00};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SeqRecWithThisChoice rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.ch && 
          rec.ch->FetchPresent() == Choice_SeqWithThisChoice::PR_seq &&
          rec.ch->seq() &&
          !rec.ch->seq()->ch
  );
#else
  INTERMEDIATE_CHECK(rec.ch && 
          rec.ch->FetchPresent() == Choice_SeqWithThisChoice::PR_seq &&
          !rec.ch->seq().ch
  );
#endif
  rec.ch->seq(nullptr);
  CHECK_OUT("SeqRecWithThisChoice ::= {\n    ch: <absent>\n}");
}

void Test468() {
  std::vector<uint8_t> test = {0x31, 0x0a, 0x31, 0x08, 0x01, 0x01, 0xff, 0x02, 
                               0x03, 0x0c, 0xc3, 0x34};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_C_R_I_B rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.set.boolean == 0xFF &&
          rec.set.choice.FetchPresent() == SetRecord_ISet_C_R_I_B::set::choice::PR_integer &&
          rec.set.choice.integer() &&
          *rec.set.choice.integer() == 836404
  );
#else
  INTERMEDIATE_CHECK(rec.set.boolean == 0xFF &&
          rec.set.choice.FetchPresent() == SetRecord_ISet_C_R_I_B::set::choice::PR_integer &&
          rec.set.choice.integer() == 836404
  );
#endif
  CHECK_OUT("SetRecord-ISet-C-R-I-B ::= {\n    set: set ::= {\n        "
            "choice: integer: 836404\n        boolean: TRUE\n    }\n}");
}

void Test469() {
  std::vector<uint8_t> test = {0x31, 0x10, 0x31, 0x0e, 0x01, 0x01, 0x00, 0x09, 
                               0x09, 0x80, 0xd9, 0x18, 0x2b, 0x0f, 0xd9, 0x1a, 
                               0xb8, 0xe9};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_C_R_I_B rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.set.boolean == 0 &&
          rec.set.choice.FetchPresent() == SetRecord_ISet_C_R_I_B::set::choice::PR_real &&
          rec.set.choice.real() &&
          *rec.set.choice.real() == 12374.123813
  );
#else
  INTERMEDIATE_CHECK(rec.set.boolean == 0 &&
          rec.set.choice.FetchPresent() == SetRecord_ISet_C_R_I_B::set::choice::PR_real &&
          rec.set.choice.real() == 12374.123813
  );
#endif
  CHECK_OUT("SetRecord-ISet-C-R-I-B ::= {\n    set: set ::= {\n        "
            "choice: real: 12374.123813000000155\n        "
            "boolean: FALSE\n    }\n}");
}

void Test470() {
  std::vector<uint8_t> test = {0x31, 0x0a, 0x31, 0x08, 0x01, 0x01, 0xff, 0x02, 
                               0x03, 0x0c, 0xc3, 0x34};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_CO_R_I_B rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.set.boolean == 0xFF &&
          rec.set.choice &&
          rec.set.choice->FetchPresent() == SetRecord_ISet_CO_R_I_B::set::choice::PR_integer &&
          rec.set.choice->integer() &&
          *rec.set.choice->integer() == 836404
  );
#else
  INTERMEDIATE_CHECK(rec.set.boolean == 0xFF &&
          rec.set.choice &&
          rec.set.choice->FetchPresent() == SetRecord_ISet_CO_R_I_B::set::choice::PR_integer &&
          rec.set.choice->integer() == 836404
  );
#endif
  CHECK_OUT("SetRecord-ISet-CO-R-I-B ::= {\n    set: set ::= {\n        "
            "choice: integer: 836404\n        boolean: TRUE\n    }\n}");
}

void Test471() {
  std::vector<uint8_t> test = {0x31, 0x10, 0x31, 0x0e, 0x01, 0x01, 0x00, 0x09, 
                               0x09, 0x80, 0xd9, 0x18, 0x2b, 0x0f, 0xd9, 0x1a, 
                               0xb8, 0xe9};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_CO_R_I_B rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.set.boolean == 0 &&
          rec.set.choice &&
          rec.set.choice->FetchPresent() == SetRecord_ISet_CO_R_I_B::set::choice::PR_real &&
          rec.set.choice->real() &&
          *rec.set.choice->real() == 12374.123813
          
  );
#else
  INTERMEDIATE_CHECK(rec.set.boolean == 0 &&
          rec.set.choice &&
          rec.set.choice->FetchPresent() == SetRecord_ISet_CO_R_I_B::set::choice::PR_real &&
          rec.set.choice->real() == 12374.123813
          
  );
#endif
  CHECK_OUT("SetRecord-ISet-CO-R-I-B ::= {\n    set: set ::= {\n        "
            "choice: real: 12374.123813000000155\n        "
            "boolean: FALSE\n    }\n}");
}

void Test472() {
  std::vector<uint8_t> test = {0x31, 0x05, 0x31, 0x03, 0x01, 0x01, 0xff};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_CO_R_I_B rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.set.boolean == 0xFF &&
          !rec.set.choice
  );
  CHECK_OUT("SetRecord-ISet-CO-R-I-B ::= {\n    set: set ::= {\n        "
            "boolean: TRUE\n    }\n}");
}

void Test473() {
  std::vector<uint8_t> test = {0x30, 0x0a, 0x30, 0x08, 0x02, 0x03, 0x0c, 0xc3, 
                               0x34, 0x01, 0x01, 0xff};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_C_R_I_B rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0xFF &&
          rec.set.choice.FetchPresent() == SequenceRecord_IS_C_R_I_B::set::choice::PR_integer &&
          rec.set.choice.integer() &&
          *rec.set.choice.integer() == 836404
  );
#else
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0xFF &&
          rec.set.choice.FetchPresent() == SequenceRecord_IS_C_R_I_B::set::choice::PR_integer &&
          rec.set.choice.integer() == 836404
  );
#endif
  CHECK_OUT("SequenceRecord-IS-C-R-I-B ::= {\n    set: set ::= {\n        "
            "choice: integer: 836404\n        boolean: TRUE\n    }\n}");
}

void Test474() {
  std::vector<uint8_t> test = {0x30, 0x10, 0x30, 0x0e, 0x09, 0x09, 0x80, 0xd9, 
                               0x18, 0x2b, 0x0f, 0xd9, 0x1a, 0xb8, 0xe9, 0x01, 
                               0x01, 0x00};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_C_R_I_B rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0 &&
          rec.set.choice.FetchPresent() == SequenceRecord_IS_C_R_I_B::set::choice::PR_real &&
          rec.set.choice.real() &&
          *rec.set.choice.real() == 12374.123813
  );
#else
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0 &&
          rec.set.choice.FetchPresent() == SequenceRecord_IS_C_R_I_B::set::choice::PR_real &&
          rec.set.choice.real() == 12374.123813
  );
#endif
  CHECK_OUT("SequenceRecord-IS-C-R-I-B ::= {\n    set: set ::= {\n        "
            "choice: real: 12374.123813000000155\n        boolean: FALSE\n    }\n}");
}

void Test475() {
  std::vector<uint8_t> test = {0x30, 0x0a, 0x30, 0x08, 0x02, 0x03, 0x0c, 0xc3, 
                               0x34, 0x01, 0x01, 0xff};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_CO_R_I_B rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0xFF &&
          rec.set.choice &&
          rec.set.choice->FetchPresent() == SequenceRecord_IS_CO_R_I_B::set::choice::PR_integer &&
          rec.set.choice->integer() &&
          *rec.set.choice->integer() == 836404
  );
#else
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0xFF &&
          rec.set.choice &&
          rec.set.choice->FetchPresent() == SequenceRecord_IS_CO_R_I_B::set::choice::PR_integer &&
          rec.set.choice->integer() == 836404
  );
#endif
  CHECK_OUT("SequenceRecord-IS-CO-R-I-B ::= {\n    set: set ::= {\n        "
            "choice: integer: 836404\n        boolean: TRUE\n    }\n}");
}

void Test476() {
  std::vector<uint8_t> test = {0x30, 0x10, 0x30, 0x0e, 0x09, 0x09, 0x80, 0xd9, 
                               0x18, 0x2b, 0x0f, 0xd9, 0x1a, 0xb8, 0xe9, 0x01, 
                               0x01, 0x00};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_CO_R_I_B rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0 &&
          rec.set.choice &&
          rec.set.choice->FetchPresent() == SequenceRecord_IS_CO_R_I_B::set::choice::PR_real &&
          rec.set.choice->real() &&
          *rec.set.choice->real() == 12374.123813
  );
#else
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0 &&
          rec.set.choice &&
          rec.set.choice->FetchPresent() == SequenceRecord_IS_CO_R_I_B::set::choice::PR_real &&
          rec.set.choice->real() == 12374.123813
  );
#endif
  CHECK_OUT("SequenceRecord-IS-CO-R-I-B ::= {\n    set: set ::= {\n        "
            "choice: real: 12374.123813000000155\n        boolean: FALSE\n    }\n}");
}

void Test477() {
  std::vector<uint8_t> test = {0x30, 0x05, 0x30, 0x03, 0x01, 0x01, 0xff};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_CO_R_I_B rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0xFF &&
          !rec.set.choice
  );
  CHECK_OUT("SequenceRecord-IS-CO-R-I-B ::= {\n    set: set ::= {\n        "
            "boolean: TRUE\n    }\n}");
}

void Test478() {
  std::vector<uint8_t> test = {0x31, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfInteger rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 2 && 
             rec[2] == 3
  );
  CHECK_OUT("SetOfInteger ::= {\n    1\n    2\n    3\n}");
}

void Test479() {
  std::vector<uint8_t> test = {0x31, 0x10, 0x30, 0x06, 0x8a, 0x01, 0x01, 0x8c, 0x01, 0x03, 
                    0x30, 0x06, 0x8a, 0x01, 0xff, 0x8c, 0x01, 0xfd};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfSequenceRecord_I_IO_I rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 2);
  SequenceRecord_I_IO_IRef rec1(rec[0]);
  SequenceRecord_I_IO_IRef rec2(rec[1]);
  INTERMEDIATE_CHECK(rec1.type == 1 &&
              !rec1.type2 &&
          rec1.type3 == 3 && 
          
          rec2.type == -1 &&
              !rec2.type2 &&
          rec2.type3 == -3 
  );
  CHECK_OUT("SetOfSequenceRecord-I-IO-I ::= {\n    "
            "SequenceRecord-I-IO-IRef ::= {\n        type: 1\n        "
            "type3: 3\n    }\n    SequenceRecord-I-IO-IRef ::= {\n        "
            "type: -1\n        type3: -3\n    }\n}");
}

void Test480() {
  std::vector<uint8_t> test = {0x30, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceOfInteger rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 2 && 
             rec[2] == 3
  );
  CHECK_OUT("SequenceOfInteger ::= {\n    1\n    2\n    3\n}");
}

void Test481() {
  std::vector<uint8_t> test = {0x30, 0x10, 0x30, 0x06, 0x8a, 0x01, 0x01, 0x8c, 0x01, 0x03, 
                    0x30, 0x06, 0x8a, 0x01, 0xff, 0x8c, 0x01, 0xfd};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceOfSequenceRecord_I_IO_I rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.size() == 2);
  SequenceRecord_I_IO_IRef rec1(rec[0]);
  SequenceRecord_I_IO_IRef rec2(rec[1]);
  INTERMEDIATE_CHECK(rec1.type == 1 &&
              !rec1.type2 &&
          rec1.type3 == 3 && 
          
          rec2.type == -1 &&
              !rec2.type2 &&
          rec2.type3 == -3 
  );
  CHECK_OUT("SequenceOfSequenceRecord-I-IO-I ::= {\n    "
            "SequenceRecord-I-IO-IRef ::= {\n        type: 1\n        "
            "type3: 3\n    }\n    SequenceRecord-I-IO-IRef ::= {\n        "
            "type: -1\n        type3: -3\n    }\n}");
}

void Test482() {
  std::vector<uint8_t> test = {0x30, 0x12, 0x30, 0x10, 0x30, 0x06, 0x8a, 0x01, 0x01, 0x8c, 
                    0x01, 0x0a, 0x30, 0x06, 0x8a, 0x01, 0x02, 0x8c, 0x01, 0x14};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I rec;
  ret = rec.DecodeBer(test);
  const class SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I::sequenceRecord_I_IO_I& seqOf(rec.sequenceRecord_I_IO_I);
  INTERMEDIATE_CHECK(seqOf.size() == 2);
  const SequenceRecord_I_IO_I& rec1(seqOf[0]);
  const SequenceRecord_I_IO_I& rec2(seqOf[1]);
  INTERMEDIATE_CHECK(rec1.type == 1 && 
              !rec1.type2 && 
              rec1.type3 == 10 &&
              rec2.type == 2 && 
              !rec2.type2 && 
              rec2.type3 == 20
  );
  CHECK_OUT("SequenceRecord-SeqOfSeqRec-SeqRec-I-IO-I ::= {\n    "
            "sequenceRecord-I-IO-I: sequenceRecord-I-IO-I ::= {\n        "
            "SequenceRecord-I-IO-I ::= {\n            type: 1\n            "
            "type3: 10\n        }\n        SequenceRecord-I-IO-I ::= {\n"
            "            type: 2\n            type3: 20\n        }\n    }\n}");
}

void Test483() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  std::vector<uint8_t> test = {0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 
                    0xfe, 0xcd};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OctetStringRef rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe);
  CHECK_OUT("12 82 A7 8B 97 90 E3 98 FE CD");
}

void Test484() {
  std::vector<uint8_t> test = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec.choice() &&
          rec.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec.choice()->integer() &&
          *rec.choice()->integer() == 123
  );
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec.choice().integer() == 123
  );
#endif
  CHECK_OUT("choice: integer: 123");
}

void Test485() {
  std::vector<uint8_t> test = {0x09, 0x09, 0x80, 0xd2, 0x1e, 0xc7, 0xdf, 0x3b, 0x64, 0x5a, 0x1d};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger rec;
  ret = rec.DecodeBer(test);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec.choice() &&
          rec.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_real &&
          rec.choice()->real() &&
          *rec.choice()->real() == 123.123
  );
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_real &&
          rec.choice().real() == 123.123
  );
#endif
  CHECK_OUT("choice: real: 123.123000000000005");
}

void Test486() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BitStringRef rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec == mustBe && rec.GetBitsUnused() == 5);
  CHECK_OUT("12 82 A7 8B 97 90 E3 98 FE C0 (bits unused: 5)");
}

void Test487() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  std::vector<uint8_t> test = {0x31, 0x14, 0x31, 0x12, 0x80, 0x07, 0x73, 0x74, 
                               0x72, 0x69, 0x6e, 0x67, 0x31, 0x82, 0x07, 0x73, 
                               0x74, 0x72, 0x69, 0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.set.str1 == mustBe1 &&
            !rec.set.str2 &&
          rec.set.str3 == mustBe3 &&
          !rec.set.str4
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test488() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x31, 0x26, 0x31, 0x24, 0x80, 0x07, 0x73, 0x74, 
                               0x72, 0x69, 0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 
                               0x74, 0x72, 0x69, 0x6e, 0x67, 0x32, 0x82, 0x07, 
                               0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x33, 0x83, 
                               0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.set.str1 == mustBe1 &&
            rec.set.str2 && 
            *rec.set.str2 == mustBe2 &&
          rec.set.str3 == mustBe3 &&
          rec.set.str4 &&
          *rec.set.str4 == mustBe4
          
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test489() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
 std::vector<uint8_t> test = {0x31, 0x14, 0x31, 0x12, 0x80, 0x07, 0x73, 0x74, 
                               0x72, 0x69, 0x6e, 0x67, 0x31, 0x82, 0x07, 0x73, 
                               0x74, 0x72, 0x69, 0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.set.str1 == mustBe1 &&
            !rec.set.str2 &&
          rec.set.str3 == mustBe3 &&
          !rec.set.str4
  );
  CHECK_OUT("SetRecord-ISet-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO ::= "
            "{\n    set: set ::= {\n        str1: string1\n        "
            "str3: string3\n    }\n}");
}

void Test490() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  std::vector<uint8_t> test = {0x31, 0x26, 0x31, 0x24, 0x80, 0x07, 0x73, 0x74, 
                               0x72, 0x69, 0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 
                               0x74, 0x72, 0x69, 0x6e, 0x67, 0x32, 0x82, 0x07, 
                               0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x33, 0x83, 
                               0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO rec;
  ret = rec.DecodeBer(test);
  
  INTERMEDIATE_CHECK(rec.set.str1 == mustBe1 &&
            rec.set.str2 && 
            *rec.set.str2 == mustBe2 &&
          rec.set.str3 == mustBe3 &&
          rec.set.str4 &&
          *rec.set.str4 == mustBe4
          
  );
  CHECK_OUT("SetRecord-ISet-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO ::= "
             "{\n    set: set ::= {\n        str1: string1\n        "
             "str2: string2\n        str3: string3\n        str4: string4\n    }\n}");
}

void Test491() {
  std::vector<uint8_t> mustBe1 = {0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> mustBe2 = {0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 0x84, 0x73, 0x91, 0x23};
  uint8_t test[] = {0x31, 0x14, 0x8a, 0x0a, 0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 
                    0x84, 0x73, 0x91, 0x23, 0x9f, 0x32, 0x05, 0x37, 0x84, 0x73, 
                    0x91, 0x23};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_OSRef1_OSRef1O rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  SetRecord_OSRef1_OSRef1O rec2(rec);
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.ref1 == mustBe1 &&
          rec2.ref2 &&
          *rec2.ref2 == mustBe2
  );
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_RESULT(rec.ref1 == mustBe1 &&
          rec.ref2 &&
          *rec.ref2 == mustBe2
  );
}

void Test492() {
  std::vector<uint8_t> mustBe1 = {0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> mustBe2 = {0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 0x84, 0x73, 0x91, 0x23};
  uint8_t test[] = {0x31, 0x14, 0x8a, 0x0a, 0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 
                    0x84, 0x73, 0x91, 0x23, 0x9f, 0x32, 0x05, 0x37, 0x84, 0x73, 
                    0x91, 0x23};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_OSRef1_OSRef1O rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  SetRecord_OSRef1_OSRef1O rec2(std::move(rec));
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.ref1 == mustBe1 &&
          rec2.ref2 &&
          *rec2.ref2 == mustBe2
  );
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_COND(ret.code == RC_FAIL);
}

void Test493() {
  std::vector<uint8_t> mustBe1 = {0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> mustBe2 = {0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 0x84, 0x73, 0x91, 0x23};
  uint8_t test[] = {0x31, 0x14, 0x8a, 0x0a, 0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 
                    0x84, 0x73, 0x91, 0x23, 0x9f, 0x32, 0x05, 0x37, 0x84, 0x73, 
                    0x91, 0x23};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_OSRef1_OSRef1O rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  SetRecord_OSRef1_OSRef1O rec2;
  rec2 = rec;
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.ref1 == mustBe1 &&
          rec2.ref2 &&
          *rec2.ref2 == mustBe2
  );
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_RESULT(rec.ref1 == mustBe1 &&
          rec.ref2 &&
          *rec.ref2 == mustBe2
  );
}

void Test494() {
  std::vector<uint8_t> mustBe1 = {0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> mustBe2 = {0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 0x84, 0x73, 0x91, 0x23};
  uint8_t test[] = {0x31, 0x14, 0x8a, 0x0a, 0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 
                    0x84, 0x73, 0x91, 0x23, 0x9f, 0x32, 0x05, 0x37, 0x84, 0x73, 
                    0x91, 0x23};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_OSRef1_OSRef1O rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  SetRecord_OSRef1_OSRef1O rec2;
  rec2 = std::move(rec);
  size_t consumed = ret.consumed;
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.ref1 == mustBe1 &&
          rec2.ref2 &&
          *rec2.ref2 == mustBe2
  );
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_COND(ret.code == RC_FAIL);
}

void Test495() {
  uint8_t test[] = {0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoicePS_IA5 rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  Choice_IChoicePS_IA5 rec2(rec);
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec2.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec2.choice() &&
          rec2.choice()->FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec2.choice()->str1() &&
          *rec2.choice()->str1() == "string1");
#else
  INTERMEDIATE_CHECK(rec2.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec2.choice().FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec2.choice().str1() == "string1");
#endif
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec.choice() &&
          rec.choice()->FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec.choice()->str1() &&
          *rec.choice()->str1() == "string1");
#else
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec.choice().FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec.choice().str1() == "string1");
#endif
}

void Test496() {
  uint8_t test[] = {0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoicePS_IA5 rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  Choice_IChoicePS_IA5 rec2(std::move(rec));
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec2.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec2.choice() &&
          rec2.choice()->FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec2.choice()->str1() &&
          *rec2.choice()->str1() == "string1");
#else
  INTERMEDIATE_CHECK(rec2.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec2.choice().FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec2.choice().str1() == "string1");
#endif
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_COND(ret.code == RC_FAIL);
}

void Test497() {
  uint8_t test[] = {0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoicePS_IA5 rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  Choice_IChoicePS_IA5 rec2;
  rec2 = rec;
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec2.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec2.choice() &&
          rec2.choice()->FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec2.choice()->str1() &&
          *rec2.choice()->str1() == "string1");
#else
  INTERMEDIATE_CHECK(rec2.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec2.choice().FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec2.choice().str1() == "string1");
#endif
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec.choice() &&
          rec.choice()->FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec.choice()->str1() &&
          *rec.choice()->str1() == "string1");
#else
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec.choice().FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec.choice().str1() == "string1");
#endif
}

void Test498() {
  uint8_t test[] = {0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoicePS_IA5 rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  Choice_IChoicePS_IA5 rec2;
  rec2 = std::move(rec);
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec2.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec2.choice() &&
          rec2.choice()->FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec2.choice()->str1() &&
          *rec2.choice()->str1() == "string1");
#else
  INTERMEDIATE_CHECK(rec2.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec2.choice().FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec2.choice().str1() == "string1");
#endif
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_COND(ret.code == RC_FAIL);
}

void Test499() {
  uint8_t test[] = {0x31, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfInteger rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2 + 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  SetOfInteger rec2(rec);
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

void Test500() {
  uint8_t test[] = {0x31, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfInteger rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2 + 2);
  INTERMEDIATE_COND(ret.code == RC_WMORE && ret.consumed == sizeof(test) / 2);
  size_t consumed = ret.consumed;
  SetOfInteger rec2(std::move(rec));
  ret = rec2.DecodeBer(test + consumed, sizeof(test) - consumed);
  INTERMEDIATE_CHECK(rec2.size() == 3 && 
              rec2[0] == 1 && 
             rec2[1] == 2 && 
             rec2[2] == 3
  );
  ret = rec.DecodeBer(test + consumed, sizeof(test) - consumed);
  CHECK_COND(ret.code == RC_FAIL);
}

void Tests401_500() {
  Test401(); //REAL print
  Test402(); //BOOLEAN print
  Test403(); //BOOLEAN print
  Test404(); //NULL print
  Test405(); //OCTET STRING print
  Test406(); //BIT STRING print
  Test407(); //ANY print
  Test408(); //SequenceRecord-I-IO-I print
  Test409(); //SequenceRecord-I-IO-I print
  Test410(); //SequenceRecord_I_IO_I_S_1I_S_1IO_1I print
  Test411(); //SequenceRecord_I_IO_I_S_1I_S_1IO_1I print
  Test412(); //SequenceRecord-ES-2 print (checking print of <absent>)
  Test413(); //SequenceRecord-ES-2 + SequenceRecord-ESO-2  print (checking print of <absent>)
  Test414(); //SequenceRecord-IS-BmpS-BmpSO-BmpSRefWithTag-BmpSRefWithTagO print
  Test415(); //SequenceRecord-IS-BmpS-BmpSO-BmpSRefWithTag-BmpSRefWithTagO print
  Test416(); //SequenceRecord-IS-GenS-GenSO-GenSRefWithTag-GenSRefWithTagO print
  Test417(); //SequenceRecord-IS-GenS-GenSO-GenSRefWithTag-GenSRefWithTagO print
  Test418(); //SequenceRecord-IS-GraS-GraSO-GraSRefWithTag-GraSRefWithTagO print
  Test419(); //SequenceRecord-IS-GraS-GraSO-GraSRefWithTag-GraSRefWithTagO print
  Test420(); //SequenceRecord-IS-IA5S-IA5SO-IA5SRefWithTag-IA5SRefWithTagO print
  Test421(); //SequenceRecord-IS-IA5S-IA5SO-IA5SRefWithTag-IA5SRefWithTagO print
  Test422(); //SequenceRecord-IS-I646S-I646SO-I646SRefWithTag-I646SRefWithTagO print
  Test423(); //SequenceRecord-IS-I646S-I646SO-I646SRefWithTag-I646SRefWithTagO print
  Test424(); //SequenceRecord-IS-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO print
  Test425(); //SequenceRecord-IS-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO print
  Test426(); //SequenceRecord-IS-OI-OIO-OIRef-OIRefO print
  Test427(); //SequenceRecord-IS-OI-OIO-OIRef-OIRefO print
  Test428(); //SequenceRecord-IS-ObjD-ObjDO-ObjDRefWithTag-ObjDRefWithTagO print
  Test429(); //SequenceRecord-IS-ObjD-ObjDO-ObjDRefWithTag-ObjDRefWithTagO print
  Test430(); //SequenceRecord-IS-PriS-PriSO-PriSRefWithTag-PriSRefWithTagO print
  Test431(); //SequenceRecord-IS-PriS-PriSO-PriSRefWithTag-PriSRefWithTagO print
  Test432(); //SequenceRecord-IS-ROI-ROIO-ROIRefWithTag-ROIRefWithTagO print
  Test433(); //SequenceRecord-IS-ROI-ROIO-ROIRefWithTag-ROIRefWithTagO print
  Test434(); //SequenceRecord-IS-T61S-T61SO-T61SRefWithTag-T61SRefWithTagO print
  Test435(); //SequenceRecord-IS-T61S-T61SO-T61SRefWithTag-T61SRefWithTagO print
  Test436(); //SequenceRecord-IS-TeleS-TeleSO-TeleSRefWithTag-TeleSRefWithTagO print
  Test437(); //SequenceRecord-IS-TeleS-TeleSO-TeleSRefWithTag-TeleSRefWithTagO print
  Test438(); //SequenceRecord-IS-UT-UTO-UTRefWithTag-UTRefWithTagO print
  Test439(); //SequenceRecord-IS-UT-UTO-UTRefWithTag-UTRefWithTagO print
  Test440(); //SequenceRecord-IS-UTF8S-UTF8SO-UTF8SRefWithTag-UTF8SRefWithTagO print
  Test441(); //SequenceRecord-IS-UTF8S-UTF8SO-UTF8SRefWithTag-UTF8SRefWithTagO print
  Test442(); //SequenceRecord-IS-UniS-UniSO-UniSRefWithTag-UniSRefWithTagO print
  Test443(); //SequenceRecord-IS-UniS-UniSO-UniSRefWithTag-UniSRefWithTagO print
  Test444(); //SequenceRecord-IS-VidS-VidSO-VidSRefWithTag-VidSRefWithTagO print
  Test445(); //SequenceRecord-IS-VidS-VidSO-VidSRefWithTag-VidSRefWithTagO print
  Test446(); //SequenceRecord-IS-VisS-VisSO-VisSRefWithTag-VisSRefWithTagO print
  Test447(); //SequenceRecord-IS-VisS-VisSO-VisSRefWithTag-VisSRefWithTagO print
  Test448(); //IntegerRefWithTag print
  Test449(); //SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO print
  Test450(); //SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO print
  Test451(); //SetRecord-I-IO-I print
  Test452(); //SetRecord-I-IO-I print
  Test453(); //SetRecord-ISetO-I-IO-I print
  Test454(); //SetRecord-ISetO-I-IO-I print
  Test455(); //SetRecord-ISetO-I-IO-I print
  Test456(); //SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO print
  Test457(); //SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO print
  Test458(); //SetRecord-OSRef1-OSRef1O print
  Test459(); //SetRecord-OSRef1-OSRef1O print
  Test460(); //UnsignedNativeInteger print
  Test461(); //SetRecord-ESet-2 print (checking print of <absent>)
  Test462(); //SetRecord-ESet-2 + SetRecord-ESetO-2  print (checking print of <absent>)
  Test463(); //ChoiceRealInteger print
  Test464(); //ChoiceRealInteger print
  Test465(); //Choice-IChoiceRealInteger print
  Test466(); //Choice-IChoiceRealInteger print
  Test467(); //SeqRecWithThisChoice print (checking print of <absent>)
  Test468(); //SetRecord-ISet-C-R-I-B print
  Test469(); //SetRecord-ISet-C-R-I-B print
  Test470(); //SetRecord-ISet-CO-R-I-B print
  Test471(); //SetRecord-ISet-CO-R-I-B print
  Test472(); //SetRecord-ISet-CO-R-I-B print
  Test473(); //SequenceRecord-IS-C-R-I-B print
  Test474(); //SequenceRecord-IS-C-R-I-B print
  Test475(); //SequenceRecord-IS-CO-R-I-B print
  Test476(); //SequenceRecord-IS-CO-R-I-B print
  Test477(); //SequenceRecord-IS-CO-R-I-B print
  Test478(); //SetOfInteger print
  Test479(); //SetOfSequenceRecord-I-IO-I + SequenceRecord-I-IO-IRef + SequenceRecord-I-IO-I print
  Test480(); //SequenceOfInteger print
  Test481(); //SequenceOfSequenceRecord-I-IO-I + SequenceRecord-I-IO-IRef + SequenceRecord-I-IO-I print
  Test482(); //SequenceRecord-SeqOfSeqRec-SeqRec-I-IO-I + SequenceRecord-I-IO-I print
  Test483(); //OctetStringRef print
  Test484(); //Choice-IChoiceRealInteger print
  Test485(); //Choice-IChoiceRealInteger print
  Test486(); //BitStringRef print
  Test487(); //SetRecord-ISet-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO EncodeDer
  Test488(); //SetRecord-ISet-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO EncodeDer
  Test489(); //SetRecord-ISet-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO print
  Test490(); //SetRecord-ISet-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO print
  Test491(); //SetRecord-OSRef1-OSRef1O + OctetStringRef1 + OctetStringRef2 + OctetStringRef3 + OctetStringRef4 partial decoding copy constructor
  Test492(); //SetRecord-OSRef1-OSRef1O + OctetStringRef1 + OctetStringRef2 + OctetStringRef3 + OctetStringRef4 partial decoding move constructor
  Test493(); //SetRecord-OSRef1-OSRef1O + OctetStringRef1 + OctetStringRef2 + OctetStringRef3 + OctetStringRef4 partial decoding copy operator =
  Test494(); //SetRecord-OSRef1-OSRef1O + OctetStringRef1 + OctetStringRef2 + OctetStringRef3 + OctetStringRef4 partial decoding move operator =
  Test495(); //Choice-IChoicePS-IA5 partial decoding copy constructor
  Test496(); //Choice-IChoicePS-IA5 partial decoding move constructor
  Test497(); //Choice-IChoicePS-IA5 partial decoding copy operator =
  Test498(); //Choice-IChoicePS-IA5 partial decoding move operator =
  Test499(); //SetOfInteger partial decoding copy constructor
  Test500(); //SetOfInteger partial decoding move constructor
}

#endif	/* TESTS401_500_HPP */

