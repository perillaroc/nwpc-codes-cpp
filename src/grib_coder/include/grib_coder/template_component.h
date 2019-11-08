#pragma once
#include <grib_property/grib_component.h>
#include <grib_coder/template_code_table_property.h>

#include <functional>

namespace grib_coder {
class GribTemplate;
class GribSection;
class GribMessageHandler;

class TemplateComponent final: public GribComponent {
public:
    TemplateComponent() = default;

    // create using default constructor and register itself to TemplateCodeTableProperty
    explicit TemplateComponent(TemplateCodeTableProperty& property);

    void setTemplate(std::unique_ptr<GribTemplate>&& grib_template);

    bool parse(std::vector<std::byte>::const_iterator& iterator) override;

    bool decode(GribMessageHandler* handler) override;

    void dumpTemplate(GribMessageHandler* message_handler, std::size_t start_octec,
                      const DumpConfig& dump_config = DumpConfig{});

    void pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) override;

    // register all properties into section's property_map_
    void registerProperty(std::shared_ptr<GribSection> &section);

    // unregister all properties from section's property_map_
    void unregisterProperty(std::shared_ptr<GribSection> &section);

    long getByteCount() const override;

private:
    std::unique_ptr<GribTemplate> grib_template_;
};


} // namespace grib_coder
