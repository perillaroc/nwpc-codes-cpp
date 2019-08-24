#pragma once
#include <grib_property/grib_property.h>

namespace grib_coder {
class PackingTypeProperty: public GribProperty {
public:
    PackingTypeProperty() = default;
    ~PackingTypeProperty() = default;

    std::string getString() override {
        return packing_type_;
    }

    bool decode(GribPropertyContainer* container) override;

private:
    std::string packing_type_ = "MISSING";
};
} // namespace grib_coder