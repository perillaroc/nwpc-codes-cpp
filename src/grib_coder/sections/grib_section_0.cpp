#include "grib_section_0.h"

#include <grib_property/number_convert.h>
#include <grib_property/property_component.h>

#include <tuple>
#include <array>

namespace grib_coder {

GribSection0::GribSection0():
    GribSection{0} {
    init();
}

bool GribSection0::parseFile(std::FILE* file, bool header_only) {
    const size_t section_length = 16;
    std::vector<std::byte> buffer(section_length);
    auto result = std::fread(&buffer[0], 1, section_length, file);
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
    components_.push_back(std::make_unique<PropertyComponent>(4, &identifier_));
    components_.push_back(std::make_unique<PropertyComponent>(2, &reserved_));
    components_.push_back(std::make_unique<PropertyComponent>(1, &discipline_));
    components_.push_back(std::make_unique<PropertyComponent>(1, &edition_number_));
    components_.push_back(std::make_unique<PropertyComponent>(8, &total_length_));


    std::vector<std::tuple<CodeTableProperty*, std::string>> tables_id{
        { &discipline_, "0.0" },
    };
    for(const auto& item: tables_id) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }

    std::vector<std::tuple<std::string, GribProperty*>> properties_name{
        { "discipline", &discipline_ },
        { "editionNumber", &edition_number_ },
        { "totalLength", &total_length_ },
    };
    for(const auto& item: properties_name) {
        registerProperty(std::get<0>(item), std::get<1>(item));
    }
}

} // namespace grib_coder
