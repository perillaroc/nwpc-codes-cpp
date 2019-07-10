#include "number_convert.h"

#include <cstring>

namespace GribCoder {
uint64_t convertBytesToUint64(unsigned char* bytes, size_t length)
{
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
uint32_t convertBytesToUint32(unsigned char * bytes, size_t length)
{
	uint32_t n = 0;
	n |= bytes[0] << 24;
	n |= bytes[1] << 16;
	n |= bytes[2] << 8;
	n |= bytes[3];
	return n;
}
int32_t convertBytesToInt32(unsigned char* bytes, size_t length)
{
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
uint16_t convertBytesToUint16(unsigned char* bytes, size_t length)
{
	uint16_t n = 0;
	n |= bytes[0] << 8;
	n |= bytes[1];
	return n;
}
uint8_t convertBytesToUint8(unsigned char* bytes, size_t length)
{
	return uint8_t(*bytes);
}
int8_t convertBytesToInt8(unsigned char* bytes, size_t length)
{
	return int8_t(*bytes);
}
} // namespace GribCoder