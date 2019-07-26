#pragma once

#include "grib_section.h"
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
	uint8_t tables_version_;
	uint8_t local_tables_version_;
	uint8_t significance_of_reference_time_;
	uint16_t year_;
	uint8_t month_;
	uint8_t day_;
	uint8_t hour_;
	uint8_t minute_;
	uint8_t second_;
	uint8_t production_status_of_processed_data_;
	uint8_t type_of_processed_data_;
};


} // namespace GribCoder
