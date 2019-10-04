#pragma once

#include "grib_coder/grib_section.h"
#include <grib_property/computed/data_values_property.h>

namespace grib_coder {

class GribSection7 : public GribSection {
public:
    GribSection7();
    explicit GribSection7(int section_length);
    ~GribSection7() = default;

    bool parseFile(std::FILE* file, bool header_only = false) override;

    bool decode(GribMessageHandler* container) override;

    bool decodeValues(GribMessageHandler* container);

    bool encodeValues(GribMessageHandler* container);

    bool encode(GribMessageHandler* handler) override;

    void pack(std::back_insert_iterator<std::vector<std::byte>>& iterator) override;

    // TODO: just for test
    void updateSectionLength() override;

private:
    void init();

    DataValuesProperty data_values_;
};

} // namespace grib_coder
