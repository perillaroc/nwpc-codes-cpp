#pragma once
#include "grib_section.h"

namespace grib_coder {

class GribTemplate {
public:
    explicit GribTemplate(int template_length);
    virtual ~GribTemplate();

    virtual bool parse(std::vector<unsigned char> &buffer) = 0;
    virtual bool decode(GribPropertyContainer *container);

    virtual void registerProperty(std::shared_ptr<GribSection> section) = 0;
    
protected:
    std::string template_name_;
    int template_length_ = -1;
};
}