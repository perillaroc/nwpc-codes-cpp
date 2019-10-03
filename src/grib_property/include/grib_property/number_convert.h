#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace grib_coder {

uint64_t convert_bytes_to_uint64(const std::byte* bytes, size_t length = 8);
std::vector<std::byte> convert_uint64_to_bytes(uint64_t value);

uint32_t convert_bytes_to_uint32(const std::byte* bytes, size_t length = 4);
std::vector<std::byte> convert_uint32_to_bytes(uint32_t value);

int32_t convert_bytes_to_int32(const std::byte* bytes, size_t length = 4);
std::vector<std::byte> convert_int32_to_bytes(int32_t value);

uint16_t convert_bytes_to_uint16(const std::byte* bytes, size_t length = 2);
std::vector<std::byte> convert_uint16_to_bytes(uint16_t value);

int16_t convert_bytes_to_int16(const std::byte* bytes, size_t length = 2);
std::vector<std::byte> convert_int16_to_bytes(int16_t value);

uint8_t convert_bytes_to_uint8(const std::byte* bytes, size_t length = 1);
std::vector<std::byte> convert_uint8_to_bytes(uint8_t value);

int8_t convert_bytes_to_int8(const std::byte* bytes, size_t length = 1);
std::vector<std::byte> convert_int8_to_bytes(int8_t value);

float convert_bytes_to_float(const std::byte* bytes, size_t length = 4);
std::vector<std::byte> convert_float_to_bytes(float value);

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
