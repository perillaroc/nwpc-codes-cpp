#pragma once

#include "grib_coder/grib_section.h"
#include "grib_coder/template_component.h"

#include <grib_property/code_table_property.h>
#include <grib_property/number_property.h>

#include <cstdint>

namespace grib_coder {

class TemplateComponent;

class GribSection4 : public GribSection {
public:
    GribSection4();
    explicit GribSection4(int section_length);
    ~GribSection4() = default;

    bool parseFile(std::FILE* file, bool header_only = false) override;

    bool decode(GribMessageHandler* container) override;

private:
    void init();

    void generateProductionDefinitionTemplate();

    NumberProperty<uint16_t> nv_;
    CodeTableProperty product_definition_template_number_;

    TemplateComponent* product_definition_template_ = nullptr;
};

} // namespace grib_coder
