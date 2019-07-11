#include "grib_section_6.h"
#include "number_convert.h"

#include <vector>
#include <cassert>

namespace GribCoder {
GribSection6::GribSection6():
	GribSection{6}
{
}

GribSection6::GribSection6(int section_length):
	GribSection{6, section_length}
{
	assert(section_length == 6);
}

GribSection6::~GribSection6()
{
}

bool GribSection6::parseFile(std::FILE* file)
{
	auto buffer_length = section_length_ - 5;
	std::vector<unsigned char> buffer(section_length_);
	auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
	if (read_count != buffer_length) {
		return false;
	}

	bit_map_indicator_ = convertBytesToUint8(&buffer[5]);

	return true;
}
} // namespace GribCoder