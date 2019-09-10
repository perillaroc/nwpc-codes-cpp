#include "grib_template.h"
#include "grib_section.h"

namespace grib_coder {

GribTemplate::GribTemplate(int template_length):
    template_length_{template_length} {
}

bool GribTemplate::decode(GribPropertyContainer* container) {
    return true;
}

} // namespace grib_coder
