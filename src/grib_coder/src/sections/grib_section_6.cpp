#include "grib_coder/sections/grib_section_6.h"

#include <grib_property/property_component.h>
#include <gsl/span>

namespace grib_coder {
GribSection6::GribSection6():
    GribSection{6} {
    init();
}

GribSection6::GribSection6(int section_length):
    GribSection{6, section_length} {
    // assert(section_length == 6);
    init();
}

bool GribSection6::parseFile(std::FILE* file, bool header_only) {
    const auto buffer_length = section_length_ - 5;
    std::vector<std::byte> buffer(section_length_);
    const auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
    if (static_cast<long>(read_count) != buffer_length) {
        return false;
    }

    auto iterator = std::cbegin(buffer) + 5;

    auto component_span = gsl::make_span(components_);
    auto sub_component_span = component_span.subspan(2);

    for (auto& component : sub_component_span) {
        component->parse(iterator);
    }

    return true;
}

void GribSection6::init() {
    std::vector<std::tuple<size_t, std::string, GribProperty*>> components{
        {4, "section6Length", &section_length_},
        {1, "numberOfSection", &section_number_},
        {1, "bitMapIndicator", &bit_map_indicator_},
    };

    for (auto& item : components) {
        components_.push_back(std::make_unique<PropertyComponent>(
            std::get<0>(item),
            std::get<1>(item),
            std::get<2>(item)));
        registerProperty(std::get<1>(item), std::get<2>(item));
    }
}
} // namespace grib_coder
