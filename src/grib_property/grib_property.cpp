#include "grib_property.h"

namespace grib_coder {
void GribProperty::setLong(long value)
{
    throw std::exception("not implemented");
}
long GribProperty::getLong()
{
    throw std::exception("not implemented");
}
void GribProperty::setDouble(double value)
{
    throw std::exception("not implemented");
}
double GribProperty::getDouble()
{
    throw std::exception("not implemented");
}
void GribProperty::setString(const std::string& value)
{
    throw std::exception("not implemented");
}
std::string GribProperty::getString()
{
    throw std::exception("not implemented");
}
void GribProperty::setDoubleArray(std::vector<double>& values)
{
    throw std::exception("not implemented");
}
std::vector<double> GribProperty::getDoubleArray()
{
    throw std::exception("not implemented");
}
} // namespace grib_coder
