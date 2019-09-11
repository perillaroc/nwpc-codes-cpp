#include "property_component.h"
#include "grib_property.h"

namespace grib_coder {
PropertyComponent::PropertyComponent(int byte_count, GribProperty* property):
    byte_count_{ byte_count },
    property_{property}
{
}
void PropertyComponent::setByteCount(const int byte_count)
{
    byte_count_ = byte_count;
}

GribProperty* PropertyComponent::getProperty() {
    return property_;
}

bool PropertyComponent::parse(std::vector<std::byte>::const_iterator& iterator) {
    property_->parse(iterator, byte_count_);
    iterator += byte_count_;
    return true;
}

bool PropertyComponent::decode(GribPropertyContainer* container)
{
    return property_->decode(container);
}
} // namespace grib_coder