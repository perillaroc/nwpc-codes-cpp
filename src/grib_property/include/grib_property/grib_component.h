#pragma once
#include <grib_property/grib_property_container.h>
#include <grib_property/config.h>

namespace grib_coder {

class GribMessageHandler;

class GribComponent : public GribPropertyContainer {
public:
    virtual long getByteCount() const = 0;

    // parse binary bytes read from grib message.
    virtual bool parse(std::vector<std::byte>::const_iterator& iterator);

    // decode component using previous sections, such as
    //  - computed properties
    //  - some code tables which rely on other code tables.
    virtual bool decode(GribMessageHandler* handler);

    // dump component to stdout
    virtual void dump(std::size_t start_octec, const DumpConfig& dump_config = DumpConfig{});

    // encode component using all sections.
    virtual bool encode(GribMessageHandler* handler);

    // pack component into bytes vector for output
    virtual void pack(std::back_insert_iterator<std::vector<std::byte>>& iterator);

};

} // namespace grib_coder
