#include "grib_message_handler.h"

#include "grib_section_0.h"
#include "grib_section_1.h"
#include "grib_section_3.h"
#include "grib_section_4.h"
#include "grib_section_5.h"
#include "grib_section_6.h"
#include "grib_section_7.h"
#include "grib_section_8.h"
#include "number_convert.h"
#include <memory>

namespace GribCoder {

GribMessageHandler::GribMessageHandler()
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
	auto section8_start_pos = start_pos + section_0->total_length_ - 4;

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

bool GribMessageHandler::parseNextSection(std::FILE* file)
{
	unsigned char buffer[5];
	auto result = std::fread(buffer, 1, 5, file);
	if (result != 5) {
		return false;
	}
	auto section_length = convertBytesToUint32(buffer, 4);
	auto section_number = convertBytesToUint8(&buffer[4]);

	std::shared_ptr<GribSection> section;

	if (section_number == 1) {
		section = std::make_shared<GribSection1>(section_length);
		result = section->parseFile(file);
	} 
	else if (section_number == 2) {
		throw std::exception();
		result = false;
	} 
	else if (section_number == 3) {
		section = std::make_shared<GribSection3>(section_length);
		result = section->parseFile(file);
	} 
	else if (section_number == 4) {
		section = std::make_shared<GribSection4>(section_length);
		result = section->parseFile(file);
	}
	else if (section_number == 5) {
		section = std::make_shared<GribSection5>(section_length);
		result = section->parseFile(file);
	}
	else if (section_number == 6) {
		section = std::make_shared<GribSection6>(section_length);
		result = section->parseFile(file);
	}
	else if (section_number == 7) {
		auto section_7 = std::make_shared<GribSection7>(section_length);
		section = section_7;
		result = section->parseFile(file);

		if (!result) {
			return false;
		}

		// find section 5
		std::shared_ptr<GribSection5> section_5;
		for (auto iter = section_list_.rbegin(); iter != section_list_.rend(); iter++) {
			auto s = *iter;
			if (s->section_number_ == 5) {
				section_5 = std::static_pointer_cast<GribSection5>(s);
				break;
			}
		}
		if (!section_5) {
			return false;
		}

		// decode values
		result = section_7->decodeValues(section_5);
	}

	if (!result) {
		return false;
	}
	section_list_.push_back(section);

	return true;
}

std::shared_ptr<GribSection> GribMessageHandler::getSection(int section_number, size_t begin_pos)
{
	std::shared_ptr<GribSection> section;
	for (auto iter = section_list_.begin() + begin_pos; iter != section_list_.end(); iter++) {
		auto s = *iter;
		if (s->section_number_ == section_number) {
			return s;
		}
	}
	return section;
}

} // namespace GribCoder