#pragma once

#include <vector>
#include <cstddef>

namespace grib_coder {

std::vector<double> decode_jpeg2000_values(std::byte* buf, size_t raw_data_length, size_t data_count);

} // namespace grib_coder
