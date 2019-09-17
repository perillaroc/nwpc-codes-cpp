#include "data_date_property.h"
#include <grib_coder/grib_message_handler.h>

#include <fmt/format.h>

#include <cmath>

namespace grib_coder {

void DataDateProperty::setLong(long value) {
    year_ = static_cast<int>(std::floor(value / 10000));
    const auto month_day = value % 10000;
    month_ = static_cast<int>(std::floor(month_day / 100));
    day_ = month_day % 100;
}

long DataDateProperty::getLong() {
    // YYYYMMDD
    return year_ * 10000 + month_ * 100 + day_;
}

void DataDateProperty::setDouble(double value) {
    setLong(static_cast<long>(value));
}

double DataDateProperty::getDouble() {
    // YYYYMMDD
    return static_cast<double>(getLong());
}

void DataDateProperty::setString(const std::string& value) {
    // YYYY-MM-DD
    year_ = std::stoi(value.substr(0, 4));
    month_ = std::stoi(value.substr(5, 2));
    day_ = std::stoi(value.substr(8, 2));
}

std::string DataDateProperty::getString() {
    // YYYY-MM-DD
    return fmt::format("{year:04}-{month:02}-{day:02}",
                       fmt::arg("year", year_),
                       fmt::arg("month", month_),
                       fmt::arg("day", day_));
}

bool DataDateProperty::decode(GribMessageHandler* handler) {
    year_ = static_cast<int>(handler->getLong("year"));
    month_ = static_cast<int>(handler->getLong("month"));
    day_ = static_cast<int>(handler->getLong("day"));
    return true;
}

} // namespace grib_coder
