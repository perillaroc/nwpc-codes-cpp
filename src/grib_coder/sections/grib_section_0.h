#pragma once

#include "grib_section.h"
#include <grib_property/code_table_property.h>
#include <grib_property/number_property.h>

#include <string>
#include <cstdint>

namespace grib_coder {

class GribSection0 : public GribSection {
public:
	GribSection0();

	virtual ~GribSection0();

	bool parseFile(std::FILE* file, bool header_only = false) override;

private:
	void init();

public:
	std::string identifier_ = "GRIB";
	CodeTableProperty discipline_;
	NumberProperty<uint8_t> edition_number_ = 0;
	NumberProperty<uint64_t> total_length_ = 0;
};

} // namespace grib_coder