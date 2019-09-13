#pragma once

#include "grib_property.h"
#include "number_convert.h"

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
        const auto v = std::stod(value);
        setDouble(v);
    }

    std::string getString() override {
        return fmt::format("{}", value_);
    }

    bool parse(std::vector<std::byte>::const_iterator& iterator, size_t count = sizeof(T)) override {
        value_ = convert_bytes_to_number<T>(&(*iterator));
        return true;
    }

    constexpr static size_t getByteSize() {
        return sizeof(T);
    }

    void dump(const DumpConfig& dump_config) override {
        fmt::print("{}", value_);
    }

private:
    T value_;
};

} // namespace grib_coder
