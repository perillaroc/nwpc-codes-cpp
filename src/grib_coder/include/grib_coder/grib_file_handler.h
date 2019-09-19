#pragma once
#include <grib_coder/grib_message_handler.h>

namespace grib_coder {
class GribTableDatabase;

class GribFileHandler {
public:
    explicit GribFileHandler(std::FILE* file, bool header_only = false);

    ~GribFileHandler() = default;

    std::unique_ptr<GribMessageHandler> next();

private:
    bool header_only_ = false;
    std::shared_ptr<GribTableDatabase> table_database_;

    std::FILE* file_ = nullptr;
    uint64_t count_ = 0;
};
} // namespace grib_coder
