#include "grib_section.h"

namespace GribCoder {

GribSection::GribSection(int section_number):
	section_number_{section_number_}
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

} // namespace GribCoder