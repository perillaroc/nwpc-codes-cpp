#include "grib_property_container.h"
#include <stdexcept>

namespace grib_coder {
void GribPropertyContainer::setLong(const std::string& key, long value) {
    throw std::runtime_error("not implemented");
}

long GribPropertyContainer::getLong(const std::string& key) {
    throw std::runtime_error("not implemented");
}

void GribPropertyContainer::setDouble(const std::string& key, double value) {
    throw std::runtime_error("not implemented");
}

double GribPropertyContainer::getDouble(const std::string& key) {
    throw std::runtime_error("not implemented");
}

void GribPropertyContainer::setString(const std::string& key, const std::string& value) {
    throw std::runtime_error("not implemented");
}

std::string GribPropertyContainer::getString(const std::string& key) {
    throw std::runtime_error("not implemented");
}

void GribPropertyContainer::setDoubleArray(const std::string& key, std::vector<double>& values) {
    throw std::runtime_error("not implemented");
}

std::vector<double> GribPropertyContainer::getDoubleArray(const std::string& key) {
    throw std::runtime_error("not implemented");
}
} // namespace grib_coder
