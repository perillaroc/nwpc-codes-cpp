#include "grib_section_5.h"
#include "number_convert.h"

#include <vector>
#include <cassert>

namespace GribCoder {
GribSection5::GribSection5():
	GribSection{ 5 }
{
}

GribSection5::GribSection5(int section_length):
	GribSection{5, section_length}
{
	assert(section_length == 23);
}

GribSection5::~GribSection5()
{
}

bool GribSection5::parseFile(std::FILE* file)
{
	auto buffer_length = section_length_ - 5;
	std::vector<unsigned char> buffer(section_length_);
	auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
	if (read_count != buffer_length) {
		return false;
	}

	number_of_values_ = convertBytesToUint32(&buffer[5], 4);
	data_representation_template_number_ = convertBytesToUint16(&buffer[9], 2);
	reference_value_ = convertBytesToFloat(&buffer[11], 4);
	binary_scale_factor_ = convertBytesToInt16(&buffer[15], 2);
	decimal_scale_factor_ = convertBytesToInt16(&buffer[17], 2);
	bits_per_value_ = convertBytesToUint8(&buffer[19]);
	type_of_original_field_values_ = convertBytesToUint8(&buffer[20]);
	type_of_compression_used_ = convertBytesToUint8(&buffer[21]);
	target_compression_ratio_ = convertBytesToUint8(&buffer[22]);

	return true;
}
} // namespace GribCoder