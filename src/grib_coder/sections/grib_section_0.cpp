#include "grib_section_0.h"

#include <grib_property/number_convert.h>
#include <grib_property/property_component.h>

#include <tuple>

namespace grib_coder {

GribSection0::GribSection0():
    GribSection{0, 16} {
    init();
}

bool GribSection0::parseFile(std::FILE* file, bool header_only) {
    std::vector<std::byte> buffer(section_length_);
    const auto result = std::fread(&buffer[0], 1, section_length_, file);
    if (result != 16) {
        return false;
    }

    auto iterator = std::cbegin(buffer);
    for(auto & component: components_) {
        component->parse(iterator);
    }

    return true;
}

void GribSection0::init() {
    std::vector<std::tuple<size_t, std::string, GribProperty*>> components{
        { 4, "discipline", &identifier_ },
        { 2, "reserved", &reserved_ },
        { 1, "discipline", &discipline_ },
        { 1, "editionNumber", &edition_number_ },
        { 8, "totalLength", &total_length_ },
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

    std::vector<std::tuple<CodeTableProperty*, std::string>> tables_id{
        { &discipline_, "0.0" },
    };
    for(const auto& item: tables_id) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }
}

} // namespace grib_coder
