#pragma once

#include <vector>
#include <memory>
#include <cstdio>

namespace GribCoder {

class GribSection {
public:
	explicit GribSection(int section_number);
	GribSection(int section_number, long section_length);

	virtual ~GribSection();

	void setSectionLength(long length);

	virtual bool parseFile(std::FILE* file) = 0;

	virtual bool decode(std::vector<std::shared_ptr<GribSection>> section_list);

public:
	int section_number_;
	long section_length_;
};

} // namespace GribCoder