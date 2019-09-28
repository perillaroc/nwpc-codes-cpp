#include "grib_coder/templates/template_4_1.h"
#include "grib_coder/grib_section.h"
#include "grib_coder/grib_message_handler.h"

#include <grib_property/property_component.h>

#include <cassert>

namespace grib_coder {

Template_4_1::Template_4_1(int template_length):
    GribTemplate{template_length} {
    assert(template_length == 37 - 9);
    init();
}

bool Template_4_1::decode(GribMessageHandler* container) {
    const auto discipline = container->getLong("discipline");
    const auto category_table_id = fmt::format("4.1.{discipline}", fmt::arg("discipline", discipline));
    parameter_category_.setCodeTableId(category_table_id);

    const auto number_table_id = fmt::format(
        "4.2.{discipline}.{category}",
        fmt::arg("discipline", discipline),
        fmt::arg("category", parameter_category_.getLong()));
    parameter_number_.setCodeTableId(number_table_id);

    level_.decode(container);
    type_of_level_.decode(container);
    step_range_.decode(container);

    return true;
}

void Template_4_1::registerProperty(std::shared_ptr<GribSection> section) {
    GribTemplate::registerProperty(section);

    std::vector<std::tuple<std::string, GribProperty*>> properties_name{
        {"level", &level_},
        {"typeOfLevel", &type_of_level_},
        {"stepRange", &step_range_},
    };
    for (const auto& item : properties_name) {
        section->registerProperty(std::get<0>(item), std::get<1>(item));
    }
}

void Template_4_1::init() {
    std::vector<std::tuple<size_t, std::string, GribProperty*>> components{
        {1, "parameterCategory", &parameter_category_},
        {1, "parameterNumber", &parameter_number_},
        {1, "typeOfGeneratingProcess", &type_of_generating_process_},
        {1, "backgroundProcess", &background_process_},
        {1, "generatingProcessIdentifier", &generating_process_identifier_},
        {2, "hoursAfterDataCutoff", &hours_after_data_cutoff_},
        {1, "minutesAfterDataCutoff", &minutes_after_data_cutoff_},
        {1, "indicatorOfUnitOfTimeRange", &indicator_of_unit_of_time_range_},
        {4, "forecastTime", &forecast_time_},
        {1, "typeOfFirstFixedSurface", &type_of_first_fixed_surface_},
        {1, "scaleFactorOfFirstFixedSurface", &scale_factor_of_first_fixed_surface_},
        {4, "scaledValueOfFirstFixedSurface", &scaled_value_of_first_fixed_surface_},
        {1, "typeOfSecondFixedSurface", &type_of_second_fixed_surface_},
        {1, "scaleFactorOfSecondFixedSurface", &scale_factor_of_second_fixed_surface_},
        {4, "scaledValueOfSecondFixedSurface", &scaled_value_of_second_fixed_surface_},

        {1, "typeOfEnsembleForecast", &type_of_ensemble_forecast_},
        {1, "perturbationNumber", &perturbation_number_},
        {1, "numberOfForecastInEnsemble", &number_of_forecasts_in_ensemble_},
    };

    for (auto& item : components) {
        components_.push_back(std::make_unique<PropertyComponent>(
            std::get<0>(item),
            std::get<1>(item),
            std::get<2>(item)));
    }

    std::vector<std::tuple<CodeTableProperty*, std::string>> tables_id{
        {&type_of_generating_process_, "4.3"},
        {&indicator_of_unit_of_time_range_, "4.4"},
        {&type_of_first_fixed_surface_, "4.5"},
        {&type_of_second_fixed_surface_, "4.5"},

        {&type_of_ensemble_forecast_, "4.6"},
    };
    for (const auto& item : tables_id) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }
}
} // namespace grib_coder
