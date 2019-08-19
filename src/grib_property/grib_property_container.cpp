#include "grib_property_container.h"

namespace grib_coder {
void GribPropertyContainer::setLong(const std::string& key, long value)
{
    throw std::exception("not implemented");
}
long GribPropertyContainer::getLong(const std::string& key)
{
    throw std::exception("not implemented");
}
void GribPropertyContainer::setDouble(const std::string& key, double value)
{
    throw std::exception("not implemented");
}
double GribPropertyContainer::getDouble(const std::string& key)
{
    throw std::exception("not implemented");
}
void GribPropertyContainer::setString(const std::string& key, const std::string& value)
{
    throw std::exception("not implemented");
}
std::string GribPropertyContainer::getString(const std::string& key)
{
    throw std::exception("not implemented");
}
void GribPropertyContainer::setDoubleArray(const std::string& key, std::vector<double>& values)
{
    throw std::exception("not implemented");
}
std::vector<double> GribPropertyContainer::getDoubleArray(const std::string& key)
{
    throw std::exception("not implemented");
}
} // namespace grib_coder