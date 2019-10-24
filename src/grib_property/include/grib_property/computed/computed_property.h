#pragma once

#include <grib_property/grib_property.h>

namespace grib_coder {
class ComputedProperty: public GribProperty {
public:
    bool decode(GribMessageHandler* handler) override;

protected:
    // write value back to components, should be called by all available setters.
    virtual void encodeToComponents() = 0;

    // computed property needs message handler to write value back to components.
    GribMessageHandler* message_handler_ = nullptr;
};
} // namespace grib_coder