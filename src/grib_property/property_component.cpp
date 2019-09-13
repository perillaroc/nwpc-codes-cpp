#include "property_component.h"
#include "grib_property.h"

namespace grib_coder {
PropertyComponent::PropertyComponent(int byte_count, std::string property_name, GribProperty* property):
    byte_count_{ byte_count },
    property_name_{std::move(property_name)},
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

std::string PropertyComponent::getPropertyName() const {
    return property_name_;
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

void PropertyComponent::dump(std::size_t start_octec, const DumpConfig& dump_config) {
    return;
}


} // namespace grib_coder