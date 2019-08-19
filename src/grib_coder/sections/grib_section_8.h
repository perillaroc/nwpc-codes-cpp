#pragma once

#include "grib_section.h"

namespace grib_coder {

class GribSection8 : public GribSection {
public:
	GribSection8();

	~GribSection8() = default;

	bool parseFile(std::FILE* file, bool header_only = false) override;

private:
	void init();
};

} // namespace grib_coder