#pragma once
#include <grib_property/grib_component.h>

namespace grib_coder {

class PropertyComponent final: public GribComponent {
public:
    PropertyComponent(int byte_count, GribProperty* property);

    void setByteCount(const int byte_count);

    GribProperty* getProperty();

    // parse binary bytes read from grib message
    bool parse(std::vector<std::byte>::const_iterator& iterator) override;

    bool decode(GribPropertyContainer* container) override;

private:
    int byte_count_ = 1;
    GribProperty* property_ = nullptr;
};


} // namespace grib_coder