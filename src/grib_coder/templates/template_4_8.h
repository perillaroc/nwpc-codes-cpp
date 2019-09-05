#pragma once
#include "grib_template.h"

#include <grib_property/code_table_property.h>
#include <grib_property/number_property.h>
#include <grib_property/computed/level_property.h>
#include <grib_property/computed/type_of_level_property.h>
#include <grib_property/computed/step_range_property.h>

namespace grib_coder {

class Template_4_8 : public GribTemplate {
public:
    Template_4_8(int template_length);

    ~Template_4_8() = default;

    bool parse(std::vector<std::byte>& buffer) override;

    bool decode(GribPropertyContainer* container) override;

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
    NumberProperty<int8_t> scale_factor_of_first_fixed_surface_;
    NumberProperty<uint32_t> scaled_value_of_first_fixed_surface_;
    CodeTableProperty type_of_second_fixed_surface_;
    NumberProperty<int8_t> scale_factor_of_second_fixed_surface_;
    NumberProperty<uint32_t> scaled_value_of_second_fixed_surface_;

    NumberProperty<uint16_t> year_of_end_of_overall_time_interval_;
    NumberProperty<uint8_t> month_of_end_of_overall_time_interval_;
    NumberProperty<uint8_t> day_of_end_of_overall_time_interval_;
    NumberProperty<uint8_t> hour_of_end_of_overall_time_interval_;
    NumberProperty<uint8_t> minute_of_end_of_overall_time_interval_;
    NumberProperty<uint8_t> second_of_end_of_overall_time_interval_;
    NumberProperty<uint8_t> number_of_time_range_;
    NumberProperty<uint32_t> number_of_missing_statistical_process_;

    CodeTableProperty type_of_statistical_processing_;
    CodeTableProperty type_of_time_increment_;
    CodeTableProperty indicator_of_unit_for_time_range_;
    NumberProperty<uint32_t> length_of_time_range_;
    CodeTableProperty indicator_of_unit_for_time_increment_;
    NumberProperty<uint32_t> time_increment_;

    // computed
    LevelProperty level_;
    TypeOfLevelProperty type_of_level_;
    StepRangeProperty step_range_;
};

} // namespace grib_coder
