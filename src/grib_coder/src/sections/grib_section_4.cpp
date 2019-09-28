#include "grib_coder/sections/grib_section_4.h"
#include "grib_coder/templates/template_4_0.h"
#include "grib_coder/templates/template_4_1.h"
#include "grib_coder/templates/template_4_8.h"
#include "grib_coder/templates/template_4_11.h"

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
    return product_definition_template_->decode(container);
}

void GribSection4::init() {
    product_definition_template_ = new TemplateComponent{};

    product_definition_template_number_.setOctetCount(2);

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

    product_definition_template_->setGenerateFunction(
        [this]() {
            this->generateProductionDefinitionTemplate();
        });
    components_.push_back(std::unique_ptr<TemplateComponent>(product_definition_template_));

    std::vector<std::tuple<CodeTableProperty*, std::string>> tables_id{
        {&product_definition_template_number_, "4.0"},
    };
    for (const auto& item : tables_id) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }
}

void GribSection4::generateProductionDefinitionTemplate() {
    auto template_length = section_length_ - 9;
    product_definition_template_->setByteCount(template_length);
    const auto product_definition_template_number = product_definition_template_number_.getLong();

    if (product_definition_template_number == 0) {
        product_definition_template_->setTemplate(std::make_unique<Template_4_0>(template_length));
    } else if (product_definition_template_number == 1) {
        product_definition_template_->setTemplate(std::make_unique<Template_4_1>(template_length));
    } else if (product_definition_template_number == 8) {
        product_definition_template_->setTemplate(std::make_unique<Template_4_8>(template_length));
    } else if (product_definition_template_number == 11) {
        product_definition_template_->setTemplate(std::make_unique<Template_4_11>(template_length));
    } else {
        throw std::runtime_error(fmt::format("template not implemented: {}", product_definition_template_number));
    }
    product_definition_template_->registerProperty(std::dynamic_pointer_cast<GribSection>(shared_from_this()));
}

} // namespace grib_coder
