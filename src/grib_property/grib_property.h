#pragma once

#include <string>
#include <vector>

namespace grib_coder {

class GribProperty {
public:
    GribProperty() = default;

    virtual ~GribProperty() = default;

    virtual void setLong(long value);
    virtual long getLong();

    virtual void setDouble(double value);
    virtual double getDouble();

    virtual void setString(const std::string &value);
    virtual std::string getString();

    virtual void setDoubleArray(std::vector<double> &values);
    virtual std::vector<double> getDoubleArray();
};

} // namespace grib_coder

