#include "grib_property/computed/data_values_property.h"
#include <grib_coder/grib_message_handler.h>
#include "grib_property/computed/openjpeg_decoder.h"
#include <grib_property/computed/bit_map_values_property.h>

#include <fmt/format.h>

#include <algorithm>
#include <cmath>
#include <array>

namespace grib_coder {

void DataValuesProperty::setDoubleArray(std::vector<double>& values) {
    values_ = values;
}

std::vector<double> DataValuesProperty::getDoubleArray() {
    return values_;
}

void DataValuesProperty::setRawValues(std::vector<std::byte>&& raw_values) {
    raw_value_bytes_ = std::move(raw_values);
}

bool DataValuesProperty::decodeValues(GribMessageHandler* container) {
    // constant field has no data values
    if (raw_value_bytes_.empty()) {
        return decodeConstantFields(container);
    } else {
        return decodeNormalFields(container);
    }
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

    // currently we don't support bitmap.
    const auto bit_map_indicator = static_cast<uint8_t>(container->getLong("bitMapIndicator"));
    if (bit_map_indicator != std::numeric_limits<uint8_t>::max()) {
        throw std::runtime_error("bit map is not supported");
    }

    calculate(container);

    raw_value_bytes_.clear();

    if (data_count_ == 0) {
        return encodeConstantFields(container);
    } else {
        return encodeNormalFields(container);
    }
}

void DataValuesProperty::pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) {
    std::copy(std::begin(raw_value_bytes_), std::end(raw_value_bytes_), iterator);
}

// algorithm is from NCEP wgrib2 (grib2/g2clib-1.4.0/jpcpack.c)
void DataValuesProperty::calculate(GribMessageHandler* container) {
    const auto binary_scale_factor = static_cast<int>(container->getLong("binaryScaleFactor"));
    const auto decimal_scale_factor = static_cast<int>(container->getLong("decimalScaleFactor"));
    const auto old_reference_value = static_cast<float>(container->getDouble("referenceValue"));
    const auto old_bits_per_value = static_cast<int>(container->getLong("bitsPerValue"));

    const auto binary_scale = std::pow(2, -1 * binary_scale_factor);
    const auto decimal_scale = std::pow(10, decimal_scale_factor);

    auto bscale = binary_scale;
    if(binary_scale == 0) {
        bscale = 1;
    }

    const auto [min_value_iter, max_value_iter] = std::minmax_element(std::begin(values_), std::end(values_));

    const auto min_value = (*min_value_iter) * decimal_scale * bscale;
    const auto max_value = (*max_value_iter) * decimal_scale * bscale;
    const auto max_number_step = static_cast<long>(max_value-min_value);

    const auto log2 = 0.69314718; // ln(2.0)
    size_t bits_per_value = 0;

    auto reference_value = static_cast<float>(min_value);

    // if max_value and min_value are not equal, use data values.
    // or use empty data values for constant field.
    if(max_value!=min_value && max_number_step != 0) {
        const auto temp = std::log((static_cast<double>(max_number_step) + 1)) / log2;
        bits_per_value = std::ceil(temp);
    } else {
        data_count_ = 0;
        bits_per_value = 0;
        reference_value = *min_value_iter;
    }

    container->setDouble("referenceValue", reference_value);
    container->setLong("bitsPerValue", bits_per_value);
}

bool DataValuesProperty::decodeConstantFields(GribMessageHandler* container) {
    data_count_ = container->getLong("numberOfValues");
    const auto reference_value = static_cast<float>(container->getDouble("referenceValue"));

    values_.resize(data_count_);
    std::fill(std::begin(values_), std::end(values_), reference_value);

    return true;
}

bool DataValuesProperty::decodeNormalFields(GribMessageHandler* container) {
    const auto binary_scale_factor = int(container->getLong("binaryScaleFactor"));
    const auto decimal_scale_factor = int(container->getLong("decimalScaleFactor"));
    const auto reference_value = float(container->getDouble("referenceValue"));
    const auto bit_map_indicator = int(container->getLong("bitMapIndicator"));

    data_count_ = container->getLong("numberOfValues");
    codes_values_ = decode_jpeg2000_values(&raw_value_bytes_[0], raw_value_bytes_.size(), data_count_);
    std::transform(codes_values_.begin(), codes_values_.end(), codes_values_.begin(), [=](double v) {
        return (reference_value + v * std::pow(2, binary_scale_factor)) / std::pow(10, decimal_scale_factor);
    });

   
    if(bit_map_indicator == 255) {
        values_ = codes_values_;
    } else {
        const auto bitmap_property = container->getProperty("bitmap");
        const auto bitmap = dynamic_cast<const BitMapValuesProperty*>(bitmap_property);
        auto bitmap_values = bitmap->getValues();

        const auto missing_value = container->getMissingValue();

        const auto data_values_count = bitmap_values.size();
        values_.resize(data_values_count);

        auto data_iter = std::begin(values_);
        auto codes_iter = std::begin(codes_values_);
        for(auto bit: bitmap_values) {
            if(bit) {
                *data_iter = *codes_iter;
                ++codes_iter;
            } else {
                *data_iter = missing_value;
            }
            ++data_iter;
        }
    }

    return true;
}

bool DataValuesProperty::encodeConstantFields(GribMessageHandler* container) {
    const auto reference_value = values_[0];
    const auto bits_per_value = 0;
    container->setDouble("referenceValue", reference_value);
    container->setLong("bitsPerValue", bits_per_value);

    raw_value_bytes_.clear();
    data_count_ = 0;

    return true;
}

bool DataValuesProperty::encodeNormalFields(GribMessageHandler* container) {
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
    helper->values = &values_[0];
    helper->reference_value = reference_value;
    helper->divisor = std::pow(2, -1 * binary_scale_factor);
    helper->decimal = std::pow(10, decimal_scale_factor);

    std::vector<unsigned char> buffer(helper->buffer_size);
    helper->jpeg_buffer = &buffer[0];

    const auto result = encode_jpeg2000_values(helper.get());

    if (!result) {
        return false;
    }

    const auto encoded_length = helper->jpeg_length;

    raw_value_bytes_.clear();
    raw_value_bytes_.resize(encoded_length);
    std::transform(std::begin(buffer), std::begin(buffer) + encoded_length, std::begin(raw_value_bytes_),
        [](unsigned char c) -> std::byte { return static_cast<std::byte>(c); });

    return true;
}

} // namespace grib_coder
