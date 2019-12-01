#include <grib_property/computed/bit_map_values_property.h>
#include <grib_coder/grib_message_handler.h>

namespace grib_coder {

void BitMapValuesProperty::setRawValues(std::vector<std::byte>&& raw_values)
{
    raw_bytes_ = std::move(raw_values);
}

bool BitMapValuesProperty::decodeValues(GribMessageHandler* container) {
    auto count = container->getLong("numberOfDataPoints");
    values_.resize(raw_bytes_.size() * 8);
    auto iter = std::begin(values_);
    for(auto byte: raw_bytes_) {
        for(auto i=0; i<8; i++) {
            *iter = static_cast<bool>(byte >> (7 - std::to_integer<uint8_t>(byte)));
            ++iter;
        }
    }
    values_.erase(std::begin(values_) + count, std::end(values_));
    return true;
}

void BitMapValuesProperty::dump(const DumpConfig& dump_config) {
}

void BitMapValuesProperty::pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) {
}

} // namespace grib_coder