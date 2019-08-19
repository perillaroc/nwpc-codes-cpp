#include "grib_section_8.h"


namespace grib_coder {
GribSection8::GribSection8():
	GribSection{8}
{
    init();
}

bool GribSection8::parseFile(std::FILE* file, bool header_only)
{
	char buffer[4];
	auto result = std::fread(buffer, 1, 4, file);
	if (result != 4) {
		return false;
	}
	const std::string end_string{ buffer, 4 };
	if (end_string == "7777") {
		return true;
	} else {
		return false;
	}
}
void GribSection8::init()
{
}
}