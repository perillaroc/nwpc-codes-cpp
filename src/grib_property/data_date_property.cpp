#include "data_date_property.h"
#include "grib_property_container.h"

#include <fmt/format.h>

#include <cmath>

namespace grib_coder {

void DataDateProperty::setLong(long value)
{
    year_ = std::floor(value / 10000);
    const auto month_day = value % 10000;
    month_ = std::floor(month_day / 100);
    day_ = month_day % 100;
}

long DataDateProperty::getLong()
{
    // YYYYMMDD
    return year_*10000 + month_*100 + day_;
}

void DataDateProperty::setDouble(double value)
{
    setLong(static_cast<long>(value));
}

double DataDateProperty::getDouble()
{
    // YYYYMMDD
    return static_cast<double>(getLong());
}

void DataDateProperty::setString(const std::string& value)
{
    // YYYY-MM-DD
    year_ = std::stoi(value.substr(0, 4));
    month_ = std::stoi(value.substr(5, 2));
    day_ = std::stoi(value.substr(8, 2));
}

std::string DataDateProperty::getString()
{
    // YYYY-MM-DD
    return fmt::format("{year:04}-{month:02}-{day:02}", 
        fmt::arg("year", year_),
        fmt::arg("month", month_),
        fmt::arg("day", day_));
}

bool DataDateProperty::decode(GribPropertyContainer* container)
{
    year_ = static_cast<int>(container->getLong("year"));
    month_ = static_cast<int>(container->getLong("month"));
    day_ = static_cast<int>(container->getLong("day"));
    return true;
}

} // namespace grib_coder