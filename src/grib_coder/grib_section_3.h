#pragma once
#include "grib_section.h"

#include <cstdint>

namespace GribCoder {
class GribSection3 : public GribSection {
public:
	GribSection3();
	explicit GribSection3(long section_length);
	~GribSection3();

	bool parseFile(std::FILE* file) override;

public:
	uint8_t source_of_grid_definition_;
	uint32_t number_of_data_points_;
	uint8_t number_of_octects_for_number_of_points_;
	uint8_t interpretation_of_number_of_points_;
	uint16_t grid_definition_template_number_;

	// Template 3.0
	uint8_t shape_of_earth_;
	uint8_t scale_factor_of_radius_of_spherical_earth_;
	uint32_t scaled_value_of_radius_of_spherical_earth_;
	uint8_t scale_factor_of_earth_major_axis_;
	uint32_t scaled_value_of_earth_major_axis_;
	uint8_t scale_factor_of_earth_minor_axis_;
	uint32_t scaled_value_of_earth_minor_axis_;
	uint32_t ni_;
	uint32_t nj_;
	uint32_t basic_angle_of_the_initial_production_domain_;
	uint32_t subdivisions_of_basic_angle_;
	int32_t latitude_of_first_grid_point_;
	int32_t longitude_of_first_grid_point_;
	uint8_t resolution_and_component_flags_;
	int32_t latitude_of_last_grid_point_;
	int32_t longitude_of_last_grid_point_;
	uint32_t i_direction_increment_;
	uint32_t j_direction_increment_;
	uint8_t scanning_mode_;
};
} // namespace GribCoder