#include "grib_file_handler.h"

#include <iostream>

namespace GribCoder {

GribFileHandler::GribFileHandler(std::FILE* file):
	file_{file}
{
}

GribFileHandler::~GribFileHandler()
{
}

std::unique_ptr<GribMessageHandler> GribFileHandler::next()
{
	auto message_handler = std::make_unique<GribMessageHandler>();
	auto result = message_handler->parseFile(file_);
	return message_handler;
}

} // namespace GribCoder