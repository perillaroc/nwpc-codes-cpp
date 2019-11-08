#include <grib_coder/template_component.h>

#include <grib_coder/grib_template.h>
#include <grib_coder/grib_section.h>

namespace grib_coder {

TemplateComponent::TemplateComponent(TemplateCodeTableProperty& property):
    TemplateComponent{} {
    property.setTemplateComponent(this);
}

void TemplateComponent::setTemplate(std::unique_ptr<GribTemplate>&& grib_template) {
    grib_template_ = std::move(grib_template);
}


bool TemplateComponent::parse(std::vector<std::byte>::const_iterator& iterator) {
    return grib_template_->parse(iterator);;
}

bool TemplateComponent::decode(GribMessageHandler* handler) {
    return grib_template_->decode(handler);
}

void TemplateComponent::dumpTemplate(
    GribMessageHandler* message_handler, 
    std::size_t start_octec,
    const DumpConfig& dump_config
) {
    grib_template_->dumpTemplate(message_handler, start_octec, dump_config);
}

void TemplateComponent::pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) {
    grib_template_->pack(iterator);
}

void TemplateComponent::registerProperty(std::shared_ptr<GribSection> &section) {
    grib_template_->registerProperty(section);
}

void TemplateComponent::unregisterProperty(std::shared_ptr<GribSection> &section) {
    if(grib_template_ == nullptr) {
        return;
    }

    grib_template_->unregisterProperty(section);
}

long TemplateComponent::getByteCount() const {
    return grib_template_->getByteCount();
}
} // namespace grib_coder
