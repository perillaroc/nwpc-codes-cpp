#include "level_property.h"
#include <grib_property/grib_property_container.h>

#include <fmt/format.h>

#include <limits>
#include <cmath>

namespace grib_coder {

LevelProperty::LevelProperty():
    value_{std::numeric_limits<double>::max()} {
}

std::string LevelProperty::getString() {
    if (value_ == std::numeric_limits<double>::max()) {
        return "MISSING";
    }

    return fmt::format("{}", value_);
}

bool LevelProperty::decode(GribPropertyContainer* container) {
    const auto level_number_factor = container->getLong("scaleFactorOfFirstFixedSurface");
    const auto level_number_value = container->getLong("scaledValueOfFirstFixedSurface");
    const auto type_of_first_fixed_surface = container->getLong("typeOfFirstFixedSurface");

    std::string level;
    if (static_cast<uint8_t>(level_number_factor) == std::numeric_limits<uint8_t>::max() ||
        static_cast<uint32_t>(level_number_value) == std::numeric_limits<uint32_t>::max()) {

        if (type_of_first_fixed_surface < 10) {
            value_ = 0;
        }

        return true;
    }

    value_ = std::pow(10, level_number_factor) * level_number_value;
    return true;
}

} // namespace grib_coder
