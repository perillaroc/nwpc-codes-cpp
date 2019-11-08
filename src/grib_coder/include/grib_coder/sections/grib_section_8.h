#pragma once

#include <grib_coder/grib_section.h>
#include <grib_property/string_property.h>

namespace grib_coder {

class GribSection8 final: public GribSection {
public:
    GribSection8();

    bool parseFile(std::FILE* file, bool header_only = false) override;

private:
    void init();

    StringProperty end_string_;
};

} // namespace grib_coder
