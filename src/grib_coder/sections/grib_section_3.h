#pragma once
#include "grib_section.h"
#include <grib_property/code_table_property.h>
#include <grib_property/number_property.h>

#include <cstdint>

namespace grib_coder {
class GribSection3 : public GribSection {
public:
	GribSection3();
	explicit GribSection3(long section_length);
	~GribSection3() = default;

	bool parseFile(std::FILE* file, bool header_only = false) override;

private:
	void init();

	CodeTableProperty source_of_grid_definition_;
	NumberProperty<uint32_t> number_of_data_points_;
	NumberProperty<uint8_t> number_of_octects_for_number_of_points_;
	CodeTableProperty interpretation_of_number_of_points_;
	CodeTableProperty grid_definition_template_number_;

	// Template 3.0
	CodeTableProperty shape_of_earth_;
	NumberProperty<uint8_t> scale_factor_of_radius_of_spherical_earth_;
	NumberProperty<uint32_t> scaled_value_of_radius_of_spherical_earth_;
	NumberProperty<uint8_t> scale_factor_of_earth_major_axis_;
	NumberProperty<uint32_t> scaled_value_of_earth_major_axis_;
	NumberProperty<uint8_t> scale_factor_of_earth_minor_axis_;
	NumberProperty<uint32_t> scaled_value_of_earth_minor_axis_;
	NumberProperty<uint32_t> ni_;
	NumberProperty<uint32_t> nj_;
	NumberProperty<uint32_t> basic_angle_of_the_initial_production_domain_;
	NumberProperty<uint32_t> subdivisions_of_basic_angle_;
	NumberProperty<int32_t> latitude_of_first_grid_point_;
	NumberProperty<int32_t> longitude_of_first_grid_point_;
	NumberProperty<uint8_t> resolution_and_component_flags_;
	NumberProperty<int32_t> latitude_of_last_grid_point_;
	NumberProperty<int32_t> longitude_of_last_grid_point_;
	NumberProperty<uint32_t> i_direction_increment_;
	NumberProperty<uint32_t> j_direction_increment_;
	NumberProperty<uint8_t> scanning_mode_;
};
} // namespace grib_coder