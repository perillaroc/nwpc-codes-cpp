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
    const auto buffer_length = section_length_ - 5;
    std::vector<unsigned char> buffer(section_length_);
    const auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
    if (read_count != buffer_length) {
        return false;
    }

    number_of_values_ = convert_bytes_to_uint32(&buffer[5], 4);
    const auto data_representation_template_number = convert_bytes_to_uint16(&buffer[9], 2);
    data_representation_template_number_.setLong(data_representation_template_number);
    reference_value_ = convert_bytes_to_float(&buffer[11], 4);
    binary_scale_factor_ = convert_bytes_to_int16(&buffer[15], 2);
    decimal_scale_factor_ = convert_bytes_to_int16(&buffer[17], 2);
    bits_per_value_ = convert_bytes_to_uint8(&buffer[19]);
    const auto type_of_original_field_values = convert_bytes_to_uint8(&buffer[20]);
    type_of_original_field_values_.setLong(type_of_original_field_values);
    const auto type_of_compression_used = convert_bytes_to_uint8(&buffer[21]);
    type_of_compression_used_.setLong(type_of_compression_used);
    target_compression_ratio_ = convert_bytes_to_uint8(&buffer[22]);

    return true;
}

bool GribSection5::decode(GribPropertyContainer* container)
{
    const auto result = packing_type_.decode(container);
    return result;
}

void GribSection5::init() {
    std::vector<std::tuple<CodeTableProperty*, std::string>> tables_id{
        { &data_representation_template_number_, "5.0" },

        { &type_of_original_field_values_, "5.1" },
        { &type_of_compression_used_, "5.40" },
    };
    for (const auto& item : tables_id) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }

    data_representation_template_number_.setOctetCount(2);

    std::vector<std::tuple<std::string, GribProperty*>> properties_name{
        { "numberOfValues", &number_of_values_ },
        { "dataRepresentationTemplateNumber", &data_representation_template_number_ },

        { "referenceValue", &reference_value_ },
        { "binaryScaleFactor", &binary_scale_factor_ },
        { "decimalScaleFactor", &decimal_scale_factor_ },
        { "bitsPerValue", &bits_per_value_ },
        { "typeOfOriginalFieldValues", &type_of_original_field_values_ },
        { "typeOfCompressionUsed", &type_of_compression_used_ },
        { "targetCompressionRatio", &target_compression_ratio_ },

        { "packingType", &packing_type_ },
    };
    for (const auto& item : properties_name) {
        registerProperty(std::get<0>(item), std::get<1>(item));
    }
}
} // namespace grib_coder
