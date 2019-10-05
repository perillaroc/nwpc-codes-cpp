#pragma once

#include <grib_coder/grib_section.h>
#include <grib_property/code_table_property.h>
#include <grib_property/string_property.h>

#include <cstdint>

namespace grib_coder {

class GribSection0 : public GribSection {
public:
    GribSection0();

    bool parseFile(std::FILE* file, bool header_only = false) override;

    bool encode(GribMessageHandler* handler) override;

private:
    void init();

    StringProperty identifier_;
    NumberProperty<uint16_t> reserved_;
    CodeTableProperty discipline_;
    NumberProperty<uint8_t> edition_number_ = 0;
    NumberProperty<uint64_t> total_length_ = 0;
};

} // namespace grib_coder
