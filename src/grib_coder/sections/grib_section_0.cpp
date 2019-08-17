#include "grib_section_0.h"
#include "number_convert.h"

#include <algorithm>

namespace grib_coder {

GribSection0::GribSection0():
	GribSection{ 0 }
{
	init();
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
	auto discipline_number = convert_bytes_to_int8(&buffer[6]);
	discipline_.setLong(discipline_number);
	edition_number_ = convert_bytes_to_int8(&buffer[7]);
	total_length_ = convert_bytes_to_uint64(&buffer[8], 8);
	return true;
}

void GribSection0::init()
{
	discipline_.setCodeTableId("0.0");
	property_map_["discipline"] = &discipline_;
	property_map_["editionNumber"] = &edition_number_;
	property_map_["totalLength"] = &total_length_;
}

}