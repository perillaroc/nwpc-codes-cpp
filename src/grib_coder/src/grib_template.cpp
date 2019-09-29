#include "grib_template.h"
#include "grib_section.h"
#include "grib_message_handler.h"

#include <grib_property/property_component.h>
#include <grib_property/code_table_property.h>

#include <fmt/format.h>

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

void GribTemplate::dumpTemplate(GribMessageHandler* message_handler, std::size_t start_octec,
                                const DumpConfig& dump_config) {
    auto octec_index = start_octec;
    auto tables_version = fmt::format("{}", message_handler->getLong("tablesVersion"));

    for (const auto& component : components_) {
        auto property_component = dynamic_cast<PropertyComponent*>(component.get());
        if (property_component) {
            auto code_table_property = dynamic_cast<CodeTableProperty*>(property_component->getProperty());
            if (code_table_property) {
                code_table_property->setTableDatabase(message_handler->getTableDatabase());
                code_table_property->setTablesVersion(tables_version);
            }
        }
        component->dump(octec_index, dump_config);
        octec_index += component->getByteCount();
    }
}

void GribTemplate::registerProperty(std::shared_ptr<GribSection> &section) {
    for (const auto& component : components_) {
        auto property_component = dynamic_cast<PropertyComponent*>(component.get());
        if (property_component) {
            section->registerProperty(property_component->getPropertyName(), property_component->getProperty());
        }
    }
}

void GribTemplate::unregisterProperty(std::shared_ptr<GribSection> &section)
{
    for (const auto& component : components_) {
        const auto property_component = dynamic_cast<PropertyComponent*>(component.get());
        if (property_component) {
            section->unregisterProperty(property_component->getPropertyName());
        }
    }
}

} // namespace grib_coder
