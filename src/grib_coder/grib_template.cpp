#include "grib_template.h"

namespace grib_coder {

GribTemplate::GribTemplate(int template_length):
    template_length_{template_length} {
}

bool GribTemplate::parse(std::vector<std::byte>::const_iterator& iterator) {
    for (auto& component : components_) {
        component->parse(iterator);
    }
    return true;
}

} // namespace grib_coder
