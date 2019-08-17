#include "grib_section_3.h"
#include "number_convert.h"

#include <vector>
#include <cassert>

namespace grib_coder {
GribSection3::GribSection3():
	GribSection{3}
{
	init();
}

GribSection3::GribSection3(long section_length):
	GribSection{ 3, section_length }
{
	assert(section_length_ == 72);
	init();
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

	auto source_of_grid_definition = convert_bytes_to_uint8(&buffer[5]);
	source_of_grid_definition_.setLong(source_of_grid_definition);
	number_of_data_points_ = convert_bytes_to_uint32(&buffer[6], 4);
	number_of_octects_for_number_of_points_ = convert_bytes_to_uint8(&buffer[10]);
	auto interpretation_of_number_of_points = convert_bytes_to_uint8(&buffer[11]);
	interpretation_of_number_of_points_.setLong(interpretation_of_number_of_points);
	auto grid_definition_template_number = convert_bytes_to_uint16(&buffer[12], 2);
	grid_definition_template_number_.setLong(grid_definition_template_number);
	
	auto shape_of_earth = convert_bytes_to_uint8(&buffer[14]);
	shape_of_earth_.setLong(shape_of_earth);
	scale_factor_of_radius_of_spherical_earth_ = convert_bytes_to_uint8(&buffer[15]);
	scaled_value_of_radius_of_spherical_earth_ = convert_bytes_to_uint32(&buffer[16], 4);
	scale_factor_of_earth_major_axis_ = convert_bytes_to_uint8(&buffer[20]);
	scaled_value_of_earth_major_axis_ = convert_bytes_to_uint32(&buffer[21], 4);
	scale_factor_of_earth_minor_axis_ = convert_bytes_to_uint8(&buffer[25]);
	scaled_value_of_earth_minor_axis_ = convert_bytes_to_uint32(&buffer[26], 4);
	ni_ = convert_bytes_to_uint32(&buffer[30], 4);
	nj_ = convert_bytes_to_uint32(&buffer[34], 4);
	basic_angle_of_the_initial_production_domain_ = convert_bytes_to_uint32(&buffer[38], 4);
	subdivisions_of_basic_angle_ = convert_bytes_to_uint32(&buffer[42], 4);
	latitude_of_first_grid_point_ = convert_bytes_to_int32(&buffer[46], 4);
	longitude_of_first_grid_point_ = convert_bytes_to_int32(&buffer[50], 4);
	resolution_and_component_flags_ = convert_bytes_to_uint8(&buffer[54]);
	latitude_of_last_grid_point_ = convert_bytes_to_int32(&buffer[55], 4);
	longitude_of_last_grid_point_ = convert_bytes_to_int32(&buffer[59], 4);
	i_direction_increment_ = convert_bytes_to_uint32(&buffer[63], 4);
	j_direction_increment_ = convert_bytes_to_uint32(&buffer[67], 4);
	scanning_mode_ = convert_bytes_to_uint8(&buffer[71]);

	return true;
}

void GribSection3::init()
{
	source_of_grid_definition_.setCodeTableId("3.0");
	interpretation_of_number_of_points_.setCodeTableId("3.11");

	grid_definition_template_number_.setOctetCount(2);
	grid_definition_template_number_.setCodeTableId("3.1");

	shape_of_earth_.setCodeTableId("3.2");

	property_map_["sourceOfGridDefinition"] = &source_of_grid_definition_;
	property_map_["numberOfDataPoints"] = &number_of_data_points_;
	property_map_["numberOfOctectsForNumberOfPoints"] = &number_of_octects_for_number_of_points_;
	property_map_["interpretationOfNumberOfPoints"] = &interpretation_of_number_of_points_;
	property_map_["gridDefinitionTemplateNumber"] = &grid_definition_template_number_;

	property_map_["shapeOfEarth"] = &shape_of_earth_;
	property_map_["scaleFactorOfRadiusOfSphericalEarth"] = &scale_factor_of_radius_of_spherical_earth_;
	property_map_["scaledValueOfRadiusOfSphericalEarth"] = &scaled_value_of_radius_of_spherical_earth_;
	property_map_["scaleFactorOfEarthMajorAxis"] = &scale_factor_of_earth_major_axis_;
	property_map_["scaledValueOfEarthMajorAxis"] = &scaled_value_of_earth_major_axis_;
	property_map_["scaleFactorOfEarthMinorAxis"] = &scale_factor_of_earth_minor_axis_;
	property_map_["scaledValueOfEarthMinorAxis"] = &scaled_value_of_earth_minor_axis_;
	property_map_["ni"] = &ni_;
	property_map_["nj"] = &nj_;
	property_map_["basciAngleOfTheInitialProductionDomain"] = &basic_angle_of_the_initial_production_domain_;
	property_map_["subdivisionsOfBasicAngle"] = &subdivisions_of_basic_angle_;
	property_map_["latitudeOfFirstGridPoint"] = &latitude_of_first_grid_point_;
	property_map_["longitudeOfFirstGridPoint"] = &longitude_of_first_grid_point_;
	property_map_["resolutionAndComponentFlags"] = &resolution_and_component_flags_;
	property_map_["latitudeOfLastGridPoint"] = &latitude_of_last_grid_point_;
	property_map_["longitudeOfLastGridPoint"] = &longitude_of_last_grid_point_;
	property_map_["iDirectionIncrement"] = &i_direction_increment_;
	property_map_["jDirectionIncrement"] = &j_direction_increment_;
	property_map_["scanningMode"] = &scanning_mode_;
}

} // namespace grib_coder