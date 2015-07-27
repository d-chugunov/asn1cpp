#ifndef TEST1_100_HPP
#define	TEST1_100_HPP

#include "UTCTime.hpp"
#include "headers.hpp"


void Test1() {
  uint8_t test[] = {0x02, 0x04, 0x31, 0xF0, 0x2D, 0x82};
  TEST_NUMBER
  NativeInteger integer;
  asn_dec_rval_t ret;
  ret = integer.DecodeBer(test, sizeof(test));
  CHECK_RESULT(integer == 837823874);
}

void Test2() {
  TEST_NUMBER
  {
    uint8_t test[] = {0x02, 0x04, 0xfb, 0x9c, 0x80, 0xdf};
    NativeInteger integer;
    asn_dec_rval_t ret;
    ret = integer.DecodeBer(test, sizeof(test));
    INTERMEDIATE_CHECK(integer == -73629473);
  }
  {
    uint8_t test[] = {0x02, 0x04, 0x88, 0xca, 0x6c, 0x00};
    NativeInteger integer;
    asn_dec_rval_t ret;
    ret = integer.DecodeBer(test, sizeof(test));
    CHECK_RESULT(integer == -2000000000);
  }
}

void Test3() {
  uint8_t test[] = {0x30, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 
                    0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.type == 123 && 
               !rec.type2 && 
               rec.type3 == 92367624
  );
}

void Test4() {
  uint8_t test[] = {0x30, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 0xb1, 0x92, 
                    0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.type == 123 && 
               rec.type2 && *rec.type2 == 635282 &&
               rec.type3 == 92367624
  );
}

void Test5() {
  uint8_t test[] = {0x30, 0x09, 0x81, 0x01, 0x7b, 0x82, 0x04, 0x05, 0x81, 0x6b, 
                    0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IO_I_I_Automatic rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.type && 
               rec.type2 == 123 && 
               rec.type3 == 92367624
  );
}

void Test6() {
  uint8_t test[] = {0x30, 0x0e, 0x80, 0x03, 0x09, 0xb1, 0x92, 0x81, 0x01, 
                    0x7b, 0x82, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IO_I_I_Automatic rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.type && *rec.type == 635282 &&
               rec.type2 == 123 && 
               rec.type3 == 92367624
  );
}

void Test7() {
  uint8_t test[] = {0x30, 0x0f, 0x8a, 0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 
                    0x08, 0xae, 0x04, 0x81, 0x02, 0x34, 0xaf};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.type == 123 && 
                !rec.type2 &&
                rec.type3 == 92367624 &&
                !rec.type4 && 
                !rec.type5.value1 &&
                rec.type5.value2 == 13487
  );
}

void Test8() {
  uint8_t test[] = {0x30, 0x20, 0x8a, 0x01, 0x7b, 0x8b, 0x02, 0x24, 0x39, 0x8c, 
                    0x04, 0x05, 0x81, 0x6b, 0x08, 0xad, 0x05, 0x80, 0x03, 0x0d, 
                    0x4c, 0xd2, 0xae, 0x0a, 0x80, 0x04, 0x00, 0xbc, 0x69, 0xb8, 
                    0x81, 0x02, 0x34, 0xaf};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.type == 123 && 
                rec.type2 &&
                *rec.type2 == 9273 &&
                rec.type3 == 92367624 &&
                rec.type4 && 
                rec.type4->value1 == 871634 &&
                rec.type5.value1 &&
                *rec.type5.value1 == 12347832 &&
                rec.type5.value2 == 13487
  );
}

void Test9() {
  uint8_t test[] = {0x30, 0x20, 0x8a, 0x01, 0x7b, 0x8b, 0x02, 0x24, 0x39, 0x8c, 
                    0x04, 0x05, 0x81, 0x6b, 0x08, 0xad, 0x05, 0x80, 0x03, 0x0d, 
                    0x4c, 0xd2, 0xae, 0x0a, 0x80, 0x04, 0x00, 0xbc, 0x69, 0xb8, 
                    0x81, 0x02, 0x34, 0xaf};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec2(rec);
  CHECK_RESULT(rec.type == 123 && 
                rec.type2 &&
                *rec.type2 == 9273 &&
                rec.type3 == 92367624 &&
                rec.type4 && 
                rec.type4->value1 == 871634 &&
                rec.type5.value1 &&
                *rec.type5.value1 == 12347832 &&
                rec.type5.value2 == 13487 &&
          
                rec2.type == 123 && 
                rec2.type2 &&
                *rec2.type2 == 9273 &&
                rec2.type3 == 92367624 &&
                rec2.type4 && 
                rec2.type4->value1 == 871634 &&
                rec2.type5.value1 &&
                *rec2.type5.value1 == 12347832 &&
                rec2.type5.value2 == 13487
  );
}

void Test10() {
  uint8_t test[] = {0x30, 0x20, 0x8a, 0x01, 0x7b, 0x8b, 0x02, 0x24, 0x39, 0x8c, 
                    0x04, 0x05, 0x81, 0x6b, 0x08, 0xad, 0x05, 0x80, 0x03, 0x0d, 
                    0x4c, 0xd2, 0xae, 0x0a, 0x80, 0x04, 0x00, 0xbc, 0x69, 0xb8, 
                    0x81, 0x02, 0x34, 0xaf};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec2(std::move(rec));
  bool oldTypeEmpty = !rec.type && 
                !rec.type2 &&
                !rec.type3 &&
                !rec.type4 && 
                !rec.type5.value1 &&
                !rec.type5.value2;
  bool newTypeCorrect = rec2.type == 123 && 
                rec2.type2 &&
                *rec2.type2 == 9273 &&
                rec2.type3 == 92367624 &&
                rec2.type4 && 
                rec2.type4->value1 == 871634 &&
                rec2.type5.value1 &&
                *rec2.type5.value1 == 12347832 &&
                rec2.type5.value2 == 13487;
  CHECK_RESULT( oldTypeEmpty &&  newTypeCorrect);
}

void Test11() {
  uint8_t test[] = {0x30, 0x20, 0x8a, 0x01, 0x7b, 0x8b, 0x02, 0x24, 0x39, 0x8c, 
                    0x04, 0x05, 0x81, 0x6b, 0x08, 0xad, 0x05, 0x80, 0x03, 0x0d, 
                    0x4c, 0xd2, 0xae, 0x0a, 0x80, 0x04, 0x00, 0xbc, 0x69, 0xb8, 
                    0x81, 0x02, 0x34, 0xaf};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec2;
  rec2 = rec;
  CHECK_RESULT(rec.type == 123 && 
                rec.type2 &&
                *rec.type2 == 9273 &&
                rec.type3 == 92367624 &&
                rec.type4 && 
                rec.type4->value1 == 871634 &&
                rec.type5.value1 &&
                *rec.type5.value1 == 12347832 &&
                rec.type5.value2 == 13487 &&
          
                rec2.type == 123 && 
                rec2.type2 &&
                *rec2.type2 == 9273 &&
                rec2.type3 == 92367624 &&
                rec2.type4 && 
                rec2.type4->value1 == 871634 &&
                rec2.type5.value1 &&
                *rec2.type5.value1 == 12347832 &&
                rec2.type5.value2 == 13487
  );
}

void Test12() {
  uint8_t test[] = {0x30, 0x20, 0x8a, 0x01, 0x7b, 0x8b, 0x02, 0x24, 0x39, 0x8c, 
                    0x04, 0x05, 0x81, 0x6b, 0x08, 0xad, 0x05, 0x80, 0x03, 0x0d, 
                    0x4c, 0xd2, 0xae, 0x0a, 0x80, 0x04, 0x00, 0xbc, 0x69, 0xb8, 
                    0x81, 0x02, 0x34, 0xaf};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  SequenceRecord_I_IO_I_S_1I_S_1IO_1I rec2;
  rec2 = std::move(rec);
  bool oldTypeEmpty = !rec.type && 
                !rec.type2 &&
                !rec.type3 &&
                !rec.type4 && 
                !rec.type5.value1 &&
                !rec.type5.value2;
  bool newTypeCorrect = rec2.type == 123 && 
                rec2.type2 &&
                *rec2.type2 == 9273 &&
                rec2.type3 == 92367624 &&
                rec2.type4 && 
                rec2.type4->value1 == 871634 &&
                rec2.type5.value1 &&
                *rec2.type5.value1 == 12347832 &&
                rec2.type5.value2 == 13487;
  CHECK_RESULT( oldTypeEmpty &&  newTypeCorrect);
}

void Test13() {
  uint8_t test[] = {0x30, 0x08, 0xaa, 0x06, 0x02, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ES rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.type.value == 92367624
  );
}

void Test14() {
  uint8_t test[] = {0x30, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ESO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.type
  );
}

void Test15() {
  uint8_t test[] = {0x30, 0x02, 0xaa, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ESO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.type &&
              !rec.type->value
  );
}

void Test16() {
  uint8_t test[] = {0x30, 0x08, 0xaa, 0x06, 0x02, 0x04, 0x00, 0xcd, 0xa4, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ESO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.type &&
               rec.type->value &&
               *rec.type->value == 13476913
  );
}

void Test17() {
  uint8_t test[] = {0x30, 0x02, 0xaa, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ES_2 rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.ptr1 && 
                !rec.ptr1->ptr2
  );
}

void Test18() {
  uint8_t test[] = {0x30, 0x06, 0xaa, 0x04, 0x30, 0x02, 0xaa, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ES_2 rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.ptr1 && 
                rec.ptr1->ptr2 &&
                rec.ptr1->ptr2->ptr1 && 
                !rec.ptr1->ptr2->ptr1->ptr2
  );
}

void Test19() {
  uint8_t test[] = {0x30, 0x02, 0xaa, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ESO_selfRef rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.ptr1 && 
                !rec.ptr1->ptr1
  );
}

void Test20() {
  uint8_t test[] = {0x30, 0x0c, 0x30, 0x0a, 0x8a, 0x03, 0x01, 0xe4, 0xe6, 0x8c, 0x03, 0x01, 0x81, 0xca};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_DirectRef rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.field.type == 124134 &&
          !rec.field.type2 &&
          rec.field.type3 == 98762
  );
}

void Test21() {
  uint8_t test[] = {0x30, 0x10, 0x30, 0x0e, 0xaa, 0x05, 0x02, 0x03, 0x01, 0xe4, 0xe6, 0xac, 0x05, 0x02, 0x03, 0x01, 0x81, 0xca};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_DirectRef_EXPL rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.field.type == 124134 &&
          !rec.field.type2 &&
          rec.field.type3 == 98762
  );
}

void Test22() {
  uint8_t test[] = {0x30, 0x0c, 0xa0, 0x0a, 0x8a, 0x03, 0x01, 0xe4, 0xe6, 0x8c, 0x03, 0x01, 0x81, 0xca};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_DirectRef_Auto rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.field.type == 124134 &&
          !rec.field.type2 &&
          rec.field.type3 == 98762
  );
}

void Test23() {
  uint8_t test[] = {0x30, 0x0a, 0x30, 0x08, 0x30, 0x06, 0x02, 0x04, 0x08, 0x0a, 0x0b, 0xe6};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_2inner_seq rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.level1.level2.value == 134876134
  );
}

void Test24() {
  uint8_t test[] = {0x02, 0x01, 0x01};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Integer_Enumeration rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == Integer_Enumeration_enum::Integer_Enumeration_value2
  );
}

void Test25() {
  uint8_t test[] = {0x02, 0x02, 0x02, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Integer_Enumeration rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == 512
  );
}

void Test26() {
  uint8_t test[] = {0x30, 0x05, 0x30, 0x03, 0x02, 0x01, 0x01};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_IE rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.field.value == SequenceRecord_IS_IE::field::value_enum::value_value2
  );
}

void Test27() {
  uint8_t test[] = {0x30, 0x05, 0x30, 0x03, 0x02, 0x01, 0x01};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_IEO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.field.value && 
          *rec.field.value == SequenceRecord_IS_IEO::field::value_enum::value_value2
  );
}

void Test28() {
  uint8_t test[] = {0x01, 0x01, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BOOLEAN rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == 0
  );
}

void Test29() {
  uint8_t test[] = {0x01, 0x01, 0xff};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BOOLEAN rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == 0xFF
  );
}

void Test30() {
  uint8_t test[] = {0x01, 0x01, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BooleanRef rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == 0
  );
}

void Test31() {
  uint8_t test[] = {0x01, 0x01, 0xff};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BooleanRef rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == 0xFF
  );
}

void Test32() {
  uint8_t test[] = {0x30, 0x03, 0x01, 0x01, 0xff};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_B_BO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.bool1 == 0xFF &&
              !rec.continue_
  );
}

void Test33() {
  uint8_t test[] = {0x30, 0x06, 0x01, 0x01, 0x00, 0x01, 0x01, 0xff};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_B_BO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.bool1 == 0 &&
              rec.continue_ && *rec.continue_ == 0xFF
  );
}

void Test34() {
  uint8_t test[] = {0x05, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  NULL_t rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(true
  );
}

void Test35() {
  uint8_t test[] = {0x05, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  NullRef rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(true
  );
}

void Test36() {
  uint8_t test[] = {0x30, 0x02, 0x05, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_N_NO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.null2
  );
}

void Test37() {
  uint8_t test[] = {0x30, 0x04, 0x05, 0x00, 0x05, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_N_NO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.null2
  );
}

void Test38() {
  uint8_t test[] = {0x09, 0x09, 0x80, 0xe4, 0x0c, 0x60, 0x2a, 0xc1, 0xf7, 0xce, 
                    0xd9};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  NativeReal rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == 12976812.123
  );
}

void Test39() {
  uint8_t test[] = {0x09, 0x09, 0xc0, 0xed, 0x11, 0x45, 0xa6, 0x95, 0x7e, 0xfb, 
                    0xe7};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  NativeReal rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == -9272873647.873
  );
}

void Test40() {
  uint8_t test[] = {0x09, 0x09, 0x80, 0xe3, 0x18, 0xc0, 0x55, 0x87, 0x82, 0xa9, 
                    0x93};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  RealRef rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == 12976812.2347
  );
}

void Test41() {
  uint8_t test[] = {0x30, 0x0b, 0x09, 0x09, 0x80, 0xd4, 0x1f, 0x4d, 0xf7, 0xce, 
                    0xd9, 0x16, 0x87};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_R_RO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.real1 == 500.873 &&
              !rec.real2
  );
}

void Test42() {
  uint8_t test[] = {0x30, 0x16, 0x09, 0x09, 0x80, 0xd4, 0x1f, 0x4d, 0xf7, 0xce, 
                    0xd9, 0x16, 0x87, 0x09, 0x09, 0x80, 0xd5, 0x1f, 0x40, 0xfd, 
                    0xaa, 0x4f, 0xca, 0x43};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_R_RO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.real1 == 500.873 &&
              rec.real2 && *rec.real2 == 1000.12386
  );
}

void Test43() {
  uint8_t test[] = {0x02, 0x05, 0x00, 0x80, 0x00, 0x00, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  UnsignedNativeIntegerTest rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == 2147483648);
}

void Test44() {
  uint8_t test[] = {0x0a, 0x01, 0x02};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  EnumeratedTest rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == EnumeratedTest_enum::EnumeratedTest_variant2
  );
}

void Test45() {
  uint8_t test[] = {0x30, 0x05, 0x30, 0x03, 0x0a, 0x01, 0x01};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_E rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.field.value == SequenceRecord_IS_E::field::value_enum::value_value2
  );
}

void Test46() {
  uint8_t test[] = {0x30, 0x05, 0x30, 0x03, 0x0a, 0x01, 0x01};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_EO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.field.value &&
          *rec.field.value== SequenceRecord_IS_EO::field::value_enum::value_value2
  );
}

void Test47() {
  uint8_t test[] = {0x80, 0x03, 0x13, 0xa5, 0xbc};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  IntegerRefWithTag rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == 1287612
  );
}

void Test48() {
  uint8_t test[] = {0x80, 0x03, 0x13, 0xa5, 0xbc};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  IntegerRefWithTag rec;
  ret = rec.DecodeBer(test, sizeof(test));
  IntegerRefWithTag rec2(rec);
  CHECK_RESULT(rec2 == 1287612 && rec == 1287612 
  );
}

void Test49() {
  uint8_t test[] = {0x80, 0x03, 0x13, 0xa5, 0xbc};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  IntegerRefWithTag rec;
  ret = rec.DecodeBer(test, sizeof(test));
  IntegerRefWithTag rec2(std::move(rec));
  CHECK_RESULT(rec2 == 1287612 && rec == 0 
  );
}

void Test50() {
  uint8_t test[] = {0x80, 0x03, 0x13, 0xa5, 0xbc};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  IntegerRefWithTag rec;
  ret = rec.DecodeBer(test, sizeof(test));
  IntegerRefWithTag rec2;
  rec2 = rec;
  CHECK_RESULT(rec2 == 1287612 && rec == 1287612 
  );
}

void Test51() {
  uint8_t test[] = {0x80, 0x03, 0x13, 0xa5, 0xbc};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  IntegerRefWithTag rec;
  ret = rec.DecodeBer(test, sizeof(test));
  IntegerRefWithTag rec2;
  rec2 = std::move(rec);
  CHECK_RESULT(rec2 == 1287612 && rec == 0 
  );
}

void Test52() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  uint8_t test[] = {0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 
                    0xfe, 0xcd};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == mustBe
  );
}

void Test53() {
  uint8_t test1[] = {0x02, 0x04, 0x31, 0xF0, 0x2D, 0x82};
  uint8_t test2[] = {0x02, 0x04, 0xfb, 0x9c, 0x80, 0xdf};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  NativeInteger rec;
  ret = rec.DecodeBer(test1, sizeof(test1));
  INTERMEDIATE_CHECK(rec == 837823874);
  ret = rec.DecodeBer(test2, sizeof(test2));
  CHECK_RESULT(rec == -73629473
  );
}

void Test54() {
  std::vector<uint8_t> mustBe1 = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  uint8_t test1[] = {0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 
                    0xfe, 0xcd};
  std::vector<uint8_t> mustBe2 = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x9f};
  uint8_t test2[] = {0x04, 0x08, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x9f};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec;
  ret = rec.DecodeBer(test1, sizeof(test1));
  INTERMEDIATE_CHECK(rec == mustBe1);
  ret = rec.DecodeBer(test2, sizeof(test2));
  CHECK_RESULT(rec == mustBe2
  );
}

void Test55() {
  uint8_t test1[] = {0x30, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 
                    0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_I_IO_I rec;
  ret = rec.DecodeBer(test1, sizeof(test1));
  INTERMEDIATE_CHECK(rec.type == 123 && 
               !rec.type2 && 
               rec.type3 == 92367624
  );
  uint8_t test2[] = {0x30, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 0xb1, 0x92, 
                    0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  ret = rec.DecodeBer(test2, sizeof(test2));
  CHECK_RESULT(rec.type == 123 && 
               rec.type2 && *rec.type2 == 635282 &&
               rec.type3 == 92367624
  );
}

void Test56() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  uint8_t test[] = {0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 
                    0xfe, 0xcd};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OctetStringRef rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == mustBe
  );
}

void Test57() {
  std::vector<uint8_t> mustBe1 = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  std::vector<uint8_t> mustBe3 = {0x14, 0x82, 0xa7, 0x8b, 0x97};
  uint8_t test[] = {0x30, 0x13, 0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xcd, 0x04, 0x05, 0x14, 0x82, 0xa7, 0x8b, 
                    0x97};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_OS_OSO_OSRef_OSRefO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.octetString1 == mustBe1 &&
            !rec.octetString2 &&
          rec.octetString3 == mustBe3 &&
          !rec.octetString4
  );
}

void Test58() {
  std::vector<uint8_t> mustBe1 = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  std::vector<uint8_t> mustBe2 = {0x13, 0x82, 0xa7, 0x8b, 0x97, 
                           0x90, 0xe3, 0x98};
  std::vector<uint8_t> mustBe3 = {0x14, 0x82, 0xa7, 0x8b, 0x97};
  std::vector<uint8_t> mustBe4 = {0x15, 0x82, 0xa7, 0x8b, 0x97, 0x90};
  uint8_t test[] = {0x30, 0x25, 0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xcd, 0x81, 0x08, 0x13, 0x82, 0xa7, 0x8b, 
                    0x97, 0x90, 0xe3, 0x98, 0x04, 0x05, 0x14, 0x82, 0xa7, 0x8b, 
                    0x97, 0x04, 0x06, 0x15, 0x82, 0xa7, 0x8b, 0x97, 0x90};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_OS_OSO_OSRef_OSRefO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.octetString1 == mustBe1 &&
            rec.octetString2 && *rec.octetString2 == mustBe2 &&
          rec.octetString3 == mustBe3 &&
          rec.octetString4 && *rec.octetString4 == mustBe4
  );
}

void Test59() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == mustBe && rec.GetBitsUnused() == 5
  );
}

void Test60() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BitStringRef rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == mustBe && rec.GetBitsUnused() == 5
  );
}

void Test61() {
  std::vector<uint8_t> mustBe1 = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  std::vector<uint8_t> mustBe3 = {0x14, 0x82, 0xa7, 0x8b, 0x90};
  uint8_t test[] = {0x30, 0x15, 0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 
                    0x90, 0xe3, 0x98, 0xfe, 0xc0, 0x03, 0x06, 0x03, 0x14, 0x82, 
                    0xa7, 0x8b, 0x90};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_BS_BSO_BSRef_BSRefO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.bitString1 == mustBe1 &&
          rec.bitString1.GetBitsUnused() == 5 &&
            !rec.bitString2 &&
          rec.bitString3 == mustBe3 &&
          rec.bitString3.GetBitsUnused() == 3 &&
          !rec.bitString4
  );
}

void Test62() {
  std::vector<uint8_t> mustBe1 = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  std::vector<uint8_t> mustBe2 = {0x13, 0x82, 0xa7, 0x8b, 0x97, 
                           0x90, 0xe3, 0x98};
  std::vector<uint8_t> mustBe3 = {0x14, 0x82, 0xa7, 0x8b, 0x90};
  std::vector<uint8_t> mustBe4 = {0x15, 0x82, 0xa7, 0x8b, 0x97, 0x80};
  uint8_t test[] = {0x30, 0x29, 0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 
                    0x90, 0xe3, 0x98, 0xfe, 0xc0, 0x81, 0x09, 0x02, 0x13, 0x82, 
                    0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 0x03, 0x06, 0x03, 0x14, 
                    0x82, 0xa7, 0x8b, 0x90, 0x03, 0x07, 0x07, 0x15, 0x82, 0xa7, 
                    0x8b, 0x97, 0x80};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_BS_BSO_BSRef_BSRefO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.bitString1 == mustBe1 &&
            rec.bitString1.GetBitsUnused() == 5 &&
            rec.bitString2 && 
          *rec.bitString2 == mustBe2 &&
          rec.bitString2->GetBitsUnused() == 2 &&
          rec.bitString3 == mustBe3 &&
          rec.bitString3.GetBitsUnused() == 3 &&
          rec.bitString4 && 
          *rec.bitString4 == mustBe4 &&
          rec.bitString4->GetBitsUnused() == 7
  );
}

void Test63() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BitStringEnumeration rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == mustBe && rec.GetBitsUnused() == 5 && 
          BitStringEnumeration_enum::BitStringEnumeration_value1 == 1000
  );
}

void Test64() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x30, 0x0f, 0x30, 0x0d, 0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 
                    0x8b, 0x97, 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ISO_BSE_BSEO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.seq &&
          rec.seq->bitString1 == mustBe &&
          rec.seq->bitString1.GetBitsUnused() == 5 &&
          !rec.seq->bitString2 &&
          SequenceRecord_ISO_BSE_BSEO::seq::bitString1_enum::bitString1_value1 == 1000 &&
          SequenceRecord_ISO_BSE_BSEO::seq::bitString2_enum::bitString2_value1 == 1000 
  );
}

void Test65() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  uint8_t test[] = {0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 
                    0xfe, 0xcd};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test));
  OCTET_STRING rec2(rec);
  CHECK_RESULT(rec == mustBe && rec2 == mustBe
  );
}

void Test66() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  uint8_t test[] = {0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 
                    0xfe, 0xcd};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test));
  OCTET_STRING rec2(std::move(rec));
  CHECK_RESULT(rec.size() == 0 && rec2 == mustBe
  );
}

void Test67() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  uint8_t test[] = {0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 
                    0xfe, 0xcd};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test));
  OCTET_STRING rec2;
  rec2 = rec;
  CHECK_RESULT(rec == mustBe && rec2 == mustBe
  );
}

void Test68() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  uint8_t test[] = {0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 
                    0xfe, 0xcd};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test));
  OCTET_STRING rec2;
  rec2 = std::move(rec);
  CHECK_RESULT(rec.size() == 0 && rec2 == mustBe
  );
}

void Test69() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test));
  BIT_STRING rec2(rec);
  CHECK_RESULT(rec == mustBe && rec.GetBitsUnused() == 5 &&
          rec2 == mustBe && rec2.GetBitsUnused() == 5
  );
}

void Test70() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test));
  BIT_STRING rec2(std::move(rec));
  CHECK_RESULT(rec.size() == 0 && rec.GetBitsUnused() == 0 &&
          rec2 == mustBe && rec2.GetBitsUnused() == 5
  );
}

void Test71() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test));
  BIT_STRING rec2;
  rec2 = rec;
  CHECK_RESULT(rec == mustBe && rec.GetBitsUnused() == 5 &&
          rec2 == mustBe && rec2.GetBitsUnused() == 5
  );
}

void Test72() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test));
  BIT_STRING rec2;
  rec2 = std::move(rec);
  CHECK_RESULT(rec.size() == 0 && rec.GetBitsUnused() == 0 &&
          rec2 == mustBe && rec2.GetBitsUnused() == 5
  );
}

void Test73() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  if (! (1 == ret.code && sizeof(test) / 2 == ret.consumed) ) {
    TEST_FAILED
  }
  BIT_STRING rec2(rec);
  ret = rec2.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  INTERMEDIATE_CHECK(rec2 == mustBe && rec2.GetBitsUnused() == 5);
  ret = rec.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  CHECK_RESULT(rec == mustBe && rec.GetBitsUnused() == 5
  );
}

void Test74() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  if (! (1 == ret.code && sizeof(test) / 2 == ret.consumed) ) {
    TEST_FAILED
  }
  BIT_STRING rec2(std::move(rec));
  ret = rec.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  if (! (RC_FAIL == ret.code && 0 == ret.consumed) ) {
    TEST_FAILED
  }
  ret = rec2.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  CHECK_RESULT(rec2 == mustBe && rec2.GetBitsUnused() == 5
  );
}

void Test75() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  if (! (1 == ret.code && sizeof(test) / 2 == ret.consumed) ) {
    TEST_FAILED
  }
  BIT_STRING rec2;
  rec2 = rec;
  ret = rec2.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  INTERMEDIATE_CHECK(rec2 == mustBe && rec2.GetBitsUnused() == 5);
  ret = rec.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  CHECK_RESULT(rec == mustBe && rec.GetBitsUnused() == 5
  );
}

void Test76() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  if (! (1 == ret.code && sizeof(test) / 2 == ret.consumed) ) {
    TEST_FAILED
  }
  BIT_STRING rec2;
  rec2 = std::move(rec);
  ret = rec.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  if (! (RC_FAIL == ret.code && 0 == ret.consumed) ) {
    TEST_FAILED
  }
  ret = rec2.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  CHECK_RESULT(rec2 == mustBe && rec2.GetBitsUnused() == 5
  );
}

void Test77() {
  std::vector<uint8_t> mustBe1 = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  std::vector<uint8_t> mustBe3 = {0x14, 0x82, 0xa7, 0x8b, 0x90};
  uint8_t test[] = {0x30, 0x15, 0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 
                    0x90, 0xe3, 0x98, 0xfe, 0xc0, 0x03, 0x06, 0x03, 0x14, 0x82, 
                    0xa7, 0x8b, 0x90};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_BS_BSO_BSRef_BSRefO rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  if (! (1 == ret.code && sizeof(test) / 2 == ret.consumed) ) {
    TEST_FAILED
  }
  SequenceRecord_BS_BSO_BSRef_BSRefO rec2(rec);
  ret = rec2.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  INTERMEDIATE_CHECK(rec2.bitString1 == mustBe1 &&
          rec2.bitString1.GetBitsUnused() == 5 &&
            !rec2.bitString2 &&
          rec2.bitString3 == mustBe3 &&
          rec2.bitString3.GetBitsUnused() == 3 &&
          !rec2.bitString4);
  ret = rec.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  CHECK_RESULT(rec.bitString1 == mustBe1 &&
          rec.bitString1.GetBitsUnused() == 5 &&
            !rec.bitString2 &&
          rec.bitString3 == mustBe3 &&
          rec.bitString3.GetBitsUnused() == 3 &&
          !rec.bitString4
  );
}

void Test78() {
  std::vector<uint8_t> mustBe1 = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  std::vector<uint8_t> mustBe3 = {0x14, 0x82, 0xa7, 0x8b, 0x90};
  uint8_t test[] = {0x30, 0x15, 0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 
                    0x90, 0xe3, 0x98, 0xfe, 0xc0, 0x03, 0x06, 0x03, 0x14, 0x82, 
                    0xa7, 0x8b, 0x90};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_BS_BSO_BSRef_BSRefO rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  if (! (1 == ret.code && sizeof(test) / 2 == ret.consumed) ) {
    TEST_FAILED
  }
  SequenceRecord_BS_BSO_BSRef_BSRefO rec2(std::move(rec));
  ret = rec.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  if (! (RC_FAIL == ret.code && 0 == ret.consumed) ) {
    TEST_FAILED
  }
  ret = rec2.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  CHECK_RESULT(rec2.bitString1 == mustBe1 &&
          rec2.bitString1.GetBitsUnused() == 5 &&
            !rec2.bitString2 &&
          rec2.bitString3 == mustBe3 &&
          rec2.bitString3.GetBitsUnused() == 3 &&
          !rec2.bitString4
  );
}

void Test79() {
  std::vector<uint8_t> mustBe1 = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  std::vector<uint8_t> mustBe3 = {0x14, 0x82, 0xa7, 0x8b, 0x90};
  uint8_t test[] = {0x30, 0x15, 0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 
                    0x90, 0xe3, 0x98, 0xfe, 0xc0, 0x03, 0x06, 0x03, 0x14, 0x82, 
                    0xa7, 0x8b, 0x90};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_BS_BSO_BSRef_BSRefO rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  if (! (1 == ret.code && sizeof(test) / 2 == ret.consumed) ) {
    TEST_FAILED
  }
  SequenceRecord_BS_BSO_BSRef_BSRefO rec2;
  rec2 = rec;
  ret = rec2.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  INTERMEDIATE_CHECK(rec2.bitString1 == mustBe1 &&
          rec2.bitString1.GetBitsUnused() == 5 &&
            !rec2.bitString2 &&
          rec2.bitString3 == mustBe3 &&
          rec2.bitString3.GetBitsUnused() == 3 &&
          !rec2.bitString4);
  ret = rec.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  CHECK_RESULT(rec.bitString1 == mustBe1 &&
          rec.bitString1.GetBitsUnused() == 5 &&
            !rec.bitString2 &&
          rec.bitString3 == mustBe3 &&
          rec.bitString3.GetBitsUnused() == 3 &&
          !rec.bitString4
  );
}

void Test80() {
  std::vector<uint8_t> mustBe1 = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xc0};
  std::vector<uint8_t> mustBe3 = {0x14, 0x82, 0xa7, 0x8b, 0x90};
  uint8_t test[] = {0x30, 0x15, 0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 
                    0x90, 0xe3, 0x98, 0xfe, 0xc0, 0x03, 0x06, 0x03, 0x14, 0x82, 
                    0xa7, 0x8b, 0x90};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_BS_BSO_BSRef_BSRefO rec;
  ret = rec.DecodeBer(test, sizeof(test) / 2);
  if (! (1 == ret.code && sizeof(test) / 2 == ret.consumed) ) {
    TEST_FAILED
  }
  SequenceRecord_BS_BSO_BSRef_BSRefO rec2;
  rec2 = std::move(rec);
  ret = rec.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  if (! (RC_FAIL == ret.code && 0 == ret.consumed) ) {
    TEST_FAILED
  }
  ret = rec2.DecodeBer(test + sizeof(test) / 2, sizeof(test) - sizeof(test) / 2);
  CHECK_RESULT(rec2.bitString1 == mustBe1 &&
          rec2.bitString1.GetBitsUnused() == 5 &&
            !rec2.bitString2 &&
          rec2.bitString3 == mustBe3 &&
          rec2.bitString3.GetBitsUnused() == 3 &&
          !rec2.bitString4
  );
}

void Test81() {
  std::vector<uint8_t> mustBe1 = {0x2b, 0x06, 0x01, 0x04, 0x01, 0xc9, 0x13, 0x84, 0xe4, 0x7a};
  std::vector<uint8_t> mustBe3 = {0x2b, 0x06, 0x01, 0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01};
  std::vector<unsigned int> arcsMust1 = {1, 3, 6, 1, 4, 1, 9363, 78458};
  std::vector<unsigned int> arcsMust3 = {1, 3, 6, 1, 4, 3, 9363, 78458, 1};
  
  uint8_t test[] = {0x30, 0x1b, 0x30, 0x19, 0x06, 0x0a, 0x2b, 0x06, 0x01, 0x04, 
                    0x01, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x06, 0x0b, 0x2b, 0x06, 
                    0x01, 0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_OI_OIO_OIRef_OIRefO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  std::vector<unsigned int> arcs1;
  int arcs1ret = rec.seq.objectIdentifier1.GetArcs(arcs1);
  std::vector<unsigned int> arcs3;
  int arcs3ret = rec.seq.objectIdentifier3.GetArcs(arcs3);
  
  CHECK_RESULT(rec.seq.objectIdentifier1 == mustBe1 &&
            arcs1ret > 0 && arcs1 == arcsMust1 &&
            !rec.seq.objectIdentifier2 &&
          rec.seq.objectIdentifier3 == mustBe3 &&
          arcs3ret > 0 && arcs3 == arcsMust3 && 
          !rec.seq.objectIdentifier4
  );
}

void Test82() {
  std::vector<uint8_t> mustBe1 = {0x2b, 0x06, 0x01, 0x04, 0x01, 0xc9, 0x13, 0x84, 0xe4, 0x7a};
  std::vector<uint8_t> mustBe2 = {0x2b, 0x06, 0x01, 0x04, 0x02, 0xc9, 0x13};
  std::vector<uint8_t> mustBe3 = {0x2b, 0x06, 0x01, 0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01};
  std::vector<uint8_t> mustBe4 = {0x2b, 0x06, 0x01, 0x04, 0x04, 0xc9, 0x13};
  std::vector<unsigned int> arcsMust1 = {1, 3, 6, 1, 4, 1, 9363, 78458};
  std::vector<unsigned int> arcsMust2 = {1, 3, 6, 1, 4, 2, 9363};
  std::vector<unsigned int> arcsMust3 = {1, 3, 6, 1, 4, 3, 9363, 78458, 1};
  std::vector<unsigned int> arcsMust4 = {1, 3, 6, 1, 4, 4, 9363};
  
  uint8_t test[] = {0x30, 0x2d, 0x30, 0x2b, 0x06, 0x0a, 0x2b, 0x06, 0x01, 0x04, 
                    0x01, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x81, 0x07, 0x2b, 0x06, 
                    0x01, 0x04, 0x02, 0xc9, 0x13, 0x06, 0x0b, 0x2b, 0x06, 0x01, 
                    0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x06, 0x07, 
                    0x2b, 0x06, 0x01, 0x04, 0x04, 0xc9, 0x13};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_OI_OIO_OIRef_OIRefO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  std::vector<unsigned int> arcs1;
  int arcs1ret = rec.seq.objectIdentifier1.GetArcs(arcs1);
  std::vector<unsigned int> arcs2;
  int arcs2ret = rec.seq.objectIdentifier2 ? 
    rec.seq.objectIdentifier2->GetArcs(arcs2) : -1;
  std::vector<unsigned int> arcs3;
  int arcs3ret = rec.seq.objectIdentifier3.GetArcs(arcs3);
  std::vector<unsigned int> arcs4;
  int arcs4ret = rec.seq.objectIdentifier4 ? 
    rec.seq.objectIdentifier4->GetArcs(arcs4) : -1;
  
  CHECK_RESULT(rec.seq.objectIdentifier1 == mustBe1 &&
            arcs1ret > 0 && arcs1 == arcsMust1 &&
            rec.seq.objectIdentifier2 && 
            *rec.seq.objectIdentifier2 == mustBe2 &&
          arcs2ret > 0 && arcs2 == arcsMust2 &&
          rec.seq.objectIdentifier3 == mustBe3 &&
          arcs3ret > 0 && arcs3 == arcsMust3 && 
          rec.seq.objectIdentifier4 &&
          *rec.seq.objectIdentifier4 == mustBe4 &&
          arcs4ret > 0 && arcs4 == arcsMust4
  );
}

void Test83() {
  std::vector<uint8_t> mustBe = {0x2b, 0x06, 0x01, 0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01};
  std::vector<unsigned int> arcsMustBe = {1, 3, 6, 1, 4, 3, 9363, 78458, 1};
  
  TEST_NUMBER;
  OBJECT_IDENTIFIER rec;
  int ret = rec.SetArcs(arcsMustBe);
  std::vector<unsigned int> arcs;
  int arcsRet = rec.GetArcs(arcs);
  
  CHECK_COND(0 == ret && rec == mustBe && 
          arcsRet > 0 && arcs == arcsMustBe
  );
}

void Test84() {
  std::vector<uint8_t> mustBe1 = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x03, 0x06, 0x01, 0x04, 0x01};
  std::vector<uint8_t> mustBe3 = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 0x04, 0x03};
  std::vector<unsigned int> arcsMust1 = {9363, 78458, 1, 3, 6, 1, 4, 1};
  std::vector<unsigned int> arcsMust3 = {9363, 78458, 1, 1, 3, 6, 1, 4, 3};
  
  uint8_t test[] = {0x30, 0x1e, 0x30, 0x1c, 0x0d, 0x0b, 0xc9, 0x13, 0x84, 0xe4, 
                    0x7a, 0x01, 0x03, 0x06, 0x01, 0x04, 0x01, 0x9f, 0x32, 0x0c, 
                    0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 
                    0x04, 0x03};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_ROI_ROIO_ROIRefWithTag_ROIRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  std::vector<unsigned int> arcs1;
  int arcs1ret = rec.seq.relativeOid1.GetArcs(arcs1);
  std::vector<unsigned int> arcs3;
  int arcs3ret = rec.seq.relativeOid3.GetArcs(arcs3);
  
  CHECK_RESULT(rec.seq.relativeOid1 == mustBe1 &&
            arcs1ret > 0 && arcs1 == arcsMust1 &&
            !rec.seq.relativeOid2 &&
          rec.seq.relativeOid3 == mustBe3 &&
          arcs3ret > 0 && arcs3 == arcsMust3 && 
          !rec.seq.relativeOid4
  );
}

void Test85() {
  std::vector<uint8_t> mustBe1 = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x03, 0x06, 0x01, 0x04, 0x01};
  std::vector<uint8_t> mustBe2 = {0xc9, 0x13, 0x01, 0x03, 0x06, 0x01, 0x04, 0x02};
  std::vector<uint8_t> mustBe3 = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 0x04, 0x03};
  std::vector<uint8_t> mustBe4 = {0xc9, 0x13, 0x01, 0x03, 0x06, 0x01, 0x04, 0x04};
  std::vector<unsigned int> arcsMust1 = {9363, 78458, 1, 3, 6, 1, 4, 1};
  std::vector<unsigned int> arcsMust2 = {9363, 1, 3, 6, 1, 4, 2};
  std::vector<unsigned int> arcsMust3 = {9363, 78458, 1, 1, 3, 6, 1, 4, 3};
  std::vector<unsigned int> arcsMust4 = {9363, 1, 3, 6, 1, 4, 4};
  
  uint8_t test[] = {0x30, 0x33, 0x30, 0x31, 0x0d, 0x0b, 0xc9, 0x13, 0x84, 0xe4, 
                    0x7a, 0x01, 0x03, 0x06, 0x01, 0x04, 0x01, 0x81, 0x08, 0xc9, 
                    0x13, 0x01, 0x03, 0x06, 0x01, 0x04, 0x02, 0x9f, 0x32, 0x0c, 
                    0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 
                    0x04, 0x03, 0x9f, 0x32, 0x08, 0xc9, 0x13, 0x01, 0x03, 0x06, 
                    0x01, 0x04, 0x04};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_ROI_ROIO_ROIRefWithTag_ROIRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  std::vector<unsigned int> arcs1;
  int arcs1ret = rec.seq.relativeOid1.GetArcs(arcs1);
  std::vector<unsigned int> arcs2;
  int arcs2ret = rec.seq.relativeOid2 ? 
    rec.seq.relativeOid2->GetArcs(arcs2) : -1;
  std::vector<unsigned int> arcs3;
  int arcs3ret = rec.seq.relativeOid3.GetArcs(arcs3);
  std::vector<unsigned int> arcs4;
  int arcs4ret = rec.seq.relativeOid4 ? 
    rec.seq.relativeOid4->GetArcs(arcs4) : -1;
  
  CHECK_RESULT(rec.seq.relativeOid1 == mustBe1 &&
            arcs1ret > 0 && arcs1 == arcsMust1 &&
            rec.seq.relativeOid2 && 
            *rec.seq.relativeOid2 == mustBe2 &&
          arcs2ret > 0 && arcs2 == arcsMust2 &&
          rec.seq.relativeOid3 == mustBe3 &&
          arcs3ret > 0 && arcs3 == arcsMust3 && 
          rec.seq.relativeOid4 &&
          *rec.seq.relativeOid4 == mustBe4 &&
          arcs4ret > 0 && arcs4 == arcsMust4
  );
}

void Test86() {
  std::vector<uint8_t> mustBe = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 0x04, 0x03};
  std::vector<unsigned int> arcsMustBe = {9363, 78458, 1, 1, 3, 6, 1, 4, 3};
  
  TEST_NUMBER;
  RELATIVE_OID rec;
  int ret = rec.SetArcs(arcsMustBe);
  std::vector<unsigned int> arcs;
  int arcsRet = rec.GetArcs(arcs);
  
  CHECK_COND(0 == ret && rec == mustBe && 
          arcsRet > 0 && arcs == arcsMustBe
  );
}

void Test87() {
  std::vector<uint8_t> mustBe = {0x2b, 0x06, 0x01, 0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01};
  std::vector<unsigned int> arcsMustBe = {1, 3, 6, 1, 4, 3, 9363, 78458, 1};
  
  TEST_NUMBER;
  OBJECT_IDENTIFIER rec1;
  int ret1 = rec1.SetArcs(arcsMustBe);
  
  OBJECT_IDENTIFIER rec2(rec1);
  
  std::vector<unsigned int> arcs1;
  int arcsRet1 = rec1.GetArcs(arcs1);
  std::vector<unsigned int> arcs2;
  int arcsRet2 = rec2.GetArcs(arcs2);
  
  CHECK_COND(0 == ret1 && rec1 == mustBe && 
          arcsRet1 > 0 && arcs1 == arcsMustBe &&
          rec2 == mustBe && 
          arcsRet2 > 0 && arcs2 == arcsMustBe
  );
}

void Test88() {
  std::vector<uint8_t> mustBe = {0x2b, 0x06, 0x01, 0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01};
  std::vector<unsigned int> arcsMustBe = {1, 3, 6, 1, 4, 3, 9363, 78458, 1};
  
  TEST_NUMBER;
  OBJECT_IDENTIFIER rec1;
  int ret1 = rec1.SetArcs(arcsMustBe);
  
  OBJECT_IDENTIFIER rec2(std::move(rec1));
  
  std::vector<unsigned int> arcs2;
  int arcsRet2 = rec2.GetArcs(arcs2);
  
  CHECK_COND(0 == ret1 && rec1.size() == 0 && 
          rec2 == mustBe && 
          arcsRet2 > 0 && arcs2 == arcsMustBe
  );
}

void Test89() {
  std::vector<uint8_t> mustBe = {0x2b, 0x06, 0x01, 0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01};
  std::vector<unsigned int> arcsMustBe = {1, 3, 6, 1, 4, 3, 9363, 78458, 1};
  
  TEST_NUMBER;
  OBJECT_IDENTIFIER rec1;
  int ret1 = rec1.SetArcs(arcsMustBe);
  
  OBJECT_IDENTIFIER rec2;
  rec2 = rec1;
  
  std::vector<unsigned int> arcs1;
  int arcsRet1 = rec1.GetArcs(arcs1);
  std::vector<unsigned int> arcs2;
  int arcsRet2 = rec2.GetArcs(arcs2);
  
  CHECK_COND(0 == ret1 && rec1 == mustBe && 
          arcsRet1 > 0 && arcs1 == arcsMustBe &&
          rec2 == mustBe && 
          arcsRet2 > 0 && arcs2 == arcsMustBe
  );
}

void Test90() {
  std::vector<uint8_t> mustBe = {0x2b, 0x06, 0x01, 0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01};
  std::vector<unsigned int> arcsMustBe = {1, 3, 6, 1, 4, 3, 9363, 78458, 1};
  
  TEST_NUMBER;
  OBJECT_IDENTIFIER rec1;
  int ret1 = rec1.SetArcs(arcsMustBe);
  
  OBJECT_IDENTIFIER rec2;
  rec2 = std::move(rec1);
  
  std::vector<unsigned int> arcs2;
  int arcsRet2 = rec2.GetArcs(arcs2);
  
  CHECK_COND(0 == ret1 && rec1.size() == 0 && 
          rec2 == mustBe && 
          arcsRet2 > 0 && arcs2 == arcsMustBe
  );
}

void Test91() {
  std::vector<uint8_t> mustBe = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 0x04, 0x03};
  std::vector<unsigned int> arcsMustBe = {9363, 78458, 1, 1, 3, 6, 1, 4, 3};
  
  TEST_NUMBER;
  RELATIVE_OID rec1;
  int ret1 = rec1.SetArcs(arcsMustBe);
  
  RELATIVE_OID rec2(rec1);
  
  std::vector<unsigned int> arcs1;
  int arcsRet1 = rec1.GetArcs(arcs1);
  std::vector<unsigned int> arcs2;
  int arcsRet2 = rec2.GetArcs(arcs2);
  
  CHECK_COND(0 == ret1 && rec1 == mustBe && 
          arcsRet1 > 0 && arcs1 == arcsMustBe &&
          rec2 == mustBe && 
          arcsRet2 > 0 && arcs2 == arcsMustBe
  );
}

void Test92() {
  std::vector<uint8_t> mustBe = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 0x04, 0x03};
  std::vector<unsigned int> arcsMustBe = {9363, 78458, 1, 1, 3, 6, 1, 4, 3};
  
  TEST_NUMBER;
  RELATIVE_OID rec1;
  int ret1 = rec1.SetArcs(arcsMustBe);
  
  RELATIVE_OID rec2(std::move(rec1));
  
  std::vector<unsigned int> arcs2;
  int arcsRet2 = rec2.GetArcs(arcs2);
  
  CHECK_COND(0 == ret1 && rec1.size() == 0 && 
          rec2 == mustBe && 
          arcsRet2 > 0 && arcs2 == arcsMustBe
  );
}

void Test93() {
  std::vector<uint8_t> mustBe = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 0x04, 0x03};
  std::vector<unsigned int> arcsMustBe = {9363, 78458, 1, 1, 3, 6, 1, 4, 3};
  
  TEST_NUMBER;
  RELATIVE_OID rec1;
  int ret1 = rec1.SetArcs(arcsMustBe);
  
  RELATIVE_OID rec2;
  rec2 = rec1;
  
  std::vector<unsigned int> arcs1;
  int arcsRet1 = rec1.GetArcs(arcs1);
  std::vector<unsigned int> arcs2;
  int arcsRet2 = rec2.GetArcs(arcs2);
  
  CHECK_COND(0 == ret1 && rec1 == mustBe && 
          arcsRet1 > 0 && arcs1 == arcsMustBe &&
          rec2 == mustBe && 
          arcsRet2 > 0 && arcs2 == arcsMustBe
  );
}

void Test94() {
  std::vector<uint8_t> mustBe = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 0x04, 0x03};
  std::vector<unsigned int> arcsMustBe = {9363, 78458, 1, 1, 3, 6, 1, 4, 3};
  
  TEST_NUMBER;
  RELATIVE_OID rec1;
  int ret1 = rec1.SetArcs(arcsMustBe);
  
  RELATIVE_OID rec2;
  rec2 = std::move(rec1);
  
  std::vector<unsigned int> arcs2;
  int arcsRet2 = rec2.GetArcs(arcs2);
  
  CHECK_COND(0 == ret1 && rec1.size() == 0 && 
          rec2 == mustBe && 
          arcsRet2 > 0 && arcs2 == arcsMustBe
  );
}

void Test95() {
  std::vector<uint8_t> mustBe = {0x2b, 0x06, 0x01, 0x04, 0x03, 0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01};
  std::vector<unsigned int> arcsMustBe = {1, 3, 6, 1, 4, 3, 9363, 78458, 1};
  std::string stringArcs = "1.3.6.1.4.3.9363.78458.1";
  
  TEST_NUMBER;
  OBJECT_IDENTIFIER rec;
  bool ret = rec.FromArcs(stringArcs);
  std::vector<unsigned int> arcs;
  int arcsRet = rec.GetArcs(arcs);
  
  CHECK_COND(ret && rec == mustBe && 
          arcsRet > 0 && arcs == arcsMustBe
  );
}

void Test96() {
  std::vector<uint8_t> mustBe = {0xc9, 0x13, 0x84, 0xe4, 0x7a, 0x01, 0x01, 0x03, 0x06, 0x01, 0x04, 0x03};
  std::vector<unsigned int> arcsMustBe = {9363, 78458, 1, 1, 3, 6, 1, 4, 3};
  std::string stringArcs = "9363.78458.1.1.3.6.1.4.3";
  
  TEST_NUMBER;
  RELATIVE_OID rec;
  bool ret = rec.FromArcs(stringArcs);
  std::vector<unsigned int> arcs;
  int arcsRet = rec.GetArcs(arcs);
  
  CHECK_COND(ret && rec == mustBe && 
          arcsRet > 0 && arcs == arcsMustBe
  );
}

void Test97() {
  std::vector<uint8_t> mustBe1 = {0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe3 = {0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe4 = {0x34, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  
  uint8_t test[] = {0x30, 0x29, 0x30, 0x27, 0x17, 0x11, 0x31, 0x30, 0x30, 0x33, 
                    0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 
                    0x30, 0x30, 0x30, 0x9f, 0x32, 0x11, 0x33, 0x30, 0x30, 0x33, 
                    0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 
                    0x30, 0x30, 0x30};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_UT_UTO_UTRefWithTag_UTRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.time1 == mustBe1 &&
          rec.seq.time1.ToTime() == 1268239212 && 
            !rec.seq.time2 &&
          rec.seq.time3 == mustBe3 &&
          rec.seq.time3.ToTime() == 1899391212 &&
          !rec.seq.time4
  );
}

void Test98() {
  std::vector<uint8_t> mustBe1 = {0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe3 = {0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe4 = {0x33, 0x37, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  
  uint8_t test[] = {0x30, 0x50, 0x30, 0x4e, 0x17, 0x11, 0x31, 0x30, 0x30, 0x33, 
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
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.time1 == mustBe1 &&
          rec.seq.time1.ToTime() == 1268239212 && 
            rec.seq.time2 && 
          rec.seq.time2->ToTime() == 1583858412 &&
            *rec.seq.time2 == mustBe2 &&
          rec.seq.time3 == mustBe3 &&
          rec.seq.time3.ToTime() == 1899391212 &&
          rec.seq.time4 &&
          rec.seq.time4->ToTime() == 2120316012 &&
          *rec.seq.time4 == mustBe4);
}

void Test99() {
  std::vector<uint8_t> mustBe1 = {0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe3 = {0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe4 = {0x33, 0x37, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  
  uint8_t test[] = {0x30, 0x50, 0x30, 0x4e, 0x17, 0x11, 0x31, 0x30, 0x30, 0x33, 
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
  ret = rec.DecodeBer(test, sizeof(test));
  SequenceRecord_IS_UT_UTO_UTRefWithTag_UTRefWithTagO rec2(rec);
  
  CHECK_RESULT(rec.seq.time1 == mustBe1 &&
          rec.seq.time1.ToTime() == 1268239212 && 
            rec.seq.time2 && 
          rec.seq.time2->ToTime() == 1583858412 &&
            *rec.seq.time2 == mustBe2 &&
          rec.seq.time3 == mustBe3 &&
          rec.seq.time3.ToTime() == 1899391212 &&
          rec.seq.time4 &&
          rec.seq.time4->ToTime() == 2120316012 &&
          *rec.seq.time4 == mustBe4 &&
          
          rec2.seq.time1 == mustBe1 &&
          rec2.seq.time1.ToTime() == 1268239212 && 
            rec2.seq.time2 && 
          rec2.seq.time2->ToTime() == 1583858412 &&
            *rec2.seq.time2 == mustBe2 &&
          rec2.seq.time3 == mustBe3 &&
          rec2.seq.time3.ToTime() == 1899391212 &&
          rec2.seq.time4 &&
          rec2.seq.time4->ToTime() == 2120316012 &&
          *rec2.seq.time4 == mustBe4
  );
}

void Test100() {
  std::vector<uint8_t> mustBe1 = {0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe3 = {0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  std::vector<uint8_t> mustBe4 = {0x33, 0x37, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  
  uint8_t test[] = {0x30, 0x50, 0x30, 0x4e, 0x17, 0x11, 0x31, 0x30, 0x30, 0x33, 
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
  ret = rec.DecodeBer(test, sizeof(test));
  SequenceRecord_IS_UT_UTO_UTRefWithTag_UTRefWithTagO rec2(std::move(rec));
  
  CHECK_RESULT(rec.seq.time1.empty() &&
            !rec.seq.time2 && 
          rec.seq.time3.empty() &&
          !rec.seq.time4 &&
          
          rec2.seq.time1 == mustBe1 &&
          rec2.seq.time1.ToTime() == 1268239212 && 
            rec2.seq.time2 && 
          rec2.seq.time2->ToTime() == 1583858412 &&
            *rec2.seq.time2 == mustBe2 &&
          rec2.seq.time3 == mustBe3 &&
          rec2.seq.time3.ToTime() == 1899391212 &&
          rec2.seq.time4 &&
          rec2.seq.time4->ToTime() == 2120316012 &&
          *rec2.seq.time4 == mustBe4
  );
}

void Tests1_100() {
  Test1(); //NativeInteger
  Test2(); //NativeInteger
  Test3(); //SequenceRecord_I_IO_I
  Test4(); //SequenceRecord_I_IO_I
  Test5(); //SequenceRecord_IO_I_I_Automatic
  Test6(); //SequenceRecord_IO_I_I_Automatic
  Test7(); //SequenceRecord_I_IO_I_S_1I_S_1IO_1I
  Test8(); //SequenceRecord_I_IO_I_S_1I_S_1IO_1I
  Test9(); //copy constructor SequenceRecord_I_IO_I_S_1I_S_1IO_1I
  Test10(); //move constructor SequenceRecord_I_IO_I_S_1I_S_1IO_1I
  Test11(); //copy operator = SequenceRecord_I_IO_I_S_1I_S_1IO_1I
  Test12(); //move operator = SequenceRecord_I_IO_I_S_1I_S_1IO_1I
  Test13(); //SequenceRecord-ES + SequenceRecord-I
  Test14(); //SequenceRecord-ESO + SequenceRecord-IO
  Test15(); //SequenceRecord-ESO + SequenceRecord-IO
  Test16(); //SequenceRecord-ESO + SequenceRecord-IO
  Test17(); //SequenceRecord-ES-2 + SequenceRecord-ESO-2 
  Test18(); //SequenceRecord-ES-2 + SequenceRecord-ESO-2
  Test19(); //SequenceRecord-ESO-selfRef
  Test20(); //SequenceRecord-DirectRef + DirectRefRecord-S-I-IO-IO + SequenceRecord-I-IO-I
  Test21(); //SequenceRecord-DirectRef-EXPL + DirectRefRecord-S-I-IO-I-EXPL + SequenceRecord-I-IO-I-EXPL
  Test22(); //SequenceRecord-DirectRef-Auto + DirectRefRecord-S-I-IO-I-Auto + SequenceRecord-I-IO-I-Auto
  Test23(); //SequenceRecord-2inner-seq
  Test24(); //Integer-Enumeration
  Test25(); //Integer-Enumeration
  Test26(); //SequenceRecord-IS-IE
  Test27(); //SequenceRecord-IS-IEO
  Test28(); //BOOLEAN
  Test29(); //BOOLEAN
  Test30(); //BooleanRef
  Test31(); //BooleanRef
  Test32(); //SequenceRecord-B-BO
  Test33(); //SequenceRecord-B-BO
  Test34(); //NULL_t
  Test35(); //NullRef
  Test36(); //SequenceRecord-N-NO
  Test37(); //SequenceRecord-N-NO
  Test38(); //NativeReal
  Test39(); //NativeReal
  Test40(); //RealRef
  Test41(); //SequenceRecord-R-RO
  Test42(); //SequenceRecord-R-RO
  Test43(); //UnsignedNativeIntegerTest
  Test44(); //EnumeratedTest
  Test45(); //SequenceRecord-IS-E
  Test46(); //SequenceRecord-IS-EO
  Test47(); //IntegerRefWithTag
  Test48(); //IntegerRefWithTag copy constructor
  Test49(); //IntegerRefWithTag move constructor
  Test50(); //IntegerRefWithTag copy =
  Test51(); //IntegerRefWithTag move =
  Test52(); //OCTET STRING
  Test53(); //NativeInteger + the same NativeInteger again
  Test54(); //OCTET STRING + the same OCTET STRING again
  Test55(); //SequenceRecord_I_IO_I + the same SequenceRecord_I_IO_I again
  Test56(); //OctetStringRef
  Test57(); //SequenceRecord-OS-OSO-OSRef-OSRefO+OctetStringRef
  Test58(); //SequenceRecord-OS-OSO-OSRef-OSRefO+OctetStringRef
  Test59(); //BIT STRING
  Test60(); //BitStringRef
  Test61(); //SequenceRecord-BS-BSO-BSRef-BSRefO+OctetStringRef
  Test62(); //SequenceRecord-BS-BSO-BSRef-BSRefO+OctetStringRef
  Test63(); //BitStringEnumeration
  Test64(); //SequenceRecord-ISO-BSE-BSEO
  Test65(); //OCTET STRING copy constructor
  Test66(); //OCTET STRING move constructor
  Test67(); //OCTET STRING copy =
  Test68(); //OCTET STRING move =
  Test69(); //BIT STRING copy constructor
  Test70(); //BIT STRING move constructor
  Test71(); //BIT STRING copy =
  Test72(); //BIT STRING move =
  Test73(); //BIT STRING partial decoding copy constructor
  Test74(); //BIT STRING partial decoding move constructor
  Test75(); //BIT STRING partial decoding copy =
  Test76(); //BIT STRING partial decoding move =
  Test77(); //SequenceRecord-BS-BSO-BSRef-BSRefO+BitStringRef partial decoding copy constructor
  Test78(); //SequenceRecord-BS-BSO-BSRef-BSRefO+BitStringRef partial decoding move constructor
  Test79(); //SequenceRecord-BS-BSO-BSRef-BSRefO+BitStringRef partial decoding copy =
  Test80(); //SequenceRecord-BS-BSO-BSRef-BSRefO+BitStringRef partial decoding move =
  Test81(); //SequenceRecord-IS-OI-OIO-OIRef-OIRefO
  Test82(); //SequenceRecord-IS-OI-OIO-OIRef-OIRefO
  Test83(); //OBJECT_IDENTIFIER::SetArcs()
  Test84(); //SequenceRecord-IS-ROI-ROIO-ROIRefWithTag-ROIRefWithTagO
  Test85(); //SequenceRecord-IS-ROI-ROIO-ROIRefWithTag-ROIRefWithTagO
  Test86(); //RELATIVE_OID::SetArcs()
  Test87(); //OBJECT_IDENTIFIER copy constructor
  Test88(); //OBJECT_IDENTIFIER move constructor
  Test89(); //OBJECT_IDENTIFIER copy =
  Test90(); //OBJECT_IDENTIFIER move =
  Test91(); //RELATIVE_OID copy constructor
  Test92(); //RELATIVE_OID move constructor
  Test93(); //RELATIVE_OID copy =
  Test94(); //RELATIVE_OID move =
  Test95(); //OBJECT_IDENTIFIER::ParseArcs()
  Test96(); //RELATIVE_OID::ParseArcs()
  Test97(); //SequenceRecord-IS-UT-UTO-UTRefWithTag-UTRefWithTagO
  Test98(); //SequenceRecord-IS-UT-UTO-UTRefWithTag-UTRefWithTagO
  Test99(); //SequenceRecord-IS-UT-UTO-UTRefWithTag-UTRefWithTagO copy constructor
  Test100(); //SequenceRecord-IS-UT-UTO-UTRefWithTag-UTRefWithTagO move constructor
}

#endif	/* TEST1_100_HPP */

