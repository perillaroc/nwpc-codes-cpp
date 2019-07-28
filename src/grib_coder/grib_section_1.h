#pragma once

#include "grib_section.h"
#include <code_table_property.h>

#include <cstdint>

namespace GribCoder {
class GribSection1 : public GribSection {
public:
	GribSection1();
	explicit GribSection1(long section_length);
	~GribSection1();

	bool parseFile(std::FILE* file) override;

public:
	uint16_t centre_;
	uint16_t sub_centre_;
	CodeTableProperty tables_version_;
	CodeTableProperty local_tables_version_;
	CodeTableProperty significance_of_reference_time_;
	uint16_t year_;
	uint8_t month_;
	uint8_t day_;
	uint8_t hour_;
	uint8_t minute_;
	uint8_t second_;
	CodeTableProperty production_status_of_processed_data_;
	CodeTableProperty type_of_processed_data_;
};


} // namespace GribCoder
