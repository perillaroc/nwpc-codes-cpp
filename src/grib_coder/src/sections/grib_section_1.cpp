#include <grib_coder/sections/grib_section_1.h>
#include <grib_property/property_component.h>
#include <grib_coder/grib_message_handler.h>

#include <gsl/span>

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

bool GribSection1::decode(GribMessageHandler* container) {
    auto result = data_date_.decode(container);
    if (!result) return false;

    result = data_time_.decode(container);

    auto property = container->getProperty("discipline");
    if (property) {
        auto discipline = dynamic_cast<CodeTableProperty*>(property);
        if (discipline) {
            discipline->setTablesVersion(fmt::format("{}", tables_version_.getValue()));
        }
    }

    return result;
}

void GribSection1::init() {
    std::vector<std::tuple<size_t, std::string, GribProperty*>> components{
        {4, "section1Length", &section_length_},
        {1, "numberOfSection", &section_number_},
        {2, "centre", &centre_},
        {2, "subCentre", &sub_centre_},
        {1, "tablesVersion", &tables_version_},
        {1, "localTablesVersion", &local_tables_version_},
        {1, "significanceOfReferenceTime", &significance_of_reference_time_},
        {2, "year", &year_},
        {1, "month", &month_},
        {1, "day", &day_},
        {1, "hour", &hour_},
        {1, "minute", &minute_},
        {1, "second", &second_},
        {1, "productionStatusOfProcessedData", &production_status_of_processed_data_},
        {1, "typeOfProcessedData", &type_of_processed_data_},
    };

    for (auto& item : components) {
        components_.push_back(std::make_unique<PropertyComponent>(
            std::get<0>(item),
            std::get<1>(item),
            std::get<2>(item)));
        registerProperty(std::get<1>(item), std::get<2>(item));
    }

    std::vector<std::tuple<CodeTableProperty*, std::string>> tables_id{
        {&tables_version_, "1.0"},
        {&local_tables_version_, "1.1"},
        {&significance_of_reference_time_, "1.2"},
        {&production_status_of_processed_data_, "1.3"},
        {&type_of_processed_data_, "1.4"},
    };
    for (const auto& item : tables_id) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }

    std::vector<std::tuple<std::string, GribProperty*>> properties = {
        {"dataDate", &data_date_},
        {"dataTime", &data_time_}
    };

    for (const auto& item : properties) {
        registerProperty(std::get<0>(item), std::get<1>(item));
    }
}

} // namespace grib_coder
