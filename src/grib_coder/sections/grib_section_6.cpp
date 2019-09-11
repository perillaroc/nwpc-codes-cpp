#include "grib_section_6.h"
#include <grib_property/number_convert.h>
#include <grib_property/property_component.h>

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

    auto iterator = std::cbegin(buffer) + 5;
    for (auto& component : components_) {
        component->parse(iterator);
    }

    return true;
}

void GribSection6::init() {
    std::vector<std::tuple<size_t, GribProperty*>> components{
        {4, &bit_map_indicator_},
    };

    for (auto& item : components) {
        components_.push_back(std::make_unique<PropertyComponent>(std::get<0>(item), std::get<1>(item)));
    }

    std::vector<std::tuple<std::string, GribProperty*>> properties_name{
        { "bitMapIndicator", &bit_map_indicator_ },
    };
    for (const auto& item : properties_name) {
        registerProperty(std::get<0>(item), std::get<1>(item));
    }
}
} // namespace grib_coder
