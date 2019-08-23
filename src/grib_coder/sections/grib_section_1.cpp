#include "grib_section_1.h"
#include "number_convert.h"

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
    auto buffer_length = section_length_ - 5;
    std::vector<unsigned char> buffer(buffer_length);
    auto read_count = std::fread(&buffer[0], 1, buffer_length, file);
    if (read_count != buffer_length) {
        return false;
    }

    centre_ = convert_bytes_to_uint16(&buffer[0], 2);
    sub_centre_ = convert_bytes_to_uint16(&buffer[2], 2);

    auto tables_version = convert_bytes_to_uint8(&buffer[4]);
    tables_version_.setLong(tables_version);

    auto local_tables_version = convert_bytes_to_uint8(&buffer[5]);
    local_tables_version_.setLong(local_tables_version);

    auto significance_of_reference_time = convert_bytes_to_uint8(&buffer[6]);
    significance_of_reference_time_.setLong(significance_of_reference_time);

    year_ = convert_bytes_to_uint16(&buffer[7], 2);
    month_ = convert_bytes_to_uint8(&buffer[9]);
    day_ = convert_bytes_to_uint8(&buffer[10]);
    hour_ = convert_bytes_to_uint8(&buffer[11]);
    minute_ = convert_bytes_to_uint8(&buffer[12]);
    second_ = convert_bytes_to_uint8(&buffer[13]);

    auto production_status_of_processed_data = convert_bytes_to_uint8(&buffer[14]);
    production_status_of_processed_data_.setLong(production_status_of_processed_data);

    auto type_of_processed_data = convert_bytes_to_uint8(&buffer[15]);
    type_of_processed_data_.setLong(type_of_processed_data);

    return true;
}

bool GribSection1::decode(GribPropertyContainer* container) {
    auto result = data_date_.decode(container);
    if (!result) return false;

    result = data_time_.decode(container);
    return result;
}

void GribSection1::init() {
    tables_version_.setCodeTableId("1.0");
    local_tables_version_.setCodeTableId("1.1");
    significance_of_reference_time_.setCodeTableId("1.2");
    production_status_of_processed_data_.setCodeTableId("1.3");
    type_of_processed_data_.setCodeTableId("1.4");

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
