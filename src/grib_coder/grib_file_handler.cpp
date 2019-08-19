#include "grib_file_handler.h"

namespace grib_coder {

GribFileHandler::GribFileHandler(std::FILE* file, bool header_only):
	header_only_{header_only},
	file_{file}
{
	table_database_ = std::make_shared<GribTableDatabase>();
}

GribFileHandler::~GribFileHandler()
{
}

std::unique_ptr<GribMessageHandler> GribFileHandler::next()
{
	auto message_handler = std::make_unique<GribMessageHandler>(table_database_, header_only_);
	auto result = message_handler->parseFile(file_);
	if (result) {
		return message_handler;
	}

	return nullptr;
}

} // namespace grib_coder