#include "number_convert.h"

#include <cstring>

namespace grib_coder {
uint64_t convert_bytes_to_uint64(const unsigned char* bytes, size_t length) {
    uint64_t n = 0;
    n |= static_cast<uint64_t>(bytes[0]) << 56;
    n |= static_cast<uint64_t>(bytes[1]) << 48;
    n |= static_cast<uint64_t>(bytes[2]) << 40;
    n |= static_cast<uint64_t>(bytes[3]) << 32;
    n |= static_cast<uint64_t>(bytes[4]) << 24;
    n |= static_cast<uint64_t>(bytes[5]) << 16;
    n |= static_cast<uint64_t>(bytes[6]) << 8;
    n |= static_cast<uint64_t>(bytes[7]);
    return n;
}

uint32_t convert_bytes_to_uint32(const unsigned char* bytes, size_t length) {
    uint32_t n = 0;
    n |= bytes[0] << 24;
    n |= bytes[1] << 16;
    n |= bytes[2] << 8;
    n |= bytes[3];
    return n;
}

int32_t convert_bytes_to_int32(const unsigned char* bytes, size_t length) {
    int32_t n = 0;
    n |= bytes[0] << 24;
    n |= bytes[1] << 16;
    n |= bytes[2] << 8;
    n |= bytes[3];
    int32_t magic = 0x80000000;
    auto a = n & magic;
    if ((n & magic) == magic) {
        n = ~n;
        n |= magic;
        n += 1;
    }
    return n;
}

uint16_t convert_bytes_to_uint16(const unsigned char* bytes, size_t length) {
    uint16_t n = 0;
    n |= bytes[0] << 8;
    n |= bytes[1];
    return n;
}

int16_t convert_bytes_to_int16(const unsigned char* bytes, size_t length) {
    int16_t n = 0;
    n |= bytes[0] << 8;
    n |= bytes[1];
    int16_t magic = 0x8000;
    auto a = n & magic;
    if ((n & magic) == magic) {
        n = ~n;
        n |= magic;
        n += 1;
    }
    return n;
}

uint8_t convert_bytes_to_uint8(const unsigned char* bytes, size_t length) {
    return uint8_t(*bytes);
}

int8_t convert_bytes_to_int8(const unsigned char* bytes, size_t length) {
    return int8_t(*bytes);
}

float convert_bytes_to_float(const unsigned char* bytes, size_t length) {
    auto t = convert_bytes_to_uint32(bytes, 4);
    return *(reinterpret_cast<float*>(&t));
}
} // namespace grib_coder
