#include "GenBufs.hpp"
#include "External.h"
#include "ExternalASN.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  External_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.direct_reference = (OBJECT_IDENTIFIER_t*)malloc(sizeof(*rec.direct_reference));
  memset(rec.direct_reference, 0, sizeof(*rec.direct_reference));
  unsigned int arcs[] = {1, 2, 3, 4, 5};
  OBJECT_IDENTIFIER_set_arcs(rec.direct_reference, arcs, sizeof(arcs[0]), sizeof(arcs) / sizeof(arcs[0]));
  
  rec.indirect_reference = new long();
  *rec.indirect_reference = 123;
  
  rec.data_value_descriptor = new ObjectDescriptor_t();
  memset(rec.data_value_descriptor, 0, sizeof(*rec.data_value_descriptor));
  const char* data_value_descriptor = "object descriptor";
  rec.data_value_descriptor->buf = (uint8_t*)data_value_descriptor;
  rec.data_value_descriptor->size = strlen(data_value_descriptor);
  
  rec.encoding.present = External__encoding_PR::External__encoding_PR_single_ASN1_type;
  GraphicString_t message;
  memset(&message, 0, sizeof(message));
  message.buf = (uint8_t*)"the content of single ASN1 type";
  message.size = strlen((const char*)message.buf);
  ANY_fromType(&rec.encoding.choice.single_ASN1_type, &asn_DEF_GraphicString, &message);
          
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_External, &rec, (void*)buf.data(), buf.size());
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
  ExternalASN_t rec;
  memset(&rec, 0, sizeof(rec));
  rec.direct_reference = (OBJECT_IDENTIFIER_t*)malloc(sizeof(*rec.direct_reference));
  memset(rec.direct_reference, 0, sizeof(*rec.direct_reference));
  unsigned int arcs[] = {1, 2, 3, 4, 5};
  OBJECT_IDENTIFIER_set_arcs(rec.direct_reference, arcs, sizeof(arcs[0]), sizeof(arcs) / sizeof(arcs[0]));
  
  rec.indirect_reference = new long();
  *rec.indirect_reference = 123;
  
  rec.data_value_descriptor = new ObjectDescriptor_t();
  memset(rec.data_value_descriptor, 0, sizeof(*rec.data_value_descriptor));
  const char* data_value_descriptor = "object descriptor";
  rec.data_value_descriptor->buf = (uint8_t*)data_value_descriptor;
  rec.data_value_descriptor->size = strlen(data_value_descriptor);
  
  rec.encoding.present = ExternalASN__encoding_PR::ExternalASN__encoding_PR_single_ASN1_type;
  GraphicString_t message;
  memset(&message, 0, sizeof(message));
  message.buf = (uint8_t*)"the content of single ASN1 type";
  message.size = strlen((const char*)message.buf);
  ANY_fromType(&rec.encoding.choice.single_ASN1_type, &asn_DEF_GraphicString, &message);
          
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_ExternalASN, &rec, (void*)buf.data(), buf.size());
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
