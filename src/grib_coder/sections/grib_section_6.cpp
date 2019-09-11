#include "grib_section_6.h"
#include <grib_property/number_convert.h>

#include <vector>

namespace grib_coder {
GribSection6::GribSection6():
    GribSection{6} {
}

GribSection6::GribSection6(int section_length):
    GribSection{6, section_length} {
    // assert(section_length == 6);
}

bool GribSection6::parseFile(std::FILE* file, bool header_only) {
    const auto buffer_length = section_length_ - 5;
    std::vector<std::byte> buffer(section_length_);
    const auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
    if (static_cast<long>(read_count) != buffer_length) {
        return false;
    }

    bit_map_indicator_ = convert_bytes_to_uint8(&buffer[5]);

    return true;
}

void GribSection6::init() {
    std::vector<std::tuple<std::string, GribProperty*>> properties_name{
        { "bitMapIndicator", &bit_map_indicator_ },
    };
    for (const auto& item : properties_name) {
        registerProperty(std::get<0>(item), std::get<1>(item));
    }
}
} // namespace grib_coder
