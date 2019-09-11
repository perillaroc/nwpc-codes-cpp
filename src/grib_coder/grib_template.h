#pragma once
#include <grib_property/grib_component.h>

namespace grib_coder {

class GribSection;

class GribTemplate: public GribComponent {
public:
    explicit GribTemplate(int template_length);
    virtual ~GribTemplate() = default;

    bool parse(std::vector<std::byte>::const_iterator& iterator) override;

    virtual void registerProperty(std::shared_ptr<GribSection> section) = 0;

protected:
    std::string template_name_;
    int template_length_ = -1;

    std::vector<std::unique_ptr<GribComponent>> components_;
};
} // namespace grib_coder
