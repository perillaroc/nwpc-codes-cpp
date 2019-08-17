#pragma once

#include <string>
#include <vector>

namespace grib_coder {

class GribProperty {
public:
    GribProperty() = default;

    virtual ~GribProperty() = default;

    virtual void setLong(long value) = 0;
    virtual long getLong() = 0;

    virtual void setDouble(double value) = 0;
    virtual double getDouble() = 0;

    virtual void setString(const std::string &value) = 0;
    virtual std::string getString() = 0;

    virtual void setDoubleArray(std::vector<double> &values) = 0;
    virtual std::vector<double> getDoubleArray() = 0;
};

} // namespace grib_coder

