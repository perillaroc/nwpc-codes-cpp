#include "grib_section_7.h"

#include <algorithm>

namespace grib_coder {
GribSection7::GribSection7():
	GribSection{7}
{
}

GribSection7::GribSection7(int section_length):
	GribSection{7, section_length}
{
}

bool GribSection7::parseFile(std::FILE* file, bool header_only)
{
	const auto buffer_length = section_length_ - 5;
	if (buffer_length == 0) {
		return true;
	}

    if(header_only) {
        std::fseek(file, buffer_length, SEEK_CUR);
    } else {
        std::vector<unsigned char> buffer(section_length_);
        const auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
        if (read_count != buffer_length) {
            return false;
        }

        std::vector<unsigned char> raw_value_bytes;
        raw_value_bytes.resize(buffer_length);
        std::copy(buffer.begin() + 5, buffer.end(), raw_value_bytes.begin());
        data_values_.setRawValues(std::move(raw_value_bytes));
    }

	return true;
}
bool GribSection7::decode(GribPropertyContainer* container)
{
	return true;
}

bool GribSection7::decodeValues(GribPropertyContainer* container)
{
    return data_values_.decodeValues(container);
}
void GribSection7::init()
{
    registerProperty("dataValues", &data_values_);
    registerProperty("values", &data_values_);
}
} // grib_coder