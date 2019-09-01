#include "grib_section_0.h"
#include "number_convert.h"
#include <tuple>

namespace grib_coder {

GribSection0::GribSection0():
    GribSection{0} {
    init();
}

bool GribSection0::parseFile(std::FILE* file, bool header_only) {
    unsigned char buffer[16];
    auto result = std::fread(buffer, 1, 16, file);
    if (result != 16) {
        return false;
    }
    identifier_ = std::string(std::begin(buffer), std::begin(buffer) + 4);
    const auto discipline_number = convert_bytes_to_int8(&buffer[6]);
    discipline_.setLong(discipline_number);
    edition_number_ = convert_bytes_to_int8(&buffer[7]);
    total_length_ = convert_bytes_to_uint64(&buffer[8], 8);
    return true;
}

void GribSection0::init() {
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
