#pragma once
#include <grib_property/grib_property.h>

namespace grib_coder {

class LevelProperty : public GribProperty {
public:
    double getDouble() override {
        return value_;
    }

    std::string getString() override;

    bool decode(GribMessageHandler* container) override;

private:
    double value_ = std::numeric_limits<double>::max();
};

} // namespace grib_coder
