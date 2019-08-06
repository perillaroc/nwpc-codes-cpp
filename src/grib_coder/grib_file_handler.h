#pragma once

#include <cstdio>
#include <memory>

#include "grib_message_handler.h"
#include <grib_property/grib_table_database.h>

namespace GribCoder {
class GribFileHandler {
public:
	explicit GribFileHandler(std::FILE *file);

	~GribFileHandler();

	std::unique_ptr<GribMessageHandler> next();

private:
	std::shared_ptr<GribTableDatabase> table_database_;

	std::FILE* file_;
};
} // namespace GribCoder