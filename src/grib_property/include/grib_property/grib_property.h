#pragma once
#include <grib_property/config.h>

#include <string>
#include <vector>


namespace grib_coder {

class GribMessageHandler;

class GribProperty {
public:
    GribProperty() = default;
    GribProperty(const GribProperty&) = default;
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

    virtual bool decode(GribMessageHandler* handler);

    virtual void dump(const DumpConfig& dump_config);
};

} // namespace grib_coder
