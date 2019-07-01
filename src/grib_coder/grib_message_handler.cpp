#include "grib_message_handler.h"

#include "grib_section_0.h"
#include <memory>

namespace GribCoder {

GribMessageHandler::GribMessageHandler()
{
}

GribMessageHandler::~GribMessageHandler()
{
}

bool GribMessageHandler::parseFile(std::FILE* file)
{
	auto section_0 = std::make_unique<GribSection0>();
	auto result = section_0->parseFile(file);
	return result;
}

}