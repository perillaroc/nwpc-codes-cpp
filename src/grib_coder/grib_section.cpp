#include "grib_section.h"
#include "grib_message_handler.h"
#include "template_component.h"

#include <grib_property/property_component.h>
#include <grib_property/code_table_property.h>

#include <iterator>

namespace grib_coder {

GribSection::GribSection(int section_number):
    GribSection{section_number, 0} {
}

GribSection::GribSection(int section_number, long section_length):
    section_number_{section_number},
    section_length_{section_length} {
}

void GribSection::setLong(const std::string& key, long value) {
    auto property = getProperty(key);
    if (property == nullptr) {
        throw std::runtime_error("key is not found");
    }
    property->setLong(value);
}

long GribSection::getLong(const std::string& key) {
    auto property = getProperty(key);
    if (property == nullptr) {
        throw std::runtime_error("key is not found");
    }
    return property->getLong();
}

void GribSection::setDouble(const std::string& key, double value) {
    auto property = getProperty(key);
    if (property == nullptr) {
        throw std::runtime_error("key is not found");
    }
    property->setDouble(value);
}

double GribSection::getDouble(const std::string& key) {
    auto property = getProperty(key);
    if (property == nullptr) {
        throw std::runtime_error("key is not found");
    }
    return property->getDouble();
}

void GribSection::setString(const std::string& key, const std::string& value) {
    auto property = getProperty(key);
    if (property == nullptr) {
        throw std::runtime_error("key is not found");
    }
    property->setString(value);
}

std::string GribSection::getString(const std::string& key) {
    auto property = getProperty(key);
    if (property == nullptr) {
        throw std::runtime_error("key is not found");
    }
    return property->getString();
}

void GribSection::setDoubleArray(const std::string& key, std::vector<double>& values) {
    auto property = getProperty(key);
    if (property == nullptr) {
        throw std::runtime_error("key is not found");
    }
    property->setDoubleArray(values);
}

std::vector<double> GribSection::getDoubleArray(const std::string& key) {
    auto property = getProperty(key);
    if (property == nullptr) {
        throw std::runtime_error("key is not found");
    }
    return property->getDoubleArray();
}

bool GribSection::hasProperty(const std::string& key) {
    const auto property = getProperty(key);
    return property != nullptr;
}

void GribSection::setSectionLength(long length) {
    section_length_.setLong(length);
}

long GribSection::getSectionLength() const {
    return static_cast<long>(section_length_);
}

long GribSection::getByteCount() const {
    return static_cast<long>(section_length_);
}

int GribSection::getSectionNumber() const {
    return static_cast<int>(section_number_);
}

bool GribSection::decode(GribMessageHandler* handler) {
    return true;
}

GribProperty* GribSection::getProperty(const std::string& name) {
    const auto property = property_map_.find(name);
    if (property == std::end(property_map_)) {
        return nullptr;
    }
    return property->second;
}

void GribSection::registerProperty(const std::string& name, GribProperty* property) {
    property_map_[name] = property;
}

void GribSection::unregisterProperty(const std::string& name)
{
    property_map_.erase(name);
}

void GribSection::dumpSection(GribMessageHandler* message_handler, std::size_t start_octec,
                              const DumpConfig& dump_config) {
    auto octec_index = start_octec;
    if (section_number_ == 0) {
        fmt::print("===============   MESSAGE {} ( length={} )    ================\n",
                   message_handler->getLong("count"), message_handler->getLong("totalLength"));
    } else {
        fmt::print(
            "======================   SECTION_{} ( length={} )    ======================\n",
            section_number_.getLong(),
            section_length_.getLong());
    }

    const auto tables_version = fmt::format("{}", message_handler->getLong("tablesVersion"));

    for (const auto& component : components_) {
        auto property_component = dynamic_cast<PropertyComponent*>(component.get());
        if (property_component) {
            auto code_table_property = dynamic_cast<CodeTableProperty*>(property_component->getProperty());
            if (code_table_property) {
                code_table_property->setTableDatabase(message_handler->getTableDatabase());
                code_table_property->setTablesVersion(tables_version);
            }
            component->dump(octec_index, dump_config);
            octec_index += component->getByteCount();
            continue;
        }

        auto template_component = dynamic_cast<TemplateComponent*>(component.get());
        if (template_component) {
            template_component->dumpTemplate(message_handler, octec_index, dump_config);
            octec_index += component->getByteCount();
            continue;
        }

        // should not be here
        throw std::runtime_error("component is not supported");
    }
}

GribProperty* get_property_from_section_list(
    const std::string& name, std::vector<std::shared_ptr<GribSection>>& section_list) {
    for (auto iter = std::rbegin(section_list); iter != std::rend(section_list); ++iter) {
        auto property = (*iter)->getProperty(name);
        if (property) {
            return property;
        }
    }
    return nullptr;
}

} // namespace grib_coder
