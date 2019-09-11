#include "template_4_8.h"
#include "sections/grib_section_0.h"

#include <grib_property/number_convert.h>
#include <grib_property/grib_property_container.h>
#include <grib_property/property_component.h>

#include <tuple>
#include <cassert>

namespace grib_coder {

Template_4_8::Template_4_8(int template_length):
    GribTemplate{template_length} {
    assert(template_length == 58 - 9);
    init();
}

bool Template_4_8::decode(GribPropertyContainer* container) {
    const auto discipline = container->getLong("discipline");
    const auto category_table_id = fmt::format("4.1.{discipline}", fmt::arg("discipline", discipline));
    parameter_category_.setCodeTableId(category_table_id);

    const auto number_table_id = fmt::format("4.2.{discipline}.{category}",
                                             fmt::arg("discipline", discipline),
                                             fmt::arg("category", parameter_category_.getLong()));
    parameter_number_.setCodeTableId(number_table_id);

    level_.decode(container);
    type_of_level_.decode(container);
    step_range_.decode(container);

    return true;
}

void Template_4_8::registerProperty(std::shared_ptr<GribSection> section) {
    const std::vector<std::tuple<std::string, GribProperty*>> properties = {
        {"parameterCategory", &parameter_category_},
        {"parameterNumber", &parameter_number_},
        {"typeOfGeneratingProcess", &type_of_generating_process_},
        {"backgroundProcess", &background_process_},
        {"generatingProcessIdentifier", &generating_process_identifier_},
        {"hoursAfterDataCutoff", &hours_after_data_cutoff_},
        {"minutesAfterDataCutoff", &minutes_after_data_cutoff_},
        {"indicatorOfUnitOfTimeRange", &indicator_of_unit_of_time_range_},
        {"forecastTime", &forecast_time_},
        {"typeOfFirstFixedSurface", &type_of_first_fixed_surface_},
        {"scaleFactorOfFirstFixedSurface", &scale_factor_of_first_fixed_surface_},
        {"scaledValueOfFirstFixedSurface", &scaled_value_of_first_fixed_surface_},
        {"typeOfSecondFixedSurface", &type_of_second_fixed_surface_},
        {"scaleFactorOfSecondFixedSurface", &scale_factor_of_second_fixed_surface_},
        {"scaledValueOfSecondFixedSurface", &scaled_value_of_second_fixed_surface_},

        {"yearOfEndOfOverallTimeInterval", &year_of_end_of_overall_time_interval_},
        {"monthOfEndOfOverallTimeInterval", &month_of_end_of_overall_time_interval_},
        {"dayOfEndOfOverallTimeInterval", &day_of_end_of_overall_time_interval_},
        {"hourOfEndOfOverallTimeInterval", &hour_of_end_of_overall_time_interval_},
        {"minuteOfEndOfOverallTimeInterval", &minute_of_end_of_overall_time_interval_},
        {"secondOfEndOfOverallTimeInterval", &second_of_end_of_overall_time_interval_},
        {"numberOfTimeRange", &number_of_time_range_},
        {"numberOfMissingInStatisticalProcess", &number_of_missing_statistical_process_},
        {"typeOfStatisticalProcessing", &type_of_statistical_processing_},
        {"typeOfTimeIncrement", &type_of_time_increment_},
        {"indicatorOfUnitForTimeRange", &indicator_of_unit_for_time_range_},
        {"lengthOfTimeRange", &length_of_time_range_},
        {"indicatorOfUnitForTimeIncrement", &indicator_of_unit_for_time_increment_},
        {"timeIncrement", &time_increment_},

        {"level", &level_},
        {"typeOfLevel", &type_of_level_},
        {"stepRange", &step_range_},
    };

    for (auto& item : properties) {
        section->registerProperty(std::get<0>(item), std::get<1>(item));
    }
}

void Template_4_8::init() {
    std::vector<std::tuple<size_t, GribProperty*>> components{
        {1, &parameter_category_},
        {1, &parameter_number_},
        {1, &type_of_generating_process_},
        {1, &background_process_},
        {1, &generating_process_identifier_},
        {2, &hours_after_data_cutoff_},
        {1, &minutes_after_data_cutoff_},
        {1, &indicator_of_unit_of_time_range_},
        {4, &forecast_time_},
        {1, &type_of_first_fixed_surface_},
        {1, &scale_factor_of_first_fixed_surface_},
        {4, &scaled_value_of_first_fixed_surface_},
        {1, &type_of_second_fixed_surface_},
        {1, &scale_factor_of_second_fixed_surface_},
        {4, &scaled_value_of_second_fixed_surface_},

        {2, &year_of_end_of_overall_time_interval_},
        {1, &month_of_end_of_overall_time_interval_},
        {1, &day_of_end_of_overall_time_interval_},
        {1, &hour_of_end_of_overall_time_interval_},
        {1, &minute_of_end_of_overall_time_interval_},
        {1, &second_of_end_of_overall_time_interval_},
        {1, &number_of_time_range_},
        {4, &number_of_missing_statistical_process_},

        {1, &type_of_statistical_processing_},
        {1, &type_of_time_increment_},
        {1, &indicator_of_unit_for_time_range_},
        {4, &length_of_time_range_},
        {1, &indicator_of_unit_for_time_increment_},
        {4, &time_increment_},
    };

    for (auto& item : components) {
        components_.push_back(std::make_unique<PropertyComponent>(std::get<0>(item), std::get<1>(item)));
    }

    const std::vector<std::tuple<CodeTableProperty*, std::string>> properties = {
        {&type_of_generating_process_, "4.3"},
        {&indicator_of_unit_of_time_range_, "4.4"},
        {&type_of_first_fixed_surface_, "4.5"},
        {&type_of_second_fixed_surface_, "4.5"},
        {&type_of_statistical_processing_, "4.10"},
        {&type_of_time_increment_, "4.11"},
        {&indicator_of_unit_for_time_range_, "4.4"},
        {&indicator_of_unit_for_time_increment_, "4.4"}
    };

    for (const auto& item : properties) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }
}
} // namespace grib_coder
