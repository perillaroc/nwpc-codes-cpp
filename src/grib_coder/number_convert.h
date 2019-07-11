#pragma once

#include <cstdint>

namespace GribCoder {

uint64_t convertBytesToUint64(unsigned char* bytes, size_t length = 8);

uint32_t convertBytesToUint32(unsigned char* bytes, size_t length = 4);
int32_t convertBytesToInt32(unsigned char* bytes, size_t length = 4);

uint16_t convertBytesToUint16(unsigned char* bytes, size_t length = 2);
int16_t convertBytesToInt16(unsigned char* bytes, size_t length = 2);

uint8_t convertBytesToUint8(unsigned char* bytes, size_t length = 1);
int8_t convertBytesToInt8(unsigned char* bytes, size_t length = 1);

float convertBytesToFloat(unsigned char* bytes, size_t length = 4);

} // namespace GribCoder