#include "data_values_property.h"
#include <grib_property/grib_property_container.h>
#include "openjpeg_decoder.h"

#include <algorithm>
#include <cmath>

namespace grib_coder {

DataValuesProperty::DataValuesProperty() {
}

DataValuesProperty::~DataValuesProperty() {
}

void DataValuesProperty::setDoubleArray(std::vector<double>& values) {
}

std::vector<double> DataValuesProperty::getDoubleArray() {
    return std::vector<double>();
}

void DataValuesProperty::setRawValues(std::vector<unsigned char>&& raw_values) {
    raw_value_bytes_ = std::move(raw_values);
}

bool DataValuesProperty::decodeValues(GribPropertyContainer* container) {
    if (raw_value_bytes_.empty()) {
        return true;
    }

    const auto binary_scale_factor = int(container->getLong("binaryScaleFactor"));
    const auto decimal_scale_factor = int(container->getLong("decimalScaleFactor"));
    const auto reference_value = float(container->getDouble("referenceValue"));

    const auto data_count = container->getLong("numberOfValues");
    code_values_ = decode_jpeg2000_values(&raw_value_bytes_[0], raw_value_bytes_.size(), data_count);
    std::transform(code_values_.begin(), code_values_.end(), code_values_.begin(), [=](double v) {
        return (reference_value + v * std::pow(2, binary_scale_factor)) / std::pow(10, decimal_scale_factor);
    });
    //for (auto i = 0; i < data_count; i++) {
    //	code_values_[i] = (reference_value + code_values_[i] * std::pow(2, int16_t(binary_scale_factor))) / std::pow(10, int16_t(decimal_scale_factor));
    //}
    return true;
}

} // namespace grib_coder
