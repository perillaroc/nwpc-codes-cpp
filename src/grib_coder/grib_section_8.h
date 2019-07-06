#pragma once

#include "grib_section.h"
#include <string>

namespace GribCoder {

class GribSection8 : public GribSection {
public:
	GribSection8();

	virtual ~GribSection8();

	bool parseFile(std::FILE* file);

public:
	
};

} // namespace GribCoder