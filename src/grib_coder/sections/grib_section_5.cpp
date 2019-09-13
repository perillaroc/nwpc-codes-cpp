#include "grib_section_5.h"
#include <grib_property/property_component.h>

#include <gsl/span>

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
    std::vector<std::byte> buffer(section_length_);
    const auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
    if (static_cast<long>(read_count) != buffer_length) {
        return false;
    }

    auto iterator = std::cbegin(buffer) + 5;

    auto component_span = gsl::make_span(components_);
    auto sub_component_span = component_span.subspan(2);

    for (auto& component : sub_component_span) {
        component->parse(iterator);
    }

    return true;
}

bool GribSection5::decode(GribPropertyContainer* container)
{
    const auto result = packing_type_.decode(container);
    return result;
}

void GribSection5::init() {
    data_representation_template_number_.setOctetCount(2);

    std::vector<std::tuple<size_t, std::string, GribProperty*>> components{
        {4, "section5Length", &section_length_ },
        {1, "numberOfSection", &section_number_ },
        {4, "numberOfValues", &number_of_values_ },
        {1, "dataRepresentationTemplateNumber", &data_representation_template_number_ },

        {4, "referenceValue", &reference_value_ },
        {2, "binaryScaleFactor", &binary_scale_factor_ },
        {2, "decimalScaleFactor", &decimal_scale_factor_ },
        {1, "bitsPerValue", &bits_per_value_ },
        {1, "typeOfOriginalFieldValues", &type_of_original_field_values_ },
        {1, "typeOfCompressionUsed", &type_of_compression_used_ },
        {1, "targetCompressionRatio", &target_compression_ratio_ },
    };

    for (auto& item : components) {
        components_.push_back(std::make_unique<PropertyComponent>(
            std::get<0>(item), 
            std::get<1>(item),
            std::get<2>(item)));
        registerProperty(std::get<1>(item), std::get<2>(item));
    }

    std::vector<std::tuple<CodeTableProperty*, std::string>> tables_id{
        { &data_representation_template_number_, "5.0" },

        { &type_of_original_field_values_, "5.1" },
        { &type_of_compression_used_, "5.40" },
    };
    for (const auto& item : tables_id) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }


    std::vector<std::tuple<std::string, GribProperty*>> properties_name{
        { "packingType", &packing_type_ },
    };
    for (const auto& item : properties_name) {
        registerProperty(std::get<0>(item), std::get<1>(item));
    }
}
} // namespace grib_coder
