#pragma once

#include "grib_section.h"
#include <string>
#include <cstdint>

namespace GribCoder {

class GribSection0 : public GribSection {
public:
	GribSection0();

	virtual ~GribSection0();

	bool parseFile(std::FILE* file) override;

public:
	std::string identifier_;
	uint8_t discipline_ = 0;
	uint8_t edition_number_ = 0;
	uint64_t total_length_ = 0;
};

} // namespace GribCoder