#include "grib_section_0.h"
#include "number_convert.h"

#include <tuple>
#include <array>

namespace grib_coder {

GribSection0::GribSection0():
    GribSection{0} {
    init();
}

bool GribSection0::parseFile(std::FILE* file, bool header_only) {
    const size_t section_length = 16;
    std::array<std::byte, section_length> buffer;
    auto result = std::fread(&buffer[0], 1, section_length, file);
    if (result != 16) {
        return false;
    }
    identifier_.setString(std::string(reinterpret_cast<unsigned char*>(&buffer[0]), reinterpret_cast<unsigned char*>(&buffer[4])));
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
