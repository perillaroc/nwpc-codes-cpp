#pragma once
#include <grib_property/grib_component.h>

#include <string>
#include <vector>

namespace grib_coder {

class GribPropertyContainer;

class GribProperty: public GribComponent {
public:
    GribProperty() = default;

    virtual ~GribProperty() = default;

    virtual void setLong(long value);
    virtual long getLong();

    virtual void setDouble(double value);
    virtual double getDouble();

    virtual void setString(const std::string& value);
    virtual std::string getString();

    virtual void setDoubleArray(std::vector<double>& values);
    virtual std::vector<double> getDoubleArray();

    bool decode(GribPropertyContainer* container) override;
};

} // namespace grib_coder
