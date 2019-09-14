#pragma once
#include <grib_property/grib_property.h>

namespace grib_coder {

class GridTypeProperty : public GribProperty {
public:
    GridTypeProperty() = default;
    ~GridTypeProperty() = default;

    std::string getString() override {
        return grid_type_;
    }

    bool decode(GribPropertyContainer* container) override;

private:
    std::string grid_type_;
};

} // namespace grib_coder
