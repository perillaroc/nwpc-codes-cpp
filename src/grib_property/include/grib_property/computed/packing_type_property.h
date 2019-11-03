#pragma once
#include <grib_property/computed/computed_property.h>

namespace grib_coder {
class PackingTypeProperty : public ComputedProperty {
public:
    std::string getString() override {
        return packing_type_;
    }

    bool decode(GribMessageHandler* handler) override;

private:
    void encodeToComponents() override;

    std::string packing_type_ = "MISSING";
};
} // namespace grib_coder
