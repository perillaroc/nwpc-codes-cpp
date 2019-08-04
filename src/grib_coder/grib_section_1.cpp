#include "grib_section_1.h"
#include "number_convert.h"

#include <vector>
#include <cassert>

namespace GribCoder {

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

bool GribSection1::parseFile(std::FILE* file)
{
	auto buffer_length = section_length_ - 5;
	std::vector<unsigned char> buffer(buffer_length);
	auto read_count = std::fread(&buffer[0], 1, buffer_length, file);
	if (read_count != buffer_length) {
		return false;
	}

	centre_ = convertBytesToUint16(&buffer[0], 2);
	sub_centre_ = convertBytesToUint16(&buffer[2], 2);

	auto tables_version = convertBytesToUint8(&buffer[4]);
	tables_version_.setLong(tables_version);

	auto local_tables_version = convertBytesToUint8(&buffer[5]);
	local_tables_version_.setLong(local_tables_version);

	auto significance_of_reference_time = convertBytesToUint8(&buffer[6]);
	significance_of_reference_time_.setLong(significance_of_reference_time);

	year_ = convertBytesToUint16(&buffer[7], 2);
	month_ = convertBytesToUint8(&buffer[9]);
	day_ = convertBytesToUint8(&buffer[10]);
	hour_ = convertBytesToUint8(&buffer[11]);
	minute_ = convertBytesToUint8(&buffer[12]);
	second_ = convertBytesToUint8(&buffer[13]);

	auto production_status_of_processed_data = convertBytesToUint8(&buffer[14]);
	production_status_of_processed_data_.setLong(production_status_of_processed_data);

	auto type_of_processed_data = convertBytesToUint8(&buffer[15]);
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

	property_map_["centre"] = &centre_;
	property_map_["subCentre"] = &sub_centre_;
	property_map_["tablesVersion"] = &tables_version_;
	property_map_["localTablesVersion"] = &local_tables_version_;
	property_map_["significanceOfReferenceTime"] = &significance_of_reference_time_;
	property_map_["year"] = &year_;
	property_map_["month"] = &month_;
	property_map_["day"] = &day_;
	property_map_["hour"] = &hour_;
	property_map_["minute"] = &minute_;
	property_map_["second"] = &second_;
	property_map_["productionStatusOfProcessedData"] = &production_status_of_processed_data_;
	property_map_["typeOfProcessedData"] = &type_of_processed_data_;
}

} // namespace GribCoder

