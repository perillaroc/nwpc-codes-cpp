#include "grib_property/computed/grid_type_property.h"

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
> grid_type_list{
    {
        "regular_ll",
        {
            {"gridDefinitionTemplateNumber", 0},
            {"PLPresent", 0},
        }
    },
    {
        "reduced_ll",
        {
            {"gridDefinitionTemplateNumber", 0},
            {"PLPresent", 1},
        }
    },
};

bool GridTypeProperty::decode(GribMessageHandler* handler) {
    std::map<std::string, long> property_map;

    property_map["gridDefinitionTemplateNumber"] = handler->getLong("gridDefinitionTemplateNumber");

    const auto numberOfOctectsForNumberOfPoints = handler->getLong("numberOfOctectsForNumberOfPoints");
    if (numberOfOctectsForNumberOfPoints == 0) {
        property_map["PLPresent"] = 0;
    } else {
        property_map["PLPresent"] = 1;
    }

    for (const auto& item : grid_type_list) {
        const auto& type_name = std::get<0>(item);
        const auto& conditions = std::get<1>(item);
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
            grid_type_ = type_name;
            break;
        }
    }
    ComputedProperty::decode(handler);
    return true;
}

void GridTypeProperty::encodeToComponents() {
    throw std::runtime_error("GridTypeProperty is a read-only property.");
}

} // namespace grib_coder
