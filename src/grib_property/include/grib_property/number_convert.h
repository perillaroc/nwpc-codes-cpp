#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace grib_coder {

// convert bytes to number

template <typename T>
T convert_bytes_to_number(const std::byte* bytes) {
    throw std::runtime_error("not implemented");
}

template <>
inline uint64_t convert_bytes_to_number(const std::byte* bytes) {
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

template <>
inline uint32_t convert_bytes_to_number(const std::byte* bytes) {
    uint32_t n = 0;
    n |= static_cast<unsigned char>(bytes[0]) << 24;
    n |= static_cast<unsigned char>(bytes[1]) << 16;
    n |= static_cast<unsigned char>(bytes[2]) << 8;
    n |= static_cast<unsigned char>(bytes[3]);
    return n;
}

template <>
inline int32_t convert_bytes_to_number(const std::byte* bytes) {
    int32_t n = 0;
    n |= static_cast<unsigned char>(bytes[0]) << 24;
    n |= static_cast<unsigned char>(bytes[1]) << 16;
    n |= static_cast<unsigned char>(bytes[2]) << 8;
    n |= static_cast<unsigned char>(bytes[3]);
    const int32_t magic = 0x80000000;
    const auto a = n & magic;
    if (a == magic) {
        n = ~n;
        n |= magic;
        n += 1;
    }
    return n;
}

template <>
inline uint16_t convert_bytes_to_number(const std::byte* bytes) {
    uint16_t n = 0;
    n |= static_cast<unsigned char>(bytes[0]) << 8;
    n |= static_cast<unsigned char>(bytes[1]);
    return n;
}

template <>
inline int16_t convert_bytes_to_number(const std::byte* bytes) {
    int16_t n = 0;
    n |= static_cast<unsigned char>(bytes[0]) << 8;
    n |= static_cast<unsigned char>(bytes[1]);
    const int16_t magic = 0x8000;
    const auto a = n & magic;
    if (a == magic) {
        n = ~n;
        n |= magic;
        n += 1;
    }
    return n;
}

template <>
inline uint8_t convert_bytes_to_number(const std::byte* bytes) {
    return uint8_t(*bytes);
}

template <>
inline int8_t convert_bytes_to_number(const std::byte* bytes) {
    int8_t n = 0;
    n |= static_cast<unsigned char>(bytes[0]);
    const int8_t magic = 0x80;
    const auto a = n & magic;
    if (a == magic) {
        n = ~n;
        n |= magic;
        n += 1;
    }
    return n;
}

template <>
inline float convert_bytes_to_number(const std::byte* bytes) {
    auto t = convert_bytes_to_number<uint32_t>(bytes);
    return *(reinterpret_cast<float*>(&t));
}

// convert number to bytes

template <typename T>
std::vector<std::byte> convert_number_to_bytes(T value) {
    throw std::runtime_error("not implemented");
}

template <>
inline std::vector<std::byte> convert_number_to_bytes(uint8_t value) {
    std::vector<std::byte> bytes{ static_cast<std::byte>(value) };
    return bytes;
}

template <>
inline std::vector<std::byte> convert_number_to_bytes(int8_t value) {
    auto value_uint8 = *(reinterpret_cast<uint8_t*>(&value));

    const uint8_t magic = 0x80;
    const auto a = value_uint8 & magic;
    if (a == magic) {
        value_uint8 = ~value_uint8;
        value_uint8 |= magic;
        value_uint8 += 1;
    }
    return convert_number_to_bytes<uint8_t>(value_uint8);
}

template <>
inline std::vector<std::byte> convert_number_to_bytes(uint16_t value) {
    std::vector<std::byte> bytes(2);
    bytes[0] = static_cast<std::byte>((value & 0xFF00) >> 8);
    bytes[1] = static_cast<std::byte>((value & 0xFF));
    return bytes;
}

template <>
inline std::vector<std::byte> convert_number_to_bytes(int16_t value) {
    auto value_uint16 = *(reinterpret_cast<uint16_t*>(&value));

    const uint16_t magic = 0x8000;
    const auto a = value_uint16 & magic;
    if (a == magic) {
        value_uint16 = ~value_uint16;
        value_uint16 |= magic;
        value_uint16 += 1;
    }
    return convert_number_to_bytes<uint16_t>(value_uint16);
}

template <>
inline std::vector<std::byte> convert_number_to_bytes(uint32_t value) {
    std::vector<std::byte> bytes(4);
    bytes[0] = static_cast<std::byte>((value & 0xFF000000) >> 24);
    bytes[1] = static_cast<std::byte>((value & 0xFF0000) >> 16);
    bytes[2] = static_cast<std::byte>((value & 0xFF00) >> 8);
    bytes[3] = static_cast<std::byte>((value & 0xFF));
    return bytes;
}

template <>
inline std::vector<std::byte> convert_number_to_bytes(int32_t value) {
    auto value_uint32 = *(reinterpret_cast<uint32_t*>(&value));

    const uint32_t magic = 0x80000000;
    const auto a = value_uint32 & magic;
    if (a == magic) {
        value_uint32 = ~value_uint32;
        value_uint32 |= magic;
        value_uint32 += 1;
    }
    return convert_number_to_bytes<uint32_t>(value_uint32);
}

template <>
inline std::vector<std::byte> convert_number_to_bytes(uint64_t value) {
    std::vector<std::byte> bytes(8);
    bytes[0] = static_cast<std::byte>((value & 0xFF00000000000000) >> 56);
    bytes[1] = static_cast<std::byte>((value & 0xFF000000000000) >> 48);
    bytes[2] = static_cast<std::byte>((value & 0xFF0000000000) >> 40);
    bytes[3] = static_cast<std::byte>((value & 0xFF00000000) >> 32);
    bytes[4] = static_cast<std::byte>((value & 0xFF000000) >> 24);
    bytes[5] = static_cast<std::byte>((value & 0xFF0000) >> 16);
    bytes[6] = static_cast<std::byte>((value & 0xFF00) >> 8);
    bytes[7] = static_cast<std::byte>((value & 0xFF));
    return bytes;
}

template <>
inline std::vector<std::byte> convert_number_to_bytes(float value) {
    const auto v = *(reinterpret_cast<uint32_t*>(&value));
    return convert_number_to_bytes<uint32_t>(v);
}

} // namespace grib_coder
