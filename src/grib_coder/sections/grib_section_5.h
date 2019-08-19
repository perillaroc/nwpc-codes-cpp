#pragma once 

#include "grib_section.h"
#include <grib_property/code_table_property.h>
#include <grib_property/number_property.h>

#include <cstdint>

namespace grib_coder {

class GribSection5 : public GribSection {
public:
	GribSection5();
	explicit GribSection5(int section_length);

	~GribSection5() = default;

	bool parseFile(std::FILE* file, bool header_only = false) override;

private:
	void init();

	NumberProperty<uint32_t> number_of_values_;
	CodeTableProperty data_representation_template_number_;

	// Template 5.40 Grid point data - JPEG 2000 code stream format
	NumberProperty<float> reference_value_; // NOTE: check std::numeric_limits<T>::is_iec559
	NumberProperty<int16_t> binary_scale_factor_;
	NumberProperty<int16_t> decimal_scale_factor_;
	NumberProperty<uint8_t> bits_per_value_;
	CodeTableProperty type_of_original_field_values_;
	CodeTableProperty type_of_compression_used_;
	NumberProperty<uint8_t> target_compression_ratio_;

};

} // namespace grib_coder