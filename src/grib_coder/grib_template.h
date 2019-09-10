#pragma once
#include <grib_property/grib_component.h>

namespace grib_coder {

class GribSection;

class GribTemplate: public GribComponent {
public:
    explicit GribTemplate(int template_length);
    virtual ~GribTemplate() = default;

    virtual bool parse(std::vector<std::byte>& buffer) = 0;
    virtual bool decode(GribPropertyContainer* container);

    virtual void registerProperty(std::shared_ptr<GribSection> section) = 0;

protected:
    std::string template_name_;
    int template_length_ = -1;
};
} // namespace grib_coder
