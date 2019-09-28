#pragma once


namespace grib_coder {

struct DumpConfig {
    enum class DumpStyle {
        WMO
    };

    DumpStyle style = DumpStyle::WMO;
    int octet_column_length = 10;
};


} // namespace grib_coder