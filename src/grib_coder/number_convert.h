#pragma once

#include <cstddef>
#include <cstdint>

namespace grib_coder {

uint64_t convert_bytes_to_uint64(const unsigned char* bytes, size_t length = 8);

uint32_t convert_bytes_to_uint32(const unsigned char* bytes, size_t length = 4);
int32_t convert_bytes_to_int32(const unsigned char* bytes, size_t length = 4);

uint16_t convert_bytes_to_uint16(const unsigned char* bytes, size_t length = 2);
int16_t convert_bytes_to_int16(const unsigned char* bytes, size_t length = 2);

uint8_t convert_bytes_to_uint8(const unsigned char* bytes, size_t length = 1);
int8_t convert_bytes_to_int8(const unsigned char* bytes, size_t length = 1);

float convert_bytes_to_float(const unsigned char* bytes, size_t length = 4);

} // namespace grib_coder
