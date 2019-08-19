#include "grib_message_handler.h"

#include "sections/grib_section_0.h"
#include "sections/grib_section_1.h"
#include "sections/grib_section_3.h"
#include "sections/grib_section_4.h"
#include "sections/grib_section_5.h"
#include "sections/grib_section_6.h"
#include "sections/grib_section_7.h"
#include "sections/grib_section_8.h"
#include "number_convert.h"

#include <memory>
#include <sstream>

namespace grib_coder {

GribMessageHandler::GribMessageHandler(std::shared_ptr<GribTableDatabase> db, bool header_only):
    GribPropertyContainer{},
	table_database_{ db },
	header_only_{ header_only }
{
}

GribMessageHandler::~GribMessageHandler()
{
}

bool GribMessageHandler::parseFile(std::FILE* file)
{
	auto start_pos = std::ftell(file);
	auto section_0 = std::make_shared<GribSection0>();
	auto result = section_0->parseFile(file);
	if (!result) {
		return false;
	}
	section_list_.push_back(section_0);

	auto current_pos = std::ftell(file);

	// check file end
    auto section8_start_pos = start_pos + section_0->getProperty("totalLength")->getLong() - 4;

	while (current_pos < section8_start_pos) {
		parseNextSection(file);
		current_pos = std::ftell(file);
	}

	if (current_pos != section8_start_pos) {
		return false;
	}

	auto section_8 = std::make_shared<GribSection8>();
	result = section_8->parseFile(file);

	if (!result) {
		return false;
	}
	
	section_list_.push_back(section_8);

	return true;
}

void GribMessageHandler::setLong(const std::string& key, long value)
{
	auto property = getProperty(key);
	if (property == nullptr) {
		throw std::exception("key is not found");
	}
	property->setLong(value);
}

long GribMessageHandler::getLong(const std::string& key)
{
	auto property = getProperty(key);
	if (property == nullptr) {
		throw std::exception("key is not found");
	}
	return property->getLong();
}

void GribMessageHandler::setDouble(const std::string& key, double value)
{
auto property = getProperty(key);
if (property == nullptr) {
	throw std::exception("key is not found");
}
property->setDouble(value);
}

double GribMessageHandler::getDouble(const std::string& key)
{
	auto property = getProperty(key);
	if (property == nullptr) {
		throw std::exception("key is not found");
	}
	return property->getDouble();
}

void GribMessageHandler::setString(const std::string& key, const std::string& value)
{
	auto property = getProperty(key);
	if (property == nullptr) {
		throw std::exception("key is not found");
	}
	auto code_table_property = dynamic_cast<CodeTableProperty*>(property);
	if (code_table_property) {
		// set grib2 table database
		auto table_version = getLong("tablesVersion");
		std::stringstream table_vsersion_stream;
		table_vsersion_stream << table_version;
		code_table_property->setTableDatabase(table_database_);
		code_table_property->setTablesVersion(table_vsersion_stream.str());
	}
	property->setString(value);
}

std::string GribMessageHandler::getString(const std::string& key)
{
	auto property = getProperty(key);
	if (property == nullptr) {
		throw std::exception("key is not found");
	}
	auto code_table_property = dynamic_cast<CodeTableProperty*>(property);
	if (code_table_property) {
		// set grib2 table database
		auto table_version = getLong("tablesVersion");
		std::stringstream table_vsersion_stream;
		table_vsersion_stream << table_version;
		code_table_property->setTableDatabase(table_database_);
		code_table_property->setTablesVersion(table_vsersion_stream.str());
	}
	return property->getString();
}


bool GribMessageHandler::parseNextSection(std::FILE* file)
{
	unsigned char buffer[5];
	auto result = std::fread(buffer, 1, 5, file);
	if (result != 5) {
		return false;
	}
	auto section_length = convert_bytes_to_uint32(buffer, 4);
	auto section_number = convert_bytes_to_uint8(&buffer[4]);

	std::shared_ptr<GribSection> section;

	if (section_number == 1) {
		section = std::make_shared<GribSection1>(section_length);
	}
	else if (section_number == 2) {
		throw std::exception();
	}
	else if (section_number == 3) {
		section = std::make_shared<GribSection3>(section_length);
	}
	else if (section_number == 4) {
		section = std::make_shared<GribSection4>(section_length);
	}
	else if (section_number == 5) {
		section = std::make_shared<GribSection5>(section_length);
	}
	else if (section_number == 6) {
		section = std::make_shared<GribSection6>(section_length);
	}
	else if (section_number == 7) {
		section = std::make_shared<GribSection7>(section_length);
	}

    // NOTE: where to put this line
    section_list_.push_back(section);

	auto flag = section->parseFile(file, header_only_);
	if (!flag) {
		return false;
	}

    flag = section->decode(this);
	if (!flag) {
		return false;
	}

	if (section_number == 7 && !header_only_) {
		auto section7 = std::static_pointer_cast<GribSection7>(section);
		if(!section7->decodeValues(this)) {
			return false;
		}
	}

	return true;
}

std::shared_ptr<GribSection> GribMessageHandler::getSection(int section_number, size_t begin_pos)
{
	std::shared_ptr<GribSection> section;
	for (auto iter = section_list_.begin() + begin_pos; iter != section_list_.end(); iter++) {
		auto s = *iter;
		if (s->getSectionLength() == section_number) {
			return s;
		}
	}
	return section;
}

GribProperty* GribMessageHandler::getProperty(const std::string& name) {
	for (auto &section : section_list_) {
		auto p = section->getProperty(name);
		if (p != nullptr) {
			return p;
		}
	}
	return nullptr;
}

} // namespace grib_coder