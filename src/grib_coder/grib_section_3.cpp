#include "grib_section_3.h"
#include "number_convert.h"

#include <vector>
#include <cassert>

namespace GribCoder {
GribSection3::GribSection3():
	GribSection{3}
{
}

GribSection3::GribSection3(long section_length):
	GribSection{ 3, section_length }
{
	assert(section_length_ == 72);
}

GribSection3::~GribSection3()
{
}

bool GribSection3::parseFile(std::FILE* file)
{
	auto buffer_length = section_length_ - 5;
	std::vector<unsigned char> buffer(section_length_);
	auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
	if (read_count != buffer_length) {
		return false;
	}

	source_of_grid_definition_ = convertBytesToUint8(&buffer[5]);
	number_of_data_points_ = convertBytesToUint32(&buffer[6], 4);
	number_of_octects_for_number_of_points_ = convertBytesToUint8(&buffer[10]);
	interpretation_of_number_of_points_ = convertBytesToUint8(&buffer[11]);
	grid_definition_template_number_ = convertBytesToUint16(&buffer[12], 2);

	shape_of_earth_ = convertBytesToUint8(&buffer[14]);
	scale_factor_of_radius_of_spherical_earth_ = convertBytesToUint8(&buffer[15]);
	scaled_value_of_radius_of_spherical_earth_ = convertBytesToUint32(&buffer[16], 4);
	scale_factor_of_earth_major_axis_ = convertBytesToUint8(&buffer[20]);
	scaled_value_of_earth_major_axis_ = convertBytesToUint32(&buffer[21], 4);
	scale_factor_of_earth_minor_axis_ = convertBytesToUint8(&buffer[25]);
	scaled_value_of_earth_minor_axis_ = convertBytesToUint32(&buffer[26], 4);
	ni_ = convertBytesToUint32(&buffer[30], 4);
	nj_ = convertBytesToUint32(&buffer[34], 4);
	basic_angle_of_the_initial_production_domain_ = convertBytesToUint32(&buffer[38], 4);
	subdivisions_of_basic_angle_ = convertBytesToUint32(&buffer[42], 4);
	latitude_of_first_grid_point_ = convertBytesToInt32(&buffer[46], 4);
	longitude_of_first_grid_point_ = convertBytesToInt32(&buffer[50], 4);
	resolution_and_component_flags_ = convertBytesToUint8(&buffer[54]);
	latitude_of_last_grid_point_ = convertBytesToInt32(&buffer[55], 4);
	longitude_of_last_grid_point_ = convertBytesToInt32(&buffer[59], 4);
	i_direction_increment_ = convertBytesToUint32(&buffer[63], 4);
	j_direction_increment_ = convertBytesToUint32(&buffer[67], 4);
	scanning_mode_ = convertBytesToUint8(&buffer[71]);

	return true;
}

} // namespace GribCoder