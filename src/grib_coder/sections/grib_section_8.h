#pragma once

#include "grib_section.h"

namespace grib_coder {

class GribSection8 : public GribSection {
public:
	GribSection8();

	~GribSection8();

	bool parseFile(std::FILE* file, bool header_only = false) override;

private:
	void init() override;
};

} // namespace grib_coder