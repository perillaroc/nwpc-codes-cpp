#pragma once
#include <grib_property/grib_property.h>

namespace grib_coder {

class DataDateProperty : public GribProperty {
public:
    DataDateProperty() = default;
    ~DataDateProperty() = default;

    void setLong(long value) override;
    long getLong() override;

    void setDouble(double value) override;
    double getDouble() override;

    void setString(const std::string& value) override;
    std::string getString() override;

    bool decode(GribMessageHandler* handler) override;

private:
    int year_;
    int month_;
    int day_;
};

} // namespace grib_coder
