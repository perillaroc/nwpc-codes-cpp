#pragma once

#include <vector>
#include <cstddef>
#include <grib_property/computed/openjpeg_helper.h>

namespace grib_coder {

std::vector<double> decode_jpeg2000_values(std::byte* buf, size_t raw_data_length, size_t data_count);

bool encode_jpeg2000_values(j2k_encode_helper* helper);

} // namespace grib_coder
