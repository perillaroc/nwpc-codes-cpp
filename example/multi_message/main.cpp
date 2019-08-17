#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include <grib_file_handler.h>

int main() {
	const std::string grib_file_path{"./dist/data/gmf.gra.2019080700003.grb2"};
	
	auto f = std::fopen(grib_file_path.c_str(), "rb");

	const auto start_time = std::chrono::system_clock::now();
	grib_coder::GribFileHandler handler(f);
	auto index = 1;
	std::cout << "Parsing message " << index << "..." << std::endl;
	auto message_handler = handler.next();

	while (message_handler) {
		const auto category = message_handler->getString("parameterCategory");
		const auto number = message_handler->getString("parameterNumber");
		const auto levelType = message_handler->getString("typeOfFirstFixedSurface");
		const auto levelNumberFactor = message_handler->getLong("scaleFactorOfFirstFixedSurface");
		const auto levelNumberValue = message_handler->getLong("scaledValueOfFirstFixedSurface");
		std::cout << category << " | " << number << " | " << levelType << " | " << levelNumberFactor << " | " << levelNumberValue << std::endl;

		index++;
		std::cout << "Parsing message " << index << "..." << std::endl;
		message_handler = handler.next();
	}

	const auto end_time = std::chrono::system_clock::now();
	const std::chrono::duration<double> duration = end_time - start_time;
	std::cout << duration.count() << std::endl;

	std::fclose(f);
	
    return 0;
}