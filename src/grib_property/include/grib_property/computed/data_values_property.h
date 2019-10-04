#pragma once
#include <grib_property/grib_property.h>

namespace grib_coder {

class DataValuesProperty : public GribProperty {
public:
    DataValuesProperty() = default;
    ~DataValuesProperty() = default;

    long getByteCount() const {
        return raw_value_bytes_.size();
    }

    void setDoubleArray(std::vector<double>& values) override;
    std::vector<double> getDoubleArray() override;

    void setRawValues(std::vector<std::byte>&& raw_values);

    bool decodeValues(GribMessageHandler* container);

    void dump(const DumpConfig& dump_config) override;

    bool encodeValues(GribMessageHandler* container);

    void pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) override;

private:
    std::vector<std::byte> raw_value_bytes_;
    std::vector<double> code_values_;
    long data_count_ = -1;
};
} // namespace grib_coder
