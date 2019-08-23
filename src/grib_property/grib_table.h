#pragma once
#include <string>
#include <vector>
#include <optional>

namespace grib_coder {

const std::string RecordUnknownValue = "unknown";

class GribTableRecord {
public:
    bool isValid() const {
        return code_ != -1;
    }

    int code_ = -1;
    std::string abbreviation_ = RecordUnknownValue;
    std::string title_ = RecordUnknownValue;
    std::string units_ = RecordUnknownValue;
};

class GribTable {
public:
    std::optional<GribTableRecord> getRecord(int code);

    std::vector<GribTableRecord> records_;
};


} // namespace grib_coder
