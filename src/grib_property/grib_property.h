#pragma once

#include <string>

namespace grib_coder {

class GribProperty {
public:
    GribProperty();

    virtual ~GribProperty();

    virtual void setLong(long value) = 0;
    virtual long getLong() = 0;

    virtual void setDouble(double value) = 0;
    virtual double getDouble() = 0;

    virtual void setString(const std::string &value) = 0;
    virtual std::string getString() = 0;

protected:

};

} // namespace grib_coder

