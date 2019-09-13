#include "grib_template.h"
#include "grib_section.h"

#include <grib_property/property_component.h>

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

void GribTemplate::registerProperty(std::shared_ptr<GribSection> section) {
    for (const auto& component : components_) {
        auto property_component = dynamic_cast<PropertyComponent*>(component.get());
        if (property_component) {
            section->registerProperty(property_component->getPropertyName(), property_component->getProperty());
        }
    }
}

} // namespace grib_coder
