#include "grib_section.h"

namespace GribCoder {

GribSection::GribSection(int section_number):
	section_number_{section_number},
	section_length_{0}
{

}

GribSection::GribSection(int section_number, long section_length):
	section_number_{section_number},
	section_length_{section_length}
{
}

GribSection::~GribSection()
{

}

void GribSection::setSectionLength(long length)
{
	section_length_ = length;
}

bool GribSection::decode(std::vector<std::shared_ptr<GribSection>> section_list)
{
	return true;
}

GribProperty* GribSection::getProperty(const std::string& name)
{
	for (auto const& i : property_map_) {
		if (i.first == name) {
			return i.second;
		}
	}
	return nullptr;
}

} // namespace GribCoder