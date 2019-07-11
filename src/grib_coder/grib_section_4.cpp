#include "grib_section_4.h"
#include "number_convert.h"

#include <vector>
#include <cassert>

namespace GribCoder {
GribSection4::GribSection4():
	GribSection{4}
{
}

GribSection4::GribSection4(int section_length_):
	GribSection{4, section_length_}
{
	assert(section_length_ == 34);
}

GribSection4::~GribSection4()
{

}

bool GribSection4::parseFile(std::FILE* file)
{
	auto buffer_length = section_length_ - 5;
	std::vector<unsigned char> buffer(section_length_);
	auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
	if (read_count != buffer_length) {
		return false;
	}

	nv_ = convertBytesToUint16(&buffer[5], 2);
	product_definition_template_number_ = convertBytesToUint16(&buffer[7], 2);

	assert(product_definition_template_number_ == 0);

	parameter_category_ = convertBytesToUint8(&buffer[9]);
	parameter_number_ = convertBytesToUint8(&buffer[10]);
	type_of_generating_process_ = convertBytesToUint8(&buffer[11]);
	background_process_ = convertBytesToUint8(&buffer[12]);
	generating_process_identifier_ = convertBytesToUint8(&buffer[13]);
	hours_after_data_cutoff_ = convertBytesToUint16(&buffer[14], 2);
	minutes_after_data_cutoff_ = convertBytesToUint8(&buffer[16]);
	indicator_of_unit_of_time_range_ = convertBytesToUint8(&buffer[17]);
	forecast_time_ = convertBytesToInt32(&buffer[18], 4);
	type_of_first_fixed_surface_ = convertBytesToUint8(&buffer[22]);
	scale_factor_of_first_fixed_surface_ = convertBytesToInt8(&buffer[23]);
	scaled_value_of_first_fixed_surface_ = convertBytesToUint32(&buffer[24], 4);
	type_of_second_fixed_surface_ = convertBytesToUint8(&buffer[28]);
	scale_factor_of_second_fixed_surface_ = convertBytesToInt8(&buffer[29]);
	scaled_value_of_second_fixed_surface_ = convertBytesToUint32(&buffer[30]);

	return true;
}

} // namespace GribCoder