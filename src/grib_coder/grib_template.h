#pragma once
#include <grib_property/grib_component.h>

namespace grib_coder {

class GribSection;
class GribMessageHandler;

class GribTemplate : public GribComponent {
public:
    explicit GribTemplate(int template_length);
    virtual ~GribTemplate() = default;

    long getByteCount() const override {
        return template_length_;
    }

    bool parse(std::vector<std::byte>::const_iterator& iterator) override;

    void dumpTemplate(GribMessageHandler* message_handler, std::size_t start_octec,
                      const DumpConfig& dump_config = DumpConfig{});

    virtual void registerProperty(std::shared_ptr<GribSection> section);
    virtual void unregisterProperty(std::shared_ptr<GribSection> section);

protected:
    std::vector<std::unique_ptr<GribComponent>> components_;

    std::string template_name_;
    long template_length_ = -1;
};
} // namespace grib_coder
