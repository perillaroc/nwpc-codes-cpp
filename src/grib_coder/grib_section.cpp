#include "grib_section.h"
#include <iterator>

namespace grib_coder {

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

void GribSection::setSectionLength(long length)
{
	section_length_.setLong(length);
}

long GribSection::getSectionLength() const
{
    return static_cast<long>(section_length_);
}

int GribSection::getSectionNumber() const
{
    return static_cast<int>(section_number_);
}

bool GribSection::decode(GribPropertyContainer* container)
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

void GribSection::registerProperty(const std::string& name, GribProperty* property)
{
    property_map_[name] = property;
}

GribProperty* get_property_from_section_list(
    const std::string& name, std::vector<std::shared_ptr<GribSection>>& section_list)
{
    for(auto iter=std::rbegin(section_list);iter != std::rend(section_list); ++iter) {
        auto property = (*iter)->getProperty(name);
        if (property) {
            return property;
        }
    }
    return nullptr;
}

} // namespace grib_coder