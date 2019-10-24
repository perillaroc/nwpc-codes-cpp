#pragma once
#include <grib_property/grib_property.h>

namespace grib_coder {

class GridTypeProperty : public GribProperty {
public:
    std::string getString() override {
        return grid_type_;
    }

    bool decode(GribMessageHandler* container) override;

private:
    std::string grid_type_ = "MISSING";
};

} // namespace grib_coder
