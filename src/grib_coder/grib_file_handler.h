#pragma once

#include "grib_message_handler.h"
#include <grib_property/grib_table_database.h>

namespace grib_coder {
class GribFileHandler {
public:
    explicit GribFileHandler(std::FILE* file, bool header_only = false);

    ~GribFileHandler();

    std::unique_ptr<GribMessageHandler> next();

private:
    bool header_only_ = false;
    std::shared_ptr<GribTableDatabase> table_database_;

    std::FILE* file_ = nullptr;
};
} // namespace grib_coder
