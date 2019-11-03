#pragma once
#include <grib_property/computed/computed_property.h>

namespace grib_coder {

class GridTypeProperty : public ComputedProperty {
public:
    std::string getString() override {
        return grid_type_;
    }

    bool decode(GribMessageHandler* handler) override;

private:
    void encodeToComponents() override;

    std::string grid_type_ = "MISSING";
};

} // namespace grib_coder
