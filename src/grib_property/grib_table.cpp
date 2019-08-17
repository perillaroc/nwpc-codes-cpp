#include "grib_table.h"

namespace grib_coder {

std::optional<GribTableRecord> GribTable::getRecord(int code)
{
    for (auto& i : records_) {
        if (i.code_ == code) {
            return i;
        }
    }
    return {};
}

} // namespace grib_coder


