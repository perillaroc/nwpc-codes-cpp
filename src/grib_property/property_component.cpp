#include "property_component.h"
#include "grib_property.h"

#include <fmt/printf.h>

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
    std::string octec_range;
    if(byte_count_==1) {
        octec_range = fmt::format("{}", start_octec);
    } else {
        const auto end_octec = start_octec + byte_count_ - 1;
        octec_range = fmt::format("{}-{}", start_octec, end_octec);        
    }
    const auto octec_column = fmt::format("{:<{}}", octec_range, dump_config.octet_column_length);
    const auto property_name = fmt::format("{} = ", property_name_);
    fmt::print("{}{}", octec_column, property_name);
    property_->dump(dump_config);
    fmt::print("\n");
}


} // namespace grib_coder