#include <grib_coder/grib_file_handler.h>
#include <grib_property/grib_table_database.h>

namespace grib_coder {

GribFileHandler::GribFileHandler(std::FILE* file, bool header_only):
    header_only_{header_only},
    file_{file} {
    table_database_ = std::make_shared<GribTableDatabase>();
}

std::unique_ptr<GribMessageHandler> GribFileHandler::next() {
    count_ += 1;
    auto message_handler = std::make_unique<GribMessageHandler>(table_database_, header_only_);
    const auto result = message_handler->parseFile(file_);
    if (result) {
        message_handler->setCount(count_);
        return message_handler;
    }

    return nullptr;
}

} // namespace grib_coder
