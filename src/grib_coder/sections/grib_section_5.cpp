#include "grib_section_5.h"
#include "number_convert.h"

#include <vector>
#include <cassert>

namespace grib_coder {
GribSection5::GribSection5():
    GribSection{5} {
    init();
}

GribSection5::GribSection5(int section_length):
    GribSection{5, section_length} {
    assert(section_length == 23);
    init();
}

bool GribSection5::parseFile(std::FILE* file, bool header_only) {
    auto buffer_length = section_length_ - 5;
    std::vector<unsigned char> buffer(section_length_);
    auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
    if (read_count != buffer_length) {
        return false;
    }

    number_of_values_ = convert_bytes_to_uint32(&buffer[5], 4);
    auto data_representation_template_number = convert_bytes_to_uint16(&buffer[9], 2);
    data_representation_template_number_.setLong(data_representation_template_number);
    reference_value_ = convert_bytes_to_float(&buffer[11], 4);
    binary_scale_factor_ = convert_bytes_to_int16(&buffer[15], 2);
    decimal_scale_factor_ = convert_bytes_to_int16(&buffer[17], 2);
    bits_per_value_ = convert_bytes_to_uint8(&buffer[19]);
    auto type_of_original_field_values = convert_bytes_to_uint8(&buffer[20]);
    type_of_original_field_values_.setLong(type_of_original_field_values);
    auto type_of_compression_used = convert_bytes_to_uint8(&buffer[21]);
    type_of_compression_used_.setLong(type_of_compression_used);
    target_compression_ratio_ = convert_bytes_to_uint8(&buffer[22]);

    return true;
}

bool GribSection5::decode(GribPropertyContainer* container)
{
    auto result = packing_type_.decode(container);
    return result;
}

void GribSection5::init() {
    data_representation_template_number_.setCodeTableId("5.0");
    data_representation_template_number_.setOctetCount(2);

    type_of_original_field_values_.setCodeTableId("5.1");
    type_of_compression_used_.setCodeTableId("5.40");

    registerProperty("numberOfValues", &number_of_values_);
    registerProperty("dataRepresentationTemplateNumber", &data_representation_template_number_);

    registerProperty("referenceValue", &reference_value_);
    registerProperty("binaryScaleFactor", &binary_scale_factor_);
    registerProperty("decimalScaleFactor", &decimal_scale_factor_);
    registerProperty("bitsPerValue", &bits_per_value_);
    registerProperty("typeOfOriginalFieldValues", &type_of_original_field_values_);
    registerProperty("typeOfCompressionUsed", &type_of_compression_used_);
    registerProperty("targetCompressionRatio", &target_compression_ratio_);

    registerProperty("packingType", &packing_type_);
}
} // namespace grib_coder
