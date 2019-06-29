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
	char buffer[4];
	auto result = std::fread(buffer, 1, 4, file_);
	if (result != 4) {
		return std::unique_ptr<GribMessageHandler>();
	}
	std::cout << buffer << std::endl;
	return std::unique_ptr<GribMessageHandler>();
}

} // namespace GribCoder