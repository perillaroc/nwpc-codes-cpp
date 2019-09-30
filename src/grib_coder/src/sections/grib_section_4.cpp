#include "grib_coder/sections/grib_section_4.h"
#include "grib_coder/templates/template_4_0.h"
#include "grib_coder/templates/template_4_1.h"
#include "grib_coder/templates/template_4_8.h"
#include "grib_coder/templates/template_4_11.h"
#include "grib_coder/template_component.h"

#include <grib_property/property_component.h>

#include <gsl/span>

#include <cassert>
#include <stdexcept>

namespace grib_coder {
GribSection4::GribSection4():
    GribSection{4} {
    init();
}

GribSection4::GribSection4(int section_length):
    GribSection{4, section_length} {
    assert(section_length_ >= 9);
    init();
}

GribSection4::~GribSection4() {
}

bool GribSection4::parseFile(std::FILE* file, bool header_only) {
    const auto buffer_length = section_length_ - 5;
    std::vector<std::byte> buffer(section_length_);
    const auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
    if (static_cast<long>(read_count) != buffer_length) {
        return false;
    }

    auto iterator = std::cbegin(buffer) + 5;

    auto component_span = gsl::make_span(components_);
    auto sub_component_span = component_span.subspan(2);

    for (auto& component : sub_component_span) {
        component->parse(iterator);
    }

    return true;
}

bool GribSection4::decode(GribMessageHandler* container) {
    for(auto &component: components_) {
        const auto result = component->decode(container);
        if (!result) { return false; }
    }
    return true;
}

void GribSection4::init() {
    product_definition_template_number_.setOctetCount(2);
    product_definition_template_number_.setGenerateFunction([this](TemplateComponent* template_component) {
        this->generateProductionTemplate(template_component);
    });

    std::vector<std::tuple<size_t, std::string, GribProperty*>> components{
        {4, "section4Length", &section_length_},
        {1, "numberOfSection", &section_number_},
        {2, "nv", &nv_},
        {2, "productDefinitionTemplateNumber", &product_definition_template_number_},
    };

    for (auto& item : components) {
        components_.push_back(
            std::make_unique<PropertyComponent>(std::get<0>(item), std::get<1>(item), std::get<2>(item)));
        registerProperty(std::get<1>(item), std::get<2>(item));
    }

    components_.push_back(std::make_unique<TemplateComponent>(product_definition_template_number_));

    std::vector<std::tuple<CodeTableProperty*, std::string>> tables_id{
        {&product_definition_template_number_, "4.0"},
    };
    for (const auto& item : tables_id) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }
}

void GribSection4::generateProductionTemplate(TemplateComponent* template_component) {
    auto section = std::dynamic_pointer_cast<GribSection>(shared_from_this());

    template_component->unregisterProperty(section);

    auto template_length = section_length_.getLong()- 9;

    auto product_definition_template_number = product_definition_template_number_.getLong();
    if (product_definition_template_number == 0) {
        template_component->setTemplate(std::make_unique<Template_4_0>(template_length));
    }
    else if (product_definition_template_number == 1) {
        template_component->setTemplate(std::make_unique<Template_4_1>(template_length));
    }
    else if (product_definition_template_number == 8) {
        template_component->setTemplate(std::make_unique<Template_4_8>(template_length));
    }
    else if (product_definition_template_number == 11) {
        template_component->setTemplate(std::make_unique<Template_4_11>(template_length));
    }
    else {
        throw std::runtime_error(
            fmt::format("template not implemented: {}", product_definition_template_number));
    }
    template_component->registerProperty(section);
}

} // namespace grib_coder
