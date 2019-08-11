#include "grib_table.h"

namespace GribCoder {

std::optional<GribTableRecord> GribTable::getRecord(int code)
{
    for (auto& i : records_) {
        if (i.code_ == code) {
            return i;
        }
    }
    return {};
}

} // namespace GribCoder


