#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cmath>

#include <grib_file_handler.h>

int main() {
	std::string grib_file_path{"./dist/data/gmf.gra.2019080700003.grb2"};
	
	std::FILE* f = std::fopen(grib_file_path.c_str(), "rb");

	GribCoder::GribFileHandler handler(f);
	int index = 1;
	std::cout << "Parsing message " << index << "..." << std::endl;
	auto message_handler = handler.next();

	while (message_handler) {
		auto category = message_handler->getString("parameterCategory");
		auto number = message_handler->getString("parameterNumber");
		auto levelType = message_handler->getString("typeOfFirstFixedSurface");
		auto levelNumberFactor = message_handler->getLong("scaleFactorOfFirstFixedSurface");
		auto levelNumberValue = message_handler->getLong("scaledValueOfFirstFixedSurface");
		std::cout << category << " | " << number << " | " << levelType << " | " << levelNumberFactor << " | " << levelNumberValue << std::endl;

		index++;
		std::cout << "Parsing message " << index << "..." << std::endl;
		message_handler = handler.next();
	}

	std::fclose(f);
	
    return 0;
}