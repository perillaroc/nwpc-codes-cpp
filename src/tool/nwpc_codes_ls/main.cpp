#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdint>
#include <cmath>

#include <grib_file_handler.h>

#include <CLI11/CLI11.hpp>
#include <fmt/printf.h>

int listGribFile(const std::string file_path) {
	std::FILE* f = std::fopen(file_path.c_str(), "rb");

	//auto start_time = std::chrono::system_clock::now();

	GribCoder::GribFileHandler handler(f);
	int index = 1;
	auto message_handler = handler.next();

	while (message_handler) {
		auto edition = message_handler->getLong("editionNumber");
		
		// section 1
		auto centre = message_handler->getString("centre");

		//		dataDate
		auto year = message_handler->getLong("year");
		auto month = message_handler->getLong("month");
		auto day = message_handler->getLong("day");
		auto dataDate = year * 10000 + month * 100 + day;
		auto dataType = message_handler->getString("typeOfProcessedData");

		// section 3
		//		grid type

		// section 4
		//		typeOfLevel
		auto levelType = message_handler->getString("typeOfFirstFixedSurface");

		//		level
		auto levelNumberFactor = message_handler->getLong("scaleFactorOfFirstFixedSurface");
		auto levelNumberValue = message_handler->getLong("scaledValueOfFirstFixedSurface");
		double level = std::pow(10, levelNumberFactor) * levelNumberValue;

		//		stepRange
		auto forecastTime = message_handler->getLong("forecastTime");
		auto indicator_of_unit_of_time_range = message_handler->getLong("indicatorOfUnitOfTimeRange");
		auto stepRange = fmt::format("{forecastTime}", fmt::arg("forecastTime", forecastTime));

		// section 5
		//		packagingType

		auto category = message_handler->getString("parameterCategory");
		auto number = message_handler->getString("parameterNumber");
		fmt::print("{edition} | {centre} | {dataDate} | {dataType} | {category} | {number} | {stepRange} | {levelType} | {level} \n",
			fmt::arg("edition", edition),
			fmt::arg("centre", centre),
			fmt::arg("dataDate", dataDate),
			fmt::arg("dataType", dataType),
			fmt::arg("category", category),
			fmt::arg("number", number),
			fmt::arg("stepRange", stepRange),
			fmt::arg("levelType", levelType), 
			fmt::arg("level", level));
		index++;
		message_handler = handler.next();
	}

	//auto end_time = std::chrono::system_clock::now();
	//std::chrono::duration<double> duration = end_time - start_time;
	//std::cout << duration.count() << std::endl;

	std::fclose(f);

	return 0;
}


int main(int argc, char** argv) {
	CLI::App app{"nwpc_codes_ls"};

	std::string file_path;
	app.add_option("file_path", file_path);

	CLI11_PARSE(app, argc, argv);

	auto result = listGribFile(file_path);

    return result;
}