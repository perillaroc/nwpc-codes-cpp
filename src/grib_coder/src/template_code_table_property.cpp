#include "template_code_table_property.h"

namespace grib_coder {

void TemplateCodeTableProperty::setGenerateFunction(const GenerateFunction &generate_function) {
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
} // namespace