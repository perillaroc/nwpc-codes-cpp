#pragma once
#include <grib_property/grib_component.h>

namespace grib_coder {

class GribPropertyContainer;

class GribProperty {
public:
    virtual ~GribProperty() = default;

    virtual void setLong(long value);
    virtual long getLong();

    virtual void setDouble(double value);
    virtual double getDouble();

    virtual void setString(const std::string& value);
    virtual std::string getString();

    virtual void setDoubleArray(std::vector<double>& values);
    virtual std::vector<double> getDoubleArray();

    virtual bool parse(std::vector<std::byte>::const_iterator& iterator, size_t count);

    virtual bool decode(GribPropertyContainer* container);

    virtual void dump(const DumpConfig& dump_config);
};

} // namespace grib_coder
