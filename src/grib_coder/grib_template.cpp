#include "grib_template.h"

namespace grib_coder {

GribTemplate::GribTemplate(int template_length):
    template_length_{ template_length }
{
}

GribTemplate::~GribTemplate()
{
}

bool GribTemplate::decode(std::vector<std::shared_ptr<GribSection>> section_list)
{
    return true;
}

} // namespace grib_coder