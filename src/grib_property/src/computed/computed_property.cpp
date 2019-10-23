#include <grib_property/computed/computed_property.h>

namespace grib_coder {

bool ComputedProperty::decode(GribMessageHandler* handler) {
    message_handler_ = handler;
    return true;
}
} // namespace