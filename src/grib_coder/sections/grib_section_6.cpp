#include "grib_section_6.h"
#include "number_convert.h"

#include <vector>

namespace grib_coder {
GribSection6::GribSection6():
	GribSection{6}
{
}

GribSection6::GribSection6(int section_length):
	GribSection{6, section_length}
{
	// assert(section_length == 6);
}

GribSection6::~GribSection6()
{
}

bool GribSection6::parseFile(std::FILE* file, bool header_only)
{
	auto buffer_length = section_length_ - 5;
	std::vector<unsigned char> buffer(section_length_);
	auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
	if (read_count != buffer_length) {
		return false;
	}

	bit_map_indicator_ = convert_bytes_to_uint8(&buffer[5]);

	return true;
}
void GribSection6::init()
{
    registerProperty("bitMapIndicator", &bit_map_indicator_);
}
} // namespace grib_coder