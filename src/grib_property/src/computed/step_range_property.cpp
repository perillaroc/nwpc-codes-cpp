#include "grib_property/computed/step_range_property.h"
#include <grib_coder/grib_message_handler.h>

#include <fmt/format.h>
#include <stdexcept>

namespace grib_coder {

std::string StepRangeProperty::getString() {
    if (start_ == end_) {
        return fmt::format("{}", start_);
    }
    else {
        return fmt::format("{}-{}", start_, end_);
    }
}

bool StepRangeProperty::decode(GribMessageHandler* handler) {
    const auto time_unit = handler->getLong("indicatorOfUnitOfTimeRange");
    const auto forecast_time = handler->getLong("forecastTime");
    start_ = end_ = forecast_time;
    if (time_unit != 1) {
        fmt::print(stderr, "indicatorOfUnitOfTimeRange must be hour(1), got {}", time_unit);
        return false;
    }

    if (!handler->hasProperty("indicatorOfUnitForTimeRange")) {
        return true;
    }

    const auto indicator_of_unit_for_time_range = handler->getLong("indicatorOfUnitForTimeRange");
    const auto type_of_time_increment = handler->getLong("typeOfTimeIncrement");
    const auto length_of_time_range = handler->getLong("lengthOfTimeRange");

    if (type_of_time_increment != 2) {
        fmt::print(stderr, "typeOfTimeIncrement must be 2, got {}", type_of_time_increment);
        return false;
    }
    if (indicator_of_unit_for_time_range != 1) {
        fmt::print(stderr, "indicatorOfUnitForTimeRange must be hour(1), got {}", indicator_of_unit_for_time_range);
        return false;
    }
    end_ = length_of_time_range;
    ComputedProperty::decode(handler);
    return true;
}

void StepRangeProperty::encodeToComponents() {
    throw std::runtime_error("StepRangeProperty is a read-only property.");
}

} // namespace grib_coder