#include "step_range_property.h"
#include <grib_property/grib_property_container.h>

#include <fmt/format.h>
#include <fmt/printf.h>
#include <stdexcept>

std::string grib_coder::StepRangeProperty::getString()
{
    if(start_ == end_) {
        return fmt::format("{}", start_);
    } else {
        return fmt::format("{}-{}", start_, end_);
    }
}

bool grib_coder::StepRangeProperty::decode(GribPropertyContainer* container)
{
    const auto time_unit = container->getLong("indicatorOfUnitOfTimeRange");
    const auto forecast_time = container->getLong("forecastTime");
    start_ = end_ = forecast_time;
    if(time_unit!=1) {
        fmt::print(stderr, "indicatorOfUnitOfTimeRange must be hour(1), got {}", time_unit);
        return false;
    }
    try {
        const auto indicatorOfUnitForTimeRange = container->getLong("indicatorOfUnitForTimeRange");
        const auto typeOfTimeIncrement = container->getLong("typeOfTimeIncrement");
        const auto lengthOfTimeRange = container->getLong("lengthOfTimeRange");

        if (typeOfTimeIncrement != 2) {
            fmt::print(stderr, "typeOfTimeIncrement must be 2, got {}", typeOfTimeIncrement);
            return false;
        }
        if(indicatorOfUnitForTimeRange != 1) {
            fmt::print(stderr, "indicatorOfUnitForTimeRange must be hour(1), got {}", indicatorOfUnitForTimeRange);
            return false;
        }
        end_ = lengthOfTimeRange;
    } catch(std::runtime_error &) {
        // skip
    }

    return true;
}
