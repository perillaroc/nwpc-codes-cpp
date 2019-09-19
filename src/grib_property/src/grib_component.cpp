#include "grib_component.h"

namespace grib_coder {

bool GribComponent::parse(std::vector<std::byte>::const_iterator& iterator) {
    return true;
}

bool GribComponent::decode(GribMessageHandler* handler) {
    return true;
}

void GribComponent::dump(std::size_t start_octec, const DumpConfig& dump_config) {
    return;
}


} // namespace grib_coder
