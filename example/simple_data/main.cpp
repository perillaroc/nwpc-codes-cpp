#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cmath>

#include "openjpeg_decoder.h"

float convertToFloat(uint32_t v) {
	return *(reinterpret_cast<float*>(&v));
}


int main() {
    std::string grib_file_path{"D:/windroc/project/2019/grib2/nwpc-codes-cpp/dist/data/t.850hpa.000.grb2"};

    auto start_pos = 0xB1;
    auto raw_data_length = 0x98998 - 0xB1 + 1;
	auto data_count = 1036800;

	int binary_scale_factor = 0x0;
	int decimal_scale_factor = 0x2;
	float reference_value = convertToFloat(0x46B1298E);

    auto buf = new unsigned char[raw_data_length];

	//std::FILE* f = std::fopen(grib_file_path.c_str(), "rb");
	//std::fseek(f, start_pos, SEEK_SET);
	//std::fread(buf, 1, raw_data_length, f);
	//std::fclose(f);

    std::ifstream f(grib_file_path, std::ios::binary);
	f.seekg(start_pos);
	f.read(reinterpret_cast<char*>(buf), raw_data_length);
	f.close();

	auto val = decodeJPEG2000Values(buf, raw_data_length, data_count);

    delete[] buf;

	if (val.size() == 0) {
		std::cerr << "value decode has error." << std::endl;
		return 1;
	}
	
	for (auto i = 0; i < data_count; i++) {
		val[i] = (reference_value + val[i] * std::pow(2, binary_scale_factor)) / std::pow(10, decimal_scale_factor);
	}

	
    return 0;
}