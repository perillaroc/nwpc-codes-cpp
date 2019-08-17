#include "template_4_8.h"
#include "sections/grib_section_0.h"

#include "number_convert.h"

#include <tuple>

namespace grib_coder {

Template_4_8::Template_4_8(int template_length):
    GribTemplate{ template_length }
{
    init();
}

Template_4_8::~Template_4_8()
{
}

bool Template_4_8::parse(std::vector<unsigned char>& buffer)
{
    auto parameter_category = convert_bytes_to_uint8(&buffer[9]);
    parameter_category_.setLong(parameter_category);
    auto parameter_number = convert_bytes_to_uint8(&buffer[10]);
    parameter_number_.setLong(parameter_number);
    auto type_of_generating_process = convert_bytes_to_uint8(&buffer[11]);
    type_of_generating_process_.setLong(type_of_generating_process);
    background_process_ = convert_bytes_to_uint8(&buffer[12]);
    generating_process_identifier_ = convert_bytes_to_uint8(&buffer[13]);
    hours_after_data_cutoff_ = convert_bytes_to_uint16(&buffer[14], 2);
    minutes_after_data_cutoff_ = convert_bytes_to_uint8(&buffer[16]);
    auto indicator_of_unit_of_time_range = convert_bytes_to_uint8(&buffer[17]);
    indicator_of_unit_of_time_range_.setLong(indicator_of_unit_of_time_range);
    forecast_time_ = convert_bytes_to_int32(&buffer[18], 4);
    auto type_of_first_fixed_surface = convert_bytes_to_uint8(&buffer[22]);
    type_of_first_fixed_surface_.setLong(type_of_first_fixed_surface);
    scale_factor_of_first_fixed_surface_ = convert_bytes_to_int8(&buffer[23]);
    scaled_value_of_first_fixed_surface_ = convert_bytes_to_uint32(&buffer[24], 4);
    auto type_of_second_fixed_surface = convert_bytes_to_uint8(&buffer[28]);
    type_of_second_fixed_surface_.setLong(type_of_second_fixed_surface);
    scale_factor_of_second_fixed_surface_ = convert_bytes_to_int8(&buffer[29]);
    scaled_value_of_second_fixed_surface_ = convert_bytes_to_uint32(&buffer[30]);

    return true;
}

bool Template_4_8::decode(std::vector<std::shared_ptr<GribSection>> section_list)
{
    std::shared_ptr<GribSection0> section_0;
    for (auto iter = section_list.rbegin(); iter != section_list.rend(); iter++) {
        auto s = *iter;
        if (s->section_number_ == 0) {
            section_0 = std::static_pointer_cast<GribSection0>(s);
            break;
        }
    }
    if (!section_0) {
        return false;
    }

    auto discipline = section_0->discipline_.getLong();
    std::string category_table_id = fmt::format("4.1.{discipline}", fmt::arg("discipline", discipline));
    parameter_category_.setCodeTableId(category_table_id);

    std::string number_table_id = fmt::format("4.2.{discipline}.{category}",
        fmt::arg("discipline", discipline),
        fmt::arg("category", parameter_category_.getLong()));
    parameter_number_.setCodeTableId(number_table_id);

    return true;
}

void Template_4_8::registerProperty(std::shared_ptr<GribSection> section)
{
    std::vector<std::tuple<std::string, GribProperty*>> properties = {
        {"parameterCategory", &parameter_category_},
        {"parameterNumber", &parameter_number_ },
        {"typeOfGenratingProcess", &type_of_generating_process_ },
        {"backgroundProcess", &background_process_ },
        {"generatingProcessIdentifier", &generating_process_identifier_},
        {"hoursAfterDataCutoff", &hours_after_data_cutoff_},
        {"minutesAfterDataCutoff", &minutes_after_data_cutoff_},
        {"indicatorOfUnitOfTimeRange", &indicator_of_unit_of_time_range_},
        {"forecastTime", &forecast_time_},
        {"typeOfFirstFixedSurface", &type_of_first_fixed_surface_},
        {"scaleFactorOfFirstFixedSurface", &scale_factor_of_first_fixed_surface_},
        {"scaledValueOfFirstFixedSurface", &scaled_value_of_first_fixed_surface_},
        {"typeOfSecondFixedSurfact", &type_of_second_fixed_surface_},
        {"scaleFactorOfSecondFixedSurface", &scale_factor_of_second_fixed_surface_},
        {"scaledValueOfSecondFixedSurface", &scaled_value_of_second_fixed_surface_},
    };
    
    for (auto & item : properties) {
        section->registerProperty(std::get<0>(item), std::get<1>(item));
    }    
}

void Template_4_8::init()
{
    std::vector<std::tuple<CodeTableProperty*, std::string>> properties = {
        {&type_of_generating_process_, "4.3"},
        {&indicator_of_unit_of_time_range_, "4.3" },
        {&type_of_first_fixed_surface_, "4.5" },
        {&type_of_second_fixed_surface_, "4.5" },
    };

    for (auto& item : properties) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }
}
} // namespace grib_coder
