#pragma once

#include <grib_property/grib_property.h>

namespace grib_coder {

class StepRangeProperty : public GribProperty {
public:
    std::string getString() override;

    bool decode(GribMessageHandler* container) override;

private:
    long start_ = -1;
    long end_ = -1;
};

} // namespace grib_coder
