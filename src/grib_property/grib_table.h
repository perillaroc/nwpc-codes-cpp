#pragma once
#include <string>
#include <vector>
#include <optional>

namespace grib_coder {

const std::string record_unknown_value = "unknown";

class GribTableRecord {
public:
    bool isValid() const {
        return code_ != -1;
    }

    int code_ = -1;
    std::string abbreviation_ = record_unknown_value;
    std::string title_ = record_unknown_value;
    std::string units_ = record_unknown_value;
};

class GribTable {
public:
    std::optional<GribTableRecord> getRecord(int code);

    std::vector<GribTableRecord> records_;
};


} // namespace grib_coder
