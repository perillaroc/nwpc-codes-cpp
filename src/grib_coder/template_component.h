#pragma once
#include <grib_property/grib_component.h>

#include <functional>

namespace grib_coder {
class GribTemplate;
class GribSection;
class GribMessageHandler;

class TemplateComponent : public GribComponent {
public:
    TemplateComponent() = default;
    explicit TemplateComponent(std::function<void()> generate_function);

    void setTemplate(std::unique_ptr<GribTemplate>&& grib_template);
    void setGenerateFunction(std::function<void()> generate_function);

    // parse binary bytes read from grib message
    bool parse(std::vector<std::byte>::const_iterator& iterator) override;

    bool decode(GribPropertyContainer* container) override;

    void dumpTemplate(GribMessageHandler* message_handler, std::size_t start_octec, const DumpConfig& dump_config = DumpConfig{});

    void registerProperty(std::shared_ptr<GribSection> section);

    void setByteCount(long byte_count) {
        byte_count_ = byte_count;
    }

    long getByteCount() const override {
        return byte_count_;
    }

private:
    long byte_count_ = 0;

    std::function<void()> generate_function_;
    std::unique_ptr<GribTemplate> grib_template_;
};


} // namespace grib_coder