#include "grib_template.h"

namespace GribCoder {

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

} // namespace GribCoder