#include "GenBufs.hpp"
#include "SequenceRecord-IS-OI-OIO-OIRef-OIRefO.h"

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
  unsigned long long arcs1[] = {1, 3, 6, 1, 4, 1, 9363, 78458};
  unsigned int arcs3[] = {1, 3, 6, 1, 4, 3, 9363, 78458, 1};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_IS_OI_OIO_OIRef_OIRefO_t rec;
  memset(&rec, 0, sizeof(rec));
  OBJECT_IDENTIFIER_set_arcs(&rec.seq.objectIdentifier1, arcs1, sizeof(arcs1[0]), 
                             sizeof(arcs1) / sizeof(arcs1[0]));
  rec.seq.objectIdentifier2 = 0;
  OBJECT_IDENTIFIER_set_arcs(&rec.seq.objectIdentifier3, arcs3, sizeof(arcs3[0]), 
                             sizeof(arcs3) / sizeof(arcs3[0]));
  rec.seq.objectIdentifier4 = 0;
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_IS_OI_OIO_OIRef_OIRefO, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf1");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf2() {
  unsigned int arcs1[] = {1, 3, 6, 1, 4, 1, 9363, 78458};
  unsigned int arcs2[] = {1, 3, 6, 1, 4, 2, 9363};
  unsigned int arcs3[] = {1, 3, 6, 1, 4, 3, 9363, 78458, 1};
  unsigned int arcs4[] = {1, 3, 6, 1, 4, 4, 9363};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SequenceRecord_IS_OI_OIO_OIRef_OIRefO_t rec;
  memset(&rec, 0, sizeof(rec));
  OBJECT_IDENTIFIER_set_arcs(&rec.seq.objectIdentifier1, arcs1, sizeof(arcs1[0]), 
                             sizeof(arcs1) / sizeof(arcs1[0]));
  rec.seq.objectIdentifier2 = (OBJECT_IDENTIFIER_t*)malloc(sizeof(OBJECT_IDENTIFIER_t));
  OBJECT_IDENTIFIER_set_arcs(rec.seq.objectIdentifier2, arcs2, sizeof(arcs2[0]), 
                             sizeof(arcs2) / sizeof(arcs2[0]));
  OBJECT_IDENTIFIER_set_arcs(&rec.seq.objectIdentifier3, arcs3, sizeof(arcs3[0]), 
                             sizeof(arcs3) / sizeof(arcs3[0]));
  rec.seq.objectIdentifier4 = (ObjectIdentifierRef_t*)malloc(sizeof(ObjectIdentifierRef_t));
  OBJECT_IDENTIFIER_set_arcs(rec.seq.objectIdentifier4, arcs4, sizeof(arcs4[0]), 
                             sizeof(arcs4) / sizeof(arcs4[0]));
  printf("std::vector<uint8_t> mustBe1 = "); PrintObjectIdent(rec.seq.objectIdentifier1);
  printf("std::vector<uint8_t> mustBe2 = "); PrintObjectIdent(*rec.seq.objectIdentifier2);
  printf("std::vector<uint8_t> mustBe3 = "); PrintObjectIdent(rec.seq.objectIdentifier3);
  printf("std::vector<uint8_t> mustBe4 = "); PrintObjectIdent(*rec.seq.objectIdentifier4);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SequenceRecord_IS_OI_OIO_OIRef_OIRefO, &rec, (void*)buf.data(), buf.size());
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



