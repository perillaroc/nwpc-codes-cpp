#pragma once

#include <grib_property/code_table_property.h>

#include <functional>

namespace grib_coder {

class TemplateComponent;

class TemplateCodeTableProperty final: public CodeTableProperty {
public:
    using generate_function = std::function<void(TemplateComponent*)>;

    void setGenerateFunction(const generate_function &generate_function);

    void setTemplateComponent(TemplateComponent* template_component);

    // parse CodeTableProperty and create template in TemplateComponent using generate_function
    bool parse(std::vector<std::byte>::const_iterator& iterator, size_t count = 1) override;

    void setLong(long value) override;
    void setDouble(double value) override;

private:
    // generate template using generate_function.
    generate_function generate_function_;

    // template component which is controlled by this property.
    TemplateComponent* template_component_ = nullptr;
};

} // namespace grib_coder