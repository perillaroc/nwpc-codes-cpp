#pragma once 

#include "grib_section.h"
#include <cstdint>

namespace GribCoder {

class GribSection4 : public GribSection  {
public:
	GribSection4();
	explicit GribSection4(int section_length_);
	~GribSection4();

	bool parseFile(std::FILE* file) override;

public:
	uint16_t nv_;
	uint16_t product_definition_template_number_;
	
	// Template 4.0
	uint8_t parameter_category_;
	uint8_t parameter_number_;
	uint8_t type_of_generating_process_;
	uint8_t background_process_;
	uint8_t generating_process_identifier_;
	uint16_t hours_after_data_cutoff_;
	uint8_t minutes_after_data_cutoff_;
	uint8_t indicator_of_unit_of_time_range_;
	int32_t forecast_time_;
	uint8_t type_of_first_fixed_surface_;
	uint8_t scale_factor_of_first_fixed_surface_;
	uint32_t scaled_value_of_first_fixed_surface_;
	uint8_t type_of_second_fixed_surface_;
	uint8_t scale_factor_of_second_fixed_surface_;
	uint32_t scaled_value_of_second_fixed_surface_;
};

} // namespace GribCoder