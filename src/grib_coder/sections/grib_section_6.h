#pragma once 

#include "grib_section.h"
#include <grib_property/number_property.h>

#include <cstdint>

namespace grib_coder {

class GribSection6 : public GribSection {
public:
	GribSection6();
	explicit GribSection6(int section_length);
	~GribSection6() = default;

	bool parseFile(std::FILE* file, bool header_only = false) override;

private:
	void init();

	NumberProperty<uint8_t> bit_map_indicator_;
};

} // namespace grib_coder