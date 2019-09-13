#include "grib_section_8.h"

#include <grib_property/property_component.h>


namespace grib_coder {
GribSection8::GribSection8():
    GribSection{8, 4} {
    init();
}

bool GribSection8::parseFile(std::FILE* file, bool header_only) {
    std::vector<std::byte> buffer(4);
    const auto result = std::fread(&buffer[0], 1, 4, file);
    if (result != 4) {
        return false;
    }

    auto iterator = std::cbegin(buffer);
    for (auto& component : components_) {
        component->parse(iterator);
    }

    if(end_string_.getString() != "7777") {
        return false;
    } else {
        return true;
    }
}

void GribSection8::init() {
    std::vector<std::tuple<size_t, std::string, GribProperty*>> components{
        { 4, "7777", &end_string_ }
    };

    for (auto& item : components) {
        components_.push_back(std::make_unique<PropertyComponent>(
            std::get<0>(item),
            std::get<1>(item),
            std::get<2>(item))
        );
        registerProperty(
            std::get<1>(item),
            std::get<2>(item));
    }
}
} // namespace grib_coder
