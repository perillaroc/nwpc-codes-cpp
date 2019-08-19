#pragma once 

#include "grib_section.h"
#include <grib_property/data_values_property.h>

namespace grib_coder {

class GribSection7 : public GribSection {
public:
	GribSection7();
	explicit GribSection7(int section_length);
	~GribSection7();

	bool parseFile(std::FILE* file, bool header_only=false) override;

	bool decode(GribPropertyContainer* container) override;

	bool decodeValues(GribPropertyContainer* container);

private:
	void init();

    DataValuesProperty data_values_;
};

} // namespace grib_coder