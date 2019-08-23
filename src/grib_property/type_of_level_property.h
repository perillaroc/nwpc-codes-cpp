#pragma once
#include "grib_property.h"

namespace grib_coder {

class TypeOfLevelProperty: public GribProperty{
public:
    TypeOfLevelProperty() = default;
    ~TypeOfLevelProperty() = default;

    std::string getString() override;

    bool decode(GribPropertyContainer* container) override;

private:
    std::string type_of_level_ = "MISSING";
};

} // namespace grib_coder