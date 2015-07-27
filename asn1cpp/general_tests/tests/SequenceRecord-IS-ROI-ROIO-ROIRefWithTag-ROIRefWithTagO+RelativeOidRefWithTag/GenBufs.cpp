#include "GenBufs.hpp"
#include "SequenceRecord-IS-ROI-ROIO-ROIRefWithTag-ROIRefWithTagO.h"

const size_t DEFAULT_BUF_SIZE = 1024;

void PrintObjectIdent(const OBJECT_IDENTIFIER_t& objectIdent) {
  printf("{");
  for (int i = 0; i < objectIdent.size; ++i) {
    printf("0x%.2x", objectIdent.buf[i]);
    if (i + 1 != objectIdent.size)
      printf(", ");
  }
  printf("};\n");
}

std::vector<uint8_t> Buf1() {
  unsigned long long arcs1[] = {9363, 78458, 1, 3, 6, 1, 4, 1};
  unsigned int arcs3[] = {9363, 78458, 1, 1, 3, 6, 1, 4, 3};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_IS_ROI_ROIO_ROIRefWithTag_ROIRefWithTagO_t rec;
  memset(&rec, 0, sizeof(rec));
  RELATIVE_OID_set_arcs(&rec.seq.relativeOid1, arcs1, sizeof(arcs1[0]), 
                             sizeof(arcs1) / sizeof(arcs1[0]));
  rec.seq.relativeOid2 = 0;
  RELATIVE_OID_set_arcs(&rec.seq.relativeOid3, arcs3, sizeof(arcs3[0]), 
                             sizeof(arcs3) / sizeof(arcs3[0]));
  rec.seq.relativeOid4 = 0;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_IS_ROI_ROIO_ROIRefWithTag_ROIRefWithTagO, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf1");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf2() {
  unsigned int arcs1[] = {9363, 78458, 1, 3, 6, 1, 4, 1};
  unsigned int arcs2[] = {9363, 1, 3, 6, 1, 4, 2};
  unsigned int arcs3[] = {9363, 78458, 1, 1, 3, 6, 1, 4, 3};
  unsigned int arcs4[] = {9363, 1, 3, 6, 1, 4, 4};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_IS_ROI_ROIO_ROIRefWithTag_ROIRefWithTagO_t rec;
  memset(&rec, 0, sizeof(rec));
  RELATIVE_OID_set_arcs(&rec.seq.relativeOid1, arcs1, sizeof(arcs1[0]), 
                             sizeof(arcs1) / sizeof(arcs1[0]));
  rec.seq.relativeOid2 = (RELATIVE_OID_t*)malloc(sizeof(RELATIVE_OID_t));
  RELATIVE_OID_set_arcs(rec.seq.relativeOid2, arcs2, sizeof(arcs2[0]), 
                             sizeof(arcs2) / sizeof(arcs2[0]));
  RELATIVE_OID_set_arcs(&rec.seq.relativeOid3, arcs3, sizeof(arcs3[0]), 
                             sizeof(arcs3) / sizeof(arcs3[0]));
  rec.seq.relativeOid4 = (RelativeOidRefWithTag_t*)malloc(sizeof(RelativeOidRefWithTag_t));
  RELATIVE_OID_set_arcs(rec.seq.relativeOid4, arcs4, sizeof(arcs4[0]), 
                             sizeof(arcs4) / sizeof(arcs4[0]));
  printf("std::vector<uint8_t> mustBe1 = "); PrintObjectIdent(rec.seq.relativeOid1);
  printf("std::vector<uint8_t> mustBe2 = "); PrintObjectIdent(*rec.seq.relativeOid2);
  printf("std::vector<uint8_t> mustBe3 = "); PrintObjectIdent(rec.seq.relativeOid3);
  printf("std::vector<uint8_t> mustBe4 = "); PrintObjectIdent(*rec.seq.relativeOid4);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_IS_ROI_ROIO_ROIRefWithTag_ROIRefWithTagO, &rec, (void*)buf.data(), buf.size());
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



