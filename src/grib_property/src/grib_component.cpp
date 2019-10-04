#include "grib_component.h"
#include <fmt/format.h>

namespace grib_coder {

bool GribComponent::parse(std::vector<std::byte>::const_iterator& iterator) {
    return true;
}

bool GribComponent::decode(GribMessageHandler* handler) {
    return true;
}

void GribComponent::dump(std::size_t start_octec, const DumpConfig& dump_config) {
}

bool GribComponent::encode(GribMessageHandler* handler) {
    return true;
}

void GribComponent::pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) {
    fmt::print(stderr, "GribComponent::pack() is not implemented");
}


} // namespace grib_coder
