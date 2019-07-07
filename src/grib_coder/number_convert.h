#pragma once

#include <cstdint>

namespace GribCoder {

uint64_t convertBytesToUint64(unsigned char* bytes, size_t length = 4);
uint16_t convertBytesToUint16(char* bytes, size_t length = 2);
uint8_t convertBytesToUint8(char* bytes, size_t length = 1);

} // namespace GribCoder