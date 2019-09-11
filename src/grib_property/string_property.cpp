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

} // namespace grib_coder