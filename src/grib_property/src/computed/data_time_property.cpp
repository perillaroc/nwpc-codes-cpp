#include "grib_property/computed/data_time_property.h"
#include <grib_coder/grib_message_handler.h>

#include <fmt/format.h>

#include <cmath>

namespace grib_coder {
void DataTimeProperty::setLong(long value) {
    hour_ = static_cast<int>(std::floor(value / 100));
    minute_ = value % 100;
    second_ = 0;
}

long DataTimeProperty::getLong() {
    if (hour_ == 255) {
        return 0;
    }

    if (minute_ == 255) {
        return hour_ * 100;
    }

    return hour_ * 100 + minute_;
}

void DataTimeProperty::setDouble(double value) {
    setLong(static_cast<long>(value));
}

double DataTimeProperty::getDouble() {
    return static_cast<double>(getLong());
}

void DataTimeProperty::setString(const std::string& value) {
    // HH:MM
    hour_ = std::stoi(value.substr(0, 2));
    minute_ = std::stoi(value.substr(3, 2));
    second_ = 0;
}

std::string DataTimeProperty::getString() {
    if (hour_ == 255) {
        return "00:00";
    }

    if (minute_ == 255) {
        return fmt::format("{hour:02}:00", fmt::arg("hour", hour_));
    }

    return fmt::format("{hour:02}:{minute:02}", fmt::arg("hour", hour_), fmt::arg("minute", minute_));;
}

bool DataTimeProperty::decode(GribMessageHandler* container) {
    hour_ = container->getLong("hour");
    minute_ = container->getLong("minute");
    second_ = container->getLong("second");
    return true;
}
} // namespace grib_coder
