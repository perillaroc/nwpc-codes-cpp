#include <grib_coder/template_code_table_property.h>

#include <stdexcept>

namespace grib_coder {

void TemplateCodeTableProperty::setGenerateFunction(const generate_function &generate_function) {
    generate_function_ = generate_function;
}

void TemplateCodeTableProperty::setTemplateComponent(TemplateComponent* template_component) {
    template_component_ = template_component;
}

bool TemplateCodeTableProperty::parse(std::vector<std::byte>::const_iterator& iterator, size_t count) {
    const auto result = CodeTableProperty::parse(iterator, count);
	if(!result) {
        return result;
	}
	if(template_component_ == nullptr) {
        return false;
	}
    generate_function_(template_component_);

    return true;
}

void TemplateCodeTableProperty::setLong(long value) {
    CodeTableProperty::setLong(value);
    if(template_component_==nullptr) {
        throw std::runtime_error("template component must be set.");
    }
    generate_function_(template_component_);
}

void TemplateCodeTableProperty::setDouble(double value) {
    CodeTableProperty::setDouble(value);
    if (template_component_ == nullptr) {
        throw std::runtime_error("template component must be set.");
    }
    generate_function_(template_component_);
}
} // namespace