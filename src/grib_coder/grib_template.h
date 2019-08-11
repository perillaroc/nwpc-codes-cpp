#pragma once
#include <string>
#include <memory>

#include "grib_section.h"

namespace GribCoder {

class GribTemplate {
public:
    GribTemplate(int template_length);
    ~GribTemplate();

    virtual bool parse(std::vector<unsigned char> &buffer) = 0;
    virtual bool decode(std::vector<std::shared_ptr<GribSection>> section_list);

    virtual void registerProperty(std::shared_ptr<GribSection> section) = 0;
    
protected:
    std::string template_name_;
    int template_length_ = -1;
};
}