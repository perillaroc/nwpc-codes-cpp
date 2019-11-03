#pragma once
#include <grib_property/computed/computed_property.h>

namespace grib_coder {

class LevelProperty : public ComputedProperty {
public:
    double getDouble() override {
        return value_;
    }

    std::string getString() override;

    bool decode(GribMessageHandler* handler) override;

private:
    void encodeToComponents() override;

    double value_ = std::numeric_limits<double>::max();
};

} // namespace grib_coder
