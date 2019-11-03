#pragma once

#include <grib_property/computed/computed_property.h>

namespace grib_coder {

class StepRangeProperty : public ComputedProperty {
public:
    std::string getString() override;

    bool decode(GribMessageHandler* handler) override;

private:
    void encodeToComponents() override;

    long start_ = -1;
    long end_ = -1;
};

} // namespace grib_coder
