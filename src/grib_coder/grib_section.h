#pragma once

#include <cstdio>

namespace GribCoder {

class GribSection {
public:
	GribSection(int section_number);
	GribSection(int section_number, long section_length);
	virtual ~GribSection();

	void setSectionLength(long length);

	virtual bool parseFile(std::FILE* file) = 0;

public:
	int section_number_;
	long section_length_;
};

} // namespace GribCoder