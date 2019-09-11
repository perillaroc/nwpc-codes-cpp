#include "grib_section_1.h"
#include <grib_property/number_convert.h>
#include <grib_property/property_component.h>

#include <vector>
#include <cassert>

namespace grib_coder {

GribSection1::GribSection1() :
    GribSection(1) {
    init();
}

GribSection1::GribSection1(long section_length) :
    GribSection(1, section_length) {
    assert(section_length == 21);
    init();
}

bool GribSection1::parseFile(std::FILE* file, bool header_only) {
    const auto buffer_length = section_length_ - 5;
    std::vector<std::byte> buffer(buffer_length);
    const auto read_count = std::fread(&buffer[0], 1, buffer_length, file);
    if (static_cast<long>(read_count) != buffer_length) {
        return false;
    }

    auto iterator = std::cbegin(buffer);
    for (auto& component : components_) {
        component->parse(iterator);
    }

    return true;
}

bool GribSection1::decode(GribPropertyContainer* container) {
    auto result = data_date_.decode(container);
    if (!result) return false;

    result = data_time_.decode(container);
    return result;
}

void GribSection1::init() {
    components_.push_back(std::make_unique<PropertyComponent>(2, &centre_));
    components_.push_back(std::make_unique<PropertyComponent>(2, &sub_centre_));
    components_.push_back(std::make_unique<PropertyComponent>(1, &tables_version_));
    components_.push_back(std::make_unique<PropertyComponent>(1, &local_tables_version_));
    components_.push_back(std::make_unique<PropertyComponent>(1, &significance_of_reference_time_));
    components_.push_back(std::make_unique<PropertyComponent>(2, &year_));
    components_.push_back(std::make_unique<PropertyComponent>(1, &month_));
    components_.push_back(std::make_unique<PropertyComponent>(1, &day_));
    components_.push_back(std::make_unique<PropertyComponent>(1, &hour_));
    components_.push_back(std::make_unique<PropertyComponent>(1, &minute_));
    components_.push_back(std::make_unique<PropertyComponent>(1, &second_));
    components_.push_back(std::make_unique<PropertyComponent>(1, &production_status_of_processed_data_));
    components_.push_back(std::make_unique<PropertyComponent>(1, &type_of_processed_data_));

    std::vector<std::tuple<CodeTableProperty*, std::string>> tables_id{
        { &tables_version_, "1.0" },
        { &local_tables_version_, "1.1" },
        { &significance_of_reference_time_, "1.2" },
        { &production_status_of_processed_data_, "1.3" },
        { &type_of_processed_data_, "1.4" },
    };
    for (const auto& item : tables_id) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }

    std::vector<std::tuple<std::string, GribProperty*>> properties = {
        {"centre", &centre_},
        {"subCentre", &sub_centre_},
        {"tablesVersion", &tables_version_},
        {"localTablesVersion", &local_tables_version_},
        {"significanceOfReferenceTime", &significance_of_reference_time_},
        {"year", &year_},
        {"month", &month_},
        {"day", &day_},
        {"hour", &hour_},
        {"minute", &minute_},
        {"second", &second_},
        {"productionStatusOfProcessedData", &production_status_of_processed_data_},
        {"typeOfProcessedData", &type_of_processed_data_},
        {"dataDate", &data_date_},
        {"dataTime", &data_time_}
    };

    for (const auto& item : properties) {
        registerProperty(std::get<0>(item), std::get<1>(item));
    }
}

} // namespace grib_coder
