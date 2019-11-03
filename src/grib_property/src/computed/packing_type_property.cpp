#include "grib_property/computed/packing_type_property.h"
#include <grib_coder/grib_message_handler.h>

#include <map>

namespace grib_coder {

const std::vector<
    std::tuple<
        std::string,
        std::vector<
            std::tuple<
                std::string,
                int
            >
        >
    >
> packing_type_list{
    {
        "grid_simple",
        {
            {"dataRepresentationTemplateNumber", 1},
        }
    },
    {
        "grid_jpeg",
        {
            {"dataRepresentationTemplateNumber", 40000},
        }
    },
    {
        "grid_jpeg",
        {
            {"dataRepresentationTemplateNumber", 40},
        }
    },
};

bool PackingTypeProperty::decode(GribMessageHandler* handler) {
    std::map<std::string, long> property_map;

    property_map["dataRepresentationTemplateNumber"] = handler->getLong("dataRepresentationTemplateNumber");

    for (const auto& item : packing_type_list) {
        auto type_name = std::get<0>(item);
        auto conditions = std::get<1>(item);
        auto flag = true;
        for (const auto& condition : conditions) {
            const auto& property_name = std::get<0>(condition);
            const auto& property_value = std::get<1>(condition);
            if (property_map[property_name] != property_value) {
                flag = false;
                break;
            }
        }
        if (flag) {
            packing_type_ = type_name;
            break;
        }
    }
    ComputedProperty::decode(handler);
    return true;
}

void PackingTypeProperty::encodeToComponents() {
    throw std::runtime_error("PackingTypeProperty is a read-only property.");
}

} // namespace grib_coder
