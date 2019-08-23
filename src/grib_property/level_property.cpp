#include "level_property.h"
#include "grib_property_container.h"

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
    std::string level;
    if (level_number_factor == std::numeric_limits<uint8_t>::max() || level_number_value == std::numeric_limits<uint32_t
    >::max()) {
        return true;
    }

    value_ = std::pow(10, level_number_factor) * level_number_value;
    return true;
}

} // namespace grib_coder
