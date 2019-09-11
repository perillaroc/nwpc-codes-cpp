#include "grib_component.h"

namespace grib_coder {

bool GribComponent::parse(std::vector<std::byte>& buffer) {
    return true;
}

bool GribComponent::decode(GribPropertyContainer* container) {
    return true;
}

} // namespace grib_coder