#pragma once

#include <cstdio>
#include <memory>

#include "grib_message_handler.h"

namespace GribCoder {
class GribFileHandler {
public:
	explicit GribFileHandler(std::FILE *file);

	~GribFileHandler();

	std::unique_ptr<GribMessageHandler> next();

private:
	std::FILE* file_;
};
} // namespace GribCoder