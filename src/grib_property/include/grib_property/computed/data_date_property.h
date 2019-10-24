#pragma once
#include <grib_property/computed/computed_property.h>

namespace grib_coder {
class DataDateProperty : public ComputedProperty {
public:
    void setLong(long value) override;
    long getLong() override;

    void setDouble(double value) override;
    double getDouble() override;

    void setString(const std::string& value) override;
    std::string getString() override;

    bool decode(GribMessageHandler* handler) override;

private:
    void encodeToComponents() override;

    int year_ = -1;
    int month_ = 0;
    int day_ = 0;
};

} // namespace grib_coder
