#pragma once

#include <grib_coder/grib_section.h>
#include <grib_property/computed/bit_map_values_property.h>

namespace grib_coder {

// bitmap section
class GribSection6 final: public GribSection {
public:
    GribSection6();
    explicit GribSection6(int section_length);

    bool parseFile(std::FILE* file, bool header_only = false) override;

    bool decode(GribMessageHandler* handler) override;

    bool decodeValues(GribMessageHandler* handler);

private:
    void init();

    NumberProperty<uint8_t> bit_map_indicator_;
    BitMapValuesProperty bit_map_values_;
};

} // namespace grib_coder
