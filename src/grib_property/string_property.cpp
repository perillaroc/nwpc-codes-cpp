#include "string_property.h"

namespace grib_coder {

void StringProperty::setString(const std::string& value)
{
    value_ = value;
}

std::string StringProperty::getString()
{
    return value_;
}

bool StringProperty::parse(std::vector<std::byte>::const_iterator& iterator, size_t count) {
    value_ = std::string(reinterpret_cast<const unsigned char*>(&(*iterator)), 
        reinterpret_cast<const unsigned char*>(&(*(iterator+count))));
    return true;
}

} // namespace grib_coder