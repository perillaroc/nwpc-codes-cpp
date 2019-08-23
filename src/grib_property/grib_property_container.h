#pragma once
#include <string>
#include <vector>

namespace grib_coder {

class GribProperty;

class GribPropertyContainer {
public:
    GribPropertyContainer() = default;
    virtual ~GribPropertyContainer() = default;

    virtual void setLong(const std::string& key, long value);
    virtual long getLong(const std::string& key);

    virtual void setDouble(const std::string& key, double value);
    virtual double getDouble(const std::string& key);

    virtual void setString(const std::string& key, const std::string& value);
    virtual std::string getString(const std::string& key);

    virtual void setDoubleArray(const std::string& key, std::vector<double>& values);
    virtual std::vector<double> getDoubleArray(const std::string& key);
};

} // namespace grib_coder
