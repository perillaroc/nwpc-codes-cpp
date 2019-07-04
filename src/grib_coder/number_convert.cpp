#include "number_convert.h"

namespace GribCoder {
uint64_t convertBytesToUint64(unsigned char* bytes, size_t length)
{
	uint64_t n = 0;
	for (auto index = 0; index < length; index++) {
		n <<= 8;
		n |= bytes[index];
	}
	return n;
}
} // namespace GribCoder