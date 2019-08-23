#pragma once
#include "grib_property.h"

namespace grib_coder {

class DataTimeProperty : public GribProperty {
public:
    DataTimeProperty() = default;
    ~DataTimeProperty() = default;

    void setLong(long value) override;
    long getLong() override;

    void setDouble(double value) override;
    double getDouble() override;

    void setString(const std::string& value) override;
    std::string getString() override;

    bool decode(GribPropertyContainer* container) override;

private:
    int hour_ = -1;
    int minute_ = -1;
    int second_ = -1;
};

} // namespace grib_coder
