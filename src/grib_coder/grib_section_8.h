#pragma once

#include "grib_section.h"
#include <string>

namespace GribCoder {

class GribSection8 : public GribSection {
public:
	GribSection8();

	~GribSection8();

	bool parseFile(std::FILE* file) override;

public:
	
};

} // namespace GribCoder