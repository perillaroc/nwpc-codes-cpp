#include "grib_property.h"

#include <fmt/format.h>

#include <stdexcept>

namespace grib_coder {
void GribProperty::setLong(long value) {
    throw std::runtime_error("not implemented");
}

long GribProperty::getLong() {
    throw std::runtime_error("not implemented");
}

void GribProperty::setDouble(double value) {
    throw std::runtime_error("not implemented");
}

double GribProperty::getDouble() {
    throw std::runtime_error("not implemented");
}

void GribProperty::setString(const std::string& value) {
    throw std::runtime_error("not implemented");
}

std::string GribProperty::getString() {
    throw std::runtime_error("not implemented");
}

void GribProperty::setDoubleArray(std::vector<double>& values) {
    throw std::runtime_error("not implemented");
}

std::vector<double> GribProperty::getDoubleArray() {
    throw std::runtime_error("not implemented");
}

bool GribProperty::parse(std::vector<std::byte>::const_iterator& iterator, size_t count) {
    return true;
}

bool GribProperty::decode(GribPropertyContainer* container) {
    return true;
}

void GribProperty::dump(const DumpConfig& dump_config) {
    fmt::print("not implemented");
}

} // namespace grib_coder
