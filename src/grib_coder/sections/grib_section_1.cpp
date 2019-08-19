#include "grib_section_1.h"
#include "number_convert.h"

#include <vector>
#include <cassert>

namespace grib_coder {

GribSection1::GribSection1() :
	GribSection(1)
{
	init();
}

GribSection1::GribSection1(long section_length) :
	GribSection(1, section_length)
{
	assert(section_length == 21);
	init();
}

GribSection1::~GribSection1()
{
}

bool GribSection1::parseFile(std::FILE* file, bool header_only)
{
	auto buffer_length = section_length_ - 5;
	std::vector<unsigned char> buffer(buffer_length);
	auto read_count = std::fread(&buffer[0], 1, buffer_length, file);
	if (read_count != buffer_length) {
		return false;
	}

	centre_ = convert_bytes_to_uint16(&buffer[0], 2);
	sub_centre_ = convert_bytes_to_uint16(&buffer[2], 2);

	auto tables_version = convert_bytes_to_uint8(&buffer[4]);
	tables_version_.setLong(tables_version);

	auto local_tables_version = convert_bytes_to_uint8(&buffer[5]);
	local_tables_version_.setLong(local_tables_version);

	auto significance_of_reference_time = convert_bytes_to_uint8(&buffer[6]);
	significance_of_reference_time_.setLong(significance_of_reference_time);

	year_ = convert_bytes_to_uint16(&buffer[7], 2);
	month_ = convert_bytes_to_uint8(&buffer[9]);
	day_ = convert_bytes_to_uint8(&buffer[10]);
	hour_ = convert_bytes_to_uint8(&buffer[11]);
	minute_ = convert_bytes_to_uint8(&buffer[12]);
	second_ = convert_bytes_to_uint8(&buffer[13]);

	auto production_status_of_processed_data = convert_bytes_to_uint8(&buffer[14]);
	production_status_of_processed_data_.setLong(production_status_of_processed_data);

	auto type_of_processed_data = convert_bytes_to_uint8(&buffer[15]);
	type_of_processed_data_.setLong(type_of_processed_data);

	return true;
}

void GribSection1::init()
{
	tables_version_.setCodeTableId("1.0");
	local_tables_version_.setCodeTableId("1.1");
	significance_of_reference_time_.setCodeTableId("1.2");
	production_status_of_processed_data_.setCodeTableId("1.3");
	type_of_processed_data_.setCodeTableId("1.4");

	registerProperty("centre", &centre_);
	registerProperty("subCentre", &sub_centre_);
	registerProperty("tablesVersion", &tables_version_);
	registerProperty("localTablesVersion", &local_tables_version_);
	registerProperty("significanceOfReferenceTime", &significance_of_reference_time_);
	registerProperty("year", &year_);
	registerProperty("month", &month_);
	registerProperty("day", &day_);
	registerProperty("hour", &hour_);
	registerProperty("minute", &minute_);
	registerProperty("second", &second_);
	registerProperty("productionStatusOfProcessedData", &production_status_of_processed_data_);
	registerProperty("typeOfProcessedData", &type_of_processed_data_);
}

} // namespace grib_coder

