#pragma once
#include "grib_template.h"

#include <grib_property/code_table_property.h>
#include <grib_property/number_property.h>

namespace grib_coder {

class Template_4_0 : public GribTemplate {
public:
    Template_4_0(int template_length);

    ~Template_4_0();

    bool parse(std::vector<unsigned char>& buffer) override;

    bool decode(std::vector<std::shared_ptr<GribSection>> section_list) override;

    void registerProperty(std::shared_ptr<GribSection> section) override;

private:
    void init();

    CodeTableProperty parameter_category_;
    CodeTableProperty parameter_number_;
    CodeTableProperty type_of_generating_process_;
    NumberProperty<uint8_t> background_process_;
    NumberProperty<uint8_t> generating_process_identifier_;
    NumberProperty<uint16_t> hours_after_data_cutoff_;
    NumberProperty<uint8_t> minutes_after_data_cutoff_;
    CodeTableProperty indicator_of_unit_of_time_range_;
    NumberProperty<int32_t> forecast_time_;
    CodeTableProperty type_of_first_fixed_surface_;
    NumberProperty<uint8_t> scale_factor_of_first_fixed_surface_;
    NumberProperty<uint32_t> scaled_value_of_first_fixed_surface_;
    CodeTableProperty type_of_second_fixed_surface_;
    NumberProperty<uint8_t> scale_factor_of_second_fixed_surface_;
    NumberProperty<uint32_t> scaled_value_of_second_fixed_surface_;
};

} // namespace grib_coder