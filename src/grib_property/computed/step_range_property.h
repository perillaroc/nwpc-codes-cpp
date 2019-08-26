#pragma once

#include <grib_property/grib_property.h>

namespace grib_coder {

class StepRangeProperty: public GribProperty {
public:
    StepRangeProperty() = default;
    ~StepRangeProperty() = default;

    std::string getString() override;

    bool decode(GribPropertyContainer* container) override;

private:
    long start_ = -1;
    long end_ = -1;
};

} // namespace grib_coder