#ifndef TESTS101_200_HPP
#define	TESTS101_200_HPP

#include "headers.hpp"

void Test101() {
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
  SequenceRecord_IS_UT_UTO_UTRefWithTag_UTRefWithTagO rec2;
  rec2 = rec;
  
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

void Test102() {
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
  SequenceRecord_IS_UT_UTO_UTRefWithTag_UTRefWithTagO rec2;
  rec2 = std::move(rec);
  
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

void Test103() {
  uint8_t test[] = {0x03, 0x0b, 0x05, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 
                    0xe3, 0x98, 0xfe, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test));
  rec.Clear();
  CHECK_RESULT(rec.empty()
  );
}

void Test104() {
  std::vector<uint8_t> mustBe1 = {0x32, 0x30, 0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe3 = {0x32, 0x30, 0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe4 = {0x32, 0x30, 0x33, 0x37, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};;
  
  uint8_t test[] = {0x30, 0x25, 0x30, 0x23, 0x18, 0x0f, 0x32, 0x30, 0x31, 0x30, 
                    0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 
                    0x5a, 0x9f, 0x3c, 0x0f, 0x32, 0x30, 0x33, 0x30, 0x30, 0x33, 
                    0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_GT_GTO_GTRefWithTag_GTRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.time1 == mustBe1 &&
          rec.seq.time1.ToTime() == 1268239212 &&
            !rec.seq.time2 &&
          rec.seq.time3 == mustBe3 &&
          rec.seq.time3.ToTime() == 1899391212 &&
          !rec.seq.time4
  );
}

void Test105() {
  std::vector<uint8_t> mustBe1 = {0x32, 0x30, 0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe3 = {0x32, 0x30, 0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe4 = {0x32, 0x30, 0x33, 0x37, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  
  uint8_t test[] = {0x30, 0x48, 0x30, 0x46, 0x18, 0x0f, 0x32, 0x30, 0x31, 0x30, 
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
          *rec.seq.time4 == mustBe4
  );
}

void Test106() {
  std::vector<uint8_t> mustBe1 = {0x32, 0x30, 0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe3 = {0x32, 0x30, 0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe4 = {0x32, 0x30, 0x33, 0x37, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  
  uint8_t test[] = {0x30, 0x48, 0x30, 0x46, 0x18, 0x0f, 0x32, 0x30, 0x31, 0x30, 
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
  ret = rec.DecodeBer(test, sizeof(test));
  SequenceRecord_IS_GT_GTO_GTRefWithTag_GTRefWithTagO rec2(rec);
  
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

void Test107() {
  std::vector<uint8_t> mustBe1 = {0x32, 0x30, 0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe3 = {0x32, 0x30, 0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe4 = {0x32, 0x30, 0x33, 0x37, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  
  uint8_t test[] = {0x30, 0x48, 0x30, 0x46, 0x18, 0x0f, 0x32, 0x30, 0x31, 0x30, 
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
  ret = rec.DecodeBer(test, sizeof(test));
  SequenceRecord_IS_GT_GTO_GTRefWithTag_GTRefWithTagO rec2(std::move(rec));
  
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

void Test108() {
  std::vector<uint8_t> mustBe1 = {0x32, 0x30, 0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe3 = {0x32, 0x30, 0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe4 = {0x32, 0x30, 0x33, 0x37, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  
  uint8_t test[] = {0x30, 0x48, 0x30, 0x46, 0x18, 0x0f, 0x32, 0x30, 0x31, 0x30, 
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
  ret = rec.DecodeBer(test, sizeof(test));
  SequenceRecord_IS_GT_GTO_GTRefWithTag_GTRefWithTagO rec2;
  rec2 = rec;
  
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

void Test109() {
  std::vector<uint8_t> mustBe1 = {0x32, 0x30, 0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe2 = {0x32, 0x30, 0x32, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe3 = {0x32, 0x30, 0x33, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  std::vector<uint8_t> mustBe4 = {0x32, 0x30, 0x33, 0x37, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  
  uint8_t test[] = {0x30, 0x48, 0x30, 0x46, 0x18, 0x0f, 0x32, 0x30, 0x31, 0x30, 
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
  ret = rec.DecodeBer(test, sizeof(test));
  SequenceRecord_IS_GT_GTO_GTRefWithTag_GTRefWithTagO rec2;
  rec2 = std::move(rec);
  
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

void Test110() {
  std::vector<uint8_t> mustBe1 = {0x32, 0x30, 0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x5a};
  
  TEST_NUMBER;
  struct tm time;
  memset(&time, 0, sizeof(time));
  time.tm_year = 110;
  time.tm_mon = 2;
  time.tm_mday = 10;
  time.tm_hour = 16;
  time.tm_min = 40;
  time.tm_sec = 12;
  GeneralizedTime rec;
  rec.FromTime(time, true);
  CHECK_COND(rec == mustBe1 && rec.ToTime() == 1268239212
  );
}

void Test111() {
  std::vector<uint8_t> mustBe1 = {0x31, 0x30, 0x30, 0x33, 0x31, 0x30, 0x31, 0x36, 0x34, 0x30, 0x31, 0x32, 0x2b, 0x30, 0x30, 0x30, 0x30};
  
  TEST_NUMBER;
  struct tm time;
  memset(&time, 0, sizeof(time));
  time.tm_year = 110;
  time.tm_mon = 2;
  time.tm_mday = 10;
  time.tm_hour = 16;
  time.tm_min = 40;
  time.tm_sec = 12;
  UTCTime rec;
  rec.FromTime(time, false);
  CHECK_COND(rec == mustBe1 && rec.ToTime() == 1268239212
  );
}

void Test112() {
  std::vector<uint8_t> mustBe = {0x31, 0xf0, 0x2d, 0x82};
  uint8_t test[] = {0x02, 0x04, 0x31, 0xf0, 0x2d, 0x82};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  long l;
  unsigned long ul;
  INTEGER rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == mustBe && 
          rec.ToLong(l) && l == 837823874 &&
          rec.ToULong(ul) && ul == 837823874
  );
}

void Test113() {
  std::vector<uint8_t> mustBe = {0xfb, 0x9c, 0x80, 0xdf};
  uint8_t test[] = {0x02, 0x04, 0xfb, 0x9c, 0x80, 0xdf};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  long l;
  unsigned long ul;
  INTEGER rec;
  ret = rec.DecodeBer(test, sizeof(test));
  rec.ToULong(ul);
  CHECK_RESULT(rec == mustBe && 
          rec.ToLong(l) && l == -73629473 && 
          rec.ToULong(ul) && ul == 4221337823
  );
}

void Test114() {
  std::vector<uint8_t> mustBe = {0x31, 0xf0, 0x2d, 0x82, 0x37, 0x31, 0xf0, 0x2d, 
                                0x82, 0x37, 0x31, 0xf0, 0x2d, 0x82, 0x37};
  uint8_t test[] = {0x02, 0x0f, 0x31, 0xf0, 0x2d, 0x82, 0x37, 0x31, 0xf0, 0x2d, 
                    0x82, 0x37, 0x31, 0xf0, 0x2d, 0x82, 0x37};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  long l;
  INTEGER rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == mustBe && !rec.ToLong(l)
  );
}

void Test115() {
  TEST_NUMBER;
  {
    std::vector<uint8_t> mustBe = {0xfb, 0x9c, 0x80, 0xdf};
    long mustBeValue = -73629473;
    long l;
    INTEGER rec;
    rec.FromLong(mustBeValue);
    INTERMEDIATE_COND(rec == mustBe && 
            rec.ToLong(l) && l == mustBeValue 
    );
  }
  {
    std::vector<uint8_t> mustBe = {0x88, 0xca, 0x6c, 0x00};
    long mustBeValue = -2000000000;
    long l;
    INTEGER rec;
    rec.FromLong(mustBeValue);
    CHECK_COND(rec == mustBe && 
            rec.ToLong(l) && l == mustBeValue 
    );
  }
}

void Test116() {
  std::vector<uint8_t> mustBe = {0x0, 0xfb, 0x9c, 0x80, 0xdf};
  unsigned long mustBeValue = 4221337823;
  
  TEST_NUMBER;
  unsigned long l;
  INTEGER rec;
  rec.FromULong(mustBeValue);
  CHECK_COND(rec == mustBe && 
          rec.ToULong(l) && l == mustBeValue 
  );
}

void Test117() {
  std::vector<uint8_t> mustBe = {0x80, 0xea, 0x0c, 0x7c, 0x0b, 0x60, 0xb6, 0xd5, 0x3d};
  uint8_t test[] = {0x09, 0x09, 0x80, 0xea, 0x0c, 0x7c, 0x0b, 0x60, 0xb6, 0xd5, 0x3d};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  double d;
  REAL rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == mustBe && rec.ToDouble(d) && d == 837823874.856765
  );
}

void Test118() {
  std::vector<uint8_t> mustBe = {0xc0, 0xe6, 0x11, 0x8d, 0xfc, 0x84, 0x7f, 0xc3, 0x2f};
  uint8_t test[] = {0x09, 0x09, 0xc0, 0xe6, 0x11, 0x8d, 0xfc, 0x84, 0x7f, 0xc3, 0x2f};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  double d;
  REAL rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == mustBe && rec.ToDouble(d) && d == -73629473.124768
  );
}

void Test119() {
  std::vector<uint8_t> mustBe = {0x80, 0xea, 0x0c, 0x7c, 0x0b, 0x60, 0xb6, 0xd5, 0x3d};
  double mustBeDouble = 837823874.856765;
  
  TEST_NUMBER;
  double d;
  REAL rec;
  bool fromDoubleSuccess = rec.FromDouble(mustBeDouble);
  CHECK_COND(fromDoubleSuccess && 
              rec == mustBe && 
              rec.ToDouble(d) && d == mustBeDouble
  );
}

void Test120() {
  std::vector<uint8_t> mustBe = {0x31, 0xf0, 0x2d, 0x82};
  //differs from INTEGER test only in tag (10)
  uint8_t test[] = {0x0a, 0x04, 0x31, 0xf0, 0x2d, 0x82};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  long l;
  unsigned long ul;
  ENUMERATED rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == mustBe && 
          rec.ToLong(l) && l == 837823874 &&
          rec.ToULong(ul) && ul == 837823874
  );
}

void Test121() {
  std::vector<uint8_t> mustBe = {0xfb, 0x9c, 0x80, 0xdf};
  //differs from INTEGER test only in tag (10)
  uint8_t test[] = {0x0a, 0x04, 0xfb, 0x9c, 0x80, 0xdf};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  long l;
  unsigned long ul;
  ENUMERATED rec;
  ret = rec.DecodeBer(test, sizeof(test));
  rec.ToULong(ul);
  CHECK_RESULT(rec == mustBe && 
          rec.ToLong(l) && l == -73629473 && 
          rec.ToULong(ul) && ul == 4221337823
  );
}

void Test122() {
  std::vector<uint8_t> mustBe = {0x31, 0xf0, 0x2d, 0x82, 0x37, 0x31, 0xf0, 0x2d, 
                                0x82, 0x37, 0x31, 0xf0, 0x2d, 0x82, 0x37};
  //differs from INTEGER test only in tag (10)
  uint8_t test[] = {0x0a, 0x0f, 0x31, 0xf0, 0x2d, 0x82, 0x37, 0x31, 0xf0, 0x2d, 
                    0x82, 0x37, 0x31, 0xf0, 0x2d, 0x82, 0x37};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  long l;
  ENUMERATED rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == mustBe && !rec.ToLong(l)
  );
}

void Test123() {
  std::vector<uint8_t> mustBe = {0xfb, 0x9c, 0x80, 0xdf};
  long mustBeValue = -73629473;
  
  TEST_NUMBER;
  long l;
  ENUMERATED rec;
  rec.FromLong(mustBeValue);
  CHECK_COND(rec == mustBe && 
          rec.ToLong(l) && l == mustBeValue 
  );
}

void Test124() {
  std::vector<uint8_t> mustBe = {0x0, 0xfb, 0x9c, 0x80, 0xdf};
  unsigned long mustBeValue = 4221337823;
  
  TEST_NUMBER;
  unsigned long l;
  ENUMERATED rec;
  rec.FromULong(mustBeValue);
  CHECK_COND(rec == mustBe && 
          rec.ToULong(l) && l == mustBeValue 
  );
}

void Test125() {
  std::vector<uint8_t> mustBe1 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  std::vector<uint8_t> mustBe2 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x32};
  std::vector<uint8_t> mustBe3 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x33};
  std::vector<uint8_t> mustBe4 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x34};

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x1e, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_BmpS_BmpSO_BmpSRefWithTag_BmpSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test126() {
  std::vector<uint8_t> mustBe1 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  std::vector<uint8_t> mustBe2 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x32};
  std::vector<uint8_t> mustBe3 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x33};
  std::vector<uint8_t> mustBe4 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x34};
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x1e, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_BmpS_BmpSO_BmpSRefWithTag_BmpSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test127() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x0c, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_UTF8S_UTF8SO_UTF8SRefWithTag_UTF8SRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test128() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x0c, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_UTF8S_UTF8SO_UTF8SRefWithTag_UTF8SRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test129() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x1b, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_GenS_GenSO_GenSRefWithTag_GenSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test130() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x1b, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_GenS_GenSO_GenSRefWithTag_GenSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test131() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x19, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_GraS_GraSO_GraSRefWithTag_GraSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test132() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x19, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_GraS_GraSO_GraSRefWithTag_GraSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test133() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x16, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_IA5S_IA5SO_IA5SRefWithTag_IA5SRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test134() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x16, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_IA5S_IA5SO_IA5SRefWithTag_IA5SRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test135() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x1a, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_VisS_VisSO_VisSRefWithTag_VisSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test136() {
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
  SequenceRecord_IS_VisS_VisSO_VisSRefWithTag_VisSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test137() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x12, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test138() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x12, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_NumS_NumSO_NumSRefWithTag_NumSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test139() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_PriS_PriSO_PriSRefWithTag_PriSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test140() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_PriS_PriSO_PriSRefWithTag_PriSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test141() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x14, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_TeleS_TeleSO_TeleSRefWithTag_TeleSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test142() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x14, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_TeleS_TeleSO_TeleSRefWithTag_TeleSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test143() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x14, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_T61S_T61SO_T61SRefWithTag_T61SRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test144() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x14, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_T61S_T61SO_T61SRefWithTag_T61SRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test145() {
  std::vector<uint8_t> mustBe1 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  std::vector<uint8_t> mustBe2 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x32};
  std::vector<uint8_t> mustBe3 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x33};
  std::vector<uint8_t> mustBe4 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x34};

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x1c, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_UniS_UniSO_UniSRefWithTag_UniSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test146() {
  std::vector<uint8_t> mustBe1 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  std::vector<uint8_t> mustBe2 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x32};
  std::vector<uint8_t> mustBe3 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x33};
  std::vector<uint8_t> mustBe4 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x34};
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x1c, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_UniS_UniSO_UniSRefWithTag_UniSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test147() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x15, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_VidS_VidSO_VidSRefWithTag_VidSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test148() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x15, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_VidS_VidSO_VidSRefWithTag_VidSRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test149() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";

  
  uint8_t test[] = {0x30, 0x15, 0x30, 0x13, 0x07, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_ObjD_ObjDO_ObjDRefWithTag_ObjDRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            !rec.seq.str2 &&
          rec.seq.str3 == mustBe3 &&
          !rec.seq.str4
  );
}

void Test150() {
  std::string mustBe1 = "string1";
  std::string mustBe2 = "string2";
  std::string mustBe3 = "string3";
  std::string mustBe4 = "string4";
  
  uint8_t test[] = {0x30, 0x28, 0x30, 0x26, 0x07, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_ObjD_ObjDO_ObjDRefWithTag_ObjDRefWithTagO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  
  CHECK_RESULT(rec.seq.str1 == mustBe1 &&
            rec.seq.str2 && 
            *rec.seq.str2 == mustBe2 &&
          rec.seq.str3 == mustBe3 &&
          rec.seq.str4 &&
          *rec.seq.str4 == mustBe4
          
  );
}

void Test151() {
  uint8_t test[] = {0x31, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 
                    0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_I_IO_I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.type == 123 && 
               !rec.type2 && 
               rec.type3 == 92367624 
  );
}

void Test152() {
  uint8_t test[] = {0x31, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 0xb1, 0x92, 
                    0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_I_IO_I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.type == 123 && 
               rec.type2 && *rec.type2 == 635282 &&
               rec.type3 == 92367624 
  );
}

void Test153() {
  uint8_t test[] = {0x31, 0x0b, 0x31, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 0x04, 0x05, 
                    0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISetO_I_IO_I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.set &&
              rec.set->type == 123 && 
               !rec.set->type2 && 
               rec.set->type3 == 92367624
  );
}

void Test154() {
  uint8_t test[] = {0x31, 0x10, 0x31, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 0x03, 0x09, 
                    0xb1, 0x92, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISetO_I_IO_I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.set &&
                rec.set->type == 123 && 
               rec.set->type2 && *rec.set->type2 == 635282 &&
               rec.set->type3 == 92367624 
  );
}

void Test155() {
  uint8_t test[] = {0x31, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISetO_I_IO_I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.set);
}

void Test156() {
  uint8_t test[] = {0x31, 0x1a, 0x31, 0x0b, 0x31, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 
                    0x04, 0x05, 0x81, 0x6b, 0x08, 0xab, 0x0b, 0x31, 0x09, 0x8a, 
                    0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.ref1.set &&
              rec.ref1.set->type == 123 && 
               !rec.ref1.set->type2 && 
               rec.ref1.set->type3 == 92367624 &&
          !rec.ref2 &&
          
              rec.ref3.set &&
              rec.ref3.set->type == 123 && 
               !rec.ref3.set->type2 && 
               rec.ref3.set->type3 == 92367624 &&
          
          !rec.ref4 
  );
}

void Test157() {
  uint8_t test[] = {0x31, 0x48, 0x31, 0x10, 0x31, 0x0e, 0x8a, 0x01, 0x7b, 0x8b, 
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
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.ref1.set &&
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
}

void Test158() {
  uint8_t test[] = {0x31, 0x1a, 0x31, 0x0b, 0x31, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 
                    0x04, 0x05, 0x81, 0x6b, 0x08, 0xab, 0x0b, 0x31, 0x09, 0x8a, 
                    0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO rec2(rec1);
  CHECK_RESULT(rec1.ref1.set &&
              rec1.ref1.set->type == 123 && 
               !rec1.ref1.set->type2 && 
               rec1.ref1.set->type3 == 92367624 &&
          !rec1.ref2 &&
          
              rec1.ref3.set &&
              rec1.ref3.set->type == 123 && 
               !rec1.ref3.set->type2 && 
               rec1.ref3.set->type3 == 92367624 &&
          !rec1.ref4 &&
          
          
          
              rec2.ref1.set &&
              rec2.ref1.set->type == 123 && 
               !rec2.ref1.set->type2 && 
               rec2.ref1.set->type3 == 92367624 &&
          !rec2.ref2 &&
          
              rec2.ref3.set &&
              rec2.ref3.set->type == 123 && 
               !rec2.ref3.set->type2 && 
               rec2.ref3.set->type3 == 92367624 &&
          !rec2.ref4 
  );
}

void Test159() {
  uint8_t test[] = {0x31, 0x1a, 0x31, 0x0b, 0x31, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 
                    0x04, 0x05, 0x81, 0x6b, 0x08, 0xab, 0x0b, 0x31, 0x09, 0x8a, 
                    0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO rec2(std::move(rec1));
  CHECK_RESULT(!rec1.ref1.set &&
          !rec1.ref2 &&
          
              !rec1.ref3.set &&
         
          !rec1.ref4 &&
          
          
              rec2.ref1.set &&
              rec2.ref1.set->type == 123 && 
               !rec2.ref1.set->type2 && 
               rec2.ref1.set->type3 == 92367624 &&
          !rec2.ref2 &&
          
              rec2.ref3.set &&
              rec2.ref3.set->type == 123 && 
               !rec2.ref3.set->type2 && 
               rec2.ref3.set->type3 == 92367624 &&

          !rec2.ref4 
  );
}

void Test160() {
  uint8_t test[] = {0x31, 0x1a, 0x31, 0x0b, 0x31, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 
                    0x04, 0x05, 0x81, 0x6b, 0x08, 0xab, 0x0b, 0x31, 0x09, 0x8a, 
                    0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO rec2;
  rec2 = rec1;
  CHECK_RESULT(rec1.ref1.set &&
              rec1.ref1.set->type == 123 && 
               !rec1.ref1.set->type2 && 
               rec1.ref1.set->type3 == 92367624 &&
          !rec1.ref2 &&
          
              rec1.ref3.set &&
              rec1.ref3.set->type == 123 && 
               !rec1.ref3.set->type2 && 
               rec1.ref3.set->type3 == 92367624 &&
          
          !rec1.ref4 &&
          
          
          
              rec2.ref1.set &&
              rec2.ref1.set->type == 123 && 
               !rec2.ref1.set->type2 && 
               rec2.ref1.set->type3 == 92367624 &&
          !rec2.ref2 &&
          
              rec2.ref3.set &&
              rec2.ref3.set->type == 123 && 
               !rec2.ref3.set->type2 && 
               rec2.ref3.set->type3 == 92367624 &&
          !rec2.ref4 
  );
}

void Test161() {
  uint8_t test[] = {0x31, 0x1a, 0x31, 0x0b, 0x31, 0x09, 0x8a, 0x01, 0x7b, 0x8c, 
                    0x04, 0x05, 0x81, 0x6b, 0x08, 0xab, 0x0b, 0x31, 0x09, 0x8a, 
                    0x01, 0x7b, 0x8c, 0x04, 0x05, 0x81, 0x6b, 0x08};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO rec2;
  rec2 = std::move(rec1);
  CHECK_RESULT(!rec1.ref1.set &&
          !rec1.ref2 &&
          
              !rec1.ref3.set &&
          
          !rec1.ref4 &&
          
          
          
              rec2.ref1.set &&
              rec2.ref1.set->type == 123 && 
               !rec2.ref1.set->type2 && 
               rec2.ref1.set->type3 == 92367624 &&

          !rec2.ref2 &&
          
              rec2.ref3.set &&
              rec2.ref3.set->type == 123 && 
               !rec2.ref3.set->type2 && 
               rec2.ref3.set->type3 == 92367624 &&

          !rec2.ref4 
  );
}

void Test162() {
  std::vector<uint8_t> mustBe1 = {0x37, 0x84, 0x73, 0x91, 0x23};
  uint8_t test[] = {0x31, 0x08, 0x9f, 0x32, 0x05, 0x37, 0x84, 0x73, 0x91, 0x23};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_OSRef1_OSRef1O rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.ref1 == mustBe1 &&
          !rec.ref2
  );
}

void Test163() {
  std::vector<uint8_t> mustBe1 = {0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> mustBe2 = {0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 0x84, 0x73, 0x91, 0x23};
  uint8_t test[] = {0x31, 0x14, 0x8a, 0x0a, 0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 
                    0x84, 0x73, 0x91, 0x23, 0x9f, 0x32, 0x05, 0x37, 0x84, 0x73, 
                    0x91, 0x23};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_OSRef1_OSRef1O rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.ref1 == mustBe1 &&
          rec.ref2 &&
          *rec.ref2 == mustBe2
  );
}

void Test164() {
  uint8_t test[] = {0x31, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfInteger rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 2 && 
             rec[2] == 3
  );
}

void Test165() {
  uint8_t test[] = {0x31, 0x09, 0x0a, 0x01, 0x01, 0x0a, 0x01, 0x02, 0x0a, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfEnumerated rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.size() == 3 && 
              rec[0] == SetOfEnumerated_value1 && 
             rec[1] == SetOfEnumerated_enum::SetOfEnumerated_value2 && 
             rec[2] == SetOfEnumerated_value3
  );
}

void Test166() {
  uint8_t test[] = {0x31, 0x10, 0x30, 0x06, 0x8a, 0x01, 0x01, 0x8c, 0x01, 0x03, 
                    0x30, 0x06, 0x8a, 0x01, 0xff, 0x8c, 0x01, 0xfd};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfSequenceRecord_I_IO_I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.size() == 2);
  SequenceRecord_I_IO_IRef rec1(rec[0]);
  SequenceRecord_I_IO_IRef rec2(rec[1]);
  CHECK_RESULT(rec1.type == 1 &&
              !rec1.type2 &&
          rec1.type3 == 3 && 
          
          rec2.type == -1 &&
              !rec2.type2 &&
          rec2.type3 == -3 
  );
}

void Test167() {
  uint8_t test[] = {0x31, 0x16, 0x31, 0x14, 0xa1, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0x01, 0x8c, 0x01, 0x03, 0xa3, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0xff, 0x8c, 0x01, 0xfd};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_seq rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.set.field1.size() == 1 && 
                  !rec.set.field2 &&
                  rec.set.field3.size() == 1 &&
                !rec.set.field4);
  SequenceRecord_I_IO_IRef rec1(rec.set.field1[0]);
  SetRecord_ISet_Sets_of_seq::set::_field3 rec3(rec.set.field3[0]);
  CHECK_RESULT(rec1.type == 1 && 
              !rec1.type2 && 
              rec1.type3 == 3 &&
          
          rec3.type == -1 &&
          !rec3.type2 &&
          rec3.type3 == -3
  );
}

void Test168() {
  uint8_t test[] = {0x31, 0x2a, 0x31, 0x28, 0xa1, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0x01, 0x8c, 0x01, 0x03, 0xa2, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0x0a, 0x8c, 0x01, 0x1e, 0xa3, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0xff, 0x8c, 0x01, 0xfd, 0xa4, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0xf6, 0x8c, 0x01, 0xe2};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_seq rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.set.field1.size() == 1 && 
                  rec.set.field2 &&
                  rec.set.field2->size() == 1 &&
                  rec.set.field3.size() == 1 &&
                rec.set.field4 && 
                rec.set.field4->size() == 1);
  SequenceRecord_I_IO_IRef rec1(rec.set.field1[0]);
  SequenceRecord_I_IO_IRef rec2((*rec.set.field2)[0]);
  SetRecord_ISet_Sets_of_seq::set::_field3 rec3(rec.set.field3[0]);
  SetRecord_ISet_Sets_of_seq::set::_field4 rec4((*rec.set.field4)[0]);
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

void Test169() {
  uint8_t test[] = {0x31, 0x07, 0x31, 0x05, 0xa3, 0x03, 0x0a, 0x01, 0x02};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_enumerated rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.set.field3.size() == 1 &&
                !rec.set.field4);
  NativeEnumerated rec3(rec.set.field3[0]);
  CHECK_RESULT(rec3 == SetRecord_ISet_Sets_of_enumerated::set::field3_enum::field3_value2
  );
}

void Test170() {
  uint8_t test[] = {0x31, 0x0c, 0x31, 0x0a, 0xa3, 0x03, 0x0a, 0x01, 0x02, 0xa4, 
                    0x03, 0x0a, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_enumerated rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.set.field3.size() == 1 &&
                rec.set.field4 && 
                rec.set.field4->size() == 1);
  NativeEnumerated rec3(rec.set.field3[0]);
  NativeEnumerated rec4((*rec.set.field4)[0]);
  CHECK_RESULT(rec3 == SetRecord_ISet_Sets_of_enumerated::set::field3_enum::field3_value2 &&
          rec4 == SetRecord_ISet_Sets_of_enumerated::set::field4_enum::field4_value3
  );
}

void Test171() {
  uint8_t test[] = {0x31, 0x0c, 0x31, 0x0a, 0xa3, 0x03, 0x0a, 0x01, 0x02, 0xa4, 
                    0x03, 0x0a, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_enumerated rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  SetRecord_ISet_Sets_of_enumerated rec2(rec1);
  INTERMEDIATE_CHECK(rec1.set.field3.size() == 1 &&
                rec1.set.field4 && 
                rec1.set.field4->size() == 1 &&
                rec2.set.field3.size() == 1 &&
                rec2.set.field4 && 
                rec2.set.field4->size() == 1);
  NativeEnumerated en3_1(rec1.set.field3[0]);
  NativeEnumerated en4_1((*rec1.set.field4)[0]);
  NativeEnumerated en3_2(rec2.set.field3[0]);
  NativeEnumerated en4_2((*rec2.set.field4)[0]);
  CHECK_RESULT(en3_1 == SetRecord_ISet_Sets_of_enumerated::set::field3_enum::field3_value2 &&
          en4_1 == SetRecord_ISet_Sets_of_enumerated::set::field4_enum::field4_value3 &&
          en3_2 == SetRecord_ISet_Sets_of_enumerated::set::field3_enum::field3_value2 &&
          en4_2 == SetRecord_ISet_Sets_of_enumerated::set::field4_enum::field4_value3
  );
}

void Test172() {
  uint8_t test[] = {0x31, 0x0c, 0x31, 0x0a, 0xa3, 0x03, 0x0a, 0x01, 0x02, 0xa4, 
                    0x03, 0x0a, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_enumerated rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  SetRecord_ISet_Sets_of_enumerated rec2(std::move(rec1));
  INTERMEDIATE_CHECK(!rec1.set.field3.size() &&
                !rec1.set.field4 && 
          
                rec2.set.field3.size() == 1 &&
                rec2.set.field4 && 
                rec2.set.field4->size() == 1);
  NativeEnumerated en3_2(rec2.set.field3[0]);
  NativeEnumerated en4_2((*rec2.set.field4)[0]);
  CHECK_RESULT(en3_2 == SetRecord_ISet_Sets_of_enumerated::set::field3_enum::field3_value2 &&
          en4_2 == SetRecord_ISet_Sets_of_enumerated::set::field4_enum::field4_value3
  );
}

void Test173() {
  uint8_t test[] = {0x31, 0x0c, 0x31, 0x0a, 0xa3, 0x03, 0x0a, 0x01, 0x02, 0xa4, 
                    0x03, 0x0a, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_enumerated rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  SetRecord_ISet_Sets_of_enumerated rec2;
  rec2 = rec1;
  INTERMEDIATE_CHECK(rec1.set.field3.size() == 1 &&
                rec1.set.field4 && 
                rec1.set.field4->size() == 1 &&
                rec2.set.field3.size() == 1 &&
                rec2.set.field4 && 
                rec2.set.field4->size() == 1);
  NativeEnumerated en3_1(rec1.set.field3[0]);
  NativeEnumerated en4_1((*rec1.set.field4)[0]);
  NativeEnumerated en3_2(rec2.set.field3[0]);
  NativeEnumerated en4_2((*rec2.set.field4)[0]);
  CHECK_RESULT(en3_1 == SetRecord_ISet_Sets_of_enumerated::set::field3_enum::field3_value2 &&
          en4_1 == SetRecord_ISet_Sets_of_enumerated::set::field4_enum::field4_value3 &&
          en3_2 == SetRecord_ISet_Sets_of_enumerated::set::field3_enum::field3_value2 &&
          en4_2 == SetRecord_ISet_Sets_of_enumerated::set::field4_enum::field4_value3
  );
}

void Test174() {
  uint8_t test[] = {0x31, 0x0c, 0x31, 0x0a, 0xa3, 0x03, 0x0a, 0x01, 0x02, 0xa4, 
                    0x03, 0x0a, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_enumerated rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  SetRecord_ISet_Sets_of_enumerated rec2;
  rec2 = std::move(rec1);
  INTERMEDIATE_CHECK(!rec1.set.field3.size() &&
                !rec1.set.field4 && 
          
                rec2.set.field3.size() == 1 &&
                rec2.set.field4 && 
                rec2.set.field4->size() == 1);
  NativeEnumerated en3_2(rec2.set.field3[0]);
  NativeEnumerated en4_2((*rec2.set.field4)[0]);
  CHECK_RESULT(en3_2 == SetRecord_ISet_Sets_of_enumerated::set::field3_enum::field3_value2 &&
          en4_2 == SetRecord_ISet_Sets_of_enumerated::set::field4_enum::field4_value3
  );
}

void Test175() {
  uint8_t test[] = {0x31, 0x04, 0x31, 0x00, 0x31, 0x00};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfSelfRec rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.size() == 2 && 
              rec[0].size() == 0 &&
                      rec[1].size() == 0
  );
}

void Test176() {
  uint8_t test[] = {0x31, 0x06, 0x31, 0x00, 0x31, 0x02, 0x31, 0x00};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfSomeSetOfRecRef rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.size() == 2 && 
              rec[0].size() == 0 &&
               rec[1].size() == 1 &&
               rec[1][0].size() == 0
  );
}

void Test177() {
  uint8_t test[] = {0x30, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceOfInteger rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 2 && 
             rec[2] == 3
  );
}

void Test178() {
  uint8_t test[] = {0x31, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetOfInteger rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 2 && 
             rec[2] == 3
  );
  rec.Erase(0);
  INTERMEDIATE_CHECK(rec.size() == 2 && 
              rec[0] == 3 && 
             rec[1] == 2  
  );
  rec.Erase(1);
  CHECK_RESULT(rec.size() == 1 && 
              rec[0] == 3 
  );
}

void Test179() {
  uint8_t test[] = {0x30, 0x09, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceOfInteger rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.size() == 3 && 
              rec[0] == 1 && 
             rec[1] == 2 && 
             rec[2] == 3
  );
  rec.Erase(0);
  INTERMEDIATE_CHECK(rec.size() == 2 && 
              rec[0] == 2 && 
             rec[1] == 3  
  );
  rec.Erase(1);
  CHECK_RESULT(rec.size() == 1 && 
              rec[0] == 2 
  );
}

void Test180() {
  uint8_t test[] = {0x30, 0x10, 0x30, 0x06, 0x8a, 0x01, 0x01, 0x8c, 0x01, 0x03, 
                    0x30, 0x06, 0x8a, 0x01, 0xff, 0x8c, 0x01, 0xfd};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceOfSequenceRecord_I_IO_I rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.size() == 2);
  SequenceRecord_I_IO_IRef rec1(rec[0]);
  SequenceRecord_I_IO_IRef rec2(rec[1]);
  CHECK_RESULT(rec1.type == 1 &&
              !rec1.type2 &&
          rec1.type3 == 3 && 
          
          rec2.type == -1 &&
              !rec2.type2 &&
          rec2.type3 == -3 
  );
}

void Test181() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ChoiceRealInteger rec;
  ret = rec.DecodeBer(test, sizeof(test));
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec.FetchPresent() == ChoiceRealInteger::PR_integer &&
          rec.integer() &&
          *rec.integer() == 123
  );
#else
  CHECK_RESULT(rec.FetchPresent() == ChoiceRealInteger::PR_integer &&
          rec.integer() == 123
  );
#endif
}

void Test182() {
  uint8_t test[] = {0x09, 0x09, 0x80, 0xd2, 0x1e, 0xc7, 0xdf, 0x3b, 0x64, 0x5a, 0x1d};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ChoiceRealInteger rec;
  ret = rec.DecodeBer(test, sizeof(test));
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec.FetchPresent() == ChoiceRealInteger::PR_real &&
          rec.real() &&
          *rec.real() == 123.123
  );
#else
  CHECK_RESULT(rec.FetchPresent() == ChoiceRealInteger::PR_real &&
          rec.real() == 123.123
  );
#endif
}

void Test183() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger rec;
  ret = rec.DecodeBer(test, sizeof(test));
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec.choice() &&
          rec.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec.choice()->integer() &&
          *rec.choice()->integer() == 123
  );
#else
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec.choice().integer() == 123
  );
#endif
}

void Test184() {
  uint8_t test[] = {0x09, 0x09, 0x80, 0xd2, 0x1e, 0xc7, 0xdf, 0x3b, 0x64, 0x5a, 0x1d};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger rec;
  ret = rec.DecodeBer(test, sizeof(test));
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec.choice() &&
          rec.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_real &&
          rec.choice()->real() &&
          *rec.choice()->real() == 123.123
  );
#else
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_real &&
          rec.choice().real() == 123.123
  );
#endif
}

void Test185() {
  uint8_t test[] = {0x30, 0x02, 0x30, 0x00};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SeqRecWithThisChoice rec;
  ret = rec.DecodeBer(test, sizeof(test));
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec.ch && 
          rec.ch->FetchPresent() == Choice_SeqWithThisChoice::PR_seq &&
          rec.ch->seq() &&
          !rec.ch->seq()->ch
          
  );
#else
  CHECK_RESULT(rec.ch && 
          rec.ch->FetchPresent() == Choice_SeqWithThisChoice::PR_seq &&
          !rec.ch->seq().ch
          
  );
#endif
}

void Test186() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  Choice_IChoiceRealInteger rec2(rec1);
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec1.choice() &&
          rec1.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec1.choice()->integer() &&
          *rec1.choice()->integer() == 123 &&
          
          rec2.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec2.choice() &&
          rec2.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec2.choice()->integer() &&
          *rec2.choice()->integer() == 123
  );
#else
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec1.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec1.choice().integer() == 123 &&
          
          rec2.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec2.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec2.choice().integer() == 123
  );
#endif
}

void Test187() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  Choice_IChoiceRealInteger rec2(std::move(rec1));
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger::PR_NOTHING &&
          !rec1.choice() &&
          
          rec2.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec2.choice() &&
          rec2.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec2.choice()->integer() &&
          *rec2.choice()->integer() == 123
  );
#else
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger::PR_NOTHING &&
          
          rec2.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec2.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec2.choice().integer() == 123
  );
#endif
}

void Test188() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  Choice_IChoiceRealInteger rec2;
  rec2 = rec1;
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec1.choice() &&
          rec1.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec1.choice()->integer() &&
          *rec1.choice()->integer() == 123 &&
          
          rec2.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec2.choice() &&
          rec2.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec2.choice()->integer() &&
          *rec2.choice()->integer() == 123
  );
#else
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec1.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec1.choice().integer() == 123 &&
          
          rec2.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec2.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec2.choice().integer() == 123
  );
#endif
}

void Test189() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  Choice_IChoiceRealInteger rec2;
  rec2 = std::move(rec1);
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger::PR_NOTHING &&
          !rec1.choice() &&
          
          rec2.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec2.choice() &&
          rec2.choice()->FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec2.choice()->integer() &&
          *rec2.choice()->integer() == 123
  );
#else
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger::PR_NOTHING &&
          
          rec2.FetchPresent() == Choice_IChoiceRealInteger::PR_choice &&
          rec2.choice().FetchPresent() == Choice_IChoiceRealInteger::choice::PR_integer &&
          rec2.choice().integer() == 123
  );
#endif
}

void Test190() {
  uint8_t test[] = {0x02, 0x01, 0x7b};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoiceRealInteger rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  rec1.Clear();
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger::PR_NOTHING &&
          !rec1.choice()
  );
#else
  CHECK_RESULT(rec1.FetchPresent() == Choice_IChoiceRealInteger::PR_NOTHING);
#endif
}

void Test191() {
  uint8_t test[] = {0x31, 0x0c, 0x31, 0x0a, 0xa3, 0x03, 0x0a, 0x01, 0x02, 0xa4, 
                    0x03, 0x0a, 0x01, 0x03};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Sets_of_enumerated rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  rec1.Clear();
  CHECK_RESULT(!rec1.set.field3.size() &&
                !rec1.set.field4
  );
}

void Test192() {
  std::vector<uint8_t> mustBe1_1 = {0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> mustBe2_1 = {0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 0x84, 0x73, 0x91, 0x23};
  uint8_t test1[] = {0x31, 0x14, 0x8a, 0x0a, 0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 
                    0x84, 0x73, 0x91, 0x23, 0x9f, 0x32, 0x05, 0x37, 0x84, 0x73, 
                    0x91, 0x23};
  
  std::vector<uint8_t> mustBe1_2 = {0x73, 0x48, 0x37, 0x19, 0x32};
  std::vector<uint8_t> mustBe2_2 = {0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 0x84, 0x73, 0x91, 0x23};
  uint8_t test2[] = {0x31, 0x14, 0x8a, 0x0a, 0x37, 0x84, 0x73, 0x91, 0x23, 0x37, 
                    0x84, 0x73, 0x91, 0x23, 0x9f, 0x32, 0x05, 0x73, 0x48, 0x37, 0x19, 0x32};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_OSRef1_OSRef1O rec;
  ret = rec.DecodeBer(test1, sizeof(test1));
  INTERMEDIATE_CHECK(rec.ref1 == mustBe1_1 &&
          rec.ref2 &&
          *rec.ref2 == mustBe2_1
  );
  ret = rec.DecodeBer(test2, sizeof(test2));
  CHECK_RESULT(rec.ref1 == mustBe1_2 &&
          rec.ref2 &&
          *rec.ref2 == mustBe2_2
  );
}

void Test193() {
  uint8_t test1[] = {0x13, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  uint8_t test2[] = {0x13, 0x06, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x32};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  Choice_IChoicePS_IA5 rec;
  ret = rec.DecodeBer(test1, sizeof(test1));
#ifdef PTR_CHOICE_GETTERS
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec.choice() &&
          rec.choice()->FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec.choice()->str1() &&
          *rec.choice()->str1() == "string1");
#else
  INTERMEDIATE_CHECK(rec.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec.choice().FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec.choice().str1() == "string1");
#endif
  ret = rec.DecodeBer(test2, sizeof(test2));
#ifdef PTR_CHOICE_GETTERS
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec.choice() &&
          rec.choice()->FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec.choice()->str1() &&
          *rec.choice()->str1() == "strin2");
#else
  CHECK_RESULT(rec.FetchPresent() == Choice_IChoicePS_IA5::PR_choice &&
          rec.choice().FetchPresent() == Choice_IChoicePS_IA5::choice::PR_str1 &&
          rec.choice().str1() == "strin2");
#endif
}

void Test194() {
  uint8_t test[] = {0x30, 0x07, 0x81, 0x02, 0x03, 0x78, 0x82, 0x01, 0x00};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ID_I_ID_ID rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.val1 && 
                rec.val2 == 888 && 
                rec.val3 == 0 &&
          !rec.val4
  );
}

void Test195() {
  uint8_t test[] = {0x30, 0x0f, 0x80, 0x01, 0x6f, 0x81, 0x02, 0x03, 0x78, 0x82, 
                    0x02, 0x02, 0x9a, 0x83, 0x02, 0x00, 0xde};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ID_I_ID_ID rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.val1 && *rec.val1 == 111 &&
                rec.val2 == 888 && 
                rec.val3 == 666 &&
          rec.val4 && *rec.val4 == 222
  );
}

void Test196() {
  
  TEST_NUMBER;
  SequenceRecord_ID_I_ID_ID rec;
#ifdef INSECURE_POINTERS
  rec.val1 = new NativeInteger();
#else
  rec.val1.reset(new NativeInteger());
#endif
  *rec.val1 = 1;
  rec.val2 = 2;
  rec.val3 = 3;
#ifdef INSECURE_POINTERS
  rec.val4 = new NativeInteger();
#else
  rec.val4.reset(new NativeInteger());
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

void Test197() {
  TEST_NUMBER;
  SequenceRecord_ID_I_ID_ID rec;
  rec.SetVal1Default();
  rec.SetVal3Default();
  rec.SetVal4Default();
  
  CHECK_COND(rec.val1 && *rec.val1 == 123 && 
             rec.val2 == 0 &&
          rec.val3 == 0 &&
          rec.val4 && *rec.val4 == 567
  );
}

void Test198() {
  uint8_t test[] = {0x30, 0x07, 0x81, 0x02, 0x03, 0x78, 0x82, 0x01, 0x00};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ED_E_ED_ED rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(!rec.val1 && 
                rec.val2 == 888 && 
                rec.val3 == 0 &&
          !rec.val4
  );
}

void Test199() {
  uint8_t test[] = {0x30, 0x0f, 0x80, 0x01, 0x6f, 0x81, 0x02, 0x03, 0x78, 0x82, 
                    0x02, 0x02, 0x9a, 0x83, 0x02, 0x00, 0xde};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ED_E_ED_ED rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec.val1 && *rec.val1 == 111 &&
                rec.val2 == 888 && 
                rec.val3 == 666 &&
          rec.val4 && *rec.val4 == 222
  );
}

void Test200() {
  
  TEST_NUMBER;
  SequenceRecord_ED_E_ED_ED rec;
#ifdef INSECURE_POINTERS
  rec.val1 = new NativeEnumerated();
#else
  rec.val1.reset(new NativeEnumerated());
#endif
  *rec.val1 = 1;
  rec.val2 = 2;
  rec.val3 = 3;
#ifdef INSECURE_POINTERS
  rec.val4 = new NativeEnumerated();
#else
  rec.val4.reset(new NativeEnumerated());
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

void Tests101_200() {
  Test101(); //SequenceRecord-IS-UT-UTO-UTRefWithTag-UTRefWithTagO copy =
  Test102(); //SequenceRecord-IS-UT-UTO-UTRefWithTag-UTRefWithTagO move =
  Test103(); //BIT_STRING::Clear()
  Test104(); //SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO
  Test105(); //SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO
  Test106(); //SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO copy constructor
  Test107(); //SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO move constructor
  Test108(); //SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO copy =
  Test109(); //SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO move =
  Test110(); //GeneralizedTime::FromTime()
  Test111(); //UTCTime::FromTime()
  Test112(); //INTEGER
  Test113(); //INTEGER
  Test114(); //INTEGER
  Test115(); //INTEGER::FromLong
  Test116(); //INTEGER::FromULong
  Test117(); //REAL
  Test118(); //REAL
  Test119(); //REAL::FromDouble
  Test120(); //ENUMERATED
  Test121(); //ENUMERATED
  Test122(); //ENUMERATED
  Test123(); //ENUMERATED::FromLong
  Test124(); //ENUMERATED::FromULong
  Test125(); //SequenceRecord-IS-BmpS-BmpSO-BmpSRefWithTag-BmpSRefWithTagO
  Test126(); //SequenceRecord-IS-BmpS-BmpSO-BmpSRefWithTag-BmpSRefWithTagO
  Test127(); //SequenceRecord-IS-UTF8S-UTF8SO-UTF8SRefWithTag-UTF8SRefWithTagO
  Test128(); //SequenceRecord-IS-UTF8S-UTF8SO-UTF8SRefWithTag-UTF8SRefWithTagO
  Test129(); //SequenceRecord-IS-GenS-GenSO-GenSRefWithTag-GenSRefWithTagO
  Test130(); //SequenceRecord-IS-GenS-GenSO-GenSRefWithTag-GenSRefWithTagO
  Test131(); //SequenceRecord-IS-GraS-GraSO-GraSRefWithTag-GraSRefWithTagO
  Test132(); //SequenceRecord-IS-GraS-GraSO-GraSRefWithTag-GraSRefWithTagO
  Test133(); //SequenceRecord-IS-IA5S-IA5SO-IA5SRefWithTag-IA5SRefWithTagO
  Test134(); //SequenceRecord-IS-IA5S-IA5SO-IA5SRefWithTag-IA5SRefWithTagO
  Test135(); //SequenceRecord-IS-VisS-VisSO-VisSRefWithTag-VisSRefWithTagO
  Test136(); //SequenceRecord-IS-VisS-VisSO-VisSRefWithTag-VisSRefWithTagO
  Test137(); //SequenceRecord-IS-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO
  Test138(); //SequenceRecord-IS-NumS-NumSO-NumSRefWithTag-NumSRefWithTagO
  Test139(); //SequenceRecord-IS-PriS-PriSO-PriSRefWithTag-PriSRefWithTagO
  Test140(); //SequenceRecord-IS-PriS-PriSO-PriSRefWithTag-PriSRefWithTagO
  Test141(); //SequenceRecord-IS-TeleS-TeleSO-TeleSRefWithTag-TeleSRefWithTagO
  Test142(); //SequenceRecord-IS-TeleS-TeleSO-TeleSRefWithTag-TeleSRefWithTagO
  Test143(); //SequenceRecord-IS-T61S-T61SO-T61SRefWithTag-T61SRefWithTagO
  Test144(); //SequenceRecord-IS-T61S-T61SO-T61SRefWithTag-T61SRefWithTagO
  Test145(); //SequenceRecord-IS-UniS-UniSO-UniSRefWithTag-UniSRefWithTagO
  Test146(); //SequenceRecord-IS-UniS-UniSO-UniSRefWithTag-UniSRefWithTagO
  Test147(); //SequenceRecord-IS-VidS-VidSO-VidSRefWithTag-VidSRefWithTagO
  Test148(); //SequenceRecord-IS-VidS-VidSO-VidSRefWithTag-VidSRefWithTagO
  Test149(); //SequenceRecord-IS-ObjD-ObjDO-ObjDRefWithTag-ObjDRefWithTagO
  Test150(); //SequenceRecord-IS-ObjD-ObjDO-ObjDRefWithTag-ObjDRefWithTagO
  Test151(); //SetRecord-I-IO-I
  Test152(); //SetRecord-I-IO-I
  Test153(); //SetRecord-ISetO-I-IO-I
  Test154(); //SetRecord-ISetO-I-IO-I
  Test155(); //SetRecord-ISetO-I-IO-I
  Test156(); //SetRecord-SeRef-SeRefO-SeDirRef-SeDirRefO + SetRecord-ISetO-I-IO-I-Ref + SetRecord-ISetO-I-IO-I
  Test157(); //SetRecord-SeRef-SeRefO-SeDirRef-SeDirRefO + SetRecord-ISetO-I-IO-I-Ref + SetRecord-ISetO-I-IO-I
  Test158(); //SetRecord-SeRef-SeRefO-SeDirRef-SeDirRefO + SetRecord-ISetO-I-IO-I-Ref + SetRecord-ISetO-I-IO-I copy constructor
  Test159(); //SetRecord-SeRef-SeRefO-SeDirRef-SeDirRefO + SetRecord-ISetO-I-IO-I-Ref + SetRecord-ISetO-I-IO-I move constructor
  Test160(); //SetRecord-SeRef-SeRefO-SeDirRef-SeDirRefO + SetRecord-ISetO-I-IO-I-Ref + SetRecord-ISetO-I-IO-I copy =
  Test161(); //SetRecord-SeRef-SeRefO-SeDirRef-SeDirRefO + SetRecord-ISetO-I-IO-I-Ref + SetRecord-ISetO-I-IO-I move =
  Test162(); //SetRecord-OSRef1-OSRef1O + OctetStringRef1 + OctetStringRef2 + OctetStringRef3 + OctetStringRef4
  Test163(); //SetRecord-OSRef1-OSRef1O + OctetStringRef1 + OctetStringRef2 + OctetStringRef3 + OctetStringRef4
  Test164(); //SetOfInteger
  Test165(); //SetOfEnumerated
  Test166(); //SetOfSequenceRecord-I-IO-I + SequenceRecord-I-IO-IRef + SequenceRecord-I-IO-I
  Test167(); //SetRecord-ISet-Sets-of-seq + SetOfSequenceRecord-I-IO-I + SequenceRecord-I-IO-IRef + SequenceRecord-I-IO-I
  Test168(); //SetRecord-ISet-Sets-of-seq + SetOfSequenceRecord-I-IO-I + SequenceRecord-I-IO-IRef + SequenceRecord-I-IO-I
  Test169(); //SetRecord-ISet-Sets-of-enumerated
  Test170(); //SetRecord-ISet-Sets-of-enumerated
  Test171(); //SetRecord-ISet-Sets-of-enumerated copy constructor
  Test172(); //SetRecord-ISet-Sets-of-enumerated move constructor
  Test173(); //SetRecord-ISet-Sets-of-enumerated copy =
  Test174(); //SetRecord-ISet-Sets-of-enumerated move =
  Test175(); //SetOfSelfRec
  Test176(); //SetOfSomeSetOfRecRef+SomeSetOfRecRef+SomeSetOfRec
  Test177(); //SequenceOfInteger
  Test178(); //SetOfInteger::Erase
  Test179(); //SequenceOfInteger::Erase
  Test180(); //SequenceOfSequenceRecord-I-IO-I + SequenceRecord-I-IO-IRef + SequenceRecord-I-IO-I
  Test181(); //ChoiceRealInteger
  Test182(); //ChoiceRealInteger
  Test183(); //Choice-IChoiceRealInteger
  Test184(); //Choice-IChoiceRealInteger
  Test185(); //Choice-SeqWithThisChoice + SeqRecWithThisChoice
  Test186(); //Choice-IChoiceRealInteger copy constructor
  Test187(); //Choice-IChoiceRealInteger move constructor
  Test188(); //Choice-IChoiceRealInteger copy =
  Test189(); //Choice-IChoiceRealInteger move =
  Test190(); //Choice-IChoiceRealInteger Clear
  Test191(); //SetRecord-ISet-Sets-of-enumerated clear
  Test192(); //SetRecord-OSRef1-OSRef1O + OctetStringRef1 + OctetStringRef2 + OctetStringRef3 + OctetStringRef4 and the same SetRecord-OSRef1-OSRef1O again
  Test193(); //Choice-IChoicePS-IA5 and the same Choice-IChoicePS-IA5 again
  Test194(); //SequenceRecord-ID-I-ID-ID
  Test195(); //SequenceRecord-ID-I-ID-ID
  Test196(); //SequenceRecord-ID-I-ID-ID
  Test197(); //SequenceRecord-ID-I-ID-ID
  Test198(); //SequenceRecord-ED-E-ED-ED
  Test199(); //SequenceRecord-ED-E-ED-ED
  Test200(); //SequenceRecord-ED-E-ED-ED
}

#endif	/* TESTS101_200_HPP */

