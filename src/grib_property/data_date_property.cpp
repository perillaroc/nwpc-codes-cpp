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
    return year_*10000 + month_*100 + day_;
}

void DataDateProperty::setDouble(double value)
{
    setLong(static_cast<long>(value));
}

double DataDateProperty::getDouble()
{
    return static_cast<double>(getLong());
}

void DataDateProperty::setString(const std::string& value)
{
    return setLong(std::stol(value));
}

std::string DataDateProperty::getString()
{
    return fmt::format("{}", getLong());
}

bool DataDateProperty::decode(GribPropertyContainer* container)
{
    year_ = static_cast<int>(container->getLong("year"));
    month_ = static_cast<int>(container->getLong("month"));
    day_ = static_cast<int>(container->getLong("day"));
    return true;
}

} // namespace grib_coder