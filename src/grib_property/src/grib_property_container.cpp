#include "grib_property_container.h"
#include <stdexcept>

namespace grib_coder {
void GribPropertyContainer::setLong(const std::string& key, long value) {
    throw std::runtime_error("setLong: not implemented");
}

long GribPropertyContainer::getLong(const std::string& key) {
    throw std::runtime_error("getLong: not implemented");
}

void GribPropertyContainer::setDouble(const std::string& key, double value) {
    throw std::runtime_error("setDouble: not implemented");
}

double GribPropertyContainer::getDouble(const std::string& key) {
    throw std::runtime_error("getDouble: not implemented");
}

void GribPropertyContainer::setString(const std::string& key, const std::string& value) {
    throw std::runtime_error("setString: not implemented");
}

std::string GribPropertyContainer::getString(const std::string& key) {
    throw std::runtime_error("getString: not implemented");
}

void GribPropertyContainer::setDoubleArray(const std::string& key, std::vector<double>& values) {
    throw std::runtime_error("setDoubleArray: not implemented");
}

std::vector<double> GribPropertyContainer::getDoubleArray(const std::string& key) {
    throw std::runtime_error("getDoubleArray: not implemented");
}

bool GribPropertyContainer::hasProperty(const std::string& key) {
    throw std::runtime_error("hasProperty: not implemented");
}

} // namespace grib_coder
