#pragma once
#include <grib_property/grib_property_container.h>


namespace grib_coder {
class GribComponent: public GribPropertyContainer {
public:

    // parse binary bytes read from grib message
    virtual bool parse(std::vector<std::byte>::const_iterator& iterator);

    // decode properties using previous sections.
    virtual bool decode(GribPropertyContainer* container);
};

} // namespace grib_coder