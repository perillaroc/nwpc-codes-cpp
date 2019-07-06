#pragma once

#include <cstdio>
#include <vector>
#include <memory>

#include "grib_section.h"

namespace GribCoder {

class GribMessageHandler {
public:
	GribMessageHandler();
	~GribMessageHandler();

	bool parseFile(std::FILE* file);

private:
	bool parseNextSection(std::FILE* file);

	std::vector < std::shared_ptr<GribSection>> section_list_;
};

} // namespace GribCoder

