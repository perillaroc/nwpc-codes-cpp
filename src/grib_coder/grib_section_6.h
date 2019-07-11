#pragma once 

#include "grib_section.h"
#include <cstdint>

namespace GribCoder {

class GribSection6 : public GribSection {
public:
	GribSection6();
	GribSection6(int section_length);
	~GribSection6();

	bool parseFile(std::FILE* file) override;

private:
	uint8_t bit_map_indicator_;
};

} // namespace GribCoder