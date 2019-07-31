#pragma once 

#include "grib_section.h"
#include <code_table_property.h>
#include <cstdint>

namespace GribCoder {

class GribSection4 : public GribSection  {
public:
	GribSection4();
	explicit GribSection4(int section_length_);
	~GribSection4();

	bool parseFile(std::FILE* file) override;

	bool decode(std::vector<std::shared_ptr<GribSection>> section_list) override;

private:
	void init();

public:
	uint16_t nv_;
	CodeTableProperty product_definition_template_number_;
	
	// Template 4.0
	CodeTableProperty parameter_category_;
	CodeTableProperty parameter_number_;
	CodeTableProperty type_of_generating_process_;
	uint8_t background_process_;
	uint8_t generating_process_identifier_;
	uint16_t hours_after_data_cutoff_;
	uint8_t minutes_after_data_cutoff_;
	CodeTableProperty indicator_of_unit_of_time_range_;
	int32_t forecast_time_;
	CodeTableProperty type_of_first_fixed_surface_;
	uint8_t scale_factor_of_first_fixed_surface_;
	uint32_t scaled_value_of_first_fixed_surface_;
	CodeTableProperty type_of_second_fixed_surface_;
	uint8_t scale_factor_of_second_fixed_surface_;
	uint32_t scaled_value_of_second_fixed_surface_;
};

} // namespace GribCoder