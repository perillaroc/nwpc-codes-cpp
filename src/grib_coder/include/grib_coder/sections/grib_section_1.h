#pragma once

#include <grib_coder/grib_section.h>
#include <grib_property/code_table_property.h>
#include <grib_property/computed/data_date_property.h>
#include <grib_property/computed/data_time_property.h>

#include <cstdint>

namespace grib_coder {
class GribSection1 : public GribSection {
public:
    GribSection1();
    explicit GribSection1(long section_length);

    bool parseFile(std::FILE* file, bool header_only = false) override;

    bool decode(GribMessageHandler* container) override;

private:
    void init();

    NumberProperty<uint16_t> centre_;
    NumberProperty<uint16_t> sub_centre_;
    CodeTableProperty tables_version_;
    CodeTableProperty local_tables_version_;
    CodeTableProperty significance_of_reference_time_;
    NumberProperty<uint16_t> year_;
    NumberProperty<uint8_t> month_;
    NumberProperty<uint8_t> day_;
    NumberProperty<uint8_t> hour_;
    NumberProperty<uint8_t> minute_;
    NumberProperty<uint8_t> second_;
    CodeTableProperty production_status_of_processed_data_;
    CodeTableProperty type_of_processed_data_;

    DataDateProperty data_date_;
    DataTimeProperty data_time_;
};


} // namespace grib_coder
