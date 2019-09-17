#pragma once
#include <grib_property/grib_property_container.h>


namespace grib_coder {

class GribMessageHandler;

struct DumpConfig {
    enum class DumpStyle {
        WMO
    };

    DumpStyle style = DumpStyle::WMO;
    int octet_column_length = 10;
};


class GribComponent : public GribPropertyContainer {
public:
    virtual long getByteCount() const = 0;

    // parse binary bytes read from grib message
    virtual bool parse(std::vector<std::byte>::const_iterator& iterator);

    // decode component using previous sections.
    virtual bool decode(GribMessageHandler* handler);

    // dump component
    virtual void dump(std::size_t start_octec, const DumpConfig& dump_config = DumpConfig{});
};

} // namespace grib_coder
