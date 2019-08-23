#pragma once

#include "grib_property.h"
#include <fmt/format.h>

namespace grib_coder {

template <class T>
class NumberProperty : public GribProperty {
public:
    NumberProperty() : GribProperty{}, value_{} {
    }

    NumberProperty(T value) : GribProperty{}, value_{value} {
    }

    ~NumberProperty() = default;

    operator T() const {
        return value_;
    }

    T value() const {
        return value_;
    }

    void setLong(long value) override {
        value_ = static_cast<T>(value);
    }

    long getLong() override {
        return static_cast<long>(value_);
    }

    void setDouble(double value) override {
        value_ = static_cast<T>(value);
    }

    double getDouble() override {
        return static_cast<double>(value_);
    }

    void setString(const std::string& value) override {
        auto v = std::stod(value);
        setDouble(v);
    }

    std::string getString() override {
        return fmt::format("{}", value_);
    }

private:
    T value_;
};

} // namespace grib_coder
