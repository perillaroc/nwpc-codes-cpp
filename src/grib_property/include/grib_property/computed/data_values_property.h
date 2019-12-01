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

    // decode, dump and encode

    bool decodeValues(GribMessageHandler* container);

    void dump(const DumpConfig& dump_config) override;

    bool encodeValues(GribMessageHandler* container);

    void pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) override;

private:
    // calculate bitsPerValue and referenceValue using binaryScaleFactor and decimalScaleFactor.
    // and check whether field is constant.
    void calculate(GribMessageHandler* container);

    // decode constant fields using referenceValue.
    bool decodeConstantFields(GribMessageHandler* container);

    bool decodeNormalFields(GribMessageHandler* container);

    // encode referenceValue for constant fields.
    bool encodeConstantFields(GribMessageHandler* container);

    bool encodeNormalFields(GribMessageHandler* container);

    std::vector<std::byte> raw_value_bytes_;
    std::vector<double> codes_values_;
    std::vector<double> values_;
    long data_count_ = -1;
};
} // namespace grib_coder
