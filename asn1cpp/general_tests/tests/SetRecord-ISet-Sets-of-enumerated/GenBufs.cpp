#include "GenBufs.hpp"
#include "SetRecord-ISet-Sets-of-enumerated.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  long val3;
  val3 = e_SetRecord_ISet_Sets_of_enumerated__set__field3__Member::SetRecord_ISet_Sets_of_enumerated__set__field3__Member_value2;
  
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_ISet_Sets_of_enumerated_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_set_add(&rec.set.field3, &val3);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ISet_Sets_of_enumerated, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf1");
    exit(0);
  }
  return std::move(buf);
}

std::vector<uint8_t> Buf2() {
  long val3;
  val3 = e_SetRecord_ISet_Sets_of_enumerated__set__field3__Member::SetRecord_ISet_Sets_of_enumerated__set__field3__Member_value2;
  
  long val4;
  val4 = e_SetRecord_ISet_Sets_of_enumerated__set__field4__Member::SetRecord_ISet_Sets_of_enumerated__set__field4__Member_value3;
  
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  SetRecord_ISet_Sets_of_enumerated_t rec;
  memset(&rec, 0, sizeof(rec));
  asn_set_add(&rec.set.field3, &val3);
  rec.set.field4 = (struct SetRecord_ISet_Sets_of_enumerated::SetRecord_ISet_Sets_of_enumerated__set::SetRecord_ISet_Sets_of_enumerated__set__field4*)malloc(sizeof(*rec.set.field4));
  memset(rec.set.field4, 0, sizeof(*rec.set.field4));
  asn_set_add(rec.set.field4, &val4);
  asn_enc_rval_t rval;
  rval = der_encode_to_buffer(&asn_DEF_SetRecord_ISet_Sets_of_enumerated, &rec, (void*)buf.data(), buf.size());
  if (rval.encoded >= 0) {
    buf.resize(rval.encoded);
  } else {
    printf("cannot encode record in Buf2");
    exit(0);
  }
  return std::move(buf);
}

std::vector<std::vector<uint8_t>> GenBufs() {
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(std::move(Buf1()));
  bufs.push_back(std::move(Buf2()));
  return std::move(bufs);
}