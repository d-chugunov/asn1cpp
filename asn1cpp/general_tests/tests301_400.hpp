#ifndef TESTS301_400_HPP
#define	TESTS301_400_HPP

#include "headers.hpp"

void Test301() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test302() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test303() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test304() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test305() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test306() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test307() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test308() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test309() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test310() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test311() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test312() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test313() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test314() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test315() {
  std::vector<uint8_t> mustBe1 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  std::vector<uint8_t> mustBe2 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x32};
  std::vector<uint8_t> mustBe3 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x33};
  std::vector<uint8_t> mustBe4 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x34};

  
  std::vector<uint8_t> test = {0x30, 0x15, 0x30, 0x13, 0x1c, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x33};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_UniS_UniSO_UniSRefWithTag_UniSRefWithTagO rec;
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

void Test316() {
  std::vector<uint8_t> mustBe1 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x31};
  std::vector<uint8_t> mustBe2 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x32};
  std::vector<uint8_t> mustBe3 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x33};
  std::vector<uint8_t> mustBe4 = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x34};
  
  std::vector<uint8_t> test = {0x30, 0x28, 0x30, 0x26, 0x1c, 0x07, 0x73, 0x74, 0x72, 0x69, 
                    0x6e, 0x67, 0x31, 0x81, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x32, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x33, 0x9f, 0x32, 0x07, 0x73, 0x74, 0x72, 0x69, 0x6e, 
                    0x67, 0x34};
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test317() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test318() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test319() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test320() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test321() {
  std::vector<uint8_t> test = {0x80, 0x03, 0x13, 0xa5, 0xbc};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  IntegerRefWithTag rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == 1287612);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test322() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test323() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test324() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test325() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test326() {
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
  std::vector<uint8_t> bufferEnc; 
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test327() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test328() {
  std::vector<uint8_t> test = {0x31, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISetO_I_IO_I rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(!rec.set
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test329() {
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
               rec.ref1.set->type3 == 92367624 &&
          !rec.ref2 &&
          
              rec.ref3.set &&
              rec.ref3.set->type == 123 && 
               !rec.ref3.set->type2 && 
               rec.ref3.set->type3 == 92367624 &&
          !rec.ref4 
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test330() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test331() {
  std::vector<uint8_t> mustBe1 = {0x37, 0x84, 0x73, 0x91, 0x23};
  std::vector<uint8_t> test = {0x31, 0x08, 0x9f, 0x32, 0x05, 0x37, 0x84, 0x73, 0x91, 0x23};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_OSRef1_OSRef1O rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.ref1 == mustBe1 &&
          !rec.ref2
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test332() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test333() {
  std::vector<uint8_t> test = {0x31, 0x07, 0x81, 0x02, 0x03, 0x78, 0x82, 0x01, 0x00};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ID_I_ID_ID rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(!rec.val1 && 
                rec.val2 == 888 && 
                rec.val3 == 0 &&
                !rec.val4 
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test334() {
  std::vector<uint8_t> test = {0x31, 0x0f, 0x80, 0x01, 0x6f, 0x81, 0x02, 0x03, 0x78, 0x82, 
                    0x02, 0x02, 0x9a, 0x83, 0x02, 0x00, 0xde};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ID_I_ID_ID rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.val1 && *rec.val1 == 111 &&
                rec.val2 == 888 && 
                rec.val3 == 666 &&
          rec.val4 && *rec.val4 == 222 
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test335() {
  std::vector<uint8_t> test = {0x30, 0x07, 0x81, 0x02, 0x03, 0x78, 0x82, 0x01, 0x00};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ID_I_ID_ID rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(!rec.val1 && 
                rec.val2 == 888 && 
                rec.val3 == 0 &&
          !rec.val4
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test336() {
  std::vector<uint8_t> test = {0x30, 0x0f, 0x80, 0x01, 0x6f, 0x81, 0x02, 0x03, 0x78, 0x82, 
                    0x02, 0x02, 0x9a, 0x83, 0x02, 0x00, 0xde};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_ID_I_ID_ID rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.val1 && *rec.val1 == 111 &&
                rec.val2 == 888 && 
                rec.val3 == 666 &&
          rec.val4 && *rec.val4 == 222
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test337() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test338() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test339() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test340() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test341() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test342() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test343() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test344() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test345() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test346() {
  std::vector<uint8_t> test = {0x31, 0x05, 0x31, 0x03, 0x01, 0x01, 0xff};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_CO_R_I_B rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec.set.boolean == 0xFF &&
          !rec.set.choice
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test347() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test348() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test349() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test350() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test351() {
  std::vector<uint8_t> test = {0x30, 0x05, 0x30, 0x03, 0x01, 0x01, 0xff};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_IS_CO_R_I_B rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(
          rec.set.boolean == 0xFF &&
          !rec.set.choice
  );
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test352() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test353() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test354() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test355() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test356() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test357() {
  std::vector<uint8_t> mustBe = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                                 0x90, 0xe3, 0x98, 0xfe, 0xcd};
  std::vector<uint8_t> test = {0x04, 0x0a, 0x12, 0x82, 0xa7, 0x8b, 0x97, 0x90, 0xe3, 0x98, 
                    0xfe, 0xcd};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OctetStringRef rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe);
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test358() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test359() {
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
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test360() {
  uint8_t test[] = {0x30, 0x12, 0x30, 0x10, 0x30, 0x06, 0x8a, 0x01, 0x01, 0x8c, 
                    0x01, 0x0a, 0x30, 0x06, 0x8a, 0x01, 0x02, 0x8c, 0x01, 0x14};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I rec2(rec1);
  CHECK_RESULT(rec1.sequenceRecord_I_IO_I.size() == 2 && 
              rec1.sequenceRecord_I_IO_I[0].type == 1 && 
              !rec1.sequenceRecord_I_IO_I[0].type2 && 
              rec1.sequenceRecord_I_IO_I[0].type3 == 10 &&
              rec1.sequenceRecord_I_IO_I[1].type == 2 && 
              !rec1.sequenceRecord_I_IO_I[1].type2 && 
              rec1.sequenceRecord_I_IO_I[1].type3 == 20 &&
          
          rec2.sequenceRecord_I_IO_I.size() == 2 && 
              rec2.sequenceRecord_I_IO_I[0].type == 1 && 
              !rec2.sequenceRecord_I_IO_I[0].type2 && 
              rec2.sequenceRecord_I_IO_I[0].type3 == 10 &&
              rec2.sequenceRecord_I_IO_I[1].type == 2 && 
              !rec2.sequenceRecord_I_IO_I[1].type2 && 
              rec2.sequenceRecord_I_IO_I[1].type3 == 20
  );
}

void Test361() {
  uint8_t test[] = {0x30, 0x12, 0x30, 0x10, 0x30, 0x06, 0x8a, 0x01, 0x01, 0x8c, 
                    0x01, 0x0a, 0x30, 0x06, 0x8a, 0x01, 0x02, 0x8c, 0x01, 0x14};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I rec2(std::move(rec1));
  CHECK_RESULT(rec1.sequenceRecord_I_IO_I.size() == 0 &&
          
          rec2.sequenceRecord_I_IO_I.size() == 2 && 
              rec2.sequenceRecord_I_IO_I[0].type == 1 && 
              !rec2.sequenceRecord_I_IO_I[0].type2 && 
              rec2.sequenceRecord_I_IO_I[0].type3 == 10 &&
              rec2.sequenceRecord_I_IO_I[1].type == 2 && 
              !rec2.sequenceRecord_I_IO_I[1].type2 && 
              rec2.sequenceRecord_I_IO_I[1].type3 == 20
  );
}

void Test362() {
  uint8_t test[] = {0x30, 0x12, 0x30, 0x10, 0x30, 0x06, 0x8a, 0x01, 0x01, 0x8c, 
                    0x01, 0x0a, 0x30, 0x06, 0x8a, 0x01, 0x02, 0x8c, 0x01, 0x14};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I rec2;
  rec2 = rec1;
  CHECK_RESULT(rec1.sequenceRecord_I_IO_I.size() == 2 && 
              rec1.sequenceRecord_I_IO_I[0].type == 1 && 
              !rec1.sequenceRecord_I_IO_I[0].type2 && 
              rec1.sequenceRecord_I_IO_I[0].type3 == 10 &&
              rec1.sequenceRecord_I_IO_I[1].type == 2 && 
              !rec1.sequenceRecord_I_IO_I[1].type2 && 
              rec1.sequenceRecord_I_IO_I[1].type3 == 20 &&
          
          rec2.sequenceRecord_I_IO_I.size() == 2 && 
              rec2.sequenceRecord_I_IO_I[0].type == 1 && 
              !rec2.sequenceRecord_I_IO_I[0].type2 && 
              rec2.sequenceRecord_I_IO_I[0].type3 == 10 &&
              rec2.sequenceRecord_I_IO_I[1].type == 2 && 
              !rec2.sequenceRecord_I_IO_I[1].type2 && 
              rec2.sequenceRecord_I_IO_I[1].type3 == 20
  );
}

void Test363() {
  uint8_t test[] = {0x30, 0x12, 0x30, 0x10, 0x30, 0x06, 0x8a, 0x01, 0x01, 0x8c, 
                    0x01, 0x0a, 0x30, 0x06, 0x8a, 0x01, 0x02, 0x8c, 0x01, 0x14};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I rec1;
  ret = rec1.DecodeBer(test, sizeof(test));
  SequenceRecord_SeqOfSeqRec_SeqRec_I_IO_I rec2;
  rec2 = std::move(rec1);
  CHECK_RESULT(rec1.sequenceRecord_I_IO_I.size() == 0 &&
          
          rec2.sequenceRecord_I_IO_I.size() == 2 && 
              rec2.sequenceRecord_I_IO_I[0].type == 1 && 
              !rec2.sequenceRecord_I_IO_I[0].type2 && 
              rec2.sequenceRecord_I_IO_I[0].type3 == 10 &&
              rec2.sequenceRecord_I_IO_I[1].type == 2 && 
              !rec2.sequenceRecord_I_IO_I[1].type2 && 
              rec2.sequenceRecord_I_IO_I[1].type3 == 20
  );
}

void Test364() {
  uint8_t test[] = {0x31, 0x16, 0x31, 0x14, 0xa1, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0x01, 0x8c, 0x01, 0x03, 0xa3, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0xff, 0x8c, 0x01, 0xfd};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Seqs_of_seq rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.set.field1.size() == 1 && 
                  !rec.set.field2 &&
                  rec.set.field3.size() == 1 &&
                !rec.set.field4);
  SequenceRecord_I_IO_IRef rec1(rec.set.field1[0]);
  SetRecord_ISet_Seqs_of_seq::set::_field3 rec3(rec.set.field3[0]);
  CHECK_RESULT(rec1.type == 1 && 
              !rec1.type2 && 
              rec1.type3 == 3 &&
          
          rec3.type == -1 &&
          !rec3.type2 &&
          rec3.type3 == -3
  );
}

void Test365() {
  uint8_t test[] = {0x31, 0x2a, 0x31, 0x28, 0xa1, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0x01, 0x8c, 0x01, 0x03, 0xa2, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0x0a, 0x8c, 0x01, 0x1e, 0xa3, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0xff, 0x8c, 0x01, 0xfd, 0xa4, 0x08, 0x30, 0x06, 0x8a, 0x01, 
                    0xf6, 0x8c, 0x01, 0xe2};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  SetRecord_ISet_Seqs_of_seq rec;
  ret = rec.DecodeBer(test, sizeof(test));
  INTERMEDIATE_CHECK(rec.set.field1.size() == 1 && 
                  rec.set.field2 &&
                  rec.set.field2->size() == 1 &&
                  rec.set.field3.size() == 1 &&
                rec.set.field4 && 
                rec.set.field4->size() == 1);
  SequenceRecord_I_IO_IRef rec1(rec.set.field1[0]);
  SequenceRecord_I_IO_IRef rec2((*rec.set.field2)[0]);
  SetRecord_ISet_Seqs_of_seq::set::_field3 rec3(rec.set.field3[0]);
  SetRecord_ISet_Seqs_of_seq::set::_field4 rec4((*rec.set.field4)[0]);
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

void Test366() {
  std::vector<uint8_t> mustBe = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
  uint8_t test[] = {0x24, 0x0c, 0x04, 0x04, 0x01, 0x23, 0x45, 0x67, 0x04, 0x04, 0x89, 0xab, 0xcd, 0xef};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec;
  ret = rec.DecodeBer(test, sizeof(test));
  CHECK_RESULT(rec == mustBe);
}

void Test367() {
  std::vector<uint8_t> mustBe = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
  uint8_t test[] = {0x24, 0x0c, 0x04, 0x04, 0x01, 0x23, 0x45, 0x67, 0x04, 0x04, 0x89, 0xab, 0xcd, 0xef};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  OCTET_STRING rec2(rec1);
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test368() {
  std::vector<uint8_t> mustBe = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
  uint8_t test[] = {0x24, 0x0c, 0x04, 0x04, 0x01, 0x23, 0x45, 0x67, 0x04, 0x04, 0x89, 0xab, 0xcd, 0xef};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  OCTET_STRING rec2(std::move(rec1));
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test369() {
  std::vector<uint8_t> mustBe = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
  uint8_t test[] = {0x24, 0x0c, 0x04, 0x04, 0x01, 0x23, 0x45, 0x67, 0x04, 0x04, 0x89, 0xab, 0xcd, 0xef};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  OCTET_STRING rec2;
  rec2 = rec1;
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test370() {
  std::vector<uint8_t> mustBe = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
  uint8_t test[] = {0x24, 0x0c, 0x04, 0x04, 0x01, 0x23, 0x45, 0x67, 0x04, 0x04, 0x89, 0xab, 0xcd, 0xef};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  OCTET_STRING rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  OCTET_STRING rec2;
  rec2 = std::move(rec1);
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test371() {
  std::vector<uint8_t> mustBe = {0x6e, 0x5d, 0xc0};
  uint8_t test[] = {0x23, 0x09, 0x03, 0x03, 0x00, 0x6e, 0x5d, 0x03, 0x02, 0x06, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  BIT_STRING rec2(rec1);
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe && rec2.GetBitsUnused() == 6);
}

void Test372() {
  std::vector<uint8_t> mustBe = {0x6e, 0x5d, 0xc0};
  uint8_t test[] = {0x23, 0x09, 0x03, 0x03, 0x00, 0x6e, 0x5d, 0x03, 0x02, 0x06, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  BIT_STRING rec2(std::move(rec1));
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe && rec2.GetBitsUnused() == 6);
}

void Test373() {
  std::vector<uint8_t> mustBe = {0x6e, 0x5d, 0xc0};
  uint8_t test[] = {0x23, 0x09, 0x03, 0x03, 0x00, 0x6e, 0x5d, 0x03, 0x02, 0x06, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  BIT_STRING rec2;
  rec2 = rec1;
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe && rec2.GetBitsUnused() == 6);
}

void Test374() {
  std::vector<uint8_t> mustBe = {0x6e, 0x5d, 0xc0};
  uint8_t test[] = {0x23, 0x09, 0x03, 0x03, 0x00, 0x6e, 0x5d, 0x03, 0x02, 0x06, 0xc0};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  BIT_STRING rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  BIT_STRING rec2;
  rec2 = std::move(rec1);
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe && rec2.GetBitsUnused() == 6);
}

void Test375() {
  std::string mustBe = "test1@rsa.com";
  uint8_t test[] = {0x36, 0x13, 0x16, 0x05, 0x74, 0x65, 0x73, 0x74, 0x31, 0x16, 
                    0x01, 0x40, 0x16, 0x07, 0x72, 0x73, 0x61, 0x2e, 0x63, 0x6f, 0x6d};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  IA5String rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  IA5String rec2(rec1);
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test376() {
  std::string mustBe = "test1@rsa.com";
  uint8_t test[] = {0x36, 0x13, 0x16, 0x05, 0x74, 0x65, 0x73, 0x74, 0x31, 0x16, 
                    0x01, 0x40, 0x16, 0x07, 0x72, 0x73, 0x61, 0x2e, 0x63, 0x6f, 0x6d};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  IA5String rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  IA5String rec2(std::move(rec1));
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test377() {
  std::string mustBe = "test1@rsa.com";
  uint8_t test[] = {0x36, 0x13, 0x16, 0x05, 0x74, 0x65, 0x73, 0x74, 0x31, 0x16, 
                    0x01, 0x40, 0x16, 0x07, 0x72, 0x73, 0x61, 0x2e, 0x63, 0x6f, 0x6d};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  IA5String rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  IA5String rec2;
  rec2 = rec1;
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test378() {
  std::string mustBe = "test1@rsa.com";
  uint8_t test[] = {0x36, 0x13, 0x16, 0x05, 0x74, 0x65, 0x73, 0x74, 0x31, 0x16, 
                    0x01, 0x40, 0x16, 0x07, 0x72, 0x73, 0x61, 0x2e, 0x63, 0x6f, 0x6d};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  IA5String rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  IA5String rec2;
  rec2 = std::move(rec1);
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test379() {
  std::string mustBe = "Test User 1";
  uint8_t test[] = {0x33, 0x0f, 0x13, 0x05, 0x54, 0x65, 0x73, 0x74, 0x20, 0x13, 
                    0x06, 0x55, 0x73, 0x65, 0x72, 0x20, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  PrintableString rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  PrintableString rec2(rec1);
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test380() {
  std::string mustBe = "Test User 1";
  uint8_t test[] = {0x33, 0x0f, 0x13, 0x05, 0x54, 0x65, 0x73, 0x74, 0x20, 0x13, 
                    0x06, 0x55, 0x73, 0x65, 0x72, 0x20, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  PrintableString rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  PrintableString rec2(std::move(rec1));
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test381() {
  std::string mustBe = "Test User 1";
  uint8_t test[] = {0x33, 0x0f, 0x13, 0x05, 0x54, 0x65, 0x73, 0x74, 0x20, 0x13, 
                    0x06, 0x55, 0x73, 0x65, 0x72, 0x20, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  PrintableString rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  PrintableString rec2;
  rec2 = rec1;
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test382() {
  std::string mustBe = "Test User 1";
  uint8_t test[] = {0x33, 0x0f, 0x13, 0x05, 0x54, 0x65, 0x73, 0x74, 0x20, 0x13, 
                    0x06, 0x55, 0x73, 0x65, 0x72, 0x20, 0x31};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  PrintableString rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  PrintableString rec2;
  rec2 = std::move(rec1);
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test383() {
  std::string mustBe = std::string("cl") + (char)0xc2 + "es publiques";
  uint8_t test[] = {0x34, 0x15, 0x14, 0x05, 0x63, 0x6c, 0xc2, 0x65, 0x73, 0x14, 
                    0x01, 0x20, 0x14, 0x09, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x71, 
                    0x75, 0x65, 0x73};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  T61String rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  T61String rec2(rec1);
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test384() {
  std::string mustBe = std::string("cl") + (char)0xc2 + "es publiques";
  uint8_t test[] = {0x34, 0x15, 0x14, 0x05, 0x63, 0x6c, 0xc2, 0x65, 0x73, 0x14, 
                    0x01, 0x20, 0x14, 0x09, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x71, 
                    0x75, 0x65, 0x73};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  T61String rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  T61String rec2(std::move(rec1));
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test385() {
  std::string mustBe = std::string("cl") + (char)0xc2 + "es publiques";
  uint8_t test[] = {0x34, 0x15, 0x14, 0x05, 0x63, 0x6c, 0xc2, 0x65, 0x73, 0x14, 
                    0x01, 0x20, 0x14, 0x09, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x71, 
                    0x75, 0x65, 0x73};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  T61String rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  T61String rec2;
  rec2 = rec1;
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test386() {
  std::string mustBe = std::string("cl") + (char)0xc2 + "es publiques";
  uint8_t test[] = {0x34, 0x15, 0x14, 0x05, 0x63, 0x6c, 0xc2, 0x65, 0x73, 0x14, 
                    0x01, 0x20, 0x14, 0x09, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x71, 
                    0x75, 0x65, 0x73};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  T61String rec1;
  ret = rec1.DecodeBer(test, sizeof(test) / 2);
  INTERMEDIATE_COND(ret.code = RC_WMORE);
  T61String rec2;
  rec2 = std::move(rec1);
  ret = rec2.DecodeBer(test + ret.consumed, sizeof(test) - ret.consumed);
  CHECK_RESULT(rec2 == mustBe);
}

void Test387() {
  std::vector<uint8_t> test = {0x02, 0x04, 0x31, 0xF0, 0x2D, 0x82};
  TEST_NUMBER
  NativeInteger rec;
  asn_dec_rval_t ret;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == 837823874);
  CHECK_OUT("837823874");
}

void Test388() {
  std::vector<uint8_t> test = {0x02, 0x04, 0xfb, 0x9c, 0x80, 0xdf};
  TEST_NUMBER
  NativeInteger rec;
  asn_dec_rval_t ret;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == -73629473);
  CHECK_OUT("-73629473");
}

void Test389() {
  std::vector<uint8_t> test = {0x02, 0x05, 0x00, 0x80, 0x00, 0x00, 0x00};
  std::vector<uint8_t> mustBe = {0x00, 0x80, 0x00, 0x00, 0x00};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  UnsignedNativeIntegerTest rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == 2147483648);
  
  {
    INTEGER rec2;
    rec2.FromULong(2147483648);
    INTERMEDIATE_CHECK(rec2 == mustBe);
  }
  
  std::vector<uint8_t> bufferEnc;
  asn_enc_rval_t enc = rec.EncodeDer(bufferEnc);
  CHECK_RESULT_ENCODING(bufferEnc == test);
}

void Test390() {
  std::vector<uint8_t> test = {0x0a, 0x04, 0x31, 0xF0, 0x2D, 0x82};
  TEST_NUMBER
  NativeEnumerated rec;
  asn_dec_rval_t ret;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == 837823874);
  CHECK_OUT("837823874");
}

void Test391() {
  std::vector<uint8_t> test = {0x0a, 0x04, 0xfb, 0x9c, 0x80, 0xdf};
  TEST_NUMBER
  NativeEnumerated rec;
  asn_dec_rval_t ret;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == -73629473)
  CHECK_OUT("-73629473");
}

void Test392() {
  std::vector<uint8_t> test = {0x09, 0x09, 0x80, 0xe4, 0x0c, 0x60, 0x2a, 0xc1, 0xf7, 0xce, 
                    0xd9};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  NativeReal rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == 12976812.123);
  CHECK_OUT("12976812.122999999672174");
}

void Test393() {
  std::vector<uint8_t> test = {0x09, 0x09, 0xc0, 0xed, 0x11, 0x45, 0xa6, 0x95, 0x7e, 0xfb, 
                    0xe7};
  TEST_NUMBER;
  asn_dec_rval_t ret;
  NativeReal rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == -9272873647.873);
  CHECK_OUT("-9272873647.87299919128418");
}

void Test394() {
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
  CHECK_OUT("837823874");
}

void Test395() {
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
  CHECK_OUT("-73629473");
}

void Test396() {
  std::vector<uint8_t> mustBe = {0x31, 0xf0, 0x2d, 0x82, 0x84, 0x12, 0x83, 0x74, 0x34, 0x98};
  std::vector<uint8_t> test = {0x02, 0x0a, 0x31, 0xf0, 0x2d, 0x82, 0x84, 0x12, 0x83, 0x74, 0x34, 0x98};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  INTEGER rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe);
  CHECK_OUT("31:F0:2D:82:84:12:83:74:34:98");
}

void Test397() {
  std::vector<uint8_t> mustBe = {0x31, 0xf0, 0x2d, 0x82};
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
  CHECK_OUT("837823874");
}

void Test398() {
  std::vector<uint8_t> mustBe = {0xfb, 0x9c, 0x80, 0xdf};
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
  CHECK_OUT("-73629473");
}

void Test399() {
  std::vector<uint8_t> mustBe = {0x31, 0xf0, 0x2d, 0x82, 0x84, 0x12, 0x83, 0x74, 0x34, 0x98};
  std::vector<uint8_t> test = {0x0a, 0x0a, 0x31, 0xf0, 0x2d, 0x82, 0x84, 0x12, 0x83, 0x74, 0x34, 0x98};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  ENUMERATED rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe);
  CHECK_OUT("31:F0:2D:82:84:12:83:74:34:98");
}

void Test400() {
  std::vector<uint8_t> mustBe = {0x80, 0xea, 0x0c, 0x7c, 0x0b, 0x60, 0xb6, 0xd5, 0x3d};
  std::vector<uint8_t> test = {0x09, 0x09, 0x80, 0xea, 0x0c, 0x7c, 0x0b, 0x60, 0xb6, 0xd5, 0x3d};
  
  TEST_NUMBER;
  asn_dec_rval_t ret;
  double d;
  REAL rec;
  ret = rec.DecodeBer(test);
  INTERMEDIATE_CHECK(rec == mustBe && rec.ToDouble(d) && d == 837823874.856765
  );
  CHECK_OUT("837823874.856765031814575");
}

void Tests301_400() {
  Test301(); //SequenceRecord-IS-ObjD-ObjDO-ObjDRefWithTag-ObjDRefWithTagO::EncodeDer
  Test302(); //SequenceRecord-IS-ObjD-ObjDO-ObjDRefWithTag-ObjDRefWithTagO::EncodeDer
  Test303(); //SequenceRecord-IS-PriS-PriSO-PriSRefWithTag-PriSRefWithTagO::EncodeDer
  Test304(); //SequenceRecord-IS-PriS-PriSO-PriSRefWithTag-PriSRefWithTagO::EncodeDer
  Test305(); //SequenceRecord-IS-ROI-ROIO-ROIRefWithTag-ROIRefWithTagO::EncodeDer
  Test306(); //SequenceRecord-IS-ROI-ROIO-ROIRefWithTag-ROIRefWithTagO::EncodeDer
  Test307(); //SequenceRecord-IS-T61S-T61SO-T61SRefWithTag-T61SRefWithTagO::EncodeDer
  Test308(); //SequenceRecord-IS-T61S-T61SO-T61SRefWithTag-T61SRefWithTagO::EncodeDer
  Test309(); //SequenceRecord-IS-TeleS-TeleSO-TeleSRefWithTag-TeleSRefWithTagO::EncodeDer
  Test310(); //SequenceRecord-IS-TeleS-TeleSO-TeleSRefWithTag-TeleSRefWithTagO::EncodeDer
  Test311(); //SequenceRecord-IS-UT-UTO-UTRefWithTag-UTRefWithTagO::EncodeDer
  Test312(); //SequenceRecord-IS-UT-UTO-UTRefWithTag-UTRefWithTagO::EncodeDer
  Test313(); //SequenceRecord-IS-UTF8S-UTF8SO-UTF8SRefWithTag-UTF8SRefWithTagO::EncodeDer
  Test314(); //SequenceRecord-IS-UTF8S-UTF8SO-UTF8SRefWithTag-UTF8SRefWithTagO::EncodeDer
  Test315(); //SequenceRecord-IS-UniS-UniSO-UniSRefWithTag-UniSRefWithTagO::EncodeDer
  Test316(); //SequenceRecord-IS-UniS-UniSO-UniSRefWithTag-UniSRefWithTagO::EncodeDer
  Test317(); //SequenceRecord-IS-VidS-VidSO-VidSRefWithTag-VidSRefWithTagO::EncodeDer
  Test318(); //SequenceRecord-IS-VidS-VidSO-VidSRefWithTag-VidSRefWithTagO::EncodeDer
  Test319(); //SequenceRecord-IS-VisS-VisSO-VisSRefWithTag-VisSRefWithTagO::EncodeDer
  Test320(); //SequenceRecord-IS-VisS-VisSO-VisSRefWithTag-VisSRefWithTagO::EncodeDer
  Test321(); //IntegerRefWithTag::EncodeDer
  Test322(); //SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO::EncodeDer
  Test323(); //SequenceRecord-IS-GT-GTO-GTRefWithTag-GTRefWithTagO::EncodeDer
  Test324(); //SetRecord-I-IO-I::EncodeDer
  Test325(); //SetRecord-I-IO-I::EncodeDer
  Test326(); //SetRecord-ISetO-I-IO-I::EncodeDer
  Test327(); //SetRecord-ISetO-I-IO-I::EncodeDer
  Test328(); //SetRecord-ISetO-I-IO-I::EncodeDer
  Test329(); //SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO::EncodeDer
  Test330(); //SetRecord_SeRef_SeRefO_SeDirRef_SeDirRefO::EncodeDer
  Test331(); //SetRecord-OSRef1-OSRef1O::EncodeDer
  Test332(); //SetRecord-OSRef1-OSRef1O::EncodeDer
  Test333(); //SetRecord-ID-I-ID-ID::EncodeDer
  Test334(); //SetRecord-ID-I-ID-ID::EncodeDer
  Test335(); //SequenceRecord-ID-I-ID-ID::EncodeDer
  Test336(); //SequenceRecord-ID-I-ID-ID::EncodeDer
  Test337(); //ChoiceRealInteger::EncodeDer
  Test338(); //ChoiceRealInteger::EncodeDer
  Test339(); //Choice-IChoiceRealInteger::EncodeDer
  Test340(); //Choice-IChoiceRealInteger::EncodeDer
  Test341(); //SeqRecWithThisChoice::EncodeDer
  Test342(); //SetRecord-ISet-C-R-I-B::EncodeDer
  Test343(); //SetRecord-ISet-C-R-I-B::EncodeDer
  Test344(); //SetRecord-ISet-CO-R-I-B::EncodeDer
  Test345(); //SetRecord-ISet-CO-R-I-B::EncodeDer
  Test346(); //SetRecord-ISet-CO-R-I-B::EncodeDer
  Test347(); //SequenceRecord-IS-C-R-I-B::EncodeDer
  Test348(); //SequenceRecord-IS-C-R-I-B::EncodeDer
  Test349(); //SequenceRecord-IS-CO-R-I-B::EncodeDer
  Test350(); //SequenceRecord-IS-CO-R-I-B::EncodeDer
  Test351(); //SequenceRecord-IS-CO-R-I-B::EncodeDer
  Test352(); //SetOfInteger::EncodeDer
  Test353(); //SetOfSequenceRecord-I-IO-I + SequenceRecord-I-IO-IRef + SequenceRecord-I-IO-I::EncodeDer
  Test354(); //SequenceOfInteger::EncodeDer
  Test355(); //SequenceOfSequenceRecord-I-IO-I + SequenceRecord-I-IO-IRef + SequenceRecord-I-IO-I::EncodeDer
  Test356(); //SequenceRecord-SeqOfSeqRec-SeqRec-I-IO-I + SequenceRecord-I-IO-I::EncodeDer
  Test357(); //OctetStringRef::EncodeDer
  Test358(); //Choice-IChoiceRealInteger::EncodeDer
  Test359(); //Choice-IChoiceRealInteger::EncodeDer
  Test360(); //SequenceRecord-SeqOfSeqRec-SeqRec-I-IO-I copy constructor
  Test361(); //SequenceRecord-SeqOfSeqRec-SeqRec-I-IO-I move constructor
  Test362(); //SequenceRecord-SeqOfSeqRec-SeqRec-I-IO-I copy =
  Test363(); //SequenceRecord-SeqOfSeqRec-SeqRec-I-IO-I move =
  Test364(); //SetRecord-ISet-Seqs-of-seq + SeqOfSequenceRecord-I-IO-I + SequenceRecord-I-IO-IRef + SequenceRecord-I-IO-I
  Test365(); //SetRecord-ISet-Seqs-of-seq + SeqOfSequenceRecord-I-IO-I + SequenceRecord-I-IO-IRef + SequenceRecord-I-IO-I
  Test366(); //OCTET STRING constructed decoding
  Test367(); //OCTET STRING copy ctx in constructor
  Test368(); //OCTET STRING move ctx in constructor
  Test369(); //OCTET STRING copy ctx in =
  Test370(); //OCTET STRING move ctx in =
  Test371(); //BIT STRING copy ctx in constructor
  Test372(); //BIT STRING move ctx in constructor
  Test373(); //BIT STRING copy ctx in =
  Test374(); //BIT STRING move ctx in =
  Test375(); //IA5String copy ctx in constructor
  Test376(); //IA5String move ctx in constructor
  Test377(); //IA5String copy ctx in =
  Test378(); //IA5String move ctx in =
  Test379(); //PrintableString copy ctx in constructor
  Test380(); //PrintableString move ctx in constructor
  Test381(); //PrintableString copy ctx in =
  Test382(); //PrintableString move ctx in =
  Test383(); //T61String copy ctx in constructor
  Test384(); //T61String move ctx in constructor
  Test385(); //T61String copy ctx in =
  Test386(); //T61String move ctx in =
  Test387(); //NativeInteger print
  Test388(); //NativeInteger print
  Test389(); //UnsignedNativeIntegerTest::EncodeDer
  Test390(); //NativeEnumerated print
  Test391(); //NativeEnumerated print
  Test392(); //NativeReal print
  Test393(); //NativeReal print
  Test394(); //INTEGER print
  Test395(); //INTEGER print
  Test396(); //INTEGER print
  Test397(); //ENUMERATED print
  Test398(); //ENUMERATED print
  Test399(); //ENUMEREATED print
  Test400(); //REAL print
}

#endif	/* TESTS301_400_HPP */

