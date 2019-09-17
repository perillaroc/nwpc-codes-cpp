#include "step_range_property.h"
#include <grib_coder/grib_message_handler.h>

#include <fmt/format.h>
#include <fmt/printf.h>
#include <stdexcept>

std::string grib_coder::StepRangeProperty::getString() {
    if (start_ == end_) {
        return fmt::format("{}", start_);
    } else {
        return fmt::format("{}-{}", start_, end_);
    }
}

bool grib_coder::StepRangeProperty::decode(GribMessageHandler* container) {
    const auto time_unit = container->getLong("indicatorOfUnitOfTimeRange");
    const auto forecast_time = container->getLong("forecastTime");
    start_ = end_ = forecast_time;
    if (time_unit != 1) {
        fmt::print(stderr, "indicatorOfUnitOfTimeRange must be hour(1), got {}", time_unit);
        return false;
    }

    if (!container->hasProperty("indicatorOfUnitForTimeRange")) {
        return true;
    }

    const auto indicator_of_unit_for_time_range = container->getLong("indicatorOfUnitForTimeRange");
    const auto type_of_time_increment = container->getLong("typeOfTimeIncrement");
    const auto length_of_time_range = container->getLong("lengthOfTimeRange");

    if (type_of_time_increment != 2) {
        fmt::print(stderr, "typeOfTimeIncrement must be 2, got {}", type_of_time_increment);
        return false;
    }
    if (indicator_of_unit_for_time_range != 1) {
        fmt::print(stderr, "indicatorOfUnitForTimeRange must be hour(1), got {}", indicator_of_unit_for_time_range);
        return false;
    }
    end_ = length_of_time_range;
    return true;
}
