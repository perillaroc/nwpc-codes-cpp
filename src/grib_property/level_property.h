#pragma once
#include "grib_property/grib_property.h"

namespace grib_coder {

class LevelProperty: public GribProperty {
public:
    LevelProperty();
    ~LevelProperty() = default;

    double getDouble() override {
        return value_;
    }

    std::string getString() override;
    
    bool decode(GribPropertyContainer* container) override;

private:
    double value_;
};

} // namespace grib_coder