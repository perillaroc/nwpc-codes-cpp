#include "grib_property/computed/data_values_property.h"
#include <grib_coder/grib_message_handler.h>
#include "grib_property/computed/openjpeg_decoder.h"

#include <fmt/format.h>

#include <algorithm>
#include <cmath>
#include <array>

namespace grib_coder {

void DataValuesProperty::setDoubleArray(std::vector<double>& values) {
}

std::vector<double> DataValuesProperty::getDoubleArray() {
    return std::vector<double>();
}

void DataValuesProperty::setRawValues(std::vector<std::byte>&& raw_values) {
    raw_value_bytes_ = std::move(raw_values);
}

bool DataValuesProperty::decodeValues(GribMessageHandler* container) {
    if (raw_value_bytes_.empty()) {
        data_count_ = 0;
        return true;
    }

    const auto binary_scale_factor = int(container->getLong("binaryScaleFactor"));
    const auto decimal_scale_factor = int(container->getLong("decimalScaleFactor"));
    const auto reference_value = float(container->getDouble("referenceValue"));

    data_count_ = container->getLong("numberOfValues");
    code_values_ = decode_jpeg2000_values(&raw_value_bytes_[0], raw_value_bytes_.size(), data_count_);
    std::transform(code_values_.begin(), code_values_.end(), code_values_.begin(), [=](double v) {
        return (reference_value + v * std::pow(2, binary_scale_factor)) / std::pow(10, decimal_scale_factor);
    });
    //for (auto i = 0; i < data_count; i++) {
    //	code_values_[i] = (reference_value + code_values_[i] * std::pow(2, int16_t(binary_scale_factor))) / std::pow(10, int16_t(decimal_scale_factor));
    //}
    return true;
}

void DataValuesProperty::dump(const DumpConfig& dump_config) {
    if (data_count_ == -1) {
        fmt::print("not decode");
    } else if (data_count_ == 0) {
        fmt::print("empty");
    } else {
        fmt::print("({}, {})", data_count_, raw_value_bytes_.size());
    }
}

bool DataValuesProperty::encodeValues(GribMessageHandler* container) {
    if (code_values_.empty()) {
        data_count_ = 0;
        return true;
    }

    const auto bit_map_indicator = static_cast<uint8_t>(container->getLong("bitMapIndicator"));
    if(bit_map_indicator != std::numeric_limits<uint8_t>::max()) {
        throw std::runtime_error("bit map is not supported");
    }

    const auto ni = container->getLong("ni");
    const auto nj = container->getLong("nj");
    const auto binary_scale_factor = static_cast<int>(container->getLong("binaryScaleFactor"));
    const auto decimal_scale_factor = static_cast<int>(container->getLong("decimalScaleFactor"));
    const auto reference_value = static_cast<float>(container->getDouble("referenceValue"));
    const auto bits_per_value = static_cast<int>(container->getLong("bitsPerValue"));

    auto helper = std::make_unique<j2k_encode_helper>();

    const auto simple_packing_size = (((bits_per_value * data_count_) + 7) / 8) * sizeof(std::byte);
    helper->buffer_size = simple_packing_size + 10240;
    helper->width = ni;
    helper->height = nj;
    helper->bits_per_value = bits_per_value;

    // TODO: check target compression ratio
    helper->compression = 0;
    helper->no_values = data_count_;
    helper->values = &code_values_[0];
    helper->reference_value = reference_value;
    helper->divisor = std::pow(2, -1 * binary_scale_factor);
    helper->decimal = std::pow(10, decimal_scale_factor);

    std::vector<unsigned char> buffer(helper->buffer_size);
    helper->jpeg_buffer = &buffer[0];

    auto result = encode_jpeg2000_values(helper.get());

    if(!result) {
        return false;
    }

    const auto encoded_length = helper->jpeg_length;

    raw_value_bytes_.clear();
    raw_value_bytes_.resize(encoded_length);
    std::transform(std::begin(buffer), std::begin(buffer) + encoded_length, std::begin(raw_value_bytes_),
        [](unsigned char c) -> std::byte { return static_cast<std::byte>(c); });

    return true;
}

void DataValuesProperty::pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) {
    std::copy(std::begin(raw_value_bytes_), std::end(raw_value_bytes_), iterator);
}

} // namespace grib_coder
