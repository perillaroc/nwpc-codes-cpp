#include "grib_section_4.h"
#include "grib_section_0.h"
#include "number_convert.h"

#include <vector>
#include <sstream>
#include <cassert>

namespace GribCoder {
GribSection4::GribSection4():
	GribSection{4}
{
	init();
}

GribSection4::GribSection4(int section_length_):
	GribSection{4, section_length_}
{
	assert(section_length_ == 34);
	init();
}

GribSection4::~GribSection4()
{

}

bool GribSection4::parseFile(std::FILE* file)
{
	auto buffer_length = section_length_ - 5;
	std::vector<unsigned char> buffer(section_length_);
	auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
	if (read_count != buffer_length) {
		return false;
	}

	nv_ = convertBytesToUint16(&buffer[5], 2);
	auto product_definition_template_number = convertBytesToUint16(&buffer[7], 2);
	assert(product_definition_template_number == 0);
	product_definition_template_number_.setLong(product_definition_template_number);

	auto parameter_category = convertBytesToUint8(&buffer[9]);
	parameter_category_.setLong(parameter_category);
	auto parameter_number = convertBytesToUint8(&buffer[10]);
	parameter_number_.setLong(parameter_number);
	auto type_of_generating_process = convertBytesToUint8(&buffer[11]);
	type_of_generating_process_.setLong(type_of_generating_process);
	background_process_ = convertBytesToUint8(&buffer[12]);
	generating_process_identifier_ = convertBytesToUint8(&buffer[13]);
	hours_after_data_cutoff_ = convertBytesToUint16(&buffer[14], 2);
	minutes_after_data_cutoff_ = convertBytesToUint8(&buffer[16]);
	auto indicator_of_unit_of_time_range = convertBytesToUint8(&buffer[17]);
	indicator_of_unit_of_time_range_.setLong(indicator_of_unit_of_time_range);
	forecast_time_ = convertBytesToInt32(&buffer[18], 4);
	auto type_of_first_fixed_surface = convertBytesToUint8(&buffer[22]);
	type_of_first_fixed_surface_.setLong(type_of_first_fixed_surface);
	scale_factor_of_first_fixed_surface_ = convertBytesToInt8(&buffer[23]);
	scaled_value_of_first_fixed_surface_ = convertBytesToUint32(&buffer[24], 4);
	auto type_of_second_fixed_surface = convertBytesToUint8(&buffer[28]);
	type_of_second_fixed_surface_.setLong(type_of_second_fixed_surface);
	scale_factor_of_second_fixed_surface_ = convertBytesToInt8(&buffer[29]);
	scaled_value_of_second_fixed_surface_ = convertBytesToUint32(&buffer[30]);

	return true;
}

bool GribSection4::decode(std::vector<std::shared_ptr<GribSection>> section_list)
{
	std::shared_ptr<GribSection0> section_0;
	for (auto iter = section_list.rbegin(); iter != section_list.rend(); iter++) {
		auto s = *iter;
		if (s->section_number_ == 0) {
			section_0 = std::static_pointer_cast<GribSection0>(s);
			break;
		}
	}
	if (!section_0) {
		return false;
	}

	std::ostringstream discipline_stream;
	auto discipline = section_0->discipline_.getLong();
	discipline_stream << "4.1." << discipline;
	std::string category_table_id = discipline_stream.str();
	parameter_category_.setCodeTableId(category_table_id);

	std::ostringstream number_stream;
	number_stream << "4.2." << discipline << "." << parameter_category_.getLong();
	std::string number_table_id = number_stream.str();
	parameter_number_.setCodeTableId(number_table_id);

	return true;
}

void GribSection4::init()
{
	product_definition_template_number_.setOctetCount(2);
	product_definition_template_number_.setCodeTableId("4.0");

	type_of_generating_process_.setCodeTableId("4.3");
	indicator_of_unit_of_time_range_.setCodeTableId("4.4");
	type_of_first_fixed_surface_.setCodeTableId("4.5");
	type_of_second_fixed_surface_.setCodeTableId("4.5");

	property_map_["nv"] = &nv_;
	property_map_["productDefinitionTemplateNumber"] = &product_definition_template_number_;

	property_map_["parameterCategory"] = &parameter_category_;
	property_map_["parameterNumber"] = &parameter_number_;
	property_map_["typeOfGenratingProcess"] = &type_of_generating_process_;
	property_map_["backgroundProcess"] = &background_process_;
	property_map_["generatingProcessIdentifier"] = &generating_process_identifier_;
	property_map_["hoursAfterDataCutoff"] = &hours_after_data_cutoff_;
	property_map_["minutesAfterDataCutoff"] = &minutes_after_data_cutoff_;
	property_map_["indicatorOfUnitOfTimeRange"] = &indicator_of_unit_of_time_range_;
	property_map_["forecastTime"] = &forecast_time_;
	property_map_["typeOfFirstFixedSurface"] = &type_of_first_fixed_surface_;
	property_map_["scaleFactorOfFirstFixedSurface"] = &scale_factor_of_first_fixed_surface_;
	property_map_["scaledValueOfFirstFixedSurface"] = &scaled_value_of_first_fixed_surface_;
	property_map_["typeOfSecondFixedSurfact"] = &type_of_second_fixed_surface_;
	property_map_["scaleFactorOfSecondFixedSurface"] = &scale_factor_of_second_fixed_surface_;
	property_map_["scaledValueOfSecondFixedSurface"] = &scaled_value_of_second_fixed_surface_;
}

} // namespace GribCoder