#include "sections/grib_section_4.h"
#include "sections/grib_section_0.h"
#include "templates/template_4_0.h"
#include "templates/template_4_8.h"
#include "templates/template_4_11.h"
#include "number_convert.h"

#include <vector>
#include <sstream>
#include <cassert>
#include <stdexcept>

namespace grib_coder {
GribSection4::GribSection4():
    GribSection{4} {
    init();
}

GribSection4::GribSection4(int section_length):
    GribSection{4, section_length} {
    assert(section_length_ == 34 || section_length_ == 58 || section_length_ == 61);
    init();
}

bool GribSection4::parseFile(std::FILE* file, bool header_only) {
    const auto buffer_length = section_length_ - 5;
    std::vector<std::byte> buffer(section_length_);
    const auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
    if (static_cast<long>(read_count) != buffer_length) {
        return false;
    }

    nv_ = convert_bytes_to_uint16(&buffer[5], 2);
    const auto product_definition_template_number = convert_bytes_to_uint16(&buffer[7], 2);

    // TODO: different product definition template
    assert(
        product_definition_template_number == 0 \
        || product_definition_template_number == 8 \
        || product_definition_template_number == 11 
    );

    product_definition_template_number_.setLong(product_definition_template_number);

    auto template_length = section_length_ - 9;

    if (product_definition_template_number == 0) {
        product_definition_template_ = std::make_shared<Template_4_0>(template_length);
    } else if (product_definition_template_number == 8) {
        product_definition_template_ = std::make_shared<Template_4_8>(template_length);
    } else if (product_definition_template_number == 11) {
        product_definition_template_ = std::make_shared<Template_4_11>(template_length);
    } else {
        throw std::runtime_error("template not implemented");
    }
    product_definition_template_->registerProperty(shared_from_this());
    product_definition_template_->parse(buffer);

    return true;
}

bool GribSection4::decode(GribPropertyContainer* container) {
    return product_definition_template_->decode(container);
}

void GribSection4::init() {
    std::vector<std::tuple<CodeTableProperty*, std::string>> tables_id{
        { &product_definition_template_number_, "4.0" },
    };
    for (const auto& item : tables_id) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }

    product_definition_template_number_.setOctetCount(2);


    std::vector<std::tuple<std::string, GribProperty*>> properties_name{
        { "nv", &nv_ },
        { "productDefinitionTemplateNumber", &product_definition_template_number_ },
    };
    for (const auto& item : properties_name) {
        registerProperty(std::get<0>(item), std::get<1>(item));
    }
}

} // namespace grib_coder
