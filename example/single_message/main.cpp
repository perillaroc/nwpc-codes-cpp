#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cmath>

#include <grib_file_handler.h>

int main() {
    std::string grib_file_path{"./dist/data/t.850hpa.000.grb2"};	
	
	std::FILE* f = std::fopen(grib_file_path.c_str(), "rb");

	GribCoder::GribFileHandler handler(f);

	auto message_handler = handler.next();

	std::fclose(f);
	
    return 0;
}