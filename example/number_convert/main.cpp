#include <grib_property/number_convert.h>

int main() {
    const uint32_t value1 = 250000;
    auto value1_bytes = grib_coder::convert_number_to_bytes(value1);

    const int32_t value2 = -89875000;
    auto value2_bytes = grib_coder::convert_number_to_bytes(value2);


    return 0;
}

