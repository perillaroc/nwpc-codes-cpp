#pragma once
#include <grib_property/grib_property.h>

namespace grib_coder {

class BitMapValuesProperty : public GribProperty {
public:
    BitMapValuesProperty() = default;
    
    void setRawValues(std::vector<std::byte>&& raw_values);

    std::vector<bool> getValues() const {
        return values_;
    }

    // decode, dump, encode and pack

    bool decodeValues(GribMessageHandler* container);

    void dump(const DumpConfig& dump_config) override;

    void pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) override;

private:
    std::vector<std::byte> raw_bytes_;
    std::vector<bool> values_;
};

} // namespace grib_coder