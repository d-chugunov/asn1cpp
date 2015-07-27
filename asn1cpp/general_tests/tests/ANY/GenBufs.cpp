#include "GenBufs.hpp"
#include "ANY.h"
#include "NativeInteger.h"

const size_t DEFAULT_BUF_SIZE = 1024;

std::vector<uint8_t> Buf1() {
  uint8_t octetString[] = {0x12, 0x82, 0xa7, 0x8b, 0x97, 
                           0x90, 0xe3, 0x98, 0xfe, 0xcd};
  std::vector<uint8_t> buf(DEFAULT_BUF_SIZE);
  long rec;
  rec = 28463;
  ANY_t* any = ANY_new_fromType(&asn_DEF_NativeInteger, &rec);
  buf = std::vector<uint8_t>(any->buf, any->buf + any->size);
  return std::move(buf);
}

std::vector<std::vector<uint8_t>> GenBufs()
{
  std::vector<std::vector<uint8_t>> bufs;
  bufs.push_back(Buf1());
  return std::move(bufs);
}



