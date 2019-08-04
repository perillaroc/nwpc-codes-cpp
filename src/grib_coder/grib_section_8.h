#pragma once

#include "grib_section.h"

namespace GribCoder {

class GribSection8 : public GribSection {
public:
	GribSection8();

	~GribSection8();

	bool parseFile(std::FILE* file) override;

private:
	void init() override;
};

} // namespace GribCoder