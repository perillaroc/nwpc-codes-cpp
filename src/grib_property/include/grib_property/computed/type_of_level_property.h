#pragma once
#include <grib_property/computed/computed_property.h>

namespace grib_coder {

class TypeOfLevelProperty : public ComputedProperty {
public:
    std::string getString() override;

    bool decode(GribMessageHandler* handler) override;

private:
    void encodeToComponents() override;

    std::string type_of_level_ = "MISSING";
};

} // namespace grib_coder
