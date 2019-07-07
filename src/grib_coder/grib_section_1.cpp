#include "grib_section_1.h"
#include "number_convert.h"

#include <vector>
#include <cassert>

namespace GribCoder {

GribSection1::GribSection1() :
	GribSection(1)
{
}

GribSection1::GribSection1(long section_length) :
	GribSection(1, section_length)
{
	assert(section_length == 21);
}

GribSection1::~GribSection1()
{
}

bool GribSection1::parseFile(std::FILE* file)
{
	auto buffer_length = section_length_ - 5;
	std::vector<char> buffer(buffer_length);
	auto read_count = std::fread(&buffer[0], 1, buffer_length, file);
	if (read_count != buffer_length) {
		return false;
	}

	centre_ = convertBytesToUint16(&buffer[0], 2);
	sub_centre_ = convertBytesToUint16(&buffer[2], 2);
	tables_version_ = convertBytesToUint8(&buffer[4]);
	local_tables_version_ = convertBytesToUint8(&buffer[5]);
	significance_of_reference_time_ = convertBytesToUint8(&buffer[6]);
	year_ = convertBytesToUint16(&buffer[7], 2);
	month_ = convertBytesToUint8(&buffer[9]);
	day_ = convertBytesToUint8(&buffer[10]);
	hour_ = convertBytesToUint8(&buffer[11]);
	minute_ = convertBytesToUint8(&buffer[12]);
	second_ = convertBytesToUint8(&buffer[13]);
	production_status_of_processed_data_ = convertBytesToUint8(&buffer[14]);
	type_of_processed_data_ = convertBytesToUint8(&buffer[15]);

	return true;
}

} // namespace GribCoder

