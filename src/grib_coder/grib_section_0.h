#pragma once

#include "grib_section.h"
#include <string>

namespace GribCoder {

class GribSection0 : public GribSection {
public:
	GribSection0();

	virtual ~GribSection0();

	bool parseFile(std::FILE* file);

public:
	std::string identifier_;
	unsigned int discipline_ = 0;
	unsigned int edition_number_ = 0;
	unsigned long long total_length_ = 0;
};

} // namespace GribCoder