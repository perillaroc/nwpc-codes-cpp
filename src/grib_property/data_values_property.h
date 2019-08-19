#pragma once
#include "grib_property.h"

namespace grib_coder {

class DataValuesProperty: public GribProperty {
public:
    DataValuesProperty();
    ~DataValuesProperty();

    void setDoubleArray(std::vector<double>& values) override;
    std::vector<double> getDoubleArray() override;

    void setRawValues(std::vector<unsigned char>&& raw_values);

    bool decodeValues(GribPropertyContainer *container);

private:
    std::vector<unsigned char> raw_value_bytes_;
    std::vector<double> code_values_;


};
} // namespace grib_coder