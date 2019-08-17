#pragma once 

#include "grib_section.h"
#include "grib_template.h"

#include <grib_property/code_table_property.h>
#include <grib_property/number_property.h>

#include <cstdint>

namespace grib_coder {

class GribSection4 : public GribSection  {
public:
	GribSection4();
	explicit GribSection4(int section_length_);
	~GribSection4();

	bool parseFile(std::FILE* file, bool header_only = false) override;

	bool decode(std::vector<std::shared_ptr<GribSection>> section_list) override;

private:
	void init();

public:
	NumberProperty<uint16_t> nv_;
	CodeTableProperty product_definition_template_number_;

    std::shared_ptr<GribTemplate> product_definition_template_;
};

} // namespace grib_coder