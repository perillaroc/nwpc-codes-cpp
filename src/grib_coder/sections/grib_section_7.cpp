#include "grib_section_7.h"

#include <grib_property/property_component.h>

#include <algorithm>

namespace grib_coder {
GribSection7::GribSection7():
    GribSection{7} {
    init();
}

GribSection7::GribSection7(int section_length):
    GribSection{7, section_length} {
    init();
}

bool GribSection7::parseFile(std::FILE* file, bool header_only) {
    const auto buffer_length = section_length_ - 5;
    if (buffer_length == 0) {
        return true;
    }

    components_.push_back(std::make_unique<PropertyComponent>(
        buffer_length,
        "dataValues",
        &data_values_
    ));

    // if (header_only) {
    //     std::fseek(file, buffer_length, SEEK_CUR);
    // } else {
    std::vector<std::byte> buffer(section_length_);
    const auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
    if (static_cast<long>(read_count) != buffer_length) {
        return false;
    }

    std::vector<std::byte> raw_value_bytes;
    raw_value_bytes.resize(buffer_length);
    std::copy(buffer.begin() + 5, buffer.end(), raw_value_bytes.begin());
    data_values_.setRawValues(std::move(raw_value_bytes));
    // }

    return true;
}

bool GribSection7::decode(GribMessageHandler* container) {
    return true;
}

bool GribSection7::decodeValues(GribPropertyContainer* container) {
    return data_values_.decodeValues(container);
}

void GribSection7::init() {
    std::vector<std::tuple<size_t, std::string, GribProperty*>> components{
        {4, "section7Length", &section_length_},
        {1, "numberOfSection", &section_number_},
    };

    for (auto& item : components) {
        components_.push_back(std::make_unique<PropertyComponent>(
            std::get<0>(item),
            std::get<1>(item),
            std::get<2>(item)));
        registerProperty(std::get<1>(item), std::get<2>(item));
    }

    std::vector<std::tuple<std::string, GribProperty*>> properties_name{
        {"dataValues", &data_values_},
        {"values", &data_values_},
    };
    for (const auto& item : properties_name) {
        registerProperty(std::get<0>(item), std::get<1>(item));
    }
}
} // grib_coder
