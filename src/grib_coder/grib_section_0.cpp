#include "grib_section_0.h"
#include "number_convert.h"

#include <algorithm>

namespace GribCoder {

GribSection0::GribSection0():
	GribSection{ 0 }
{
}

GribSection0::~GribSection0()
{
}

bool GribSection0::parseFile(std::FILE* file)
{
	unsigned char buffer[16];
	auto result = std::fread(buffer, 1, 16, file);
	if (result != 16) {
		return false;
	}
	identifier_ = std::string(std::begin(buffer), std::begin(buffer) + 4);
	discipline_ = static_cast<unsigned int>(buffer[6]);
	edition_number_ = static_cast<unsigned int>(buffer[7]);

	unsigned char length_buffer[8];
	std::copy(std::begin(buffer) + 8, std::begin(buffer) + 16, std::begin(length_buffer));

	total_length_ = convertBytesToUint64(length_buffer, 8);
}

}