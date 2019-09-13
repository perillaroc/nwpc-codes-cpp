#include "template_component.h"
#include "template_component.h"

#include "grib_template.h"
#include "grib_section.h"

namespace grib_coder {
TemplateComponent::TemplateComponent(std::function<void()> generate_function):
    generate_function_{std::move(generate_function)}
{
}

void TemplateComponent::setTemplate(std::unique_ptr<GribTemplate>&& grib_template) {
    grib_template_ = std::move(grib_template);
}

void TemplateComponent::setGenerateFunction(std::function<void()> generate_function) {
    generate_function_ = std::move(generate_function);
}

bool TemplateComponent::parse(std::vector<std::byte>::const_iterator& iterator)
{
    generate_function_();
    return grib_template_->parse(iterator);;
}
bool TemplateComponent::decode(GribPropertyContainer* container)
{
    return grib_template_->decode(container);
}
void TemplateComponent::dump(GribMessageHandler* message_handler, std::size_t start_octec, const DumpConfig& dump_config)
{
    grib_template_->dump(message_handler, start_octec, dump_config);
}

void TemplateComponent::registerProperty(std::shared_ptr<GribSection> section) {
    grib_template_->registerProperty(section);
}
} // namespace grib_coder