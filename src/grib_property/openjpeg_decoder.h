#pragma once

#include <vector>

namespace grib_coder {

std::vector<double> decodeJPEG2000Values(unsigned char *buf, size_t raw_data_length, size_t data_count);

} // namespace grib_coder