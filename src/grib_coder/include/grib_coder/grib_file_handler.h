#pragma once
#include <grib_coder/grib_message_handler.h>

namespace grib_coder {
class GribTableDatabase;

class GribFileHandler {
public:
    explicit GribFileHandler(std::FILE* file, bool header_only = false);

    ~GribFileHandler() = default;

    // parse the next grib message, return nullptr if no message is available.
    std::unique_ptr<GribMessageHandler> next();

private:
    // if false, data values in section 7 will not be decoded.
    bool header_only_ = false;

    // all grib messages use the same table database.
    std::shared_ptr<GribTableDatabase> table_database_;

    // handler of an opened grib file for reading, users should open and close it themselves.
    std::FILE* file_ = nullptr;

    // current grib message count, used for message handler
    uint64_t count_ = 0;
};
} // namespace grib_coder
