#pragma once

#include <grib_property/grib_property.h>

namespace grib_coder {
class ComputedProperty: public GribProperty {
public:
    bool decode(GribMessageHandler* handler) override;

protected:
    virtual void encodeToComponents() = 0;

    // computed property needs message handler to write value back to components.
    GribMessageHandler* message_handler_ = nullptr;
};
} // namespace grib_coder