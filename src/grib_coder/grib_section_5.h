#pragma once 

#include "grib_section.h"
#include <cstdint>

namespace GribCoder {

class GribSection5 : public GribSection {
public:
	GribSection5();
	GribSection5(int section_length);
	~GribSection5();

	bool parseFile(std::FILE* file) override;

private:
	uint32_t number_of_values_;
	uint16_t data_representation_template_number_;

	// Template 5.40 Grid point data - JPEG 2000 code stream format
	float reference_value_; // NOTE: check std::numeric_limits<T>::is_iec559
	int16_t binary_scale_factor_;
	int16_t decimal_scale_factor_;
	uint8_t bits_per_value_;
	uint8_t type_of_original_field_values_;
	uint8_t type_of_compression_used_;
	uint8_t target_compression_ratio_;

};

} // namespace GribCoder