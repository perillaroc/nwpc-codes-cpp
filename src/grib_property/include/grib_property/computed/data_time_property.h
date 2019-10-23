#pragma once
#include <grib_property/computed/computed_property.h>

namespace grib_coder {

class DataTimeProperty : public ComputedProperty {
public:
    DataTimeProperty() = default;
    ~DataTimeProperty() = default;

    void setLong(long value) override;
    long getLong() override;

    void setDouble(double value) override;
    double getDouble() override;

    void setString(const std::string& value) override;
    std::string getString() override;

    bool decode(GribMessageHandler* container) override;

private:
    void encodeToComponents() override;

    int hour_ = -1;
    int minute_ = -1;
    int second_ = -1;

    GribMessageHandler* message_handler_ = nullptr;
};

} // namespace grib_coder
