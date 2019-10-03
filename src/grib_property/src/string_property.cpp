#include "string_property.h"
#include <fmt/format.h>

namespace grib_coder {

void StringProperty::setString(const std::string& value) {
    value_ = value;
}

std::string StringProperty::getString() {
    return value_;
}

bool StringProperty::parse(std::vector<std::byte>::const_iterator& iterator, size_t count) {
    value_ = std::string(reinterpret_cast<const char*>(&(*iterator)), count);
    return true;
}

void StringProperty::dump(const DumpConfig& dump_config) {
    fmt::print("{}", value_);
}

void StringProperty::pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) {
    std::vector<std::byte> bytes(value_.size());
    std::transform(std::begin(value_), std::end(value_), std::begin(bytes),
        [](char c) { return std::byte(c); });
    std::copy(std::begin(bytes), std::end(bytes), iterator);
}

} // namespace grib_coder
