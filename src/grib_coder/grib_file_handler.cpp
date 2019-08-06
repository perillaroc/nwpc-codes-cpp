#include "grib_file_handler.h"

#include <iostream>

namespace GribCoder {

GribFileHandler::GribFileHandler(std::FILE* file):
	file_{file}
{
	table_database_ = std::make_shared<GribTableDatabase>();
}

GribFileHandler::~GribFileHandler()
{
}

std::unique_ptr<GribMessageHandler> GribFileHandler::next()
{
	auto message_handler = std::make_unique<GribMessageHandler>(table_database_);
	auto result = message_handler->parseFile(file_);
	return message_handler;
}

} // namespace GribCoder