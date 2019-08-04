#pragma once

#include "grib_section.h"
#include <grib_property/code_table_property.h>
#include <grib_property/number_property.h>

#include <cstdint>

namespace GribCoder {
class GribSection1 : public GribSection {
public:
	GribSection1();
	explicit GribSection1(long section_length);
	~GribSection1();

	bool parseFile(std::FILE* file) override;

private:
	void init() override;

public:
	NumberProperty<uint16_t> centre_;
	NumberProperty<uint16_t> sub_centre_;
	CodeTableProperty tables_version_;
	CodeTableProperty local_tables_version_;
	CodeTableProperty significance_of_reference_time_;
	NumberProperty<uint16_t> year_;
	NumberProperty<uint8_t> month_;
	NumberProperty<uint8_t> day_;
	NumberProperty<uint8_t> hour_;
	NumberProperty<uint8_t> minute_;
	NumberProperty<uint8_t> second_;
	CodeTableProperty production_status_of_processed_data_;
	CodeTableProperty type_of_processed_data_;
};


} // namespace GribCoder
