#pragma once

namespace GribCoder {

class GribSection {
public:
	GribSection(int section_number);
	virtual ~GribSection();

	void setSectionLength(long length);

protected:
	int section_number_;
	long section_length_;
};

} // namespace GribCoder