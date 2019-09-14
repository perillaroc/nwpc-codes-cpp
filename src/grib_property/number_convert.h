#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace grib_coder {

uint64_t convert_bytes_to_uint64(const std::byte* bytes, size_t length = 8);

uint32_t convert_bytes_to_uint32(const std::byte* bytes, size_t length = 4);
int32_t convert_bytes_to_int32(const std::byte* bytes, size_t length = 4);

uint16_t convert_bytes_to_uint16(const std::byte* bytes, size_t length = 2);
int16_t convert_bytes_to_int16(const std::byte* bytes, size_t length = 2);

uint8_t convert_bytes_to_uint8(const std::byte* bytes, size_t length = 1);
int8_t convert_bytes_to_int8(const std::byte* bytes, size_t length = 1);

float convert_bytes_to_float(const std::byte* bytes, size_t length = 4);

template <typename T>
T convert_bytes_to_number(const std::byte* bytes) {
    throw std::runtime_error("not implemented");
}

template <>
inline uint64_t convert_bytes_to_number(const std::byte* bytes) {
    return convert_bytes_to_uint64(bytes);
}

template <>
inline uint32_t convert_bytes_to_number(const std::byte* bytes) {
    return convert_bytes_to_uint32(bytes);
}

template <>
inline int32_t convert_bytes_to_number(const std::byte* bytes) {
    return convert_bytes_to_int32(bytes);
}

template <>
inline uint16_t convert_bytes_to_number(const std::byte* bytes) {
    return convert_bytes_to_uint16(bytes);
}

template <>
inline int16_t convert_bytes_to_number(const std::byte* bytes) {
    return convert_bytes_to_int16(bytes);
}

template <>
inline uint8_t convert_bytes_to_number(const std::byte* bytes) {
    return convert_bytes_to_uint8(bytes);
}

template <>
inline int8_t convert_bytes_to_number(const std::byte* bytes) {
    return convert_bytes_to_int8(bytes);
}

template <>
inline float convert_bytes_to_number(const std::byte* bytes) {
    return convert_bytes_to_float(bytes);
}

} // namespace grib_coder
