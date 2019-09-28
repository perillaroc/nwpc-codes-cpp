#pragma once
#include <grib_property/grib_component.h>

#include <functional>

namespace grib_coder {
class GribTemplate;
class GribSection;
class GribMessageHandler;

class TemplateComponent : public GribComponent {
public:
    using GenerateFunction = std::function<void()>;

    TemplateComponent() = default;
    explicit TemplateComponent(GenerateFunction generate_function);

    void setTemplate(std::unique_ptr<GribTemplate>&& grib_template);
    void setGenerateFunction(GenerateFunction generate_function);

    // call GenerateFunction and parse binary bytes read from grib message
    bool parse(std::vector<std::byte>::const_iterator& iterator) override;

    bool decode(GribMessageHandler* handler) override;

    void dumpTemplate(GribMessageHandler* message_handler, std::size_t start_octec,
                      const DumpConfig& dump_config = DumpConfig{});

    void registerProperty(std::shared_ptr<GribSection> section);
    void unregisterProperty(std::shared_ptr<GribSection> section);

    void setByteCount(long byte_count) {
        byte_count_ = byte_count;
    }

    long getByteCount() const override {
        return byte_count_;
    }

private:
    long byte_count_ = 0;

    GenerateFunction generate_function_;
    std::unique_ptr<GribTemplate> grib_template_;
};


} // namespace grib_coder
