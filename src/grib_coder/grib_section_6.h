#pragma once 

#include "grib_section.h"
#include <grib_property/number_property.h>

#include <cstdint>

namespace GribCoder {

class GribSection6 : public GribSection {
public:
	GribSection6();
	explicit GribSection6(int section_length);
	~GribSection6();

	bool parseFile(std::FILE* file) override;

private:
	void init() override;

public:
	NumberProperty<uint8_t> bit_map_indicator_;
};

} // namespace GribCoder