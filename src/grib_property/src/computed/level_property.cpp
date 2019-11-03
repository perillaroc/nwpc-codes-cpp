#include "grib_property/computed/level_property.h"
#include <grib_coder/grib_message_handler.h>

#include <fmt/format.h>

#include <limits>
#include <cmath>

namespace grib_coder {
std::string LevelProperty::getString() {
    if (value_ == std::numeric_limits<double>::max()) {
        return "MISSING";
    }

    return fmt::format("{}", value_);
}

bool LevelProperty::decode(GribMessageHandler* handler) {
    const auto level_number_factor = handler->getLong("scaleFactorOfFirstFixedSurface");
    const auto level_number_value = handler->getLong("scaledValueOfFirstFixedSurface");
    const auto type_of_first_fixed_surface = handler->getLong("typeOfFirstFixedSurface");

    std::string level;
    if (static_cast<uint8_t>(level_number_factor) == std::numeric_limits<uint8_t>::max() ||
        static_cast<uint32_t>(level_number_value) == std::numeric_limits<uint32_t>::max()) {

        if (type_of_first_fixed_surface < 10) {
            value_ = 0;
        }

        return true;
    }

    value_ = std::pow(10, level_number_factor) * level_number_value;
    ComputedProperty::decode(handler);
    return true;
}

void LevelProperty::encodeToComponents() {
    throw std::runtime_error("LevelProperty is a read-only property.");
}

} // namespace grib_coder
