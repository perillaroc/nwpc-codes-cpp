#include "number_convert.h"


namespace grib_coder {
uint64_t convert_bytes_to_uint64(const std::byte* bytes, size_t length) {
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

std::vector<std::byte> convert_uint64_to_bytes(uint64_t value) {
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

uint32_t convert_bytes_to_uint32(const std::byte* bytes, size_t length) {
    uint32_t n = 0;
    n |= static_cast<unsigned char>(bytes[0]) << 24;
    n |= static_cast<unsigned char>(bytes[1]) << 16;
    n |= static_cast<unsigned char>(bytes[2]) << 8;
    n |= static_cast<unsigned char>(bytes[3]);
    return n;
}

std::vector<std::byte> convert_uint32_to_bytes(uint32_t value) {
    std::vector<std::byte> bytes(4);
    bytes[0] = static_cast<std::byte>((value & 0xFF000000) >> 24);
    bytes[1] = static_cast<std::byte>((value & 0xFF0000) >> 16);
    bytes[2] = static_cast<std::byte>((value & 0xFF00) >> 8);
    bytes[3] = static_cast<std::byte>((value & 0xFF));
    return bytes;
}

int32_t convert_bytes_to_int32(const std::byte* bytes, size_t length) {
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

std::vector<std::byte> convert_int32_to_bytes(int32_t value) {
    auto value_uint32 = *(reinterpret_cast<uint32_t*>(&value));

    const uint32_t magic = 0x80000000;
    const auto a = value_uint32 & magic;
    if (a == magic) {
        value_uint32 = ~value_uint32;
        value_uint32 |= magic;
        value_uint32 += 1;
    }
    return convert_uint32_to_bytes(value_uint32);
}

uint16_t convert_bytes_to_uint16(const std::byte* bytes, size_t length) {
    uint16_t n = 0;
    n |= static_cast<unsigned char>(bytes[0]) << 8;
    n |= static_cast<unsigned char>(bytes[1]);
    return n;
}

std::vector<std::byte> convert_uint16_to_bytes(uint16_t value) {
    std::vector<std::byte> bytes(2);
    bytes[1] = static_cast<std::byte>((value & 0x00FF) >> 8);
    bytes[2] = static_cast<std::byte>((value & 0xFF));
    return bytes;
}

int16_t convert_bytes_to_int16(const std::byte* bytes, size_t length) {
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

std::vector<std::byte> convert_int16_to_bytes(int16_t value) {
    auto value_uint16 = *(reinterpret_cast<uint16_t*>(&value));

    const uint16_t magic = 0x8000;
    const auto a = value_uint16 & magic;
    if (a == magic) {
        value_uint16 = ~value_uint16;
        value_uint16 |= magic;
        value_uint16 += 1;
    }
    return convert_uint16_to_bytes(value_uint16);
}

uint8_t convert_bytes_to_uint8(const std::byte* bytes, size_t length) {
    return uint8_t(*bytes);
}

std::vector<std::byte> convert_uint8_to_bytes(uint8_t value) {
    std::vector<std::byte> bytes{static_cast<std::byte>(value)};
    return bytes;
}

int8_t convert_bytes_to_int8(const std::byte* bytes, size_t length) {
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

std::vector<std::byte> convert_int8_to_bytes(int8_t value) {
    auto value_uint8 = *(reinterpret_cast<uint8_t*>(&value));

    const uint8_t magic = 0x80;
    const auto a = value_uint8 & magic;
    if (a == magic) {
        value_uint8 = ~value_uint8;
        value_uint8 |= magic;
        value_uint8 += 1;
    }
    return convert_uint8_to_bytes(value_uint8);
}

float convert_bytes_to_float(const std::byte* bytes, size_t length) {
    auto t = convert_bytes_to_uint32(bytes, 4);
    return *(reinterpret_cast<float*>(&t));
}

std::vector<std::byte> convert_float_to_bytes(float value) {
    const auto v = *(reinterpret_cast<uint32_t*>(&value));
    return convert_uint32_to_bytes(v);
}
} // namespace grib_coder
