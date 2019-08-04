#include "grib_section_7.h"
#include "number_convert.h"
#include "openjpeg_decoder.h"

#include <algorithm>
#include <cmath>

namespace GribCoder {
GribSection7::GribSection7():
	GribSection{7}
{
}

GribSection7::GribSection7(int section_length):
	GribSection{7, section_length}
{
}

GribSection7::~GribSection7()
{
}

bool GribSection7::parseFile(std::FILE* file)
{
	auto buffer_length = section_length_ - 5;
	std::vector<unsigned char> buffer(section_length_);
	auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
	if (read_count != buffer_length) {
		return false;
	}

	raw_value_bytes_.resize(buffer_length);
	std::copy(buffer.begin() + 5, buffer.end(), raw_value_bytes_.begin());

	return true;
}
bool GribSection7::decode(std::vector<std::shared_ptr<GribSection>> section_list)
{
	// find section 5
	std::shared_ptr<GribSection5> section_5;
	for (auto iter = section_list.rbegin(); iter != section_list.rend(); iter++) {
		auto s = *iter;
		if (s->section_number_ == 5) {
			section_5 = std::static_pointer_cast<GribSection5>(s);
			break;
		}
	}
	if (!section_5) {
		return false;
	}
	
	auto binary_scale_factor = section_5->binary_scale_factor_;
	auto decimal_scale_factor = section_5->decimal_scale_factor_;
	auto reference_value = section_5->reference_value_;

	auto data_count = section_5->number_of_values_;

	code_values_ = decodeJPEG2000Values(&raw_value_bytes_[0], raw_value_bytes_.size(), data_count);
	for (auto i = 0; i < data_count; i++) {
		code_values_[i] = (reference_value + code_values_[i] * std::pow(2, int16_t(binary_scale_factor))) / std::pow(10, int16_t(decimal_scale_factor));
	}
	return true;

}
void GribSection7::init()
{
}
} // GribCoder