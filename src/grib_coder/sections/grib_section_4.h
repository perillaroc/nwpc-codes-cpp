#pragma once

#include "grib_section.h"
#include "grib_template.h"

#include <grib_property/code_table_property.h>
#include <grib_property/number_property.h>

#include <cstdint>

namespace grib_coder {

class GribSection4 : public GribSection {
public:
    GribSection4();
    explicit GribSection4(int section_length);
    ~GribSection4() = default;

    bool parseFile(std::FILE* file, bool header_only = false) override;

    bool decode(GribPropertyContainer* container) override;

private:
    void init();

    NumberProperty<uint16_t> nv_;
    CodeTableProperty product_definition_template_number_;

    std::unique_ptr<GribTemplate> product_definition_template_;
};

} // namespace grib_coder
