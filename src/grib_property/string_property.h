#pragma once

#include <grib_property/grib_property.h>

namespace grib_coder {

class StringProperty : public GribProperty {
public:
    void setLength(const int length) {
        length_ = length;
    };

    void setString(const std::string& value) override;
    std::string getString() override;

    bool parse(std::vector<std::byte>::const_iterator& iterator, size_t count) override;

    void dump(const DumpConfig& dump_config) override;

private:
    std::string value_;
    int length_;
};

} // namespace grib_coder
