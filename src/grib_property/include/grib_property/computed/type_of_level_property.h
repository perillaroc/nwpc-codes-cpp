#pragma once
#include <grib_property/grib_property.h>

namespace grib_coder {

class TypeOfLevelProperty : public GribProperty {
public:
    std::string getString() override;

    bool decode(GribMessageHandler* container) override;

private:
    std::string type_of_level_ = "MISSING";
};

} // namespace grib_coder
